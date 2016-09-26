#include <iostream>
#include <time.h>
#include<chrono>
#include "Workspace.h"
#include "PlanGenerator.h"
#include "WorkspaceParser.h"
#include "PathSearchNode.h"
#include "stlastar.h"

AvoidPositions *avoidsArr = NULL;
int sizeof_avoids = 0;
int GetEndLocation(int robotid) {
	if (robotid >= WORKSPACE_INFO->ends.size)
	{
		cout << "BUG !!" << endl;
		exit(0);
	}
	int ret = WORKSPACE_INFO->ends.locations[robotid];
	return ret;
}

int GetStartLocation(int robotid) {
	if (robotid >= WORKSPACE_INFO->starts.size)
	{
		cout << "BUG !!" << endl;
		exit(0);
	}
	int ret = WORKSPACE_INFO->starts.locations[robotid];
	return ret;
}

void CreateRandomAvoidsSet()
{
	cout << "Generating avoids" << endl;
	int counter = 0;
	int* output_seq_of_locations = (int*)malloc(100 * sizeof(int));
	int outsize;
	int numRobots = WORKSPACE_INFO->numOfRobots;
	avoidsArr = (AvoidPositions*)malloc((numRobots - 1) * sizeof(AvoidPositions));
	sizeof_avoids = 0;
	while (counter < (numRobots - 1))
	{
		int st = GetStartLocation(counter);
		int g = GetEndLocation(counter);
		cout << st << endl;
		cout << g << endl;
		output_seq_of_locations = (int*)malloc(1000 * sizeof(int));
		GenerateMotionPlanFor(*WORKSPACE_INFO, st, g, WORKSPACE_INFO->obstacles.locations, WORKSPACE_INFO->obstacles.size, avoidsArr, sizeof_avoids, output_seq_of_locations, &outsize);
		cout << "Trajectory Length = " << outsize << endl;
		cout << "Trajectory: " << endl;
		for (int count = 0; count < outsize; count++)
		{
			cout << output_seq_of_locations[count] << " ";
		}
		cout << endl;
		avoidsArr[counter].size = outsize;
		for (int i = 0; i < outsize; i++)
		{
			avoidsArr[counter].PositionsOccupied[i] = output_seq_of_locations[i];
		}
		sizeof_avoids++;
		counter++;
	}
	cout << "------------" << endl;
}

int main()
{
	int count;
	int* output_seq_of_locations = (int*)malloc(100 * sizeof(int));
	int output_size = 0;
	srand(time(NULL));

	//Initialize the workspace
	WORKSPACE_INFO = ParseWorkspaceConfig("C:\\Workspace\\Drona\\Src\\Workspaces\\Exp1\\Workspace.xml");

	int exp = 3;

	cout << "--------------------------------" << endl;
	cout << "Num Robots: " << WORKSPACE_INFO->numOfRobots << endl;
	CreateRandomAvoidsSet();
	exp = 5;
	while (exp > 0)
	{
		cout << "Experiment " << exp << endl;
		int st = GetStartLocation(WORKSPACE_INFO->numOfRobots - 1);
		int g = GetEndLocation(WORKSPACE_INFO->numOfRobots -1);
		cout << st << endl;
		cout << g << endl;
		output_seq_of_locations = (int*)malloc(1000 * sizeof(int));
		GenerateMotionPlanFor(*WORKSPACE_INFO, st, g, WORKSPACE_INFO->obstacles.locations, WORKSPACE_INFO->obstacles.size, avoidsArr, sizeof_avoids, output_seq_of_locations, &output_size);
		cout << "Trajectory Length = " << output_size << endl;
		cout << "Trajectory: " << endl;
		for (count = 0; count < output_size; count++)
		{
			cout << output_seq_of_locations[count] << " ";
		}
		cout << endl;
		free(output_seq_of_locations);
		exp--;
		cout << "--------------------------------" << endl;
	}
	return 0;
}


