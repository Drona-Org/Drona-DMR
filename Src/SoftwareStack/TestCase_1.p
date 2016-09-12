#include "DriverIncludes.p"

machine Main
{
    start state Init
    {
        entry
        {
            new MissionPlannerMachine();
        }
    }

}