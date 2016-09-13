#pragma once

class EventListener
{
public:
	virtual void Write(int category, int eventId, const char* msg) = 0;
};
