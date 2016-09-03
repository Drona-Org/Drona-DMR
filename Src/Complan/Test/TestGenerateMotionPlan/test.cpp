#include <iostream>

#ifdef PLAT_WINDOWS
#include "..\..\Complan\Complan.h"
#else
#include "../../Complan/Complan.h"
#endif

using namespace std;

int main()
{
	int count;
	int* output_seq_of_locations = (int*)malloc(100 * sizeof(int));
	int output_size = 0;
	int obs[1] = {};
	AvoidPositions avoidsArr[] = { { { 10, 11, 10 }, 3 }, { { 11, 14 }, 2 } };
	GenerateMotionPlanFor(5, 13, obs, 0, avoidsArr, 2, output_seq_of_locations, &output_size);
	cout << "Trajectory Length = " << output_size << endl;
	cout << "Trajectory: " << endl;
	for (count = 0; count < output_size; count++)
	{
		cout << output_seq_of_locations[count] << endl;
	}
	free(output_seq_of_locations);
	output_seq_of_locations = (int*)malloc(100 * sizeof(int));
	if (GenerateMotionPlanFor(10, 4, obs, 0, avoidsArr, 2, output_seq_of_locations, &output_size)) {
		cout << "Trajectory Length = " << output_size << endl;
		cout << "Trajectory: " << endl;
		for (count = 0; count < output_size; count++)
		{
			cout << output_seq_of_locations[count] << endl;
		}
	}

	free(output_seq_of_locations);
	output_seq_of_locations = (int*)malloc(100 * sizeof(int));
	if (GenerateMotionPlanFor(2, 16, obs, 0, avoidsArr, 2, output_seq_of_locations, &output_size))
	{
		cout << "Trajectory Length = " << output_size << endl;
		cout << "Trajectory: " << endl;
		for (count = 0; count < output_size; count++)
		{
			cout << output_seq_of_locations[count] << endl;
		}
	}

	
	GenerateMotionPlanFor(9, 10, obs, 0, avoidsArr, 2, output_seq_of_locations, &output_size);
	cout << "Trajectory Length = " << output_size << endl;
	cout << "Trajectory: " << endl;
	for (count = 0; count < output_size; count++)
	{
		cout << output_seq_of_locations[count] << endl;
	}

	/*
	GenerateMotionPlanFor(16, 13, obs, 0, avoidsArr, 2, output_seq_of_locations, &output_size);
	cout << "Trajectory Length = " << output_size << endl;
	cout << "Trajectory: " << endl;
	for (count = 0; count < output_size; count++)
	{
		cout << output_seq_of_locations[count] << endl;
	}
	
	GenerateMotionPlanFor(2, 13, obs, 0, avoidsArr, 2, output_seq_of_locations, &output_size);

	cout << "Trajectory Length = " << output_size << endl;
	cout << "Trajectory: " << endl;
	for (count = 0; count < output_size; count++)
	{
		cout << output_seq_of_locations[count] << endl;
	}*/
	getchar();
	return 0;
}
