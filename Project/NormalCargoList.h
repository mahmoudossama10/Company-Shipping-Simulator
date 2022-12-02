#pragma once
#include "List.h"
#include "NormalCargo.h"

// Template Specialization So We Can Search For The List By Its ID
class NormalCargoList : public List<NormalCargo*>
{
public:
	NormalCargoList()
	{

	}
	virtual void Remove(NormalCargo* Val)
	{
		if (!Head)
			return;
		else
			if (Head->GetValue()->GetID() == Val->GetID())
			{
				Node<NormalCargo*>* Ptr = Head;
				Head = Head->GetNext();
				delete Ptr;
			}
			else
			{
				Node<NormalCargo*>* Ptr = Head;
				while (Ptr->GetNext() && Ptr->GetNext()->GetValue()->GetID() != Val->GetID())
				{
					Ptr = Ptr->GetNext();
				}
				if (Ptr->GetNext())
				{
					Node<NormalCargo*>* DelPtr = Ptr->GetNext();
					Ptr->SetNext(DelPtr->GetNext());
					delete DelPtr;
				}
			}
	}
};