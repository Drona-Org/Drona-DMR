// MPU6000Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

extern "C" {
#include "MPU6000.h"
}

int main()
{
    unsigned char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, (LPSTR)buffer);

    Init(buffer);
    RunSimulation();
    return 0;
}

