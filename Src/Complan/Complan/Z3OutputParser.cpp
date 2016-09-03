#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;


double ExtractTrajectoryCostInformation()
{
  ifstream ifp;
  int location;
  string line;
  string var;
  string value;
  string str;
  double val1, val2;
  double cost = 0.0;

  ifp.open("z3_output");
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      line = line.substr(2, strlen(line.c_str()) - 4);
      location = line.find(' ');
      if (location != -1)
      {
        var = line.substr(0, location);
        if (var == "total_cost")
        {
          value = line.substr(location + 4);
          location = value.find(' ');
          str = value.substr(0, location - 1);
          val1 = atof(str.c_str());
          str = value.substr(location + 1);
          val2 = atof(str.c_str());
          cost = val1 / val2;
        }
      }
    }
  }
  ifp.close();
  return cost;
}


void ExtractTrajectoryVelocityInformation(vector< vector<int> > & velocities)
{
  ifstream ifp;
  int location;
  string line;
  string var;
  string index;
  int value;
  int robot, time;

  //cout << filename << endl;
  //ifp.open(filename.c_str());
  ifp.open("z3_output");
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      location = line.find(' ');
      if (location != -1)
      {
        var = line.substr(0, location);
        istringstream (line.substr(location + 1)) >> value;
        location = var.find("vel_i_");
        if (location != -1)
        {
          index = var.substr(location + 6);
          location = index.find('_');
          if (location != -1)
          {
            istringstream (index.substr(0, location)) >> robot;
            istringstream (index.substr(location + 1)) >> time;
            //cout << "line=" << line << "--" << endl; 
            //cout << "var=" << var << "--" << endl; 
            //cout << "value=" << value << endl;
            //cout << "index=" << index << "--" << endl;
            //cout << "robot=" << robot << endl;
            //cout << "time=" << time << endl;
            if (robot > velocities.size())
            {
              velocities.resize(robot);
            }
            velocities[robot - 1].push_back(value);
          }
          else
          {
            cout << "Complan error: parsing error on vel.." << endl;
            exit(0);
          }
        }
      }
    }
  }
  ifp.close();
}


bool ExtractTrajectoryRobotPositionXInformation(vector< vector<int> > &X)
{
  ifstream ifp;
  int location;
  string line;
  string var;
  string index;
  int value;
  int robot, time;

  //cout << filename << endl;
  //ifp.open(filename.c_str());
  ifp.open("z3_output");
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      //cout << line << endl;
      line = line.substr(2, strlen(line.c_str()) - 4);
      //cout << line << endl;
      location = line.find(' ');
      if (location != -1)
      {
        var = line.substr(0, location);
        istringstream (line.substr(location + 1)) >> value;
        location = var.find("x_");
        if (location != -1)
        {
          index = var.substr(location + 2);
          location = index.find("f_");
          if (location == -1)
          {
            location = index.find('_');
            if (location != -1)
            {
              istringstream (index.substr(0, location)) >> robot;
              istringstream (index.substr(location + 1)) >> time;
              //cout << "line=" << line << "--" << endl;
              //cout << "var=" << var << "--" << endl;
              //cout << "value=" << value << endl;
              //cout << "index=" << index << "--" << endl;
              //cout << "robot=" << robot << endl;
              //cout << "time=" << time << endl;
              if (robot > X.size())
              {
                X.resize(robot);
              }
              X[robot - 1].push_back(value);
            }
            else
            {
              cout << "Complan Error : parsing error on X.." << endl;
	      return false;
            }
          }
        }
      }
    }
  }
  ifp.close();
  return true;
}


bool ExtractTrajectoryRobotPositionYInformation(vector< vector<int> > &Y)
{
  ifstream ifp;
  int location;
  string line;
  string var;
  string index;
  int value;
  int robot, time;

  //cout << filename << endl;
  //ifp.open(filename.c_str());
  ifp.open("z3_output");
  if (ifp.is_open())
  {
    while (getline(ifp, line))
    {
      line = line.substr(2, strlen(line.c_str()) - 4);
      location = line.find(' ');
      if (location != -1)
      {
        var = line.substr(0, location);
        istringstream (line.substr(location + 1)) >> value;
        location = var.find("y_");
        if (location != -1)
        {
          index = var.substr(location + 2);
          location = index.find("f_");
          if (location == -1)
          {
            location = index.find('_');
            if (location != -1)
            {
              istringstream (index.substr(0, location)) >> robot;
              istringstream (index.substr(location + 1)) >> time;
              //cout << "line=" << line << "--" << endl;
              //cout << "var=" << var << "--" << endl;
              //cout << "value=" << value << endl;
              //cout << "index=" << index << "--" << endl;
              //cout << "robot=" << robot << endl;
              //cout << "time=" << time << endl;
              if (robot > Y.size())
              {
                Y.resize(robot);
              }
              Y[robot - 1].push_back(value);
            }
            else
            {
              cout << "Complan error : parsing error on Y.." << endl;
	      return false;
            }
          }
        }
      }
    }
  }
  ifp.close();
  return true;
}
