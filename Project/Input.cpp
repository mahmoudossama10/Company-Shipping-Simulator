#include "Input.h"

Input::Input()
{
	File.open("Files/Test1.txt");
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Input::~Input()
{
	File.close();
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
char Input::ReadCharacter()
{
	char Read;
	File >> Read;
	return Read;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Input::ReadNumber()
{
	int Num;
	File >> Num;
	return Num;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Input::ReadDate()
{
	string A;
	File >> A;
	string Temp = "";
	int Time = 0;
	for (int i = 0; i < A.size(); i++)
	{
		if (A[i] == ':')
		{
			Time += stoi(Temp) * 24;
			Temp = "";
		}
		else
		{
			Temp += A[i];
		}
	}
	Time += stoi(Temp);
	return Time;
}
int Input::GetNumberFromIOStream()
{
	int X;
	cin >> X;
	return X;
}
void Input::ChangeFile(int X)
{
	File.close();
	switch (X)
	{
	case 1: File.open("Files/Test1.txt"); break;
	case 2: File.open("Files/Test2.txt"); break;
	case 3: File.open("Files/Test3.txt"); break;
	case 4: File.open("Files/Test4.txt"); break;
	case 5: File.open("Files/Test5.txt"); break;
	case 6: File.open("Files/Test6.txt"); break;
	default : File.open("Files/Test1.txt"); break;
	}
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
// The Following Two Function Is Responsible To Read The Trucks Info Section From The Input File
void Input::Loadfile(Queue<NormalTruck*>& NT, Queue<SpecialTruck*>& ST, Queue<VIPTruck*>& VT, int& max_wait, int& promotion)
{
	int NumOfTrucks[3];
	int Speed[3];
	int Capacity[3];
	int MaxJourneys;
	int MaintainanceTime[3];
	int number_of_events;
	File >> NumOfTrucks[0] >> NumOfTrucks[1] >> NumOfTrucks[2];
	File >> Speed[0] >> Speed[1] >> Speed[2];
	File >> Capacity[0] >> Capacity[1] >> Capacity[2];
	File >> MaxJourneys;
	File >> MaintainanceTime[0] >> MaintainanceTime[1] >> MaintainanceTime[2];
	int ID = 1;
	for (int i = 0; i < NumOfTrucks[0]; i++)
	{
		NormalTruck* Ptr = new NormalTruck(Speed[0], Capacity[0], MaxJourneys, MaintainanceTime[0], ID++, 'M');
		NT.Enqueue(Ptr);
	}
	for (int i = 0; i < NumOfTrucks[1]; i++)
	{
		SpecialTruck* Ptr = new SpecialTruck(Speed[1], Capacity[1], MaxJourneys, MaintainanceTime[1], ID++, 'M');
		ST.Enqueue(Ptr);
	}
	for (int i = 0; i < NumOfTrucks[2]; i++)
	{
		VIPTruck* Ptr = new VIPTruck(Speed[2], Capacity[2], MaxJourneys, MaintainanceTime[2], ID++, 'M');
		VT.Enqueue(Ptr);
	}
	File >> promotion >> max_wait;
}

void Input::Loadfilebonus(Queue<NormalTruck*>& NT, Queue<SpecialTruck*>& ST, Queue<VIPTruck*>& VT, Queue<NormalTruck*>& NTN, Queue<SpecialTruck*>& STN, Queue<VIPTruck*>& VTN, int& max_wait, int& promotion, int& TotalTrucks)
{

	int NumOfTrucks[3];
	int Capacity[3];
	int MaxJourneys;
	int MaintainanceTime[3];
	int number_of_events;
	File >> NumOfTrucks[0] >> NumOfTrucks[1] >> NumOfTrucks[2];
	TotalTrucks = NumOfTrucks[0] + NumOfTrucks[1] + NumOfTrucks[2];
	int* SpeedNormal = new int[NumOfTrucks[0]];
	int* SpeedSpecial = new int[NumOfTrucks[1]];
	int* SpeedVIP = new int[NumOfTrucks[2]];
	int* CapacityNormal = new int[NumOfTrucks[0]];
	int* CapacitySpecial = new int[NumOfTrucks[1]];
	int* CapacityVIP = new int[NumOfTrucks[2]];
	char* NormalTruckShift = new char[NumOfTrucks[0]];
	char* SpecialTruckShift = new char[NumOfTrucks[1]];
	char* VIPTruckShift = new char[NumOfTrucks[2]];

	for (int i = 0; i < NumOfTrucks[0]; i++)
	{
		File >> SpeedNormal[i];
	}
	for (int i = 0; i < NumOfTrucks[1]; i++)
	{
		File >> SpeedSpecial[i];
	}
	for (int i = 0; i < NumOfTrucks[2]; i++)
	{
		File >> SpeedVIP[i];
	}
	for (int i = 0; i < NumOfTrucks[0]; i++)
	{
		File >> CapacityNormal[i];
	}
	for (int i = 0; i < NumOfTrucks[1]; i++)
	{
		File >> CapacitySpecial[i];
	}
	for (int i = 0; i < NumOfTrucks[2]; i++)
	{
		File >> CapacityVIP[i];
	}
	for (int i = 0; i < NumOfTrucks[0]; i++)
	{
		File >> NormalTruckShift[i];
	}
	for (int i = 0; i < NumOfTrucks[1]; i++)
	{
		File >> SpecialTruckShift[i];
	}
	for (int i = 0; i < NumOfTrucks[2]; i++)
	{
		File >> VIPTruckShift[i];
	}
	File >> MaxJourneys;
	File >> MaintainanceTime[0] >> MaintainanceTime[1] >> MaintainanceTime[2];
	int ID = 1;
	for (int i = 0; i < NumOfTrucks[0]; i++)
	{
		NormalTruck* Ptr = new NormalTruck(SpeedNormal[i], CapacityNormal[i], MaxJourneys, MaintainanceTime[0], ID++, NormalTruckShift[i]);
		if (NormalTruckShift[i] == 'M')
		{
			NT.Enqueue(Ptr);
		}
		else
		{
			NTN.Enqueue(Ptr);
		}
	}
	for (int i = 0; i < NumOfTrucks[1]; i++)
	{
		SpecialTruck* Ptr = new SpecialTruck(SpeedSpecial[i], CapacitySpecial[i], MaxJourneys, MaintainanceTime[1], ID++, SpecialTruckShift[i]);
		if (SpecialTruckShift[i] == 'M')
		{
			ST.Enqueue(Ptr);
		}
		else
		{
			STN.Enqueue(Ptr);
		}
	}
	for (int i = 0; i < NumOfTrucks[2]; i++)
	{
		VIPTruck* Ptr = new VIPTruck(SpeedVIP[i], CapacityVIP[i], MaxJourneys, MaintainanceTime[2], ID++, VIPTruckShift[i]);
		if (VIPTruckShift[i] == 'M')
		{
			VT.Enqueue(Ptr);
		}
		else
		{
			VTN.Enqueue(Ptr);
		}
	}
	File >> promotion >> max_wait;

	delete[] SpeedNormal;
	delete[] SpeedSpecial;
	delete[] SpeedVIP;
	delete[] CapacityNormal;
	delete[] CapacitySpecial;
	delete[] CapacityVIP;
	delete[] NormalTruckShift;
	delete[] SpecialTruckShift;
	delete[] VIPTruckShift;
}
