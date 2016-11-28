event CommandSucceeded: int;
event CommandFailed: int;
type CommandType = (caller: machine, confirm:bool, cmd:int, a1:any, a2:any, a3:any, a4:any, a5:any, a6:any, a7:any);

event Command : CommandType;

event cm_local;

machine CommanderMachine
{
	var px4model : machine;
	start state Init {
		defer Command;
		entry (payload:machine) {
			px4model = payload;
			raise cm_local;
		}
		on cm_local goto ServiceCommands;
	}

	state ServiceCommands {
		on Command do (payload: CommandType) {
			send px4model, d_px4_command, payload;
		}
	}
}
