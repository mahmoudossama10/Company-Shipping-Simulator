#pragma once
#include "Input.h"
#include "Cargo.h"
class Event {
	char type;
	int  time;
	Input* In;
public:
	Event(char t);
	void SetTime(int t);
	char GetType();
	int GetTime();
	virtual void PolymorphismAcheive() = 0;
};