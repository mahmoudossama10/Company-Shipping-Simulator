#pragma once
#include "Cargo.h"
#include "List.h"
class CargoList : public List<Cargo*>
{
public:
	CargoList()
	{

	}
	virtual void Remove(Cargo* Val)
	{
		if (!Head)
			return;
		else
			if (Head->GetValue()->GetID() == Val->GetID())
			{
				Node<Cargo*>* Ptr = Head;
				Head = Head->GetNext();
				delete Ptr;
			}
			else
			{
				Node<Cargo*>* Ptr = Head;
				while (Ptr->GetNext() && Ptr->GetNext()->GetValue()->GetID() != Val->GetID())
				{
					Ptr = Ptr->GetNext();
				}
				if (Ptr->GetNext())
				{
					Node<Cargo*>* DelPtr = Ptr->GetNext();
					Ptr->SetNext(DelPtr->GetNext());
					delete DelPtr;
				}
			}
	}
};