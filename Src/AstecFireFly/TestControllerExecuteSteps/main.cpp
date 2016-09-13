#include "../AstecFireFly/AstecFireFlyController.h"
#include "../AstecFireFly/AstecFireFlyInternals.h"
#include <iostream>

using namespace std;

void ExecuteSteps(char* steps, int size, POSITION* currWP)
{
	for (int i = 0; i < size; i++)
	{
		switch (steps[i])
		{
		case 'f':
			MoveForward(currWP);
			break;
		case 'b':
			MoveBackward(currWP);
			break;
		case 'r':
			MoveRight(currWP);
			break;
		case 'l':
			MoveLeft(currWP);
			break;
		default:
			exit(1);
		}

		cout << "Executed One Step :" << endl;
		//WaitForUser();
	}
}


void main(){
	
	char stepsToPerform[12] = { 'f', 'f', 'f', 'r', 'r', 'r', 'b', 'b', 'b', 'l', 'l', 'l' };
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

	// start executing the plan

	ExecuteSteps(stepsToPerform, 12, &currentWP);

	CloseSerialPort();
	
}

