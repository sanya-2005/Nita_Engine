#include "Event.h"

Event::Event(IEventData* data, EventTypes type)
{
	this->data = data;
	this->type = type;
}

Event::~Event()
{
	delete data;
}

EventTypes Event::GetEventType()
{
	return type;
}

IEventData* Event::GetEventData()
{
	return data;
}

Event* OSEventQueue::GetEvent()
{
	Event* event = events.front();
	events.pop();

	return event;
}

void OSEventQueue::AddEvent(Event* event)
{
	events.push(event);
}

bool OSEventQueue::IsEvents()
{
	return events.size() != 0;
}
