#include <iostream>
#include "PlanGenerator.h"
#include "WorkspaceParser.h"
using namespace std;

int main()
{
	char* pathToWorkspace = "C:\\Workspace\\Drona\\Src\\Workspaces\\Exp2\\Workspace.xml";
	int count;
	int* output_seq_of_locations = (int*)malloc(100 * sizeof(int));
	int output_size = 0;
	/*int obs[34] = {
		21,	44,
		22,	43,
		23,	42,
		24,	41,
		25,	40,
		26,	39,
		27,	38,
		28,	37,
		78,	83,
		77,	84,
		76,	85,
		74,	87,
		71,	90,
		70,	91,
		69,	92,
		98,	127,
		97,	128
	};*/

	WorkspaceInfo* WSInfo = ParseWorkspaceConfig(pathToWorkspace);
	// Testcase: Only static obstacles.
	//AvoidPositions *avoidsArr = NULL;
	//GenerateMotionPlanFor(*WSInfo, 4, 113, WSInfo->obstacles.locations, WSInfo->obstacles.size, avoidsArr, 0, output_seq_of_locations, output_size);

	// Testcase: Two other robots are present in the workspace, but they do not block the trajectory 
	// of the current robot.
        //AvoidPositions avoidsArr[] = { { { 10, 11, 10 }, 3 }, { { 11, 14 }, 2 } };
	//GenerateMotionPlanFor(4, 113, obs, 34, avoidsArr, 2, output_seq_of_locations, output_size);

	// Testcase: The end location of one robot block the end location of the current robot. No trajectory exists.         
        //AvoidPositions avoidsArr[] = { { { 30, 29, 36, 61 }, 4 } };
	//GenerateMotionPlanFor(4, 61, obs, 34, avoidsArr, 1, output_seq_of_locations, output_size);

	// Testcase: The location of the other robot at timestep 2 blocks the shortest path of the current robot.
	// We find an alternative path that avoid collision.
	//AvoidPositions avoidsArr[] = { { { 19, 35, 51, 52 }, 4 } };
    //GenerateMotionPlanFor(*WSInfo, 3, 53, WSInfo->obstacles.locations, WSInfo->obstacles.size, avoidsArr, 1, output_seq_of_locations, output_size);

	AvoidPositions avoidsArr[] = { { { 60, 59, 58, 57 }, 4 } };
	for (int i = 0; i < WSInfo->obstacles.size; i++)
	{
		cout << WSInfo->obstacles.locations[i] << " ";
	}
	GenerateMotionPlanFor(*WSInfo, 19, 44, WSInfo->obstacles.locations, WSInfo->obstacles.size, avoidsArr, 1, output_seq_of_locations, &output_size);

	cout << "Trajectory Length = " << output_size << endl;
	cout << "Trajectory: " << endl;
	for (count = 0; count < output_size; count++)
	{
		cout << output_seq_of_locations[count] << endl;
	}
	free(output_seq_of_locations);
	getchar();
	return 0;
}
