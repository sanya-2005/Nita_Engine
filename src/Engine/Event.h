#pragma once
#include "EngineCore/Types.h"
#include "NonCopyable.h"
#include <queue>

enum EventTypes
{
	ResizeEvent,
	CloseEvent,
    ActivateWindowEvent,
    DeactivateWindowEvent
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

class Event : public NonCopyable
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
