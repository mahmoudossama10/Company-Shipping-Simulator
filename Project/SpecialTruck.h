#pragma once
#include "Truck.h"
class SpecialTruck : public Truck
{
public:
	SpecialTruck(int speed, int capacity, int max_journeys, int maintaince_time, int ID, char s);
	virtual void PolymorphismAcheive();
};