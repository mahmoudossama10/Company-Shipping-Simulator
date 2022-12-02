#include "NormalTruck.h"

NormalTruck::NormalTruck(int speed, int capacity, int max_journeys, int maintaince_time, int ID,char s)
	: Truck(speed, capacity, max_journeys, maintaince_time, ID, 'N', s)
{

}

void NormalTruck::PolymorphismAcheive()
{
	// Does Nothing But We Can Use Dynamic Cast
}
