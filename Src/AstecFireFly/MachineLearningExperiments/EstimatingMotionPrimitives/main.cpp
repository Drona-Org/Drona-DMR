#include "../../AstecFireFly/AstecFireFlyController.h"
#include "../../AstecFireFly/AstecFireFlyInternals.h"
#include <iostream>
#include <fstream>

using namespace std;
fstream resultFile;

#define GRID_SIZE 3000


void DumpY0(AstecDroneState ds)
{
	//output the current x and y
	resultFile << "Y0 " << ds.adv_rel_X << " " << ds.adv_rel_Y << endl;
	cout << "Y0 " << ds.adv_rel_X << " " << ds.adv_rel_Y << endl;
}
void DumpYI(AstecDroneState ds)
{
	//output the current x and y
	resultFile << "YI " << ds.adv_rel_X << " " << ds.adv_rel_Y << endl;
	cout << "YI " << ds.adv_rel_X << " " << ds.adv_rel_Y << endl;
}
void DumpYT(AstecDroneState ds)
{
	//output the current x and y
	resultFile << "YT " << ds.adv_rel_X << " " << ds.adv_rel_Y << endl;
	cout << "YT " << ds.adv_rel_X << " " << ds.adv_rel_Y << endl;
}

void Exp_MoveForward()
{
	//do this for 20 times.
	for (int i = 0; i < 20; i++)
	{
		POSITION gotoP;
		//get the current state
		AstecDroneState currentDroneState;


		resultFile << "----------------------------------" << endl;
		resultFile << GRID_SIZE << " " << 0 << endl;
		resultFile << "----------------------------------" << endl;
		//get it for [K, 0]
		gotoP = { GRID_SIZE, 0 };
		//get the drone in home location
		DroneComeHome();

		POSITION currentWP;
		currentWP.X = 0;
		currentWP.Y = 0;
		currentDroneState = GetUpdatedDroneState();
		while (!CheckIfReachedDestination(currentWP))
		{
			GotoWayPoint(0, 0, DEFAULT_HEIGHT);
		}

		//dump the Y0 location
		currentDroneState = GetUpdatedDroneState();
		//PrintCurrentDroneState();
		DumpY0(currentDroneState);
		//send command 
		GotoWayPoint(gotoP.X, gotoP.Y, DEFAULT_HEIGHT);
		//wait for the drone to reach destination
		while (!CheckIfReachedDestination(gotoP))
		{
			currentDroneState = GetUpdatedDroneState();
			//PrintCurrentDroneState();
			DumpYI(currentDroneState);
		}
		Sleep(2000);
		currentDroneState = GetUpdatedDroneState();
		//PrintCurrentDroneState();
		DumpYT(currentDroneState);


	}
}
void main(){
	//create the result file 
	resultFile.open("motionprimitives_results.txt", std::fstream::app | fstream::in | fstream::out);
	resultFile << "---------------New Experiment--------------------" << endl;
	getchar();

	InitializeDrone();
	cout << " Set Home Position :" << endl;
	//set the current location as the home location.
	LaunchDroneOrSetHome();

	Exp_MoveForward();
	

	resultFile.close();
	CloseSerialPort();
}