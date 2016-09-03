#include <iostream>

#ifdef PLAT_WINDOWS
#include "..\..\Semplan\Semplan.h"
#else
#include "../../Semplan/Semplan.h"
#endif

using namespace std;

int main()
{
	int count;
	int* output_seq_of_locations = (int*)malloc(100 * sizeof(int));
	int output_size = 0;
	int obs[34] = {
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
	};
	//AvoidPositions *avoidsArr = NULL;
        AvoidPositions avoidsArr[] = { { { 10, 11, 10 }, 3 }, { { 11, 14 }, 2 } };
	GenerateMotionPlanFor(4, 113, obs, 34, avoidsArr, 2, output_seq_of_locations, output_size);
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
