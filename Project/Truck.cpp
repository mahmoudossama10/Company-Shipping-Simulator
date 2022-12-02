#include "Truck.h"
#include <iostream>
bool SortByDistance(Cargo* A, Cargo* B)
{
	return A->GetDistance() < B->GetDistance();
}
Truck::Truck(int speed, int capacity, int max_journeys, int maintaince_time, int Id, char T, char s)
	: MaxSpeed(speed), Capacity(capacity), MaxJourneys(max_journeys), MaintainceTime(maintaince_time), ID(Id), Type(T), FailurePropability(FailureProb)
	, ExternalCheckup(ExternalCheck), NightShift(s == 'N')
{
	Speed = MaxSpeed;
	ActiveTime = 0;
	TotalDeliveredCargos = 0;
	Journeys = 0;
	DeliveryInterval = -1;
	CurrentCapacity = 0;
	MaxDistance = -1;
	BackAvailable();
	Load.SetSortingMethod(SortByDistance);
	NeedMaintainance = false;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
//	#		#		#		#		#		#		#		#		#		#
//		#		#		#		#		#		#		#		#		#		#
//								Getter Section
//	#		#		#		#		#		#		#		#		#		#
//		#		#		#		#		#		#		#		#		#		#
int Truck::GetSpeed()
{
	return Speed;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Truck::GetID()
{
	return ID;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
char Truck::GetType()
{
	return Type;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Truck::GetMaxCapacity()
{
	return Capacity;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Truck::GetCurrentCapacity()
{
	return CurrentCapacity;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
bool Truck::IsFullyLoaded()
{
	return CurrentCapacity == Capacity;
}
bool Truck::IsNightShift()
{
	return NightShift;
}
char Truck::GetLoadType()
{
	return Load.Get(0)->GetType();
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Truck::GetLoadId(int Index)
{
	return Load.Get(Index)->GetID();
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Cargo* Truck::CheckDeliveredCargos(int CurrentTime)
{
	Cargo* Temp;
	int OldCapacity = CurrentCapacity;
	for (int i = 0; i < OldCapacity; i++)
	{
		Temp = Load.Get(i);
		if (Temp->IsDelivered(CurrentTime))
		{
			Load.Remove(Temp);
			CurrentCapacity--;
			TotalDeliveredCargos++;
			return Temp;
		}
	}
	return nullptr;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Truck::GetEndLoadingTime()
{
	return EndLoadingTime;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Truck::GetEndJourneyTime()
{
	return EndJourneyTime;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Truck::GetEndMaintainanceTime()
{
	return EndMaintainance;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
bool Truck::FinishJourney(int CurrentTime)
{
	return CurrentTime >= EndJourneyTime;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
bool Truck::StartJourney(int CurrentTime)
{
	return CurrentTime >= EndLoadingTime;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
bool Truck::FinishedMaintainance(int CurrentTime)
{
	return CurrentTime >= EndMaintainance;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
//	#		#		#		#		#		#		#		#		#		#
//		#		#		#		#		#		#		#		#		#		#
//						Time Mangment Functions
//	#		#		#		#		#		#		#		#		#		#
//		#		#		#		#		#		#		#		#		#		#
void Truck::LoadCargo(Cargo* L, int CurrentTime)
{
	// This Is The Normal Assignment 
	// We Enqueue The Given Cargo To The Load List And Wait Start Loading To Be Called
	Load.Insert(L);
	L->SetTruckID(ID);
	CurrentCapacity++;
}
void Truck::LoadAdditionalCargo(Cargo* L, int CurrentTime)
{
	// This Function Is For The Bonus Part
	// It Will Be Used To Load An Additional Cargo To The Truck Which Has Started Loading
	Load.Insert(L);
	L->SetTruckID(ID);
	CurrentCapacity++;

	L->Load(EndLoadingTime + L->GetLoadingTime());
	EndLoadingTime += L->GetLoadingTime();

}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Truck::StartLoading(int CurrentTime)
{
	// This Function Is Responible To Set The Time Of End Loading Of The Truck And End Loading Time Of Each Cargo
	// This Time Will Be Needed When We Start The Journey As We Will Need To Know When The Loading Will End
	StartLoadingTime = CurrentTime;
	int TotalLoadingTime = 0;
	int Time = CurrentTime;
	bool ExtraTime = false;
	for (int i = 0; i < CurrentCapacity; i++)
	{
		Cargo* CurrentCargo = Load.Get(i);
		int CargoLoadingTime = CurrentCargo->GetLoadingTime();
		CurrentCargo->Load(Time);
		if (ExtraTime)
		{
			CurrentCargo->SetEndLoadingTime(CurrentCargo->GetEndLoadingTime() + 6);
			ExtraTime = false;
		}
		if ((Time % 24) + (CargoLoadingTime % 24) <= 23)
		{
			Time += CargoLoadingTime;
		}
		else
		{
			int TempTime = 23 - (Time % 24);
			Time += TempTime + 6 + (CargoLoadingTime - TempTime);
			ExtraTime = true;
		}
	}
	EndLoadingTime = Time;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Truck::StartMoving(int CurrentTime)
{
	// This Function Is Responisble Of Setting The Journey Time Of The Truck
	// It Also Set The Delivery Time For Each Cargo
	CurrentJourneyTime = CurrentTime;
	int MaxDistance = 0;
	int TotalUnLoadingTime = 0;
	Cargo* Ptr;
	int DeliveryTime = CurrentTime;
	int PrevDis = -1;
	for (int i = 0; i < CurrentCapacity; i++)
	{
		Ptr = Load.Get(i);
		Ptr->SetStartJourneyTime(CurrentTime);
		int Distance = Ptr->GetDistance();
		if (Distance != PrevDis)                                   // If The Current Distance Is The Same As The Previous One 
																   // This Means They Have The Same Destination
																   // Thus We Will Add Only The Unloading Time
			DeliveryTime += ((Distance-PrevDis) / Speed);
		DeliveryTime += (Ptr->GetLoadingTime());				   // Add The Unloading Time To The Jouney Time
		Ptr->SetDileveredTime(DeliveryTime);					   // Set The Delivery Time Of The Cargo With The Total Time
		MaxDistance = MaxDistance > Ptr->GetDistance() ? MaxDistance : Ptr->GetDistance();	// Get The MaxDistance
		TotalUnLoadingTime += Ptr->GetLoadingTime();
		PrevDis = Distance;
	}
	DeliveryInterval = CurrentTime + (MaxDistance / Speed) + TotalUnLoadingTime;
	ActiveTime += DeliveryInterval - StartLoadingTime;
	EndJourneyTime = CurrentTime + 2 * (MaxDistance / Speed) + TotalUnLoadingTime;
	Journeys++;
	if (Journeys % MaxJourneys == 0)
		NeedMaintainance = true;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
bool Truck::NeedCheckUp()
{
	return NeedMaintainance;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Truck::GoServices(int CurrentTime)
{
	StartMaintainance = CurrentTime;
	EndMaintainance = StartMaintainance + MaintainceTime;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Truck::BackAvailable()
{
	// Set All Truck Values To Its Initial Values
	StartLoadingTime = -1;
	EndLoadingTime = -1;
	CurrentJourneyTime = -1;
	EndJourneyTime = -1;
	StartMaintainance = -1;
	EndMaintainance = -1;
	DeliveryInterval = -1;
	NeedMaintainance = false;
	CurrentCapacity = 0;
}
void Truck::DeleteAllCargos()
{
	while (!Load.IsEmpty())
	{
		Cargo* Ptr = Load.Get(0);
		Load.Remove(Ptr);
		delete Ptr;
	}
}
bool Truck::EngineFailure(CargoList& L, int CurrentTime)
{
	// This Is The Last Bonus
	// Here We Set A Value Of Probabilty Of Engine Failure Say 50
	// We Randomize A Number If Its Greater Than 50 Then The Engine Has Failed
	// We Fill The Given List With The Cargos That Wasn't Delivered To Put It Back To Waiting Cargos
	// The Truck Is Moved To Maintainance 
	srand(time(0));
	int Prob = rand() % 100 + 1;
	if (Prob <= FailurePropability)
	{
		for (int i = 0; i < Load.GetSize(); i++)
		{
			L.Insert(Load.Get(i));
			Load.Remove(Load.Get(i));
		}
		GoServices(CurrentTime);
		return true;
	}
	else
	{
		return false;
	}
}
bool Truck::NeedExternalCheckUp(int CurrentTime)
{
	srand(time(0));
	int Random = rand() % 100 + 1;
	if (Random <= ExternalCheckup)
	{
		GoServices(CurrentTime);
		return true;
	}
	return false;
}
void Truck::DecreaseSpeed()
{
	Speed = MaxSpeed / 2;
}
int Truck::GetActiveTime()
{
	return ActiveTime;
}
double Truck::CalculateTruckUtilization(int CurrentTime)
{
	double TU;
	if (Journeys == 0 || CurrentTime == 0)
		return 0;
	TU = double(TotalDeliveredCargos) / double((Capacity * Journeys));
	TU *= double((ActiveTime)) / double((CurrentTime));
	return TU;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

