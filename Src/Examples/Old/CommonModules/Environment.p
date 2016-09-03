
model Environment {
	var GoalsMap : map[int, any];
	start state Init {
		entry {
			GoalsMap = GetStaticGoals();
			raise(local);
			
		}
		on local goto StartSimulation;
	}
	
	state StartSimulation {
		on GetEnv do {
			if(payload.loc in GoalsMap)
			{
				send payload.rtStateManager, EnvState, (loc = payload.loc, envState = GoalsMap[payload.loc]);
			}
			else
			{
				send payload.rtStateManager, EnvState, (loc = payload.loc, envState = null);
			}
		};
		on SetEnv do {
			GoalsMap[payload.loc] = payload.envState;
		};
		
	}
}
