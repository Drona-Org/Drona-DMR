#include "PFilesIncludes.p"

// This is for testing with Zinger.
machine Main {
	start state Init {
		entry {
			new MissionPlannerMachine();
		}
	}
}