#pragma once
#include "Cargo.h"
class NormalCargo : public Cargo
{
	int PromotionTime;
public:
	NormalCargo(int ready_time, int id, int distance, int loading_time, int cost, int MaxWait, int MaxPromotion);
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	int GetPromotionTime();
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	virtual void PolymorphismAcheive();
};