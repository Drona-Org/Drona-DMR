#pragma once
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

extern std::vector<std::string> split(std::string s, char splitChar);

class Command
{
public:
	Command();
	~Command();

	std::string Name;

	virtual bool Parse(std::vector<std::string>& args) {
		return false;
	}
	virtual void PrintHelp() {

	}
	virtual void Execute()
	{
	}
	virtual void HandleMessage(void* msg);
};

class ArmDisarmCommand : public Command
{
	float arm = 0;
public:
	ArmDisarmCommand() {
		this->Name = "arm|disarm";
	}
	virtual bool Parse(std::vector<std::string>& args) {
		if (args.size() > 0) {
			std::string cmd = args[0];
			if (cmd == "arm")
			{
				arm = 1;
				return true;
			}
			else if (cmd == "disarm") {
				arm = 0;
				return true;
			}
		}
		return false;
	}
	virtual void PrintHelp() {
		printf("arm|disam - arms or disarms the drone\n");
	}

	virtual void Execute();
};


class GetParamsCommand : public Command
{
	FILE* ptr;
public:
	GetParamsCommand() {
		this->Name = "params [logfile]";
		this->ptr = NULL;
	}
	virtual bool Parse(std::vector<std::string>& args) {
		if (args.size() > 0) {
			std::string cmd = args[0];
			if (cmd == "params") {

				if (args.size() > 1)
				{
					OpenLog(args[1].c_str());
				}
				return true;
			}
		}
		return false;
	}
	virtual void PrintHelp() {
		printf("params [logfilename] - fetches the PX4 parameters and prints them or writes them to a file.\n");
	}

	virtual void Execute();

	virtual void HandleMessage(void* msg);

private:
	void OpenLog(const char* fileName)
	{
		printf("Test");
		//fopen_s(&ptr, fileName, "w");
	}

	void Close()
	{
		if (ptr != NULL)
		{
			fclose(ptr);
			ptr = NULL;
		}
	}

};


class TakeOffCommand : public Command
{
	float altitude = 0;
	float targetAlt;
	bool reached;
	bool offground;
	const float delta = 1;
public:
	TakeOffCommand() {
		this->Name = "takeoff alt";
	}
	virtual bool Parse(std::vector<std::string>& args) {
		if (args.size() > 0) {
			std::string cmd = args[0];
			if (cmd == "takeoff") {

				if (args.size() > 1)
				{
					altitude = atof(args[1].c_str());
				}
				return true;
			}
		}
		return false;
	}
	virtual void PrintHelp() {
		printf("takeoff alt - take off to given altitude (in meters).\n");
	}

	virtual void Execute();

	virtual void HandleMessage(void* msg);

};


class LandCommand : public Command
{
	bool landed;
public:
	LandCommand() {
		this->Name = "land";
	}
	virtual bool Parse(std::vector<std::string>& args) {
		if (args.size() > 0) {
			std::string cmd = args[0];
			if (cmd == "land") {
				return true;
			}
		}
		return false;
	}
	virtual void PrintHelp() {
		printf("land  - auto-land the drone at the current location.\n");
	}

	virtual void Execute();

	virtual void HandleMessage(void* msg);

};


class RtlCommand : public Command
{
	bool landed;
public:
	RtlCommand() {
		this->Name = "rtl";
	}
	virtual bool Parse(std::vector<std::string>& args) {
		if (args.size() > 0) {
			std::string cmd = args[0];
			if (cmd == "rtl") {
				return true;
			}
		}
		return false;
	}
	virtual void PrintHelp() {
		printf("rtl  - fly home (return to launch point).\n");
	}

	virtual void Execute();

	virtual void HandleMessage(void* msg);

};



class MissionCommand : public Command
{
	bool landed;
public:
	MissionCommand() {
		this->Name = "mission";
	}
	virtual bool Parse(std::vector<std::string>& args) {
		if (args.size() > 0) {
			std::string cmd = args[0];
			if (cmd == "mission") {
				return true;
			}
		}
		return false;
	}
	virtual void PrintHelp() {
		printf("mission  - fly preprogrammed mavlink mission.\n");
	}

	virtual void Execute();

	virtual void HandleMessage(void* msg);

};


class CapabilitiesCommand : public Command
{
	bool landed;
public:
	CapabilitiesCommand() {
		this->Name = "cap";
	}
	virtual bool Parse(std::vector<std::string>& args) {
		if (args.size() > 0) {
			std::string cmd = args[0];
			if (cmd == "cap") {
				return true;
			}
		}
		return false;
	}
	virtual void PrintHelp() {
		printf("cap  - fetch and print drone capabilities.\n");
	}

	virtual void Execute();

	virtual void HandleMessage(void* msg);

};


class GotoCommand : public Command
{
	bool hasLocalPos;
	bool targetReached;
protected:
	float x, y, z; // current
	float tx, ty, tz; // target
	float vx, vy, vz; // current speed
	const float nearDelta = 0.5; // meters
public:
	GotoCommand() {
		this->Name = "goto x,y,z";
	}
	virtual bool Parse(std::vector<std::string>& args) {
		if (args.size() > 0) {
			std::string cmd = args[0];
			if (cmd == "goto") {
				if (args.size() == 4) {
					tx = atof(args[1].c_str());
					ty = atof(args[2].c_str());
					tz = atof(args[3].c_str());
					return true;
				}
				else if (args.size() == 2) {
					std::vector<std::string> coords = split(args[1], ',');
					if (coords.size() == 3) {
						tx = atof(coords[0].c_str());
						ty = atof(coords[1].c_str());
						tz = atof(coords[2].c_str());
					}
					return true;
				}
				else {
					printf("goto - expecting x,y,z arguments\n");
				}
			}
		}
		return false;
	}
	virtual void PrintHelp() {
		printf("goto x,y,z  - move the drone to local coordinates x,y,z (in meters).\n");
	}

	virtual void Execute();

	virtual void WaitForLocalPosition();

	virtual void HandleMessage(void* msg);

	virtual void HasLocalPosition();

	virtual void Goto(float x, float y, float z, float speed, float heading);

	virtual void TargetReached();
};


class OrbitCommand : public GotoCommand
{
	float radius;
	bool flyingToRadius;
	bool orbiting;
	float cx, cy, cz;
	//std::chrono::time_point<std::chrono::system_clock> lastGotoTime;
public:
	OrbitCommand() {
		this->Name = "orbit radius";
	}
	virtual bool Parse(std::vector<std::string>& args) {
		if (args.size() > 0) {
			std::string cmd = args[0];
			if (cmd == "orbit") {
				if (args.size() == 2) {
					radius = atof(args[1].c_str());
					return true;
				}
				else {
					printf("orbit - expecting radius argument\n");
				}
			}
		}
		return false;
	}
	virtual void PrintHelp() {
		printf("orbit radius  - orbit the current location & altitude at the given radius (in meters).\n");
	}

	virtual void Execute();

	virtual void HandleMessage(void* msg);

	virtual void HasLocalPosition();

	virtual void TargetReached();
};
