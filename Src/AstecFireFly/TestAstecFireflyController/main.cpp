#include "../AstecFireFly/AstecFireFlyController.h"
#include "../AstecFireFly/AstecFireFlyInternals.h"
#include <iostream>

using namespace std;

void WaitForUser()
{
	getchar();
}

void main(){
	
	
	printf("serial port opened!\n");
	InitializeDrone();
	GetUpdatedDroneState();
	PrintCurrentDroneState();

	WaitForUser();
	
	while (true)
	{
		printf("Please enter the operation to be performed\n");
		cout << "n: navigate to WP" << endl;
		cout << "e: end flight and drop the drone" << endl;
		cout << "l: launch drone or set home" << endl;
		cout << "h: bring drone back to home location" << endl;
		cout << "s: Print current state" << endl;

		char option = 'd';
		int curr_x = 0, curr_y = 0;
		cin >> option;
		switch (option)
		{
		case 'n':
			
			//going in navigation loop 
			while (true)
			{
				char dir = 'q';
				printf("Please enter the next step\n");
				cout << "f: forward" << endl;
				cout << "b: backward" << endl;
				cout << "l: left" << endl;
				cout << "r: right" << endl;
				cout << "s: stats" << endl;
				cout << "q: stats" << endl;

				cin >> dir;
				switch (dir)
				{
				case 'f':
					curr_x += SIZE_GRID;
					cout << "Going to: " << curr_x << " " << curr_y << endl;
					getchar();
					GotoWayPoint(curr_x, curr_y, DEFAULT_HEIGHT);
					break;
				case 'b':
					curr_x -= SIZE_GRID;
					cout << "Going to: " << curr_x << " " << curr_y << endl;
					getchar();
					GotoWayPoint(curr_x, curr_y, DEFAULT_HEIGHT);
					break;
				case 'l':
					curr_y += SIZE_GRID;
					cout << "Going to: " << curr_x << " " << curr_y << endl;
					getchar();
					GotoWayPoint(curr_x, curr_y, DEFAULT_HEIGHT);
					break;
				case 'r':
					curr_y -= SIZE_GRID;
					cout << "Going to: " << curr_x << " " << curr_y << endl;
					getchar();
					GotoWayPoint(curr_x, curr_y, DEFAULT_HEIGHT);
					break;
				case 's':
					GetUpdatedDroneState();
					PrintCurrentDroneState();
					break;
				case 'q':
					goto done;
					break;
				default:
					break;
				}
			}
done:
			break;
		case 'e':
			cout << "ROGER THAT : Bringing Drone Down Sir !!" << endl;
			EndFlight();
			break;
		case 'h':
			cout << "Bring the drone back home !!" << endl;
			DroneComeHome();
			break;
		case 'l':
			cout << "launch or set home :" << endl;
			LaunchDroneOrSetHome();
			break;
		case 's': 
			GetUpdatedDroneState();
			PrintCurrentDroneState();
			break;
		default:
			cout << "Invalid command !! " << endl;
			break;
		}
		


	}

	CloseSerialPort();
	
}