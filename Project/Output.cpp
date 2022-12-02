#include "Output.h"

Output::Output()
{
	File.open("Files/Output.txt");
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
Output::~Output()
{
	File.close();
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
int Output::ChooseSimulationMood()
{
	cout << "Please Choose Simulation Output Mood : " << endl;
	cout << "1 - Interactive Mood " << endl;
	cout << "2 - Step By Step Mood " << endl;
	cout << "3 - Silent Mood " << endl;
	int X;
	cin >> X;
	system("cls");
	return X;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Output::PrintCurrentTime(int CurrentTime)
{
	cout << "CurrentTime (Day:Hour) ====>" << " " << CurrentTime / 24 << ":" << CurrentTime % 24 << endl;
	cout << "*=================================================*" << endl;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Output::PrintWaitingCargos(NormalCargoList NQ, Queue<SpecialCargo*> SQ, Queue<VIPCargo*> VQ)
{
	int Total = NQ.GetSize() + SQ.CountQueue() + VQ.CountQueue();
	cout << Total << " Waiting Cargos : [";
	for (int i = 0; i < NQ.GetSize(); i++)
	{
		cout << NQ.Get(i)->GetID() << ", ";
	}
	cout << "]   (";
	while (!SQ.IsEmpty())
	{
		SpecialCargo* Temp;
		SQ.Dequeue(Temp);
		cout << Temp->GetID() << ", ";
	}
	cout << ")   {";
	while (!VQ.IsEmpty())
	{
		VIPCargo* Temp;
		VQ.Dequeue(Temp);
		cout << Temp->GetID() << ", ";
	}
	cout << "}" << endl;
	cout << "*==================================================*" << endl;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Output::PrintLoadingCargos(Queue<Truck*> Q)
{
	Truck* Temp = NULL;
	int Count = Q.CountQueue();
	cout << Count << " Loading Trucks: ";
	while (!Q.IsEmpty())
	{
		Q.Dequeue(Temp);
		if (!Temp)
			continue;
		cout << Temp->GetID();
		switch (Temp->GetType())
		{
		case 'N': cout << "["; break;
		case 'S': cout << "("; break;
		case 'V': cout << "{"; break;
		}
		cout << Temp->GetLoadId(0);
		for (int i = 1; i < Temp->GetCurrentCapacity(); i++)
		{
			cout << ", " << Temp->GetLoadId(i);
		}
		switch (Temp->GetType())
		{
		case 'N': cout << "]  "; break;
		case 'S': cout << ")  "; break;
		case 'V': cout << "}  "; break;
		}
	}
	cout << endl;
	cout << "*==================================================*" << endl;

}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Output::PrintMovingCargos(List<Truck*> Q)
{
	Truck* Temp;
	int NumOfTruck = Q.GetSize();
	int TotalNum = 0;
	for (int i = 0; i < NumOfTruck; i++)
	{
		Temp = Q.Get(i);
		TotalNum += Temp->GetCurrentCapacity();
	}
	cout << TotalNum << " Moving Cargos : ";
	for (int i = 0; i < NumOfTruck; i++)
	{
		Temp = Q.Get(i);
		cout << Temp->GetID();
		switch (Temp->GetType())
		{
		case 'N': cout << "["; break;
		case 'S': cout << "("; break;
		case 'V': cout << "{"; break;
		}
		if (Temp->GetCurrentCapacity() > 0)
		{
			cout << Temp->GetLoadId(0);
			for (int i = 1; i < Temp->GetCurrentCapacity(); i++)
			{
				cout << ", " << Temp->GetLoadId(i);
			}
		}
		switch (Temp->GetType())
		{
		case 'N': cout << "] "; break;
		case 'S': cout << ") "; break;
		case 'V': cout << "} "; break;
		}
	}
	cout << endl;
	cout << "*==================================================*" << endl;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Output::PrintDeliveredCargo(Queue<Cargo*> Q)
{
	cout << Q.CountQueue() << " Delivered Cargos : ";
	Queue<NormalCargo*> NC;
	Queue<SpecialCargo*> SC;
	Queue<VIPCargo*> VC;
	while (!Q.IsEmpty())
	{
		Cargo* Temp;
		Q.Dequeue(Temp);
		if (dynamic_cast<NormalCargo*>(Temp))
			NC.Enqueue(dynamic_cast<NormalCargo*>(Temp));
		if (dynamic_cast<SpecialCargo*>(Temp))
			SC.Enqueue(dynamic_cast<SpecialCargo*>(Temp));
		if (dynamic_cast<VIPCargo*>(Temp))
			VC.Enqueue(dynamic_cast<VIPCargo*>(Temp));
	}
	cout << "[";
	while (!NC.IsEmpty())
	{
		NormalCargo* Temp;
		NC.Dequeue(Temp);
		cout << Temp->GetID() << ", ";
	}
	cout << "]  ";
	cout << "(";
	while (!SC.IsEmpty())
	{
		SpecialCargo* Temp;
		SC.Dequeue(Temp);
		cout << Temp->GetID() << ", ";
	}
	cout << ")  ";
	cout << "{";
	while (!VC.IsEmpty())
	{
		VIPCargo* Temp;
		VC.Dequeue(Temp);
		cout << Temp->GetID() << ", ";
	}
	cout << "}  " << endl;
	cout << "*=================================================*" << endl;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Output::PrintEmptyTrucks(Queue<NormalTruck*> NT, Queue<SpecialTruck*> ST, Queue<VIPTruck*> VT)
{
	int Total = NT.CountQueue() + ST.CountQueue() + VT.CountQueue();
	cout << Total << " Empty Trucks : [";
	while (!NT.IsEmpty())
	{
		NormalTruck* Temp;
		NT.Dequeue(Temp);
		cout << Temp->GetID() << ", ";
	}
	cout << "]   (";
	while (!ST.IsEmpty())
	{
		SpecialTruck* Temp;
		ST.Dequeue(Temp);
		cout << Temp->GetID() << ", ";
	}
	cout << ")   {";
	while (!VT.IsEmpty())
	{
		VIPTruck* Temp;
		VT.Dequeue(Temp);
		cout << Temp->GetID() << ", ";
	}
	cout << "}" << endl;
	cout << "*=================================================*" << endl;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Output::PrintInCheckUpTrucks(Queue<Truck*> CT, Queue<Truck*> FCT)
{
	cout << CT.CountQueue() << " In Check-Up Trucks : ";
	Queue<NormalTruck*> NT;
	Queue<SpecialTruck*> ST;
	Queue<VIPTruck*> VT;
	while (!CT.IsEmpty() || !FCT.IsEmpty())
	{
		Truck* T;
		if (!CT.IsEmpty())
			CT.Dequeue(T);
		else
			FCT.Dequeue(T);
		switch (T->GetType())
		{
		case 'N': NT.Enqueue(dynamic_cast<NormalTruck*>(T)); break;
		case 'S': ST.Enqueue(dynamic_cast<SpecialTruck*>(T)); break;
		case 'V': VT.Enqueue(dynamic_cast<VIPTruck*>(T)); break;
		}
	}
	cout << "[";
	while (!NT.IsEmpty())
	{
		NormalTruck* temp;
		NT.Dequeue(temp);
		cout << temp->GetID() << ", ";
	}
	cout << "] (";
	while (!ST.IsEmpty())
	{
		SpecialTruck* temp;
		ST.Dequeue(temp);
		cout << temp->GetID() << ", ";
	}
	cout << ") {";
	while (!VT.IsEmpty())
	{
		VIPTruck* temp;
		VT.Dequeue(temp);
		cout << temp->GetID() << ", ";
	}
	cout << "}" << endl;
	cout << "*=================================================*" << endl;
}
// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
void Output::Mood(int CurrentTime)
{
	if (CurrentTime == -1)
	{
		cin.get();
		system("cls");
	}
	else
	{
		if ((CurrentTime % 24) % 5 == 0)
		{
			cout << flush;
			this_thread::sleep_for(chrono::seconds(2));
		}
		system("cls");
	}
}

void Output::GenerateText(string S)
{
	File << S << '\n';
}


void Output::GenerateCargoInfo(Cargo* Ptr)
{
	int DeliveredTime = Ptr->GetDeliveryTime();
	int ID = Ptr->GetID();
	int ReadyTime = Ptr->GetReady_Time();
	int WaitingTime = Ptr->GetMovingTime() - Ptr->GetReady_Time();
	int TruckId = Ptr->GetTruckID();
	File << DateGenerator(DeliveredTime) << '\t' << ID << '\t' << DateGenerator(ReadyTime) << '\t' << DateGenerator(WaitingTime) << '\t' << TruckId << '\n';
}

void Output::PrintErrMassage(string S)
{
	cout << S << endl;
	cin.get();
	system("cls");
}

void Output::PrintInfoMassage(string S)
{
	cout << S;
}

string Output::DateGenerator(int Time)
{
	string S;
	S = to_string(Time / 24) + ":" + to_string(Time % 24);
	return S;
}

void Output::PrintFileCreated()
{
	cout << "Output File Generated Successfully ^^";
	cin.get();
}

void Output::FinishSimulation()
{
	system("cls");
	cout << "Simulation Finished :) " << endl;
}

void Output::ChangeOutputFile(int X)
{
	File.close();
	switch (X)
	{
	case 1: File.open("Files/Output1.txt"); break;
	case 2: File.open("Files/Output2.txt"); break;
	case 3: File.open("Files/Output3.txt"); break;
	case 4: File.open("Files/Output4.txt"); break;
	case 5: File.open("Files/Output5.txt"); break;
	case 6: File.open("Files/Output6.txt"); break;
	default: File.open("Files/Output.txt"); break;
	}
}


