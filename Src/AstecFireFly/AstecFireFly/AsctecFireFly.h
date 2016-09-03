#ifndef __ASCTEC_H
#define __ASCTEC_H

#define PD_IMURAWDATA 0x01
#define PD_LLSTATUS 0x02
#define PD_IMUCALCDATA 0x03
#define PD_HLSTATUS 0x04
#define PD_DEBUGDATA 0x05
#define PD_CTRLOUT 0x11
#define PD_FLIGHTPARAMS 0x12
#define PD_CTRLCOMMANDS 0x13
#define PD_CTRLINTERNAL 0x14
#define PD_RCDATA 0x15
#define PD_CTRLSTATUS 0x16
#define PD_CTRLINPUT 0x17
#define PD_CTRLFALCON 0x18
#define PD_WAYPOINT 0x20
#define PD_CURRENTWAY 0x21
#define PD_NMEADATA 0x22
#define PD_GPSDATA 0x23
#define PD_SINGLEWAYPOINT 0x24
#define PD_GOTOCOMMAND 0x25
#define PD_LAUNCHCOMMAND 0x26
#define PD_LANDCOMMAND 0x27
#define PD_HOMECOMMAND 0x28
#define PD_GPSDATAADVANCED 0x29


/*
* Available data structures
*/
#pragma pack(push, 1)
typedef struct _POLL_REQUEST
{
	const char string[4];	// always initialize with ">*>p"
	unsigned short packets;
}POLL_REQUEST;

typedef struct _POLL_HEADER
{
	char startstring[3];
	unsigned short length;
	unsigned char packet_desc;
} POLL_HEADER;

typedef struct _POLL_FOOTER
{
	unsigned short crc16;
	char stopstring[3];
} POLL_FOOTER;

typedef struct _WP_COMMAND
{
	const char string[4];	// always initialize with ">*>w"
	const char cmd;			// s, g, l, e or h
} WP_COMMAND;

typedef struct _WP_HEADER
{
	char startstring[2];	// should be ">a"
	unsigned char packet_desc;
} WP_HEADER;

typedef struct _WP_FOOTER
{
	char stopstring[2];	// should be "a<"
} WP_FOOTER;

typedef struct _LL_STATUS
{
	//battery voltages in mV
	short battery_voltage_1;
	short battery_voltage_2;
	//don't care
	short status;
	//Controller cycles per second (should be ?1000)
	short cpu_load;
	//don't care
	char compass_enabled;
	char chksum_error;
	char flying;
	char motors_on;
	short flightMode;
	//Time motors are turning
	short up_time;
} LL_STATUS;

typedef struct _IMU_RAWDATA
{
	//pressure sensor 24-bit value, not scaled but bias free
	int pressure;
	//16-bit gyro readings; 32768 = 2.5V
	short gyro_x;
	short gyro_y;
	short gyro_z;
	//10-bit magnetic field sensor readings
	short mag_x;
	short mag_y;
	short mag_z;
	//16-bit accelerometer readings
	short acc_x;
	short acc_y;
	short acc_z;
	//16-bit temperature measurement using yaw-gyro internal sensor
	unsigned short temp_gyro;
	//16-bit temperature measurement using ADC internal sensor
	unsigned int temp_ADC;
} IMU_RAWDATA;

typedef struct _IMU_CALCDATA
{
	//angles derived by integration of gyro_outputs, drift compensated by data & !fusion; -90000..+90000 pitch(nick) and roll, 0..360000 yaw; 1000 = 1 & ! degree
	int angle_nick;
	int angle_roll;
	int angle_yaw;
	//angular velocities, raw values 16 bit but bias free
	int angvel_nick;
	int angvel_roll;
	int angvel_yaw;
	//acc-sensor outputs, calibrated: -10000..+10000 = -1g..+1g
	short acc_x_calib;
	short acc_y_calib;
	short acc_z_calib;
	//horizontal / vertical accelerations: -10000..+10000 = -1g..+1g
	short acc_x;
	short acc_y;
	short acc_z;
	//reference angles derived by accelerations only: -90000..+90000; 1000 = 1 & !degree
	int acc_angle_nick;
	int acc_angle_roll;
	//total acceleration measured (10000 = 1g)
	int acc_absolute_value;
	//magnetic field sensors output, offset free and scaled; units not & !determined, as only the direction of the field vector is taken into & ! account
	int Hx;
	int Hy;
	int Hz;
	//compass reading: angle reference for angle_yaw: 0..360000; 1000 = 1 degree
	int mag_heading;
	//pseudo speed measurements: integrated accelerations, pulled towards zero; & !units unknown; used for short-term position stabilization
	int speed_x;
	int speed_y;
	int speed_z;
	//height in mm (after data fusion)
	int height;
	//diff. height in mm/s (after data fusion)
	int dheight;
	//diff. height measured by the pressure sensor mm/s
	int dheight_reference;
	//height measured by the pressure sensor mm
	int height_reference;
} IMU_CALCDATA;

typedef struct _GPS_DATA
{
	//latitude/longitude in deg * 10^7
	int latitude;
	int longitude;
	//GPS height in mm
	int height;
	//speed in x (E/W) and y(N/S) in mm/s
	int speed_x;
	int speed_y;
	//GPS heading in deg * 1000
	int heading;
	//accuracy estimates in mm and mm/s
	unsigned int horizontal_accuracy;
	unsigned int vertical_accuracy;
	unsigned int speed_accuracy;
	//number of satellite vehicles used in NAV solution
	unsigned int numSV;
	// GPS status information; 0x03 = valid GPS fix
	int status;
} GPS_DATA;

typedef struct _GPS_DATA_ADVANCED
{
	//latitude/longitude in deg * 10^7
	int latitude;
	int longitude;
	//GPS height in mm
	int height;
	//speed in x (E/W) and y(N/S) in mm/s
	int speed_x;
	int speed_y;
	//GPS heading in deg * 1000
	int heading;
	//accuracy estimates in mm and mm/s
	unsigned int horizontal_accuracy;
	unsigned int vertical_accuracy;
	unsigned int speed_accuracy;
	//number of satellite vehicles used in NAV solution
	unsigned int numSV;
	//GPS status information; 0x03 = valid GPS fix
	int status;
	//coordinates of current origin in deg * 10^7
	int latitude_best_estimate;
	int longitude_best_estimate;
	//velocities in X (E/W) and Y (N/S) after data fusion
	int speed_x_best_estimate;
	int speed_y_best_estimate;
} GPS_DATA_ADVANCED;

typedef struct _RC_DATA
{
	//channels as read from R/C receiver
	unsigned short channels_in8;
	//channels bias free, remapped and scaled to 0..4095
	unsigned short channels_out8;
	//Indicator for valid R/C receiption
	unsigned char lock;
} RC_DATA;

typedef struct _CONTROLLER_OUTPUT
{
	//attitude controller outputs; 0..200 = -100 ..+100%
	int nick;
	int roll;
	int yaw;
	//current thrust (height controller output); 0..200 = 0..100%
	int thrust;
} CONTROLLER_OUTPUT;

typedef struct _CTRL_INPUT
{

	short pitch; //pitch input: -2047..+2047 (0=neutral)
	short roll; //roll input: -2047..+2047 (0=neutral)
	short yaw; //(=R/C Stick input) -2047..+2047 (0=neutral)
	short thrust; //collective: 0..4095 = 0..100%
	short ctrl; /*control byte:
				bit 0: pitch control enabled
				bit 1: roll control enabled
				bit 2: yaw control enabled
				bit 3: thrust control enabled
				bit 4: height control enabled
				bit 5: GPS position control enabled
				*/
	short chksum;
} CTRL_INPUT;

typedef struct _WAYPOINT
{
	//always set to 1
	unsigned char wp_number;

	//don't care
	unsigned char dummy_1;
	unsigned short dummy_2;

	//see WPPROP defines below
	unsigned char properties;

	//max. speed to travel to waypoint in % (default 100)
	unsigned char max_speed;

	//time to stay at a waypoint (XYZ) in 1/100th s
	unsigned short time;

	//position accuracy to consider a waypoint reached in mm (default: 2500 (= 2.5 m))
	unsigned short pos_acc;

	//chksum = 0xAAAA + wp.yaw + wp.height + wp.time + wp.X + wp.Y + wp.max_speed +	wp.pos_acc + wp.properties + wp.wp_number;
	short chksum;

	//waypoint coordinates in mm	// longitude in abs coords
	int X;
	//waypoint coordinates in mm	// latitude in abs coords
	int Y;

	//Desired heading at waypoint
	int yaw;

	//height over 0 reference in mm
	int height;
} WAYPOINT;

typedef struct _WAYPOINT_CMD{
	WP_COMMAND prefix; //always initialize with ">*>ws" (Nachshon's comment)
	WAYPOINT wp; 
}WAYPOINT_CMD;

#define WPPROP_ABSCOORDS		0x01 //if set waypoint is interpreted as absolute coordinates, else relative coords
#define WPPROP_HEIGHTENABLED	0x02 //set new height at waypoint
#define WPPROP_YAWENABLED 		0x04 //set new yaw-angle at waypoint (not yet implemented)
#define WPPROP_AUTOMATICGOTO 	0x10 //if set, vehicle will not wait for a goto command, but goto this waypoint directly
#define WPPROP_CAM_TRIGGER 		0x20 //if set, photo camera is triggered when waypoint is reached and time to stay is 80% u


typedef struct _CURRENT_WAY
{
	// the only relevant values are navigation_status and distance_to_wp
	unsigned char dummy1;
	unsigned char properties;
	//total number of waypoints uploaded to the vehicle
	unsigned short nr_of_wp;
	//the waypoint to be reached next
	unsigned char current_wp;
	//memory location of the current wp (0 .. nr_of_wp)
	unsigned char current_wp_memlocation;
	//status of waypoint engine: 0: STANDBY, 1: Executing way from Flash, 2: PC controlled waypoint navigation
	unsigned char status;
	unsigned char dummy2;
	//see WP_NAVSTAT_... defines
	unsigned short navigation_status;
	//distance to WP in dm
	unsigned short distance_to_wp;
} CURRENT_WAY;


#define WP_NAVSTAT_REACHED_POS      0x01 //vehicle has entered a radius of WAYPOINT.pos_acc and time to stay is not neccessarily over
#define WP_NAVSTAT_REACHED_POS_TIME 0x02 //vehicle is within a radius of WAYPOINT.pos_acc and time to stay is over
#define WP_NAVSTAT_20M              0x04 //vehicle within a 20m radius of the waypoint
#define WP_NAVSTAT_PILOT_ABORT      0x08 //waypoint navigation aborted by safety pilot

/*
--- Sending the waypoint structure to the vehicle ---

The following string must be sent to the vehicle, directly followed by the actual waypoint structure:
unsigned char string[]=">*>ws";

--- Commands for the waypoint navigation ---
>*>wg	"Goto waypoint"
>*>wl	"Launch / Set Home
>*>we	"End flight => land at current position"
>*>wh	"Come home"

Sending the launch command when the vehicle is hovering with the switch on the R/C in
"GPS + Height control" sets the home position.

You will receive an acknowledge if a command or a waypoint was received correctly:
>a[1 byte packet descriptor]a<
*/

#pragma pack(pop)
#endif
