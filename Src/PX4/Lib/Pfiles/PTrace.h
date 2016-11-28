#pragma once

#include "EventTrace.h"

enum EventCategories {
	PRuntime, // eventId=PRT_STATUS
	Mavlink, // eventId=Mavlink message Id
	Communication, // eventId=HRESULT
	PProgram // eventId not used
};

