#include "Event.h"

Event::Event(char t)
{
	type = t;
}

void Event::SetTime(int t)
{
	time = t;
}

char Event::GetType()
{
	return type;
}

int Event::GetTime()
{
	return time;
}
