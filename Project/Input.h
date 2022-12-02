#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Queue.h"
#include "NormalTruck.h"
#include "SpecialTruck.h"
#include "VIPTruck.h"
using namespace std;
class Input
{
	ifstream File;
public:
	Input();
	~Input();
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	// General Read From File
	// Will Be Used Inside Event Classes To Read Its Parameters
	char ReadCharacter();
	int ReadNumber();
	int ReadDate();
	int GetNumberFromIOStream();
	void ChangeFile(int X);
	// -_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
	void Loadfile(Queue<NormalTruck*>& NT, Queue<SpecialTruck*>& ST, Queue<VIPTruck*>& VT, int& max_wait, int& promotion);
	void Loadfilebonus(Queue<NormalTruck*>& NT, Queue<SpecialTruck*>& ST, Queue<VIPTruck*>& VT, Queue<NormalTruck*>& NTN, Queue<SpecialTruck*>& STN, Queue<VIPTruck*>& VTN, int& max_wait, int& promotion, int& truck);
};