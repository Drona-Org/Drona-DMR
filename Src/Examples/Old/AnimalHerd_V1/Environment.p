//The current environment models the static system and hence object location remains constant.
//To model the dynamic environment you just have to make the map dynamic.

//receives from Robot.
event SenseEnv : (robot:machine, loc: int);
event ActuateEnv : (loc: int, st:(dog: bool, cat: bool, mice: bool));
model Environment {
	var objectsLocation : map[int, (dog: bool, cat: bool, mice: bool)];
	start state Init {
		entry {
			objectsLocation = payload as  map[int, (dog: bool, cat: bool, mice: bool)];
			raise(local);
			
		}
		on local goto StartSensing;
	}
	
	state StartSensing {
		on SenseEnv do {
			send payload.robot, SensorOutput, (loc = payload.loc, st = objectsLocation[payload.loc]);
		};
		on ActuateEnv do {
			objectsLocation[payload.loc] = payload.st;
		};
		
	}
}
