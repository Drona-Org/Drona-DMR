#define _CRT_SECURE_NO_WARNINGS  
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <winnt.h>
#include <windef.h>
#include <iostream>
#include "AsctecFireFly.h"

//http://wiki.asctec.de/display/AR/Communicating+with+the+Low+Level+Processor


#define DEFAULT_HEIGHT 25000 //mm
#define SIZE_GRID 8000 //mm
#define GPS_ERROR 500 //mm
#define MAX_X_VALUE 50000 //mm
#define MAX_Y_VALUE 25000 //mm
/*
#define WP_NAVSTAT_REACHED_POS      0x01 //vehicle has entered a radius of WAYPOINT.pos_acc and time to stay is not neccessarily over
#define WP_NAVSTAT_REACHED_POS_TIME 0x02 //vehicle is within a radius of WAYPOINT.pos_acc and time to stay is over
#define WP_NAVSTAT_20M              0x04 //vehicle within a 20m radius of the waypoint
#define WP_NAVSTAT_PILOT_ABORT      0x08 //waypoint navigation aborted by safety pilot
*/

//structure to store the current state of drone
struct _AstecDroneState {
	LL_STATUS* ll_Status; //ll-status of the the drone
	double rel_X; //relative way-point X position from the start in mm
	double rel_Y; //relative way-point Y position from the start in mm
	double adv_rel_X; //relative way-point X position from the start in mm
	double adv_rel_Y; //relative way-point Y position from the start in mm
	CURRENT_WAY* curr_WP; //way-point information of the drone
	GPS_DATA* GPS_Status; //stores the GPS status.
	GPS_DATA_ADVANCED* GPS_Adv; /// GPS advanced.
	double home_lon; //longitute of the home position.
	double home_lat; //lattitute of the home position.
};

typedef struct _AstecDroneState AstecDroneState;

extern AstecDroneState DroneState;
extern HANDLE HSerial;
//Function to open the serial port for communicating with the AstecWifi device
void OpenSerialPort();

//Function to fetch the current state of drone
AstecDroneState GetUpdatedDroneState();

//Function to print the drone state
void PrintCurrentDroneState();

//Function to ask drone to goto waypoint. (asynchornous)
void GotoWayPoint(int rel_X, int rel_Y, int rel_Z);

//Function to initialize the drone. This would just take the drone to a particular height and hover.
void InitializeDrone();

//Close the Serial Port
void CloseSerialPort();

//Launch the drone or set home location
void LaunchDroneOrSetHome();

//Return the drone back to home location, this should be called after setting home location.
void DroneComeHome();

//End flight and land at the current location.
void EndFlight();

struct POSITION {
	int X;
	int Y;
};

//Motion Primitives
void MoveForward(POSITION* current_p);
void MoveBackward(POSITION* current_p);
void MoveRight(POSITION* current_p);
void MoveLeft(POSITION* current_p);




