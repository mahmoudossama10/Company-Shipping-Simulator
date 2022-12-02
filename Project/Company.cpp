#include "Company.h"
// Priority Functions For Queues And Lists
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

bool PriorityEquation(VIPCargo* First, VIPCargo* Second)                 // Consider The Truck Average Speed Is 120 KM/H
{
	double TimeA = (First->GetDistance() / 120.0) + (2 * First->GetLoadingTime());
	double TimeB = (Second->GetDistance() / 120.0) + (2 * Second->GetLoadingTime());
	return (First->GetCost() / TimeA) > (Second->GetCost() / TimeB); // The Idea Here Is We Order Them by How Much Money Will The Company Gain For A Working Hour Of This Cargo
}

bool TruckSpeedAndCapacityPriorityEquationNormal(NormalTruck* A, NormalTruck* B)
{
	double TimeA = (120.0 / A->GetSpeed());
	double TimeB = (120.0 / B->GetSpeed());
	return (200 * A->GetMaxCapacity() / TimeA) > (200 * B->GetMaxCapacity() / TimeB);
}

bool TruckSpeedAndCapacityPriorityEquationSpecial(SpecialTruck* A, SpecialTruck* B)
{
	double TimeA = (120.0 / A->GetSpeed());
	double TimeB = (120.0 / B->GetSpeed());
	return (200 * A->GetMaxCapacity() / TimeA) > (200 * B->GetMaxCapacity() / TimeB);
}

bool TruckSpeedAndCapacityPriorityEquationVIP(VIPTruck* A, VIPTruck* B)
{
	double TimeA = (120.0 / A->GetSpeed());
	double TimeB = (120.0 / B->GetSpeed());
	return (200.0 * A->GetMaxCapacity() / TimeA) > (200.0 * B->GetMaxCapacity() / TimeB);
}

bool SortByEndLoadingTime(Truck* A, Truck* B)
{
	return A->GetEndLoadingTime() < B->GetEndLoadingTime();
}

bool SortByEndJourneyTime(Truck* A, Truck* B)
{
	return A->GetEndJourneyTime() > B->GetEndJourneyTime();
}

bool SortByEndCheckupTime(Truck* A, Truck* B)
{
	return A->GetEndMaintainanceTime() < B->GetEndMaintainanceTime();
}

bool SortByCargoDelivereyTime(Cargo* A, Cargo* B)
{
	return A->GetDeliveryTime() < B->GetDeliveryTime();
}

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

int Company::current_time = 24;

//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Company::Company()
{
	// Setting Priorities And Insertion Methods
	ready_vip_cargos.SetPriority(PriorityEquation);										
	loading_trucks.SetPriority(SortByEndLoadingTime);
	moving_trucks.SetSortingMethod(SortByEndJourneyTime);
	maintenance_trucks.SetPriority(SortByEndCheckupTime);
	delivered_cargos.SetPriority(SortByCargoDelivereyTime);
	normal_trucks.SetPriority(TruckSpeedAndCapacityPriorityEquationNormal);
	special_trucks.SetPriority(TruckSpeedAndCapacityPriorityEquationSpecial);
	vip_trucks.SetPriority(TruckSpeedAndCapacityPriorityEquationVIP);
	normal_trucks_night.SetPriority(TruckSpeedAndCapacityPriorityEquationNormal);
	special_trucks_night.SetPriority(TruckSpeedAndCapacityPriorityEquationSpecial);
	vip_trucks_night.SetPriority(TruckSpeedAndCapacityPriorityEquationVIP);
	//=======================================================================================
	Pin = new Input();
	Pout = new Output();
	Pout->PrintInfoMassage("Please Enter The File Number ===> ");
	int X = Pin->GetNumberFromIOStream();
	Pin->ChangeFile(X);
	Pout->ChangeOutputFile(X);
	OutMood = Pout->ChooseSimulationMood();
	Pin->Loadfilebonus(normal_trucks, special_trucks, vip_trucks, normal_trucks_night, special_trucks_night, vip_trucks_night, max_wait, promotion, TotalTrucks);
	TotalNormalCargos = 0;
	TotalSpecialCargos = 0;
	TotalNormal = 0;
	TotalSpecial = 0;
	TotalVip = 0;
	VIPCargos = 0;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Company::~Company()
{
	delete Pin;
	delete Pout;
	RemoveAllLists();
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Input* Company::GetInput()
{
	return Pin;
}
Output* Company::GetOutput()
{
	return Pout;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Company::GetMaxWait()
{
	return max_wait;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Company::GetPromotion()
{
	return promotion;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Company::GetCurrentSimTime()
{
	return current_time;
}
int Company::GetTotalTrucks()
{
	return TotalTrucks;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Company::tick()
{
	current_time++;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
bool Company::PrintInfos()
{
	if (OutMood == 1 || OutMood == 2)
	{
		Pout->PrintCurrentTime(current_time);
		// Waiting Cargos
		Pout->PrintWaitingCargos(ready_normal_cargos, ready_special_cargos, ready_vip_cargos);
		//Loading Trucks And Cargos
		Pout->PrintLoadingCargos(loading_trucks);
		Pout->PrintEmptyTrucks(normal_trucks, special_trucks, vip_trucks);
		Pout->PrintEmptyTrucks(normal_trucks_night, special_trucks_night, vip_trucks_night);
		//Moving Trucks And Cargos
		Pout->PrintMovingCargos(moving_trucks);
		//Delivered Cargos
		Pout->PrintDeliveredCargo(delivered_cargos);
		//In Checkup Trucks
		Pout->PrintInCheckUpTrucks(maintenance_trucks , External_Normal_Maintainance);
		Pout->PrintInCheckUpTrucks(External_Special_Maintainance, External_VIP_Maintainance);
		if (OutMood == 1)
			Pout->Mood(current_time);
		else
			Pout->Mood();
	}
	if (NoCheckupTrucks() && NoExternalCheckupTrucks('N') && NoExternalCheckupTrucks('S') && NoExternalCheckupTrucks('V') && NoMovingTrucks() && NoLoadingTruck())
		if (NoReadyCargos('N') && NoReadyCargos('S') && NoReadyCargos('V'))
			return false;
	return true;
}
void Company::Finish()
{
	Pout->FinishSimulation();
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Company::add_cargo(Cargo* cargo)
{
	// This Function Is Responsible For Adding A Cargo To Its Suitable List Depending On Its Type
	if (dynamic_cast<NormalCargo*>(cargo))										// If Normal
	{
		NormalCargo* normal = dynamic_cast<NormalCargo*>(cargo);				
		ready_normal_cargos.Insert(normal);										// Insert It To Ready Normal Cargos
		TotalNormalCargos++;													// Increament Number Of Normal Cargos
	}
	if (dynamic_cast<SpecialCargo*>(cargo))										// Is Special
	{
		SpecialCargo* special = dynamic_cast<SpecialCargo*>(cargo);
		ready_special_cargos.Enqueue(special);									// Add It To Ready Special Cargos
		TotalSpecialCargos++;													// Increament Number Of Special Cargos
	}
	if (dynamic_cast<VIPCargo*>(cargo))											// If VIP
	{
		VIPCargo* vip = dynamic_cast<VIPCargo*>(cargo);
		ready_vip_cargos.Enqueue(vip);											// Add It To Ready VIP List
		VIPCargos++;															// Increament Number Of Vip Cargos 
	}
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Company::remove_cargo(int id)
{
	// Responsible For Searching For Normal Cargos And Remove It From The List Of Ready Normal Cargos
	for (int i = 0; i < ready_normal_cargos.GetSize(); i++)						
	{
		NormalCargo* traverse = ready_normal_cargos.Get(i);
		if (traverse->GetID() == id)
		{
			ready_normal_cargos.Remove(traverse);
		}
	}
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
NormalCargo* Company::SearchNormalCargo(int id)
{
	// Responsible For Searching For A Normal Cargo By Its ID
	for (int i = 0; i < ready_normal_cargos.GetSize(); i++)
	{
		NormalCargo* traverse = ready_normal_cargos.Get(i);
		if (traverse->GetID() == id)
		{
			return traverse;
		}
	}
	return nullptr;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
// The Function That Follows Is Used To Access All Company Lists Indirectly So That It Becomes No Logic Class And All Logic Are Being Done Inside Simulator Class
Cargo* Company::DequeueFirstWaitingCargo(char Type)
{
	Cargo* cargo = NULL;
	switch (Type)
	{
	case 'N':
	{
		if (ready_normal_cargos.GetSize() > 0)
		{
			NormalCargo* normal = NULL;
			normal = ready_normal_cargos.Get(0);
			ready_normal_cargos.Remove(normal);
			cargo = normal;
		}
		break;
	}
	case 'S':
	{
		SpecialCargo* special = NULL;
		if (ready_special_cargos.Dequeue(special))
			cargo = special;
		break;
	}
	case 'V':
	{
		VIPCargo* vip = NULL;
		if (ready_vip_cargos.Dequeue(vip))
			cargo = vip;
		break;
	}
	}
	return cargo;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Cargo* Company::PeekFirstWaitingCargo(char Type)
{

	Cargo* cargo = NULL;
	switch (Type)
	{
	case 'N':
	{
		NormalCargo* normal;
		if (ready_normal_cargos.GetSize() > 0)
		{
			normal = ready_normal_cargos.Get(0);
			cargo = normal;
		}
		break;
	}
	case 'S':
	{
		SpecialCargo* special;
		if (ready_special_cargos.PeekFront(special))
			cargo = special;
		break;
	}
	case 'V':
	{
		VIPCargo* vip;
		if (ready_vip_cargos.PeekFront(vip))
			cargo = vip;
		break;
	}
	}
	return cargo;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
bool Company::NoReadyCargos(char Type)
{
	switch (Type)
	{
	case 'N': return ready_normal_cargos.IsEmpty();
	case 'S': return ready_special_cargos.IsEmpty();
	case 'V': return ready_vip_cargos.IsEmpty();
	}
}
int Company::CountWaitingCargo(char Type)
{
	switch (Type)
	{
	case 'N': return ready_normal_cargos.GetSize();
	case 'S': return ready_special_cargos.CountQueue();
	case 'V': return ready_vip_cargos.CountQueue();
	}
}
int Company::CountTotalCargos(char Type)
{
	switch (Type)
	{
	case 'N': return TotalNormalCargos;
	case 'S': return TotalSpecialCargos;
	case 'V': return VIPCargos;
	}
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Truck* Company::PeekLoadingTrucks()
{
	Truck* truck;
	if (loading_trucks.PeekFront(truck))
	{
		return truck;
	}
	else
	{
		return NULL;
	}
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Truck* Company::DequeueLoadingTrucks()
{
	Truck* truck;
	if (loading_trucks.Dequeue(truck))
	{
		return truck;
	}
	else
	{
		return NULL;
	}
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Company::EnqueueLoadingTrucks(Truck* Tr)
{
	loading_trucks.Enqueue(Tr);
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
bool Company::NoLoadingTruck()
{
	return loading_trucks.IsEmpty();
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Truck* Company::GetMovingTrucks(int Index)
{
	if (moving_trucks.IsEmpty() || Index >= moving_trucks.GetSize())
		return NULL;
	return moving_trucks.Get(Index);
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Company::RemoveMovingTrucks(Truck* Tr)
{
	moving_trucks.Remove(Tr);
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Company::AddMovingTrucks(Truck* Tr)
{
	moving_trucks.Insert(Tr);
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
bool Company::NoMovingTrucks()
{
	return moving_trucks.IsEmpty();
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Truck* Company::PeekCheckupTrucks()
{
	Truck* truck;
	if (maintenance_trucks.PeekFront(truck))
	{
		return truck;
	}
	else
	{
		return NULL;
	}
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Truck* Company::DequeueCheckupTrucks()
{
	Truck* truck;
	if (maintenance_trucks.Dequeue(truck))
	{
		return truck;
	}
	else
	{
		return NULL;
	}
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Company::EnqueueCheckupTrucks(Truck* Tr)
{
	maintenance_trucks.Enqueue(Tr);
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
bool Company::NoCheckupTrucks()
{
	return maintenance_trucks.IsEmpty();
}
Truck* Company::PeekExternalCheckupTrucks(char TruckType)
{
	Truck* Ptr = nullptr;
	switch (TruckType)
	{
	case 'N': External_Normal_Maintainance.PeekFront(Ptr); break;
	case 'S': External_Special_Maintainance.PeekFront(Ptr); break;
	case 'V': External_VIP_Maintainance.PeekFront(Ptr); break;
	}
	return Ptr;
}
Truck* Company::DequeueExternalCheckupTrucks(char TruckType)
{
	Truck* Ptr = nullptr;
	switch (TruckType)
	{
	case 'N': External_Normal_Maintainance.Dequeue(Ptr); break;
	case 'S': External_Special_Maintainance.Dequeue(Ptr); break;
	case 'V': External_VIP_Maintainance.Dequeue(Ptr); break;
	}
	return Ptr;
}
void Company::EnqueueExternalCheckupTrucks(Truck* Tr)
{
	if (Tr)
	{
		switch (Tr->GetType())
		{
		case 'N': External_Normal_Maintainance.Enqueue(Tr); break;
		case 'S': External_Special_Maintainance.Enqueue(Tr); break;
		case 'V': External_VIP_Maintainance.Enqueue(Tr); break;
		}
	}
}
bool Company::NoExternalCheckupTrucks(char TruckType)
{
	switch (TruckType)
	{
	case 'N': return External_Normal_Maintainance.IsEmpty();
	case 'S': return External_Special_Maintainance.IsEmpty();
	case 'V': return External_VIP_Maintainance.IsEmpty();
	}
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Truck* Company::PeekEmptyTrucks(char Type)
{
	Truck* truck;
	switch (Type)
	{
	case 'N':
		NormalTruck * normal;
		if (normal_trucks.PeekFront(normal))
		{
			truck = normal;
			return truck;
		}
		break;
	case 'S':
		SpecialTruck * special;
		if (special_trucks.PeekFront(special))
		{
			truck = special;
			return truck;
		}
		break;
	case 'V':
		VIPTruck * vip;
		if (vip_trucks.PeekFront(vip))
		{
			truck = vip;
			return truck;
		}
		break;
	}
	return NULL;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Truck* Company::DequeueEmptyTrucks(char Type)
{
	Truck* truck = NULL;
	switch (Type)
	{
	case 'N':
	{
		NormalTruck* normal;
		if (normal_trucks.Dequeue(normal))
			truck = normal;
		else
			truck = NULL;
		break;
	}
	case 'S':
	{
		SpecialTruck* special;
		if (special_trucks.Dequeue(special))
			truck = special;
		else
			truck = NULL;
		break;
	}
	case 'V':
	{
		VIPTruck* vip;

		if (vip_trucks.Dequeue(vip))
			truck = vip;
		else
			truck = NULL;
		break;
	}
	}
	return truck;
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Company::EnqueueEmptyTrucks(Truck* Tr)
{
	switch (Tr->GetType())
	{
	case 'N':
	{
		NormalTruck* normal = dynamic_cast<NormalTruck*>(Tr);
		normal_trucks.Enqueue(normal);
		break;
	}
	case 'S':
	{
		SpecialTruck* special = dynamic_cast<SpecialTruck*>(Tr);
		special_trucks.Enqueue(special);
		break;
	}
	case 'V':
	{
		VIPTruck* vip = dynamic_cast<VIPTruck*>(Tr);
		vip_trucks.Enqueue(vip);
		break;
	}
	}
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
bool Company::NoEmptyTrucks(char Type)
{
	switch (Type)
	{
	case 'N': return !normal_trucks.IsEmpty();
	case 'S': return !special_trucks.IsEmpty();
	case 'V': return !vip_trucks.IsEmpty();
	}
}
int Company::CountEmptyTrucks(char Type)
{
	switch (Type)
	{
	case 'N': return normal_trucks.CountQueue();
	case 'S': return special_trucks.CountQueue();
	case 'V': return vip_trucks.CountQueue();
	}
}
Truck* Company::PeekEmptyNightTrucks(char Type)
{
	Truck* truck;
	switch (Type)
	{
	case 'N':
		NormalTruck * normal;
		if (normal_trucks_night.PeekFront(normal))
		{
			truck = normal;
			return truck;
		}
		break;
	case 'S':
		SpecialTruck * special;
		if (special_trucks_night.PeekFront(special))
		{
			truck = special;
			return truck;
		}
		break;
	case 'V':
		VIPTruck * vip;
		if (vip_trucks_night.PeekFront(vip))
		{
			truck = vip;
			return truck;
		}
		break;
	}
	return NULL;
}
Truck* Company::DequeueEmptyNightTrucks(char Type)
{
	Truck* truck = NULL;
	switch (Type)
	{
	case 'N':
	{
		NormalTruck* normal;
		if (normal_trucks_night.Dequeue(normal))
			truck = normal;
		else
			truck = NULL;
		break;
	}
	case 'S':
	{
		SpecialTruck* special;
		if (special_trucks_night.Dequeue(special))
			truck = special;
		else
			truck = NULL;
		break;
	}
	case 'V':
	{
		VIPTruck* vip;

		if (vip_trucks_night.Dequeue(vip))
			truck = vip;
		else
			truck = NULL;
		break;
	}
	}
	return truck;
}
void Company::EnqueueEmptyNightTrucks(Truck* Tr)
{
	switch (Tr->GetType())
	{
	case 'N':
	{
		NormalTruck* normal = dynamic_cast<NormalTruck*>(Tr);
		normal_trucks_night.Enqueue(normal);
		break;
	}
	case 'S':
	{
		SpecialTruck* special = dynamic_cast<SpecialTruck*>(Tr);
		special_trucks_night.Enqueue(special);
		break;
	}
	case 'V':
	{
		VIPTruck* vip = dynamic_cast<VIPTruck*>(Tr);
		vip_trucks_night.Enqueue(vip);
		break;
	}
	}
}
bool Company::NoEmptyNightTrucks(char Type)
{
	switch (Type)
	{
	case 'N': return !normal_trucks_night.IsEmpty();
	case 'S': return !special_trucks_night.IsEmpty();
	case 'V': return !vip_trucks_night.IsEmpty();
	}
}
int Company::CountEmptyNightTrucks(char Type)
{
	switch (Type)
	{
	case 'N': return normal_trucks_night.CountQueue();
	case 'S': return special_trucks_night.CountQueue();
	case 'V': return vip_trucks_night.CountQueue();
	}
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Company::EnqueueDelivered(Cargo* C)
{
	delivered_cargos.Enqueue(C);
}
Cargo* Company::DequeueDelivered()
{
	Cargo* Ptr = NULL;
	if (!delivered_cargos.IsEmpty())
		delivered_cargos.Dequeue(Ptr);
	return Ptr;
}
bool Company::NoDeliveredCargos()
{
	return delivered_cargos.IsEmpty();
}
//-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-




void Company::RemoveAllLists()
{
	while (!ready_special_cargos.IsEmpty())
	{
		SpecialCargo* Ptr;
		ready_special_cargos.Dequeue(Ptr);
		delete Ptr;
	}
	while (!ready_vip_cargos.IsEmpty())
	{
		VIPCargo* Ptr;
		ready_vip_cargos.Dequeue(Ptr);
		delete Ptr;
	}
	while (!normal_trucks.IsEmpty())
	{
		NormalTruck* Ptr;
		normal_trucks.Dequeue(Ptr);
		delete Ptr;
	}
	while (!special_trucks.IsEmpty())
	{
		SpecialTruck* Ptr;
		special_trucks.Dequeue(Ptr);
		delete Ptr;
	}
	while (!vip_trucks.IsEmpty())
	{
		VIPTruck* Ptr;
		vip_trucks.Dequeue(Ptr);
		delete Ptr;
	}
	while (!loading_trucks.IsEmpty())
	{
		Truck* Ptr;
		loading_trucks.Dequeue(Ptr);
		delete Ptr;
	}
	while (!maintenance_trucks.IsEmpty())
	{
		Truck* Ptr;
		maintenance_trucks.Dequeue(Ptr);
		delete Ptr;
	}
	while (!delivered_cargos.IsEmpty())
	{
		Cargo* Ptr;
		delivered_cargos.Dequeue(Ptr);
		delete Ptr;
	}
	while (!ready_normal_cargos.IsEmpty())
	{
		NormalCargo* Ptr = ready_normal_cargos.Get(0);
		ready_normal_cargos.Remove(Ptr);
		delete Ptr;
	}
	while (!moving_trucks.IsEmpty())
	{
		Truck* Tr = moving_trucks.Get(0);
		Tr->DeleteAllCargos();
		moving_trucks.Remove(Tr);
		delete Tr;
	}
}

void Company::CheckFailureJourneys()
{
	for (int i = 0; i < moving_trucks.GetSize(); i++)
	{
		CargoList Temp;
		if (moving_trucks.Get(i)->EngineFailure(Temp, current_time))
		{
			Truck* Tr = moving_trucks.Get(i);
			for (int i = 0; i < Temp.GetSize(); i++)
				add_cargo(Temp.Get(i));
			moving_trucks.Remove(Tr);
			EnqueueCheckupTrucks(Tr);
			string ErrMsg = "Engine Failure For Truck Number " + to_string(Tr->GetID()) + " All Its Non Delivered Cargos Will Be Back Soon ...";
			Pout->PrintErrMassage(ErrMsg);
		}
	}
}

void Company::GetTruckStatistics(int& TotalActive, double& TotalUse)
{
	TotalActive = 0;
	TotalUse = 0;
	while (!normal_trucks.IsEmpty())
	{
		Truck* Tr = DequeueEmptyTrucks('N');
		TotalActive += Tr->GetActiveTime();
		TotalUse += Tr->CalculateTruckUtilization(current_time);
	}
	while (!special_trucks.IsEmpty())
	{
		Truck* Tr = DequeueEmptyTrucks('S');
		TotalActive += Tr->GetActiveTime();
		TotalUse += Tr->CalculateTruckUtilization(current_time);
	}
	while (!vip_trucks.IsEmpty())
	{
		Truck* Tr = DequeueEmptyTrucks('V');
		TotalActive += Tr->GetActiveTime();
		TotalUse += Tr->CalculateTruckUtilization(current_time);
	}
	while (!normal_trucks_night.IsEmpty())
	{
		Truck* Tr = DequeueEmptyNightTrucks('N');
		TotalActive += Tr->GetActiveTime();
		TotalUse += Tr->CalculateTruckUtilization(current_time);
	}
	while (!special_trucks_night.IsEmpty())
	{
		Truck* Tr = DequeueEmptyNightTrucks('S');
		TotalActive += Tr->GetActiveTime();
		TotalUse += Tr->CalculateTruckUtilization(current_time);
	}
	while (!vip_trucks_night.IsEmpty())
	{
		Truck* Tr = DequeueEmptyNightTrucks('V');
		TotalActive += Tr->GetActiveTime();
		TotalUse += Tr->CalculateTruckUtilization(current_time);
	}
}


