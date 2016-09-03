#include "../../../AstecFireFly/AstecFireFlyController.h"
#include "../../../AstecFireFly/AstecFireFlyInternals.h"
#include <iostream>
#include <fstream>

using namespace std;
fstream resultFile;

int K[5] = { 5000, 7000, 8000, 9000, 10000 };


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

void main(){
	//create the result file 
	resultFile.open("gridSize_results.txt", std::fstream::app | fstream::in | fstream::out);
	resultFile << "---------------New Experiment--------------------" << endl;
	getchar();

	InitializeDrone();
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

	//change the value of K
	for (int i = 0; i < 5; i++)
	{
		POSITION gotoP;
		//get the current state
		AstecDroneState currentDroneState;


		resultFile << "----------------------------------" << endl;
		resultFile << K[i] << " " << 0 << endl;
		resultFile << "----------------------------------" << endl;
		//get it for [K, 0]
		gotoP = { K[i], 0 };
		//get the drone in home location
		DroneComeHome();
		

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
		Sleep(5000);
		currentDroneState = GetUpdatedDroneState();
		//PrintCurrentDroneState();
		DumpYT(currentDroneState);
		
		resultFile << "----------------------------------" << endl;
		resultFile << 0 << " " << K[i] << endl;
		resultFile << "----------------------------------" << endl;
		//get it for [0, K]
		gotoP = { 0, K[i] };
		//get the drone in home location
		DroneComeHome();


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
		
		currentDroneState = GetUpdatedDroneState();
		//PrintCurrentDroneState();
		DumpYT(currentDroneState);
		Sleep(5000);

		resultFile << "----------------------------------" << endl;
		resultFile << -K[i] << " " << 0 << endl;
		resultFile << "----------------------------------" << endl;
		//get it for [-K, 0]
		gotoP = {-K[i], 0};
		//get the drone in home location
		DroneComeHome();


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
		
		currentDroneState = GetUpdatedDroneState();
		//PrintCurrentDroneState();
		DumpYT(currentDroneState);

		Sleep(5000);
		resultFile << "----------------------------------" << endl;
		resultFile << 0 << " " << -K[i] << endl;
		resultFile << "----------------------------------" << endl;
		//get it for [0, -K]
		gotoP = { 0, -K[i] };
		//get the drone in home location
		DroneComeHome();


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
		currentDroneState = GetUpdatedDroneState();
		//PrintCurrentDroneState();
		DumpYT(currentDroneState);
		Sleep(5000);
	}
	
	resultFile.close();
	CloseSerialPort();
}