#include "SpecialTruck.h"

SpecialTruck::SpecialTruck(int speed, int capacity, int max_journeys, int maintaince_time, int ID, char s)
	: Truck(speed, capacity, max_journeys, maintaince_time, ID, 'S', s)
{

}

void SpecialTruck::PolymorphismAcheive()
{
	// Does Nothing But We Can Use Dynamic Cast
}
