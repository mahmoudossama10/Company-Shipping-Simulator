#include "Ready.h"

Ready::Ready(int Maxwaite, int PromoTime, Input* In)
	: Event('R')
{
	Max_Wait = Maxwaite;
	Promotion_Time = PromoTime;
	Type = In->ReadCharacter();
	Time = In->ReadDate();
	ID = In->ReadNumber();
	Distance = In->ReadNumber();
	LoadingTime = In->ReadNumber();
	Cost = In->ReadNumber();
	SetTime(Time);
}



Cargo* Ready::Execute(int Clock)
{
	if (Clock != GetTime())
	{
		return nullptr;
	}
	else
	{
		Cargo* C = nullptr;
		if (Type == 'N') {
			/*NormalCargo* N*/ C = new NormalCargo(Time, ID, Distance, LoadingTime, Cost, Max_Wait, Promotion_Time);
			//	NO.Insert(N);
			//LN.Insert(N);
		}

		if (Type == 'S') {
			/*SpecialCargo* S*/ C = new SpecialCargo(Time, ID, Distance, LoadingTime, Cost, Max_Wait);
			//SP.Enqueue(S);
		}
		if (Type == 'V') {
			/*VIPCargo* V*/ C = new VIPCargo(Time, ID, Distance, LoadingTime, Cost, Max_Wait);
			//LV.Enqueue(V);
		}
		return C;
	}
}

void Ready::PolymorphismAcheive()
{
	// Does Nothing But We Can Use Dynamic Cast
}
