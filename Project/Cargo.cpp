#include "Cargo.h"

Cargo::Cargo(int ready_time, int id, int distance, int loading_time, int cost, int Maxwait, char type)
	: ReadyTime(ready_time), ID(id), Distance(distance), LoadingTime(loading_time), Cost(cost), MaxWait(Maxwait), Type(type)
{
	WaitingLimits = ready_time + MaxWait;
	StartMovingTime = -1;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Cargo::GetReady_Time()
{
	return ReadyTime;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Cargo::GetMaxWaitTime(int CurrentTime)
{
	return WaitingLimits;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Cargo::GetStartLoadingTime()
{
	return StartLoadingTime;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Cargo::GetEndLoadingTime()
{
	return EndLoadingTime;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Cargo::GetDeliveryTime()
{
	return DeliveredTime;
}
int Cargo::GetMovingTime()
{
	return StartMovingTime;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Cargo::GetID()
{
	return ID;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Cargo::GetDistance()
{
	return Distance;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Cargo::GetCost()
{
	return Cost;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Cargo::GetLoadingTime()
{
	return LoadingTime;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Cargo::GetMaxWait()
{
	return MaxWait;
}
int Cargo::GetTruckID()
{
	return TruckID;
}
char Cargo::GetType()
{
	return Type;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Cargo::Load(int CurrentTime)
{
	StartLoadingTime = CurrentTime;												// Set Start Loading Time With The Given Time
	EndLoadingTime = CurrentTime + LoadingTime;									// Add The Loading Time So We Get End Loading Time
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Cargo::SetDileveredTime(int Time)
{
	DeliveredTime = Time;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
bool Cargo::IsDelivered(int CurrentTime)
{
	return DeliveredTime <= CurrentTime;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Cargo::SetEndLoadingTime(int Time)
{
	EndLoadingTime = Time;
}
void Cargo::SetTruckID(int I)
{
	TruckID = I;
}
void Cargo::FailureHappened()
{
	StartLoadingTime = -1;
	EndLoadingTime = -1;
	DeliveredTime = -1;
}
void Cargo::SetStartJourneyTime(int CurrentTime)
{
	StartMovingTime = CurrentTime;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-