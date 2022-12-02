#pragma once
#include "Cargo.h"
class SpecialCargo : public Cargo
{
public:
	SpecialCargo(int ready_time, int id, int distance, int loading_time, int cost, int MaxWait);
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	virtual void PolymorphismAcheive();
};