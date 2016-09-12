#include "AstecFireFlyController.h"
#include "AstecFireFlyInternals.h"
#include <iostream>
using namespace std;

//global variables
HANDLE hSerial;
AstecDroneState DroneState;

//http://www.csgnetwork.com/degreelenllavcalc.html
#define ONE_DEG_LAT_M (111183.32)
#define ONE_DEG_LONG_M (75140.30)

void InitializeDrone()
{
	//open serial port
	OpenSerialPort();

	//initialize the drone state.
	DroneState.curr_WP = (CURRENT_WAY*)malloc(sizeof(CURRENT_WAY));
	DroneState.ll_Status = (LL_STATUS*)malloc(sizeof(LL_STATUS));
	DroneState.GPS_Status = (GPS_DATA*)malloc(sizeof(GPS_DATA));
	DroneState.GPS_Adv = (GPS_DATA_ADVANCED*)malloc(sizeof(GPS_DATA_ADVANCED));

}


void PrintCurrentDroneState()
{
	cout << "-------------------------------------------------------" << endl;
	cout << "	Drone State    " << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << "Home Location" << endl;
	cout << "-------------------------------------------------------" << endl;
	printf("home LAT : %f \n", DroneState.home_lat);
	printf("home LONG : %f \n", DroneState.home_lon);
	cout << "-------------------------------------------------------" << endl;
	cout << "Current Relative Position" << endl;
	cout << "-------------------------------------------------------" << endl;
	printf("X : %f m\n", DroneState.rel_X);
	printf("Y : %f m\n", DroneState.rel_Y);
	printf("adv X : %f m\n", DroneState.adv_rel_X);
	printf("adv Y : %f m\n", DroneState.adv_rel_Y);

	cout << "-------------------------------------------------------" << endl;
	cout << "LL Status" << endl;
	cout << "-------------------------------------------------------" << endl;
	printf("Battery_1 : %d mv\n", DroneState.ll_Status->battery_voltage_1);
	printf("Battery_2 : %d mv\n", DroneState.ll_Status->battery_voltage_2);
	printf("Up time : %d \n", DroneState.ll_Status->up_time);
	cout << "-------------------------------------------------------" << endl;
	cout << "Current GPS Data" << endl;
	cout << "-------------------------------------------------------" << endl;
	//printf("Heading : %d deq*1000\n", DroneState.GPS_Status->heading);
	//printf("Height : %d mm\n", DroneState.GPS_Status->height);
	//printf("Horizontal Accuracy : %d mm/s\n", DroneState.GPS_Status->horizontal_accuracy);
	printf("Lattitude : %d deq*10^7\n", DroneState.GPS_Status->latitude);
	printf("Longitute : %d deq*10^7\n", DroneState.GPS_Status->longitude);
	printf("Num Satellite : %d \n", DroneState.GPS_Status->numSV);
	//printf("Speed X : %d mm/s\n", DroneState.GPS_Status->speed_x);
	//printf("Speed Y : %d mm/s\n", DroneState.GPS_Status->speed_y);
	cout << "-------------------------------------------------------" << endl;
	cout << "Current WP" << endl;
	cout << "-------------------------------------------------------" << endl;
	printf("Distance to WP : %d mm\n", DroneState.curr_WP->distance_to_wp * 100);
	printf("Navigation Status : %d \n", DroneState.curr_WP->navigation_status);

	

}

XY_COOR CalculateRelXY(double home_lat, double home_lon, double curr_lat, double curr_long)
{
	double diff = 0;
	XY_COOR xy;
	diff = (curr_lat - home_lat) * ONE_DEG_LAT_M;
	xy.Y = diff * 1000;
	diff = (curr_long - home_lon) * ONE_DEG_LONG_M;
	xy.X = diff * 1000;

	return xy;
}
AstecDroneState GetUpdatedDroneState() {
	printf("Attempting to get current state of the drone ... \n"); 
	
	//get the battery level
	POLL_REQUEST req_1 = { { '>', '*', '>', 'p' }, 0x0001 | 0x0100 | 0x0080 | 0x0200 }; //get LL_STATUS and curr_wp and GPS_data and GPS_Advanced
	DWORD written_1; 
	BOOL res = WriteFile(hSerial, (LPCVOID)&req_1, sizeof(POLL_REQUEST), &written_1, 0);
	if (!res || written_1 != sizeof(POLL_REQUEST)){
		printf("error writing to port. Exiting...\n"); 
		exit(1); 
	}

	//sleep for sometime
	Sleep(100); 
	
	DWORD dwBytesRead = 0;

	char buff_1[500] = { 0 };

	if (!ReadFile(hSerial, buff_1, 500, &dwBytesRead, NULL))
	{
		printf("Error reading port. Existing.. \n"); 
		exit(1); 
	}

	if (dwBytesRead > 0){
		printf("Successfully updated the state..\n", dwBytesRead);
		ParseDataAndUpdate(buff_1, dwBytesRead);
	}
	else{
		printf("Nothing to update, strange!!!\n"); 
	}

	//update the relative positions
	DroneState.rel_X = CalculateRelXY(DroneState.home_lat, DroneState.home_lon, DroneState.GPS_Status->latitude / pow(10, 7), DroneState.GPS_Status->longitude/ pow(10, 7)).X;
	DroneState.rel_Y = CalculateRelXY(DroneState.home_lat, DroneState.home_lon, DroneState.GPS_Status->latitude / pow(10, 7), DroneState.GPS_Status->longitude /pow(10,7)).Y;
	//update the adv relative positions
	DroneState.adv_rel_X = CalculateRelXY(DroneState.home_lat, DroneState.home_lon, DroneState.GPS_Adv->latitude_best_estimate / pow(10, 7), DroneState.GPS_Adv->longitude_best_estimate / pow(10, 7)).X;
	DroneState.adv_rel_Y = CalculateRelXY(DroneState.home_lat, DroneState.home_lon, DroneState.GPS_Adv->latitude_best_estimate / pow(10, 7), DroneState.GPS_Adv->longitude_best_estimate / pow(10, 7)).Y;
	return DroneState;
}

void ParseDataAndUpdate(char buff[], int dwBytesRead){
	for (int i = 0; i < dwBytesRead;)
	{
		POLL_HEADER* pHead;
		POLL_FOOTER* pFoot;
		pHead = (POLL_HEADER*)&buff[i];

		i += sizeof(POLL_HEADER);

		switch (pHead->packet_desc)
		{
		case PD_LLSTATUS:
		{
			LL_STATUS* pLLData = (LL_STATUS*)&buff[i];
			DroneState.ll_Status->battery_voltage_1 = pLLData->battery_voltage_1;
			DroneState.ll_Status->battery_voltage_2 = pLLData->battery_voltage_2;
			DroneState.ll_Status->flightMode = pLLData->flightMode;
			DroneState.ll_Status->up_time = pLLData->up_time;
			break;
		}
		case PD_CURRENTWAY:
		{
			CURRENT_WAY *currWPData = (CURRENT_WAY*)&buff[i];
			DroneState.curr_WP->navigation_status = currWPData->navigation_status;
			DroneState.curr_WP->distance_to_wp = currWPData->distance_to_wp;
			break;
		}
		case PD_GPSDATA:
		{
			GPS_DATA* gps_data = (GPS_DATA*)&buff[i];
			DroneState.GPS_Status->heading = gps_data->heading;
			DroneState.GPS_Status->height = gps_data->height;
			DroneState.GPS_Status->horizontal_accuracy = gps_data->horizontal_accuracy;
			DroneState.GPS_Status->latitude = gps_data->latitude;
			DroneState.GPS_Status->longitude = gps_data->longitude;
			DroneState.GPS_Status->numSV = gps_data->numSV;
			DroneState.GPS_Status->speed_accuracy = gps_data->speed_accuracy;
			DroneState.GPS_Status->speed_x = gps_data->speed_x;
			DroneState.GPS_Status->speed_y = gps_data->speed_y;
			break;

		}
		case PD_GPSDATAADVANCED:
		{
			GPS_DATA_ADVANCED* gps_data = (GPS_DATA_ADVANCED*)&buff[i];
			DroneState.GPS_Adv->latitude_best_estimate = gps_data->latitude_best_estimate;
			DroneState.GPS_Adv->longitude_best_estimate = gps_data->longitude_best_estimate;
			DroneState.GPS_Adv->horizontal_accuracy = gps_data->horizontal_accuracy;
			DroneState.GPS_Adv->vertical_accuracy = gps_data->vertical_accuracy;
			DroneState.GPS_Adv->numSV = gps_data->numSV;
			break;
		}
		}
		i += pHead->length;

		pFoot = (POLL_FOOTER*)&buff[i];
		//printf("crc: %04hX\n", pFoot->crc16);
		//printf("stop string: %.3s\n", pFoot->stopstring);

		i += sizeof(POLL_FOOTER);
	}
	
}

void GotoWayPoint(int rel_X, int rel_Y, int rel_Z)
{
	if (rel_X <= MAX_X_VALUE && rel_Y <= MAX_Y_VALUE)
	{
		//First send the WP information
		SendWPInformation(rel_X, rel_Y, rel_Z);

		//Send the command to goto WayPoint
		NavigatetoAssignedWP();

		//Update the Drone state
		GetUpdatedDroneState();
	}
	else
	{
		cout << "MAX BOUND EXCEEDED FOR X OR Y VALUES" << endl;
	}
}

void SendWPInformation(int rel_x, int rel_y, int rel_z){
	printf("Sending a waypoint to the drone (not yet activating) x=%dmm, y=%dmm\n", rel_x, rel_y); 

	WAYPOINT_CMD wp = { { '>', '*', '>', 'w', 's' } }; 
	wp.wp.wp_number = 1; 
	wp.wp.dummy_1 = 0; wp.wp.dummy_2 = 0; 
	wp.wp.properties = 0;
	wp.wp.max_speed = 25; //50%
	wp.wp.time = 10000; //1 second. 
	wp.wp.pos_acc = 1000; // 2.5 m
	wp.wp.X = rel_x; 
	wp.wp.Y = rel_y; 
	wp.wp.yaw = 0; 
	wp.wp.height = rel_z; 
	wp.wp.chksum = 0xAAAA + wp.wp.yaw + wp.wp.height + wp.wp.time + wp.wp.X + wp.wp.Y + wp.wp.max_speed + wp.wp.pos_acc + wp.wp.properties + wp.wp.wp_number;

	DWORD written;
	BOOL res = WriteFile(hSerial, (LPCVOID)&wp, sizeof(WAYPOINT_CMD), &written, 0);
	if (!res || written != sizeof(WAYPOINT_CMD)){
		printf("Error: failed writing to the serial port. Exiting...\n"); 
		exit(1); 
	}

	Sleep(100);
	const int n = 500;

	DWORD dwBytesRead = 0;

	char buff[n] = { 0 };

	if (!ReadFile(hSerial, buff, n, &dwBytesRead, NULL))
	{
		printf("Error reading from device. Exiting...\n"); 
		exit(1); 
	}

	if (dwBytesRead == 5 &&
		buff[0] == '>' && buff[1] == 'a' && buff[3] == 'a' && buff[4] == '<'){
		printf("WP sent correctly. Packet descriptor = %d (%#x)\n", buff[2], buff[2]); 
	}
	else{
		printf("failed to read any repond from device\n"); 
	}

	
	//Update the Drone state
	GetUpdatedDroneState();
}

void NavigatetoAssignedWP(){
	printf("Sending Goto waypoint command\n"); 
	//update the current waypoint
	
	WP_COMMAND cmd = { '>', '*', '>', 'w', 'g' }; 
	DWORD written;
	BOOL res = WriteFile(hSerial, (LPCVOID)&cmd, sizeof(WP_COMMAND), &written, 0);
	if (!res || written != sizeof(WP_COMMAND)){
		printf("Error: failed writing to the serial port. Exiting...\n");
		exit(1);
	}

	Sleep(100);
	const int n = 500;

	DWORD dwBytesRead = 0;

	char buff[n] = { 0 };

	if (!ReadFile(hSerial, buff, n, &dwBytesRead, NULL))
	{
		printf("Error reading from device. Exiting...\n");
		exit(1);
	}
	if (dwBytesRead == 5 &&
		buff[0] == '>' && buff[1] == 'a' && buff[3] == 'a' && buff[4] == '<'){
		printf("WP received correctly. Packet descriptor = %d (%#x)\n", buff[2], buff[2]);
	}
	else {
		printf("failed to read any repond from device\n");
	}

	//Update the Drone state
	GetUpdatedDroneState();
}



//Serial Port Functions

void OpenSerialPort() {

	hSerial = CreateFile(TEXT("COM4"),
		GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hSerial == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			printf("Error : serialportdoesnotexist.Informuser\n");
			exit(1);
			//serialportdoesnotexist.Informuser.
		}
		printf("Error : someothererroroccurred.Informuser.\n");
		exit(1);

		//someothererroroccurred.Informuser.
	}

	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		printf("Error : errorgettingstate\n");
		exit(1);
		//errorgettingstate
	}

	dcbSerialParams.BaudRate = CBR_57600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;

	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		printf("Error : errorsettingserialportstate\n");
		exit(1);
		//errorsettingserialportstate
	}

	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 10;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (!SetCommTimeouts(hSerial, &timeouts))
	{
		printf("Erorr : erroroccureed.Informuser\n");
		exit(1);
		//erroroccureed.Informuser
	}

}

void CloseSerialPort()
{
	CloseHandle(hSerial);
}

//Drone related functions
//Launch the drone or set home location
void LaunchDroneOrSetHome()
{
	printf("Sending Launch command\n");
	//update the current waypoint

	WP_COMMAND cmd = { '>', '*', '>', 'w', 'l' };
	DWORD written;
	BOOL res = WriteFile(hSerial, (LPCVOID)&cmd, sizeof(WP_COMMAND), &written, 0);
	if (!res || written != sizeof(WP_COMMAND)){
		printf("Error: failed writing to the serial port. Exiting...\n");
		exit(1);
	}

	Sleep(100);
	const int n = 500;

	DWORD dwBytesRead = 0;

	char buff[n] = { 0 };

	if (!ReadFile(hSerial, buff, n, &dwBytesRead, NULL))
	{
		printf("Error reading from device. Exiting...\n");
		exit(1);
	}
	if (dwBytesRead == 5 &&
		buff[0] == '>' && buff[1] == 'a' && buff[3] == 'a' && buff[4] == '<'){
		printf("WP command for launch received correctly. Packet descriptor = %d (%#x)\n", buff[2], buff[2]);
	}
	else {
		printf("failed to read any repond from device\n");
	}

	AstecDroneState DS;
	//update the state of drone.
	DS = GetUpdatedDroneState();

	//take snapshot of the home state.
	DroneState.home_lon = DS.GPS_Status->longitude / pow(10, 7);
	DroneState.home_lat = DS.GPS_Status->latitude / pow(10, 7);

	//update the state of drone.
	DS = GetUpdatedDroneState();
}


//Return the drone back to home location, this should be called after setting home location.
void DroneComeHome()
{
	printf("Sending return home command\n");
	//update the current waypoint

	WP_COMMAND cmd = { '>', '*', '>', 'w', 'h' };
	DWORD written;
	BOOL res = WriteFile(hSerial, (LPCVOID)&cmd, sizeof(WP_COMMAND), &written, 0);
	if (!res || written != sizeof(WP_COMMAND)){
		printf("Error: failed writing to the serial port. Exiting...\n");
		exit(1);
	}

	Sleep(100);
	const int n = 500;

	DWORD dwBytesRead = 0;

	char buff[n] = { 0 };

	if (!ReadFile(hSerial, buff, n, &dwBytesRead, NULL))
	{
		printf("Error reading from device. Exiting...\n");
		exit(1);
	}
	if (dwBytesRead == 5 &&
		buff[0] == '>' && buff[1] == 'a' && buff[3] == 'a' && buff[4] == '<'){
		printf("WP command for returning back home received correctly. Packet descriptor = %d (%#x)\n", buff[2], buff[2]);
	}
	else {
		printf("failed to read any repond from device\n");
	}

	//Update the Drone state
	GetUpdatedDroneState();
}


//End flight and land at the current location.
void EndFlight()
{
	printf("Sending end flight command\n");
	//update the current waypoint

	WP_COMMAND cmd = { '>', '*', '>', 'w', 'e' };
	DWORD written;
	BOOL res = WriteFile(hSerial, (LPCVOID)&cmd, sizeof(WP_COMMAND), &written, 0);
	if (!res || written != sizeof(WP_COMMAND)){
		printf("Error: failed writing to the serial port. Exiting...\n");
		exit(1);
	}

	Sleep(100);
	const int n = 500;

	DWORD dwBytesRead = 0;

	char buff[n] = { 0 };

	if (!ReadFile(hSerial, buff, n, &dwBytesRead, NULL))
	{
		printf("Error reading from device. Exiting...\n");
		exit(1);
	}
	if (dwBytesRead == 5 &&
		buff[0] == '>' && buff[1] == 'a' && buff[3] == 'a' && buff[4] == '<'){
		printf("WP command for ending flight received correctly. Packet descriptor = %d (%#x)\n", buff[2], buff[2]);
	}
	else {
		printf("failed to read any repond from device\n");
	}

	//Update the Drone state
	GetUpdatedDroneState();
}


bool CheckIfReachedDestination(POSITION wp){
	AstecDroneState DS = GetUpdatedDroneState();
	if (abs(wp.X - DS.adv_rel_X) <= GPS_ERROR && abs(wp.Y - DS.adv_rel_Y) <= GPS_ERROR)
		return true;
	else
		return false;
}

void MoveForward(POSITION* wp)
{
	wp->X += SIZE_GRID;
	cout << "Moving to location : " << wp->X << " " << wp->Y << endl;
	while (!CheckIfReachedDestination(*wp))
	{
		GotoWayPoint(wp->X, wp->Y, DEFAULT_HEIGHT);
	}
	cout << "Reached location (+/- 2m) : " << wp->X << " " << wp->Y << endl;
}

void MoveBackward(POSITION* wp)
{
	wp->X -= SIZE_GRID;
	cout << "Moving to location : " << wp->X << " " << wp->Y << endl;
	while (!CheckIfReachedDestination(*wp))
	{
		GotoWayPoint(wp->X, wp->Y, DEFAULT_HEIGHT);
	}
	cout << "Reached location (+/- 2m) : " << wp->X << " " << wp->Y << endl;
}

void MoveRight(POSITION* wp)
{
	wp->Y -= SIZE_GRID;
	cout << "Moving to location : " << wp->X << " " << wp->Y << endl;
	while (!CheckIfReachedDestination(*wp))
	{
		GotoWayPoint(wp->X, wp->Y, DEFAULT_HEIGHT);
	}
	cout << "Reached location (+/- 2m) : " << wp->X << " " << wp->Y << endl;
}

void MoveLeft(POSITION* wp)
{
	wp->Y += SIZE_GRID;
	cout << "Moving to location : " << wp->X << " " << wp->Y << endl;
	while (!CheckIfReachedDestination(*wp))
	{
		GotoWayPoint(wp->X, wp->Y, DEFAULT_HEIGHT);
	}
	cout << "Reached location (+/- 2m) : " << wp->X << " " << wp->Y << endl;
}