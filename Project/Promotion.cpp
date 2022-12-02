#include "Promotion.h"

Promotion::Promotion(int MaxWait, Input* In)
	: Event('P')
{
	Max_Wait = MaxWait;
	int Time = In->ReadDate();
	SetTime(Time);
	ID = In->ReadNumber();
	Cost = In->ReadNumber();
}



void Promotion::PolymorphismAcheive()
{
	// Does Nothing But We Can Use Dynamic Cast
}

int Promotion::Execute(int clock,int& Cost)
{
	NormalCargo* X = nullptr;
	//Queue<NormalCargo*> temp;
	if (clock != GetTime())
	{
		return false;
	}
	else
	{
		Cost = this->Cost;
		return ID;
	}
}

