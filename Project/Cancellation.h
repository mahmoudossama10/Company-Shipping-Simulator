#pragma once

#include"Event.h"
#include"Input.h"

#include"NormalCargo.h"
#include"NormalCargoList.h"

class Cancellation :public Event
{
	int ID;
public:
	Cancellation(Input* In);
	int Execute(int clock);
	virtual void PolymorphismAcheive();
};