#pragma once
class Cargo
{
	// Time Management Members
	const int ReadyTime;             // The Time At Which The Cargo Is Ready To Be Assigned
	int StartLoadingTime;            // The Time At Which The Cargo Begin Being Loaded To A Truck
	int EndLoadingTime;              // The Time At Which The Cargo Is Finished Loading And Ready To Move
	int DeliveredTime;               // The Time At Which The Cargo Is Delivered To The Destination
	int WaitingLimits;               // The Time At Which The Cargo Reaches The Max Wait And Should Be Immediately Assigned
	int StartMovingTime;
	// ===============================
	const int ID;					 // Cargo ID
	const char Type;                 // Cargo Type (N,S,V)
	const int Distance;              // Distance Of The Cargo Journey
	const int LoadingTime;           // The Time Needed To Load Or Unload A Cargo To Or From A Truck
	const int Cost;                  // The Cost Of The Cargo
	const int MaxWait;               // The Max Time That A Cargo Can Wait Till Being Loaded To A Truck
	int TruckID;
	// ===============================
public:
	Cargo(int ready_time, int id, int distance, int loading_time, int cost, int Maxwait, char type);
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Time Control Getters
	int GetReady_Time();					    // Get The Time At Which The Cargo Was Ready
	int GetMaxWaitTime(int CurrentTime);		// Get The Time At Which The Cargo Will Reach Max Wait " Comparable With Current Time "
	int GetStartLoadingTime();					// Get The Time At Which The Cargo Was Started Loading " Comparable With Current Time "
	int GetEndLoadingTime();					// Get The Time At Which The Cargo Was Ended Loading " Comparable With Current Time "
	int GetDeliveryTime();					    // Get The Time At Which The Cargo Was Delivered " Comparable With Current Time "
	int GetMovingTime();
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Cargo Properties Getters
	int GetID();
	int GetDistance();
	int GetCost();
	int GetLoadingTime();
	int GetMaxWait();
	int GetTruckID();
	char GetType();
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// Cargo Assignment Functions
	void Load(int CurrentTime);					// Sets The Start Loading And End Loading Time Of The Cargo
	void SetDileveredTime(int Time);			// Sets The Time At Which The Cargo Will Be Delivered
	bool IsDelivered(int CurrentTime);			// Check If The Cargo Was Delivered Or Not
	void SetEndLoadingTime(int Time);			// Sets The End Loading Time Of The Cargo
	void SetTruckID(int I);
	void FailureHappened();						// The Last Bonus
	void SetStartJourneyTime(int CurrentTime);
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	virtual void PolymorphismAcheive() = 0;
};