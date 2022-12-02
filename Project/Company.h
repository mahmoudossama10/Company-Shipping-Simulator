#pragma once
#include "Cancellation.h"
#include "Promotion.h"
#include "Ready.h"
#include "VIPCargo.h"
#include "VIPTruck.h"
#include "NormalCargo.h"
#include "NormalTruck.h"
#include "SpecialCargo.h"
#include "SpecialTruck.h"
#include "Input.h"
#include "Output.h"
#include"List.h"


class Company
{
	NormalCargoList ready_normal_cargos;									
	Queue<SpecialCargo*> ready_special_cargos;
	Queue<VIPCargo*> ready_vip_cargos;
	//====================================================================
	Queue<NormalTruck*> normal_trucks;
	Queue<SpecialTruck*> special_trucks;
	Queue<VIPTruck*> vip_trucks;
	Queue<NormalTruck*> normal_trucks_night;
	Queue<SpecialTruck*> special_trucks_night;
	Queue<VIPTruck*> vip_trucks_night;
	//====================================================================
	Queue<Truck*> loading_trucks;
	//====================================================================
	List<Truck*> moving_trucks;
	//====================================================================
	Queue<Cargo*> delivered_cargos;
	Queue<Truck*> maintenance_trucks;
	Queue<Truck*> External_Normal_Maintainance;
	Queue<Truck*> External_Special_Maintainance;
	Queue<Truck*> External_VIP_Maintainance;
	//====================================================================
	Input* Pin;
	Output* Pout;
	//====================================================================
	int max_wait;
	int promotion;
	int OutMood;
	//====================================================================
	static int current_time;	
	int TotalNormalCargos;
	int TotalSpecialCargos;
	int VIPCargos;
	int TotalTrucks;
	int TotalNormal;
	int TotalSpecial;
	int TotalVip;
public:

	// Start Simulation Functions ( Read Functions )
	Company();
	~Company();
	//====================================================================================
	Input* GetInput();																	  // Get A Pointer To The Input
	Output* GetOutput();
	int GetMaxWait();																	  // Get The Max Wait Of All Cargos
	int GetPromotion();																	  // Get The Max Promotion Time
	int GetCurrentSimTime();															  // Get The Simulation Current Time
	int GetTotalTrucks();
	//====================================================================================
	// Main Simulation Function														
	void tick();																		  // Increament Current Time
	bool PrintInfos();																	  // Print All Infos To The Command
	void Finish();
	//====================================================================================
	// Functions For Events Execution
	void add_cargo(Cargo* cargo);														  // Add A Cargo To The Waiting Lists
	void remove_cargo(int id);															  // Cancel Or Promote A Normal Cargo
	NormalCargo* SearchNormalCargo(int id);												  // Search For A Cargo Using ID
	//====================================================================================
	// Functions For Operating On Ready Cargos

	Cargo* DequeueFirstWaitingCargo(char Type);											  // Get The First Element Of The Waiting Cargo Of A Passed Type And Remove It 
	Cargo* PeekFirstWaitingCargo(char Type);											  // Get The First Element Without Removing It
	bool NoReadyCargos(char Type);														  // Boolean To Check If There Is No Ready Cargos Of Passed Type
	int CountWaitingCargo(char Type);
	int CountTotalCargos(char Type);

	//====================================================================================
	// Functions For Operating On Loading Trucks

	Truck* PeekLoadingTrucks();
	Truck* DequeueLoadingTrucks();
	void EnqueueLoadingTrucks(Truck* Tr);
	bool NoLoadingTruck();


	//====================================================================================
	// Functions For Operating On Moving Trucks

	Truck* GetMovingTrucks(int Index);
	void RemoveMovingTrucks(Truck* Tr);
	void AddMovingTrucks(Truck* Tr);
	bool NoMovingTrucks();

	//====================================================================================
	// Functions For Operating On Checkup Trucks

	Truck* PeekCheckupTrucks();
	Truck* DequeueCheckupTrucks();
	void EnqueueCheckupTrucks(Truck* Tr);
	bool NoCheckupTrucks();

	Truck* PeekExternalCheckupTrucks(char TruckType);
	Truck* DequeueExternalCheckupTrucks(char TruckType);
	void EnqueueExternalCheckupTrucks(Truck* Tr);
	bool NoExternalCheckupTrucks(char TruckType);

	//====================================================================================
	// Functions For Operating On Empty Trucks

	Truck* PeekEmptyTrucks(char Type);
	Truck* DequeueEmptyTrucks(char Type);
	void EnqueueEmptyTrucks(Truck* Tr);
	bool NoEmptyTrucks(char Type);
	int CountEmptyTrucks(char Type);

	Truck* PeekEmptyNightTrucks(char Type);
	Truck* DequeueEmptyNightTrucks(char Type);
	void EnqueueEmptyNightTrucks(Truck* Tr);
	bool NoEmptyNightTrucks(char Type);
	int CountEmptyNightTrucks(char Type);

	//====================================================================================
	// Functions For Operating On Delivered Cargos

	void EnqueueDelivered(Cargo* C);
	Cargo* DequeueDelivered();
	bool NoDeliveredCargos();

	//====================================================================================
	// Delete All Dynamically Allocated Cargos And Trucks
	void RemoveAllLists();
	//====================================================================================
	void CheckFailureJourneys();

	void GetTruckStatistics(int& TotalActive , double& TotalUse);
};