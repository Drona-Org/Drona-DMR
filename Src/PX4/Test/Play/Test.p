
event init;
event battery_critical;
event take_off;
event fmom_battery_critical;

machine Main {
	
	start state Init {
		entry {
			raise init;
		}
		on init push Standby;

		on battery_critical do {
			raise fmom_battery_critical;
		}

		ignore fmom_battery_critical;

	}

	state Standby {
		
		entry {
			raise take_off;
		}
		
		on take_off push Flying;

		on fmom_battery_critical  do {
			print "battery is critical!\n";
			pop;
		}
	}

	
	state Flying {
		
		entry {
			print "flying...\n";
			raise battery_critical;
		}
	}

}