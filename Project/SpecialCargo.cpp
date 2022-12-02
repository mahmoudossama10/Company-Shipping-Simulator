#include "SpecialCargo.h"

SpecialCargo::SpecialCargo(int ready_time, int id, int distance, int loading_time, int cost, int MaxWait)
	: Cargo(ready_time, id, distance, loading_time, cost, MaxWait, 'S')
{
}

void SpecialCargo::PolymorphismAcheive()
{
	// Does Nothing But We Can Use Dynamic Cast
}
