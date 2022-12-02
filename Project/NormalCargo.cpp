#include "NormalCargo.h"

NormalCargo::NormalCargo(int ready_time, int id, int distance, int loading_time, int cost, int MaxWait, int MaxPromotion)
	: Cargo(ready_time, id, distance, loading_time, cost, MaxWait, 'N')
{
	PromotionTime = ready_time + (MaxPromotion * 24);
}

int NormalCargo::GetPromotionTime()
{
	return PromotionTime;
}

void NormalCargo::PolymorphismAcheive()
{
	// Does Nothing But We Can Use Dynamic Cast
}
