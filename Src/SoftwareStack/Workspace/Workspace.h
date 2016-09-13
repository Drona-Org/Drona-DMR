#ifndef DRONA_WORKSPACE_H
#define DRONA_WORKSPACE_H
#include<stdio.h>
#include<iostream>
using namespace std;

#ifdef __cplusplus
extern "C"{
#endif

typedef struct WS_Dimension {
	int x_dim;
	int y_dim;
	int z_dim;
} WS_Dimension;

typedef struct WS_Coord {
	int x;
	int y;
	int z;
} WS_Coord;

typedef struct WS_LocationsList {
	int size;
	int* locations; //integers list representing the cells occupied by obstacles
} WS_LocationsList;

typedef struct WS_RobotInfo {
	int id;
	int start_position; //integer representing the starting cell.
	//other information
} WS_RobotInfo;

typedef struct WorkspaceInfo {
	WS_Dimension dimension;
	WS_LocationsList obstacles;
	WS_LocationsList starts;
	WS_LocationsList ends;
	int numOfRobots;
	WS_RobotInfo *robots; //list of all robot-info for the numOfRobots.
} WorkspaceInfo;

/*
Currently implemented for two dimensions and will be updated to three dimentions soon !!!
*/
inline int ConvertCoordToGridLocation(WS_Coord coord, WS_Dimension dim)
{
	int g_loc;
	if (coord.x >= dim.x_dim || coord.y >= dim.y_dim)
		cout << "Error: Invalid co-ordinate" << endl;
	if (coord.x % 2 == 0)
	{
		g_loc = dim.y_dim * coord.x + coord.y + 1;
	}
	else
	{
		g_loc = dim.y_dim * coord.x + (dim.y_dim - coord.y);
	}

	return g_loc;
}

inline WS_Coord ExtractCoordFromGridLocation(int loc, WS_Dimension dim)
{
	WS_Coord coord;
	if (loc < 1 || loc >(dim.x_dim * dim.y_dim))
		cout << "Error: Invalid location" << endl;
	//cout << "id = " << id << endl;
	coord.x = (loc - 1) / dim.y_dim;
	coord.y = (loc - 1) % dim.y_dim;
	//cout << "x = " << x << " " << "y = " << y << endl;
	if (((loc - 1) / dim.y_dim) % 2 == 1)
	{
		coord.y = dim.y_dim - coord.y - 1;
	}
	return coord;
}

#ifdef __cplusplus
}
#endif
#endif