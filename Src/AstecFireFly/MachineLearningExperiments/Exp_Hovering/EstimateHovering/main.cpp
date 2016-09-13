#include "../../../AstecFireFly/AstecFireFlyController.h"
#include "../../../AstecFireFly/AstecFireFlyInternals.h"
#include <iostream>
#include <fstream>

using namespace std;
fstream resultFile;

void DumpLocation(AstecDroneState ds)
{
	//output the current x and y
	resultFile << "location " << ds.adv_rel_X << " " << ds.adv_rel_Y << endl;
	cout << "location " << ds.adv_rel_X << " " << ds.adv_rel_Y << endl;
	//gps data
	resultFile << "gps " << ds.GPS_Adv->horizontal_accuracy << " " << ds.GPS_Adv->vertical_accuracy << " " << ds.GPS_Adv->numSV << endl;
	//gps data
	resultFile << "gpspos" << ds.GPS_Adv->latitude_best_estimate << " " << ds.GPS_Adv->longitude_best_estimate << endl;
	//home location
	resultFile << "home " << ds.home_lat << " " << ds.home_lon << endl;
	resultFile << "-----------------------------------" << endl;
}
void main(){
	//create the result file 
	resultFile.open("hovering_results.txt", std::fstream::app | fstream::in | fstream::out);
	resultFile << "---------------New Experiment--------------------" << endl;
	InitializeDrone();

	getchar();

	cout << " Set Home Position :" << endl;
	//set the current location as the home location.
	LaunchDroneOrSetHome();

	//get the current state
	AstecDroneState currentDroneState;
	POSITION currentWP;
	currentWP.X = 0;
	currentWP.Y = 0;
	currentDroneState = GetUpdatedDroneState();

	while (!CheckIfReachedDestination(currentWP))
	{
		GotoWayPoint(currentWP.X, currentWP.Y, DEFAULT_HEIGHT);
	}

	//start taking the hovering readings.
	int i = 0;
	while (i < 1000)
	{
		currentDroneState = GetUpdatedDroneState();
		//PrintCurrentDroneState();
		DumpLocation(currentDroneState);
		resultFile.flush();
		i++;
	}
	resultFile.close();
	CloseSerialPort();
}