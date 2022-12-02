#pragma once
#include "CargoList.h"
#include "Cargo.h"

#define FailureProb 0
#define ExternalCheck 0

class Truck
{
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Truck Properties
	const int MaxSpeed;
	int Speed;
	const int Capacity;
	const int MaxJourneys;
	const int MaintainceTime;
	const int ID;
	const bool NightShift;
	const char Type;
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	const int FailurePropability;
	const int ExternalCheckup;
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Truck Time Management
	int StartLoadingTime;
	int EndLoadingTime;
	int CurrentJourneyTime;
	int EndJourneyTime;
	int StartMaintainance;
	int EndMaintainance;
	int DeliveryInterval;
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Truck Assignment Needs
	CargoList Load;
	int Journeys;
	int CurrentCapacity;
	int MaxDistance;
	int ActiveTime;
	int TotalDeliveredCargos;
	bool NeedMaintainance;
public:
	Truck(int speed, int capacity, int max_journeys, int maintaince_time, int Id, char T, char shift);
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Get Truck Infos
	int GetSpeed();
	int GetID();
	char GetType();
	int GetMaxCapacity();
	int GetCurrentCapacity();
	bool IsFullyLoaded();
	bool IsNightShift();
	char GetLoadType();
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Get Cargos Infos
	int GetLoadId(int Index);
	Cargo* CheckDeliveredCargos(int CurrentTime);
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Time Managment
	int GetEndLoadingTime();
	int GetEndJourneyTime();
	int GetEndMaintainanceTime();

	bool FinishJourney(int CurrentTime);
	bool StartJourney(int CurrentTime);
	bool FinishedMaintainance(int CurrentTime);

	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Cargo Assignment Functions
	void LoadCargo(Cargo* L, int CurrentTime);
	void LoadAdditionalCargo(Cargo* L, int CurrentTime);
	void StartLoading(int CurrentTime);
	void StartMoving(int CurrentTime);
	bool NeedCheckUp();
	void GoServices(int CurrentTime);
	void BackAvailable();
	void DeleteAllCargos();

	bool EngineFailure(CargoList& L, int CurrentTime);
	bool NeedExternalCheckUp(int CurrentTime);
	void DecreaseSpeed();
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Statistics Functions
	int GetActiveTime();
	double CalculateTruckUtilization(int CurrentTime);
	virtual void PolymorphismAcheive() = 0;
};