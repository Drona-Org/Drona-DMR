#include "timer.p"

event ATTACH_DRIVER: machine;
event READY;
event SELFTEST_FAILED;

type MpuReport = (status:int,ax:int,ay:int,az:int,temp:int,gx:int,gy:int,gz:int);
type Point = (x:int,y:int,z:int);


machine MPU6000Client
{
    start state Init 
    {
        ignore SELFTEST_FAILED;
    }

}

fun MPU6000WhoAmI() : int {
    return 104; // 0x68;
}

fun RegisterWhoAmI() : int {
    return 117; // 0x75;
}

// #define MPUREG_GYRO_CONFIG		0x1B
fun MPUREG_GYRO_CONFIG() : int {
    return 27; // 0x1B;
}

// #define MPUREG_ACCEL_CONFIG		0x1C
fun MPUREG_ACCEL_CONFIG() : int {
    return 28; // 0x1C;
}

fun RegisterAccelSelfTest() : int {
    return 28; // 0x1C;
}

fun GyroSelfTestConfig() : int {
    return 224; // 0xE0;
		  //BITS_FS_250DPS |
		  //BITS_GYRO_ST_X |
		  //BITS_GYRO_ST_Y |
		  //BITS_GYRO_ST_Z;
}

//#define MPUREG_TRIM1			0x0D
fun MPUREG_TRIM1() : int {
    return 13; // 0x0D;
}

//#define MPUREG_TRIM2			0x0E
fun MPUREG_TRIM2() : int {
    return 14; // 0x0E;
}

//#define MPUREG_TRIM3			0x0F
fun MPUREG_TRIM3() : int {
    return 15; // 0x0F;
}

//#define MPUREG_TRIM4			0x10
fun MPUREG_TRIM4() : int {
    return 16; // 0x10;
}

// #define BITS_FS_250DPS			0x00
fun BITS_FS_250DPS() : int {
    return 0;
}

// #define BITS_FS_2000DPS			0x00
fun BITS_FS_2000DPS() : int {
    return 24; // 0x18;
}

fun SpiTimeout() : int {
    return 100;
}



// This is a model of the MPU-6000 sensor from InvenSense.
// http://store.invensense.com/datasheets/invensense/MPU-6050_DataSheet_V3%204.pdf
machine MPU6000Sensor
{
    var gyroEnabled: int;
    var gyroSpeed: int;
    var accelEnabled: int;
    var accelSpeed: int;
    var dmpEnabled: int; // digital motion processor.
    var driver: machine;

    start state Init 
    {
        entry {
            gyroEnabled = 0;  
            accelEnabled = 0;
            gyroSpeed = 0;
            accelSpeed = 0;
            dmpEnabled = 0;
        }
        on ATTACH_DRIVER goto Ready;
    }

    state Ready
    {
        entry  (payload:machine) {
            driver = payload;
        }
        
    }

}

machine MPU6000Driver
{
    var sensor: machine;
    var timer: machine;
    var client: machine;
    
    model fun ReadRegister(reg:int) : int
    {
        return 0;
    }

    model fun WriteRegister(reg:int, value:int)
    {
    }

    model fun GetMeasurement() : MpuReport
    {   
        return (status=0,ax=0,ay=0,az=0,temp=0,gx=0,gy=0,gz=0);
    }


    model fun CheckGyroLimits(baseline:Point, selfTest:Point, trim:Point) : bool
    {
        return $;
    }
    
    model fun CheckAccelLimits(baseline:Point, selfTest:Point, trim:Point, trimAccel:int) : bool
    {
        return $;
    }

    fun SelfTest() : bool
    {
        var i: int;
        var gyroSelfTest: Point;
        var gyroBaseline: Point;
        var accelSelfTest: Point;
        var accelBaseline: Point;
        var trim: Point;
        var accelTrim: int;
        var report: MpuReport;
        var result: any;
        var success: bool;
        var total: int;
        var prime: int;
        var savedGyroConfig: int;
        var savedAccelConfig: int;

        total = 10;
        prime = 10; // read 10 values to warm up the sensor.

        savedGyroConfig = ReadRegister(MPUREG_GYRO_CONFIG());
        savedAccelConfig = ReadRegister(MPUREG_ACCEL_CONFIG());

        trim.x = ReadRegister(MPUREG_TRIM1());
        trim.y = ReadRegister(MPUREG_TRIM2());
        trim.z = ReadRegister(MPUREG_TRIM3());
        accelTrim = ReadRegister(MPUREG_TRIM4());

        // todo: check WHO_AM_I
        i = ReadRegister(RegisterWhoAmI());

        if (i != MPU6000WhoAmI())
        {
            return false;
        }
        
        WriteRegister(MPUREG_GYRO_CONFIG(), BITS_FS_250DPS());
                
        while (i < total + prime)
        {
            report = GetMeasurement();
            if (i >= prime)
            {
                gyroBaseline.x  = report.gx + gyroBaseline.x;
                gyroBaseline.y  = report.gy + gyroBaseline.y;
                gyroBaseline.z  = report.gz + gyroBaseline.z;
                accelBaseline.x = report.ax + accelBaseline.x;
                accelBaseline.y = report.ay + accelBaseline.y;
                accelBaseline.z = report.az + accelBaseline.z;
            }
            i = i + 1;
        }

        i = 0;

        WriteRegister(MPUREG_GYRO_CONFIG(), GyroSelfTestConfig());

        // get 10 good values
        while (i < total)
        {
            report = GetMeasurement();
            gyroSelfTest.x  = report.gx + gyroSelfTest.x;
            gyroSelfTest.y  = report.gy + gyroSelfTest.y;
            gyroSelfTest.z  = report.gz + gyroSelfTest.z;
            accelSelfTest.x = report.ax + accelSelfTest.x;
            accelSelfTest.y = report.ay + accelSelfTest.y;
            accelSelfTest.z = report.az + accelSelfTest.z;
            i = i + 1;
        }

        gyroSelfTest.x = gyroSelfTest.x / total;
        gyroSelfTest.y = gyroSelfTest.y / total;
        gyroSelfTest.z = gyroSelfTest.z / total;
        gyroBaseline.x = gyroBaseline.x / total;
        gyroBaseline.y = gyroBaseline.y / total;
        gyroBaseline.z = gyroBaseline.z / total;
        
        accelSelfTest.x = accelSelfTest.x / total;
        accelSelfTest.y = accelSelfTest.y / total;
        accelSelfTest.z = accelSelfTest.z / total;
        accelBaseline.x = accelBaseline.x / total;
        accelBaseline.y = accelBaseline.y / total;
        accelBaseline.z = accelBaseline.z / total;
        
	    WriteRegister(MPUREG_GYRO_CONFIG(), savedGyroConfig);
	    WriteRegister(MPUREG_ACCEL_CONFIG(), savedAccelConfig);

        success = CheckGyroLimits(gyroBaseline, gyroSelfTest, trim);
        if (!success)
        {
            return false;
        }
        
        success = CheckAccelLimits(accelBaseline, accelSelfTest, trim, accelTrim);
        if (!success)
        {
            return false;
        }

        return success;
    }

    start state Init 
    {
        entry (payload:(machine, machine))
        {
            var x : bool;  
            timer = CreateTimer(this);
            sensor = payload.0;
            client = payload.1;
            send sensor, ATTACH_DRIVER, this;
            x = SelfTest();
            if (x)
            {
                raise READY;
            }
            else 
            {
                send client, SELFTEST_FAILED;
            }
        }
        on READY goto Ready;

    }

    state Ready
    {
        entry
        {
            // read sensor values and publish them to the uORB at 1000 Hz
            send client, READY;
        }
    }
}

machine TestDriver
{
    var driver: machine;
    var sensor: machine;
    var client: machine;

    start state Init 
    {
        entry 
        {
            client = new MPU6000Client();
            sensor = new MPU6000Sensor();
            driver = new MPU6000Driver((sensor, client));
        }
    }
}