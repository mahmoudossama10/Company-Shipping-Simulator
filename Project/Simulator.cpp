#include "Simulator.h"
Simulator::Simulator()
{
	C = new Company;
	max_wait = C->GetMaxWait();
	promotion = C->GetPromotion();
	NumOfPromotedCargos = 0;
	TotalCargosNumber = 0;
	TotalNormal = 0;
	TotalSpecial = 0;
	TotalVIP = 0;
	NormalLoading = false;
	SpecialLoading = false;
	VIPLoading = false;
	read_events();
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Simulator::~Simulator()
{
	delete C;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::read_events()
{
	// This Function Being Called When The Company Is Constructed
	// It's Responsible For Reading All Info About Events And Enqueue It Inside Events Queue
	Input* Pin = C->GetInput();
	number_of_events = Pin->ReadNumber();										// Read The Number Of Events From File
	char event_type;
	Event* fvent = NULL;
	for (int i = 0; i < number_of_events; i++)
	{
		event_type = Pin->ReadCharacter();
		switch (event_type)
		{
		case 'R': fvent = new Ready(max_wait, promotion, Pin); break;			// Ready Event
		case 'X': fvent = new Cancellation(Pin); break;							// Cancellation Event
		case 'P': fvent = new Promotion(max_wait, Pin); break;					// Promotion Event
		}
		events_list.Enqueue(fvent);
	}
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::assign_cargos_to_truck()
{
	int current_time = C->GetCurrentSimTime();												// Get The Current Time
	if (C->NoReadyCargos('N') && C->NoReadyCargos('V') && C->NoReadyCargos('S'))
		return;
	if ((current_time % 24) % 5 == 0)
	{
		if (C->NoEmptyTrucks('N'))
		{
			Truck* Ptr = C->DequeueEmptyTrucks('N');
			if (!C->NoReadyCargos('N'))
			{
				Cargo* CPtr = C->DequeueFirstWaitingCargo('N');
				Ptr->LoadCargo(CPtr, current_time);
			}
			if (!C->NoReadyCargos('S'))
			{
				Cargo* SPtr = C->DequeueFirstWaitingCargo('S');
				Ptr->LoadCargo(SPtr, current_time);
			}
			if (!C->NoReadyCargos('V'))
			{
				Cargo* VPtr = C->DequeueFirstWaitingCargo('V');
				Ptr->LoadCargo(VPtr, current_time);
			}
			if (Ptr->GetCurrentCapacity() > 0)
			{
				Ptr->StartLoading(current_time);
				C->EnqueueLoadingTrucks(Ptr);
			}
		}
	}
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Truck* Simulator::GetSuitableTruck(char CargoType)
{
	// This Function Is Resposible For Getting Suitable Truck For The Cargo Assignment
	// A Suitable Truck Vary Depending On The Load Type And The Hour Of The Assigned
	// It Checks The Cargo Type And Depending On It Retruns A Truck For It

	int CurrentTime = C->GetCurrentSimTime();
	if ((CurrentTime % 24) >= 5 && (CurrentTime % 24) <= 23)								// If The Company Is Morning
	{
		Truck* VTruck = C->PeekEmptyTrucks('V');											// Get First Ready VIP Truck
		Truck* STruck = C->PeekEmptyTrucks('S');											// Get First Ready Special Truck
		Truck* NTruck = C->PeekEmptyTrucks('N');											// Get First Ready Normal Truck
		switch (CargoType)
		{
		case 'N':			// If The Cargo Is Normal Cargo
		{
			if (NTruck)		// And There Is Normal Truck
			{
				return C->DequeueEmptyTrucks('N');		// Return It
			}
			else
				if (VTruck)								// If There Is A Vip Truck
					return C->DequeueEmptyTrucks('V');  // Return It
				else
					return 	GetSuitableNightTruck(CargoType);					// If There Is Neither Normal Nor Vip Return Null ( No Suitable Truck Available)
		}
		case 'S':										// If It's Special Cargo
		{
			if (STruck)									// And There is a special Truck
			{
				return C->DequeueEmptyTrucks('S');		// Return It
			}
			else
				return GetSuitableNightTruck(CargoType);							// If Not Return NULL
		}
		case 'V':										// If The Cargo Is Vip
		{
			if (VTruck)									// And There Is Vip Truck
			{
				return C->DequeueEmptyTrucks('V');		// Return It
			}
			else
				if (NTruck)								// If There Is Normal Truck
					return C->DequeueEmptyTrucks('N');  // Return It
				else if (STruck)
					return C->DequeueEmptyTrucks('S');	// If There Is Special Truck, Return It
				else
					return GetSuitableNightTruck(CargoType);						// If There is No Suitable Truck, Try To Check The Night Trucks
		}
		}
	}
	else																			// If The Company Is In Nights
	{
		return GetSuitableNightTruck(CargoType);									// Check Night Trucks If Available
	}
}
Truck* Simulator::GetSuitableNightTruck(char CargoType)
{
	// if Night
	// This Function Is Resposible For Getting Suitable Night Truck For The Cargo Assignment
	// It Checks The Cargo Type And Depending On It Retruns A Truck For It
	Truck* VTruck = C->PeekEmptyNightTrucks('V');											// Get First Ready VIP Truck
	Truck* STruck = C->PeekEmptyNightTrucks('S');											// Get First Ready Special Truck
	Truck* NTruck = C->PeekEmptyNightTrucks('N');											// Get First Ready Normal Truck
	switch (CargoType)
	{
	case 'N':			// If The Cargo Is Normal Cargo
	{
		if (NTruck)		// And There Is Normal Truck
		{
			return C->DequeueEmptyNightTrucks('N');		// Return It
		}
		else
			if (VTruck)								// If There Is A Vip Truck
				return C->DequeueEmptyNightTrucks('V');  // Return It
			else
				return NULL;						// If There Is Neither Normal Nor Vip Return Null ( No Suitable Truck Available)
	}
	case 'S':										// If It's Special Cargo
	{
		if (STruck)									// And There is a special Truck
		{
			return C->DequeueEmptyNightTrucks('S');		// Return It
		}
		else
			return NULL;							// If Not Return NULL
	}
	case 'V':										// If The Cargo Is Vip
	{
		if (VTruck)									// And There Is Vip Truck
		{
			return C->DequeueEmptyNightTrucks('V');		// Return It
		}
		else
			if (NTruck)								// If There Is Normal Truck
				return C->DequeueEmptyNightTrucks('N');  // Return It
			else if (STruck)
				return C->DequeueEmptyNightTrucks('S');
			else
				return NULL;						// If There is No Suitable Truck Return NUll
	}
	}
}
Truck* Simulator::GetSuitableMaxWaitTruck(char CargoType)
{
	// The Difference Is That It May Get A Truck From The External Check UP To Be Assigned
	// That Happens If There Wasn't Any Available Truck That Is Ready
	Truck* Ptr = nullptr;
	Ptr = GetSuitableTruck(CargoType);
	if (Ptr)
		return Ptr;
	else
	{
		Ptr = C->DequeueExternalCheckupTrucks(CargoType);
		if (Ptr)
			Ptr->DecreaseSpeed();
		return Ptr;
	}
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::AssignCargos()
{
	CheckVIPMaxWait();
	CheckVIPAssignment();											// Assign VIP Cargo First

	CheckSpecialMaxWait();											// Then Check Special Cargo Max Wait Then Assign It
	CheckSpecialAssignment();

	CheckAutoPromotion();											// Check Normal Cargos
	CheckNormalMaxWait();
	CheckNormalAssignment();
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::CheckAutoPromotion()
{
	// This Function Checks If There Is A Normal Cargo That Have Excceeded The AutoP
	// If There Is One We Promote It To Vip Cargo
	bool flag = true;								// Bool To Check If The Peeked Cargo Exceeded The AutoP Or Not ( Yes = 1 )
	int i = 0;
	while (flag && !(C->NoReadyCargos('N')))
	{
		Cargo* cargo = C->PeekFirstWaitingCargo('N');						// Get The First Ready Normal Cargo
		NormalCargo* normal_cargo = dynamic_cast<NormalCargo*>(cargo);		// Dynamic Casting To Normal Cargo 
		if (normal_cargo->GetPromotionTime() <= C->GetCurrentSimTime())		// If Its Promotion Time Reached
		{
			VIPCargo* vip_cargo = new VIPCargo(normal_cargo);				// Create A New Vip Cargo With The Same Parameters
			i = normal_cargo->GetID();										// Get The Cargo ID											
			C->remove_cargo(i);												// Search For It And Remove It From The List
			delete normal_cargo;											// Delete The Normal Cargo Pointer
			C->add_cargo(vip_cargo);										// Add The VIP Cargo
			NumOfPromotedCargos++;
		}
		else
		{
			flag = false;													// If The Promotion Time Not Reached Exit The Loop
		}
	}
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::CheckNormalMaxWait()
{
	// Resposible To Check Normal Cargos That Reached Max Wait
	// If There Is One We Start Loading Immediately
	Cargo* normal_cargo = C->PeekFirstWaitingCargo('N');								// Peek The First Normal Cargo
	int current_time = C->GetCurrentSimTime();											// Get Current Simulation Time
	if (normal_cargo && normal_cargo->GetMaxWaitTime(current_time) <= current_time && !NormalLoading)  // If There Is A Cargo And It Has Reached Its Max Time And No Normal Cargos Is Currently Loading
	{
		Truck* truck = GetSuitableMaxWaitTruck('N');									// Get A Suitable Truck To Assign The Cargo To It
		if (!truck)																		// If There Is No Suitable Truck Do Nothing And Return
		{
			return;
		}
		while (!C->NoReadyCargos('N') && !truck->IsFullyLoaded())						// While The Truck Is Not Fully Loaded Or There Is No More Cargos
		{
			normal_cargo = C->DequeueFirstWaitingCargo('N');							// Remove The Cargo From Ready
			truck->LoadCargo(normal_cargo, current_time);								// Move The Cargo To The Truck Load List
		}
		truck->StartLoading(current_time);												// Start Loading The Truck With Given Cargos
		NormalLoading = true;
		C->EnqueueLoadingTrucks(truck);													// Insert The Truck To Loading Trucks
		normal_cargo = C->PeekFirstWaitingCargo('N');									// Peek Next Normal Cargo

	}
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::CheckNormalAssignment()
{
	int current_time = C->GetCurrentSimTime();											// Get Current Simulation Time
	Truck* truck = GetSuitableTruck('N');												// Get A Suitable Truck To Assign The Cargo To
	if (!truck)																			// If There Is No One Return
	{
		return;
	}
	if (truck && C->CountWaitingCargo('N') >= truck->GetMaxCapacity() && !NormalLoading)	// If The Number Of Cargos Greater Than Or Equal The Capacity, And There Is NO Loading Normal Cargos
	{
		for (int i = 0; i < truck->GetMaxCapacity(); i++)
		{
			truck->LoadCargo(C->DequeueFirstWaitingCargo('N'), current_time);			// Assign The Capacity Number Of Cargos To The Truck
		}
		truck->StartLoading(current_time);												// Start Loading The Truck
		C->EnqueueLoadingTrucks(truck);													// Insert It To Loading Trucks
		NormalLoading = true;
		truck = GetSuitableTruck('N');													// Get Another Truck
	}
	if (truck)																			// If There Is A Truck Which Hasn't Been Assigned
	{
		if (truck->IsNightShift())
		{
			C->EnqueueEmptyNightTrucks(truck);
		}
		else
		{
			C->EnqueueEmptyTrucks(truck);													// Put It Back To Empty Trucks
		}
	}
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::CheckSpecialMaxWait()
{
	// This Function Checks For The Special Cargos That Reached Max Wait
	// If There Is One We Start Loading Immediately
	Cargo* SC = C->PeekFirstWaitingCargo('S');
	int CurrentTime = C->GetCurrentSimTime();
	if (SC && SC->GetMaxWaitTime(CurrentTime) <= CurrentTime && !SpecialLoading) // If The Cargo Reached Max Wait And No Special Cargos Is Loading
	{
		Truck* Tr = GetSuitableMaxWaitTruck('S');
		if (!Tr)
			return;

		while (!C->NoReadyCargos('S') && !Tr->IsFullyLoaded())					// While There Is A Cargo And The Truck Isn't Fully Loaded
		{																		// That Means Load As Many Cargos As Possible
			SC = C->DequeueFirstWaitingCargo('S');
			Tr->LoadCargo(SC, CurrentTime);
		}
		Tr->StartLoading(CurrentTime);											// Set The Time Of Start And End Loading For The Truck And Cargos Inside
		C->EnqueueLoadingTrucks(Tr);											// Insert It To Loading Trucks Queue
		SpecialLoading = true;
		SC = C->PeekFirstWaitingCargo('S');
	}
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::CheckSpecialAssignment()
{
	int CurrentTime = C->GetCurrentSimTime();
	Truck* STruck = GetSuitableTruck('S');
	if (!STruck)
		return;

	if (STruck && C->CountWaitingCargo('S') >= STruck->GetMaxCapacity() && !SpecialLoading)
	{
		for (int i = 0; i < STruck->GetMaxCapacity(); i++)
		{
			STruck->LoadCargo(C->DequeueFirstWaitingCargo('S'), CurrentTime);
		}
		STruck->StartLoading(CurrentTime);
		C->EnqueueLoadingTrucks(STruck);
		SpecialLoading = true;
		STruck = GetSuitableTruck('S');
	}
	if (STruck)																			// If There Is A Truck Which Hasn't Been Assigned
	{
		if (STruck->IsNightShift())
		{
			C->EnqueueEmptyNightTrucks(STruck);
		}
		else
		{
			C->EnqueueEmptyTrucks(STruck);												// Put It Back To Empty Trucks
		}
	}

}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-

void Simulator::CheckVIPMaxWait()
{
	// This Function Checks For The VIP Cargos That Reached Max Wait
	// If There Is One We Start Loading Immediately
	Cargo* VC = C->PeekFirstWaitingCargo('V');
	int CurrentTime = C->GetCurrentSimTime();
	if (VC && VC->GetMaxWaitTime(CurrentTime) <= CurrentTime && !VIPLoading)
	{
		Truck* Tr = GetSuitableMaxWaitTruck('V');
		if (!Tr)
			return;

		while (!C->NoReadyCargos('V') && !Tr->IsFullyLoaded())
		{
			VC = C->DequeueFirstWaitingCargo('V');
			Tr->LoadCargo(VC, CurrentTime);
		}
		Tr->StartLoading(CurrentTime);
		C->EnqueueLoadingTrucks(Tr);
		VIPLoading = true;
		VC = C->PeekFirstWaitingCargo('V');
	}
}

void Simulator::CheckVIPAssignment()
{
	int current_time = C->GetCurrentSimTime();									// Get Current Simulation Time
	Truck* truck = GetSuitableTruck('V');										// Get A Suitable Truck To Assign The Cargo To
	if (!truck)																	// If There Is No Such Truck
	{
		return;																	// Exit The Function
	}
	if (truck && C->CountWaitingCargo('V') >= truck->GetMaxCapacity() && !VIPLoading)
	{
		for (int i = 0; i < truck->GetMaxCapacity(); i++)
		{
			truck->LoadCargo(C->DequeueFirstWaitingCargo('V'), current_time);	// Fill This Truck With Cargos
		}
		truck->StartLoading(current_time);										// Start Loading The Truck
		C->EnqueueLoadingTrucks(truck);											// Insert It To Loading Trucks
		VIPLoading = true;
		truck = GetSuitableTruck('V');											// Get Another Truck
	}
	if (truck)																			// If There Is A Truck Which Hasn't Been Assigned
	{
		if (truck->IsNightShift())
		{
			C->EnqueueEmptyNightTrucks(truck);
		}
		else
		{
			C->EnqueueEmptyTrucks(truck);													// Put It Back To Empty Trucks
		}
	}
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::execute_events()
{
	// Responsible For Executing Events If Its Time Reached
	Event* temp;
	int current_time = C->GetCurrentSimTime();									// Get Current Simulation Time
	if (!events_list.PeekFront(temp))											// Get The First Event On The List
	{
		temp = NULL;															// If There Is No One Make It NULL
	}
	while (temp && (current_time >= temp->GetTime()))							// If The Event Time Has Reached
	{
		events_list.Dequeue(temp);												// Remove It From The Events List
		if (dynamic_cast<Promotion*> (temp))									// If It's Promotion Event
		{
			Promotion* event = dynamic_cast<Promotion*> (temp);
			int Cost;
			NormalCargo* X;
			X = C->SearchNormalCargo(event->Execute(current_time, Cost));		// Get The ID Of The Targeted Cargo And It's Additional Price
			if (X)																// If There Is Such A Cargo
			{
				VIPCargo* Y = new VIPCargo(X->GetReady_Time(), X->GetID(), X->GetDistance(), X->GetLoadingTime(), X->GetCost() + Cost, max_wait);	// Make A New VIP Cargo With The Same Parameters
				C->remove_cargo(X->GetID());									// Remove The Old Cargo From The List
				C->add_cargo(Y);												// Add The New One
				delete X;														// Delete The Pointer
			}
		}
		if (dynamic_cast<Ready*> (temp))										// If It's Ready Events
		{
			Ready* event = dynamic_cast<Ready*> (temp);
			Cargo* Car = event->Execute(current_time);							// Get A Pointer To That REady Cargo
			C->add_cargo(Car);													// Add It To It's Suitable List
			switch (Car->GetType())												// Check For The Type To Increase The Number Of This Type Cargos Number
			{
			case 'N': TotalNormal++; break;
			case 'S': TotalSpecial++; break;
			case 'V': TotalVIP++; break;
			}
			TotalCargosNumber++;												// Increase The Total Cargos Number
		}
		if (dynamic_cast<Cancellation*> (temp))									// If It's Cancellation
		{
			Cancellation* event = dynamic_cast<Cancellation*> (temp);
			int ID = event->Execute(current_time);								// Get The Cargo ID
			Cargo* CargoToRemove = C->SearchNormalCargo(ID);					// Search For IT
			C->remove_cargo(ID);												// Remove It
			delete CargoToRemove;												// Then Delete It
		}
		delete temp;															// Delete The Pointer Of The Current Event
		if (!events_list.PeekFront(temp))										// Get The Next Event
		{
			temp = NULL;
		}
	}
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::move_loading_trucks_to_moving()
{
	// Responsible For Checking If There Is A Truck That Finished Loading
	// If There Is One Insert It To The Moving Trucks And Start ITs Journey
	Truck* truck = C->PeekLoadingTrucks();
	int current_time = C->GetCurrentSimTime();
	while (truck && current_time >= truck->GetEndLoadingTime())
	{
		truck = C->DequeueLoadingTrucks();
		C->AddMovingTrucks(truck);
		truck->StartMoving(current_time);
		switch (truck->GetLoadType())
		{
		case 'N': NormalLoading = false; break;
		case 'S': SpecialLoading = false; break;
		case 'V': VIPLoading = false; break;
		}
		truck = C->PeekLoadingTrucks();
	}
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::move_moving_trucks_to_Checkup_or_Empty()
{
	// Resposible To Check If There Is A Truck That Finished Its Journey
	// If There Is A Truck It Checks If It Needs Maintainance Or Not
	// If Yes Insert It To In Check Up Queue
	// If No Insert It To Empty Trucks
	int j = 0;
	int current_time = C->GetCurrentSimTime();
	Truck* truck = C->GetMovingTrucks(j);				// Get First Moving Truck
	while (truck)
	{
		if (truck->FinishJourney(current_time))			// If It Has Finished Its Journey
		{
			C->RemoveMovingTrucks(truck);				// Remove It From Moving Trucks
			if (truck->NeedExternalCheckUp(current_time))
			{
				C->EnqueueExternalCheckupTrucks(truck);
				C->GetOutput()->PrintErrMassage("External Maintainance Needed Moving Truck Number " + to_string(truck->GetID()) + " To External Check Up ");
			}
			else if (truck->NeedCheckUp())				// If It Needs Maintainance
			{
				C->EnqueueCheckupTrucks(truck);			// Insert It To In Check Up Trucks
				truck->GoServices(current_time);		// Set Its End Check Up Time
			}
			else										// If Not
			{
				truck->BackAvailable();					// Get It Back To Work

				if (truck->IsNightShift())
				{
					C->EnqueueEmptyNightTrucks(truck);
				}
				else
				{
					C->EnqueueEmptyTrucks(truck);			// Insert It To Empty Trucks
				}
			}
		}
		else
		{
			j++;
		}
		truck = C->GetMovingTrucks(j);
	}
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::move_checkup_trucks_to_available()
{
	// Responsible For Checking If There Is A Truck That Finished Its Maintainance
	// If There Is One Remove It From In Check Up Trucks And Insert It Inside Empty Trucks

	Truck* truck = C->PeekCheckupTrucks();
	int current_time = C->GetCurrentSimTime();

	while (truck && truck->FinishedMaintainance(current_time))			// While There Is A Truck And This Truck Finished Its Maintainance
	{
		truck = C->DequeueCheckupTrucks();								// Remove It From In Check-Up Trucks
		truck->BackAvailable();											// Make It Ready To Go
		if (truck->IsNightShift())
		{
			C->EnqueueEmptyNightTrucks(truck);
		}
		else
		{
			C->EnqueueEmptyTrucks(truck);			// Insert It To Empty Trucks
		}								// Insert It Inside Empty Trucks
		truck = C->PeekCheckupTrucks();									// Get The Next One To Check For It
	}

	char S[3] = { 'N','S','V' };
	for (int i = 0; i < 3; i++)
	{
		truck = C->PeekExternalCheckupTrucks(S[i]);

		while (truck && truck->FinishedMaintainance(current_time))
		{
			truck = C->DequeueExternalCheckupTrucks(S[i]);
			truck->BackAvailable();
			if (truck->IsNightShift())
			{
				C->EnqueueEmptyNightTrucks(truck);
			}
			else
			{
				C->EnqueueEmptyTrucks(truck);			// Insert It To Empty Trucks
			}
			truck = C->PeekExternalCheckupTrucks(S[i]);
		}
	}

}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::CheckDeliveredCargos()
{
	// Check Every Moving Truck To See If There Is A Cargo That Was Delivered
	// If There Is One We Insert The Cargo ( Returning From Check Delivered Cargos) And Enqueue It Inside Delivered Cargos

	Cargo* Temp;
	int i = 0;

	int current_time = C->GetCurrentSimTime();			// Get Current Simulation Time
	Truck* T = C->GetMovingTrucks(i);					// Get The Truck At First Index 
	while (T)
	{
		Temp = T->CheckDeliveredCargos(current_time);	// If There Is A Cargo Delivered
		while (Temp)
		{
			C->EnqueueDelivered(Temp);						// Enqueue It In Delivered Cargos
			Temp = T->CheckDeliveredCargos(current_time);	// Check If There Is Another One Inside This Truck
		}
		T = C->GetMovingTrucks(++i);						// Get Next Truck
	}
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::CreateStatistics()
{
	// Responisble For Creating The Statistics After The End Of The Simulation
	string Info;
	Output* Pout = C->GetOutput();
	int TotalActive;
	double TotalUse;
	int TotalTrucks = C->CountEmptyTrucks('N') + C->CountEmptyTrucks('V') + C->CountEmptyTrucks('S');
	TotalTrucks += C->CountEmptyNightTrucks('N') + C->CountEmptyNightTrucks('V') + C->CountEmptyNightTrucks('S');
	// Printing Cargos Infos \\

	Info = "CDT	ID	PT	WT	TID";
	Pout->GenerateText(Info);

	int TotalCargosTime = 0;
	while (!C->NoDeliveredCargos())
	{
		Cargo* Ptr = C->DequeueDelivered();
		TotalWaitingTime += Ptr->GetMovingTime() - Ptr->GetReady_Time();
		TotalCargosTime += Ptr->GetDeliveryTime() - Ptr->GetReady_Time();
		Pout->GenerateCargoInfo(Ptr);
	}
	Info = "================================================================================ " + '\n';
	Pout->GenerateText(Info);
	//================================================================================
	// Extra Statistics

	Info = "Total Cargos : " + to_string(TotalCargosNumber) + " | Normal = " + to_string(TotalNormal) + ", Special = " + to_string(TotalSpecial) + ", VIP = " + to_string(TotalVIP) + " | " + '\n';

	// Calculate Average Max Wait


	int AvgWait = TotalWaitingTime / TotalCargosNumber;
	Info += "Average Waiting Time : " + to_string(AvgWait / 24) + ":" + to_string(AvgWait % 24) + '\n';

	// Calculated Auto Promoted Cargos Precentage

	Info += "Auto Promoted Cargos : ";

	if (TotalNormal > 0)
		Info += to_string(double(NumOfPromotedCargos) * 100 / double(TotalNormal));
	else
		Info += "0 ";
	Info += '\n';
	// Calculate Total Trucks

//	TotalTruck = C->CountEmptyTrucks('N') + C->CountEmptyTrucks('S') + C->CountEmptyTrucks('V');
	Info += "Total Trucks : " + to_string(TotalTrucks) + " | Normal = " + to_string(C->CountEmptyTrucks('N') + C->CountEmptyNightTrucks('N')) + ", Special = " + to_string(C->CountEmptyTrucks('S') + C->CountEmptyNightTrucks('S')) + " , Vip = " + to_string(C->CountEmptyTrucks('V') + C->CountEmptyNightTrucks('V')) + "| " + '\n';

	// Calculate Trucks Average Active Time And Utilistaion

	C->GetTruckStatistics(TotalActive, TotalUse);
	Info += "Average Active Time = " + to_string(TotalActive / TotalTrucks) + '\n';
	Info += "Average Utilisation = " + to_string(TotalUse * 100 / TotalTrucks) + '\n';

	// Printitng The Full Text In The File

	Pout->GenerateText(Info);
	Pout->PrintFileCreated();				// Info Massage That Tells The User That The File Was Generated
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
bool Simulator::CompleteHour()
{
	execute_events();									// Execute An Event If Its Time Has Been Reached

	move_moving_trucks_to_Checkup_or_Empty();			// Check If There Is A Truck That Has Returned From Its Journey

	move_checkup_trucks_to_available();					// Check If A Truck Finished Its Maintainance

	CheckDeliveredCargos();								// Check If There Are Cargos That Have Been Delivered

//	if ((C->GetCurrentSimTime() % 24) > 5 && (C->GetCurrentSimTime() % 24) < 23)


	move_loading_trucks_to_moving();					// Check If There Is A Truck That Finished Loading And Ready To Go

	AssignCargos();										// Start Assigning Cargos (If Possible)

	C->CheckFailureJourneys();							// Check If There Was A Truck Failure During The Journey

	bool Finished;

	Finished = C->PrintInfos();							// Print Infos And Check If The Simulation Has Finished Or Not

	tick();												// Increase The Current Time By 1

	if (!Finished && events_list.IsEmpty())
		return false;
	else
		return true;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::FinishSim()
{
	C->Finish();
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::tick()
{
	C->tick();
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Simulator::PrintInfos()
{
	C->PrintInfos();
}