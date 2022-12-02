#include "VIPCargo.h"

VIPCargo::VIPCargo(int ready_time, int id, int distance, int loading_time, int cost, int MaxWait)
	: Cargo(ready_time, id, distance, loading_time, cost, MaxWait, 'V')
{

}


VIPCargo::VIPCargo(NormalCargo* normal_cargo) : Cargo(normal_cargo->GetReady_Time(), normal_cargo->GetID(), normal_cargo->GetDistance(), normal_cargo->GetLoadingTime(), normal_cargo->GetCost(), normal_cargo->GetMaxWait(), 'V')
{

}

void VIPCargo::PolymorphismAcheive()
{
	// Does Nothing But We Can Use Dynamic Cast
}
