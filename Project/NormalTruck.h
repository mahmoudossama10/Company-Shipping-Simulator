#pragma once
#include "Truck.h"
class NormalTruck : public Truck
{
public:
	NormalTruck(int speed, int capacity, int max_journeys, int maintaince_time, int ID, char s);
	virtual void PolymorphismAcheive();
};