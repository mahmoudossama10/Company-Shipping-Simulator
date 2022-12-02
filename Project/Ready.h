#pragma once

#include"Input.h"
#include"Event.h"


#include"Cargo.h"
#include"NormalCargo.h"
#include"VIPCargo.h"
#include"SpecialCargo.h"

#include"Queue.h"
#include"List.h"
#include "NormalCargoList.h"

class Ready :public Event/*,public Cargo,public NormalCargo,public VIPCargo,public SpecialCargo*/
{
	int ReadyTime;
	int ID;
	int Distance;
	int LoadingTime;
	int Cost;
	int WaitingLimits;
	char Type;
	int Time;
	int Max_Wait;
	int Promotion_Time;
public:
	Ready(int Maxwaite, int PromoTime, Input* In);
	Cargo* Execute(int Clock);
	virtual void PolymorphismAcheive();
};