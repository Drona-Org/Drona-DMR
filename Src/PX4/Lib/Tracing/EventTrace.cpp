#include "stdafx.h"
#include "EventTrace.h"
#include <mutex>
#include <vector>

std::mutex EventTrace::_lock;

std::vector<EventListener*> EventTrace::_listeners;

extern "C"
{
	void EventTrace(int category, int eventId, const char* format, ...)
	{
		if (EventTrace::Listening(category, eventId))
		{
			static std::mutex mtx;
			mtx.lock();
			const int buflen = 8000;
			static char* buffer = (char*)malloc(buflen);
			va_list args;
			va_start(args, format);
			vsprintf_s(buffer, buflen, format, args);
			va_end(args);
			EventTrace::Write(category, eventId, buffer);
			mtx.unlock();
		}
	}
}
