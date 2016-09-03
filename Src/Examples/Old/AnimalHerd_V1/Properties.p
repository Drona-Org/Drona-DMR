/*
----------------------------------------------------
Monitors that implement the specifications
----------------------------------------------------
Predicates:
sCat : Sensed cat.
sDog : Sensed dog.
sMice : Sensed mice.
hCat : robot is herding cat.
hDog : robot is herding dog.
hMice : robot is herding mice.
rDog : 1 dog in cage.
rCat : 1 cat in cage.
rMice : 1 mice in cage.
noAmimals : all animals are in cage.


Properties to be checked:
1) G!(hCat ^ hDog)
2) G!(hCat ^ hMice)
6) sDog ^ !hCat -> X hDog
7) sDog ^ sCat -> X hDog
8) sMice ^ sCat -> X hCat
9)  sCat ^ !hMice ^ !sDog -> X hCat

3) !noAmimals -> F(hCat | hMice | hDog)
10) hDog -> X ((hDog U (rDog))
10) hCat -> X ((hCat U (rCat))
10) hMice -> X ((hMice U (rMice))
*/
event M_hDog;
event M_sDog;
event M_rDog;
event M_hCat;
event M_sCat;
event M_rCat;
event M_hMice;
event M_sMice;
event M_rMice;

spec Prop_1 monitors M_hCat, M_hDog, M_rDog, M_rCat {
	var hCat : bool;
	var hDog : bool;
	
	start state Init {
		entry {
			hCat = false;
			hDog = false;
		}
		on M_hDog do { hDog = true; assert(!(hDog && hCat));};
		on M_hCat do { hCat = true; assert(!(hDog && hCat));};
		on M_rDog do { hDog = false;};
		on M_rCat do { hCat = false;};
	}
}

spec Prop_2 monitors M_hCat, M_rCat, M_hMice, M_rMice {
	var hCat : bool;
	var hMice : bool;
	
	start state Init {
		entry {
			hCat = false;
			hMice = false;
		}
		on M_hMice do { hMice = true; assert(!(hMice && hCat));};
		on M_hCat do { hCat = true; assert(!(hMice && hCat));};
		on M_rMice do { hMice = false;};
		on M_rCat do { hCat = false;};
	}	
}

spec Prop_6 monitors M_sDog, M_hCat, M_rCat, M_hDog {
	var hCat : bool;
	
	start state Init {
		entry {
			hCat = false;
			raise local;
		}
		on local goto Wait;
		
	}
	state Wait {
		on M_sDog do {if(!hCat) raise local;};
		on local goto Wait_M_hDog;
		on M_hCat do {hCat = true;};
		on M_rCat do {hCat = false;};
	}
	
	state Wait_M_hDog {
		on M_hDog goto Wait;
	}
}

spec Prop_7 monitors M_sDog, M_sCat, M_hDog, M_hDog {

	start state Init {
		entry {
			raise local;
		}
		on local goto Wait;
		
	}
	state Wait {
		on M_sDog goto WaitHDog;
		on M_sCat goto WaitHCat;
	}
	
	state WaitHDog {
		ignore M_sCat;
		on M_hDog goto Wait;
	}
	
	state WaitHCat {
		on M_hCat goto Wait;
		on M_sDog goto WaitHDog;
	}
}

spec Prop_8 monitors M_sCat, M_sMice, M_hCat, M_hMice {

	start state Init {
		entry {
			raise local;
		}
		on local goto Wait;
		
	}
	state Wait {
		on M_sCat goto WaitHCat;
		on M_sMice goto WaitHMice;
	}
	
	state WaitHCat {
		ignore M_sMice;
		on M_hCat goto Wait;
	}
	
	state WaitHMice {
		on M_hMice goto Wait;
		on M_sCat goto WaitHCat;
	}
}

spec Prop_9 monitors M_sCat, M_sDog, M_hMice, M_hCat, M_hDog, M_rMice {
	var hMice : bool;
	var sDog : bool;
	start state Init {
		entry {
			hMice = false;
			sDog = false;
			raise local;
		}
		on local goto Wait;
		
	}
	state Wait {
		on M_sCat do {if(hMice == false && sDog == false) raise local;};
		on M_sDog do {sDog = true;};
		on M_hDog do {sDog = false;};
		on local goto WaitHCat;
		on M_hMice do {hMice = true;};
		on M_rMice do {hMice = false;};
	}
	
	state WaitHCat {
		on M_hCat goto Wait;
	}
}

spec Prop_3 monitors M_hCat, M_hDog, M_hMice {
	var noAnimals : int;
	start state Init {
		entry {
			noAnimals = payload as int;
			raise local;
		}
		on local goto WaitForHerding;
	}
	
	hot state WaitForHerding {
		
		on M_hCat do {noAnimals = noAnimals - 1; if(noAnimals == 0) raise local;};
		on M_hDog do {noAnimals = noAnimals - 1; if(noAnimals == 0) raise local;};
		on M_hMice do {noAnimals = noAnimals - 1; if(noAnimals == 0) raise local;};
		on local goto Done;
	}
	
	state Done {
		
	}
}

spec Prop_10a monitors M_hDog, M_rDog {
	start state Init {
		on M_hDog goto WaitrDog;
	}
	
	hot state WaitrDog {
		on M_rDog goto Done;
	}
		
	state Done {
		
	}
}

spec Prop_10b monitors M_hCat, M_rCat {
	start state Init {
		on M_hCat goto WaitrCat;
	}
	
	hot state WaitrCat {
		on M_rCat goto Done;
	}
		
	state Done {
		
	}
}

spec Prop_10c monitors M_hMice, M_rMice {
	start state Init {
		on M_hMice goto WaitrMice;
	}
	
	hot state WaitrMice {
		on M_rMice goto Done;
	}
		
	state Done {
		
	}
}
