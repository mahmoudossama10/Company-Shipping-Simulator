#include "Cancellation.h"

Cancellation::Cancellation(Input* In)
	:Event('X')
{
	int Time = In->ReadDate();
	SetTime(Time);
	ID = In->ReadNumber();
}

int Cancellation::Execute(int clock)
{
	if (clock != GetTime())
	{
		return -1;
	}
	else
	{
		return ID;
	}
}



void Cancellation::PolymorphismAcheive()
{
	// Does Nothing But We Can Use Dynamic Cast
}
