#pragma once

#include <stdio.h>
#include <Windows.h>
#include "EventTrace.h"

class EventLog : EventListener
{
private:
	FILE* ptr;
public:
	EventLog(char* filename)
	{
		fopen_s(&ptr, filename, "a");
		EventTrace::AddListener(this);
	}
	~EventLog()
	{
		fclose(ptr);
		EventTrace::RemoveListener(this);
	}

	void Write(int category, int eventId, const char* msg)
	{
		// write message to a file, with each record prepended with a timestamp, and the message category, id.
		if (ptr != NULL)
		{
			static std::mutex _lock;
			_lock.lock();
			fprintf(ptr, "%ld, %d, %d, %s", GetTickCount(), category, eventId, msg);
			fflush(ptr);
			OutputDebugStringA(msg);
			_lock.unlock();
		}
	}
};