#pragma once
#include "Cargo.h"
#include "NormalCargo.h"
class VIPCargo : public Cargo
{
public:
	VIPCargo(int ready_time, int id, int distance, int loading_time, int cost, int MaxWait);
	VIPCargo(NormalCargo* normal_cargo);
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	virtual void PolymorphismAcheive();
};