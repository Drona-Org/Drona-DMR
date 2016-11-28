#pragma once

#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>
#include <mutex>
#include <vector>
#include "EventListener.h"

class EventTrace
{
public:
	static inline bool Listening(int category, int eventId)
	{
		return _listeners.size() > 0;
	}

	static void Write(int category, int eventId, const char* msg)
	{
		for (auto iter = _listeners.begin(); iter < _listeners.end(); iter++)
		{
			EventListener* listener = *iter;
			listener->Write(category, eventId, msg);
		}
	}

	static void AddListener(EventListener* listener)
	{
		_lock.lock();
		_listeners.push_back(listener);
		_lock.unlock();
	}

	static void RemoveListener(EventListener* listener)
	{
		_lock.lock();
		for (auto iter = _listeners.begin(); iter < _listeners.end(); iter++)
		{
			EventListener* it = *iter;
			if (it == listener)
			{
				_listeners.erase(iter);
				break;
			}
		}
		_lock.unlock();
	}

private:
	static std::mutex _lock;
	static std::vector<EventListener*> _listeners;
};

extern "C"
{
	void EventTrace(int category, int eventId, const char* format, ...);
}



