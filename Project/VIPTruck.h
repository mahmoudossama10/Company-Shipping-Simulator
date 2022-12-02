#pragma once
#include "Truck.h"
class VIPTruck : public Truck
{
public:
	VIPTruck(int speed, int capacity, int max_journeys, int maintaince_time, int ID, char s);
	virtual void PolymorphismAcheive();
};