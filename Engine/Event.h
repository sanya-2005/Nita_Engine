#pragma once
#include "utils.h"
#include "INonCopyable.h"
#include <queue>

enum Keys
{
	A = 0x41,
	S = 0x53,
	D = 0x44,
	W = 0x57
};

enum EventTypes
{
	ResizeEvent,
	CloseEvent,
};

class IEventData
{
public:
	IEventData() = default;
	virtual ~IEventData() {};
};

class ResizeEventData : public IEventData
{
public:
	Size newSize;
};

class Event : public INonCopyable
{
private:
	IEventData* data;
	EventTypes type;

public:
	Event(IEventData* data, EventTypes type);
	~Event();

	EventTypes GetEventType();
	IEventData* GetEventData();
};

class OSEventQueue
{
private:
	std::queue<Event*> events;

public:
	Event* GetEvent();
	
	void AddEvent(Event* event);
	bool IsEvents();
};
