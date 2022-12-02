#pragma once

#include "Event.h"
#include "Input.h"

#include "NormalCargo.h"
#include "VIPCargo.h"

#include "Queue.h"
#include "NormalCargoList.h"

class Promotion :public Event
{
	int ID;
	int Cost;
	int Max_Wait;
public:
	Promotion(int MaxWait, Input* In);
	int Execute(int clock, int& Cost);
	virtual void PolymorphismAcheive();
};