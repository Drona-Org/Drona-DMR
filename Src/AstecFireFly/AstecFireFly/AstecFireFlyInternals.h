struct XY_COOR {
	double X;
	double Y;
};

//local internal functions
void SendWPInformation(int rel_x, int rel_y, int rel_z);
void NavigatetoAssignedWP();
void ParseDataAndUpdate(char buff[], int dwBytesRead);

//calculate the relative x and y coordinates based on lat and long
XY_COOR CalculateRelXY(double home_lat, double home_lon, double curr_lat, double curr_long);

//check if the destination reached
bool CheckIfReachedDestination(POSITION dest_position);
