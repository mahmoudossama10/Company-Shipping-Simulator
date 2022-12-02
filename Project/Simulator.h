#pragma once
#include "Cancellation.h"
#include "Promotion.h"
#include "Ready.h"

#include "NormalCargo.h"
#include "SpecialCargo.h"
#include "VIPCargo.h"

#include "NormalTruck.h"
#include "SpecialTruck.h"
#include "VIPTruck.h"

#include "Company.h"

class Simulator
{
	Queue<Event*> events_list;
	int number_of_events;
	int max_wait;
	int promotion;
	//====================================================================
	int TotalCargosNumber;
	int TotalNormal;
	int TotalSpecial;
	int TotalVIP;
	int TotalWaitingTime;
	int NumOfPromotedCargos;

	bool NormalLoading;
	bool SpecialLoading;
	bool VIPLoading;

	//====================================================================
	Company* C;
public:
	Simulator();
	~Simulator();
	void read_events();                                                          // Reads The Events From The Input File And Declares Them

	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Phase 1 Function
	void assign_cargos_to_truck();  // For Phase 1 Only
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	void AssignCargos();                                                         // Calls The Assignment Functions Of the Three Types
	Truck* GetSuitableTruck(char CargoType);                                     // Gets The Suitable Truck For The Given Type According To The Priority Arrangement Required
	Truck* GetSuitableNightTruck(char CargoType);                                // Gets The Suitable Night Truck For The Given Type According To The Priority Arrangement Required
	Truck* GetSuitableMaxWaitTruck(char CargoType);                              // If No Ready Truck Is Available, It gets A Maintenance Truck With Half The Speed
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Cargo Assignment Functions
	// Normal Cargos
	void CheckAutoPromotion();                                                   // Promotes A Normal Cargo To A VIP One If The Cargo Waits for A Given Number Of Days
	void CheckNormalMaxWait();                                                   // Immediately Loads Normal Cargos Waiting For A Given Number Of Hours
	void CheckNormalAssignment();                                                // Assigns The Normal Cargos To Their Suitable Trucks
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Special Cargo
	void CheckSpecialMaxWait();                                                  // Immediately Loads Special Cargos Waiting For A Given Number Of Hours
	void CheckSpecialAssignment();                                               // Assigns The Special Cargos To Their Suitable Trucks
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// VIP Cargo
	void CheckVIPMaxWait();														 // Immediately Loads VIP Cargos Waiting For A Given Number Of Hours
	void CheckVIPAssignment();                                                   // Assigns The VIP Cargos To Their Suitable Trucks
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Simulation Functions
	void execute_events();                                                       // Executes The Events For The Current Hour
	void move_loading_trucks_to_moving();                                        // Moves Loading Trucks To Moving
	void move_moving_trucks_to_Checkup_or_Empty();                               // Moves Moving Trucks To Checkup Or Ready Queues Depending On The Number Of Journeys It Travelled
	void move_checkup_trucks_to_available();	                                 // Moves Checkup Trucks To Ready Once Again
	void CheckDeliveredCargos();                                                 // Enqueues Delivered Cargos To Their Respectable Queues
	void CreateStatistics();                                                     // Outputs The Statistics In The Output File

	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Interface Functions
	bool CompleteHour();                                                         // Basically Calls All The Required Operations Every hour
	void FinishSim();                                                            // Prints A Message Indicating That The Simulation Is Complete
	void tick();                                                                 // Increases Time By an Hour
	void PrintInfos();                                                           // Prints The Cargo And Truck Information On the cmd Screen
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Bonus
};