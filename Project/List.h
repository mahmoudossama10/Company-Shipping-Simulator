#pragma once
#include "Node.h"
template <class T>
class List
{
protected:
	Node<T>* Head;
	Node<T>* Tail;
	bool(*Sorting)(T, T);
	//_______________________________________________________________________________
	Node<T>* CreateNode(T Value)
	{
		Node<T>* Ptr = new Node<T>(Value);
		return Ptr;
	}
public:
	// Constructors And Destructor
	//_______________________________________________________________________________
	List()
	{
		Head = nullptr;
	}
	//_______________________________________________________________________________
	List(List& L)
	{
		Sorting = L.Sorting;
		if (L.Head)
		{
			Head = CreateNode(L.Head->GetValue());
			Node<T>* Ptr = Head;
			Node<T>* LPtr = L.Head->GetNext();
			while (LPtr)
			{
				Ptr->SetNext(CreateNode(LPtr->GetValue()));
				Ptr = Ptr->GetNext();
				LPtr = LPtr->GetNext();
			}
		}
		else
		{
			Head = nullptr;
		}
	}
	//_______________________________________________________________________________
	~List()
	{
		while (Head)
		{
			Node<T>* Ptr = Head;
			Head = Head->GetNext();
			delete Ptr;
		}
	}
	//_______________________________________________________________________________
	void SetSortingMethod(bool (*S)(T, T))
	{
		Sorting = S;
	}
	//_______________________________________________________________________________
	void Insert(T Value)
	{
		if (!Head)
		{
			Head = CreateNode(Value);
			Tail = Head;
			return;
		}
		if (!Sorting)
		{
			Tail->SetNext(CreateNode(Value));
			Tail = Tail->GetNext();
		}
		else
		{
			if (!Sorting(Head->GetValue(), Value)) // If The Element Should Be At The Start Of The List
			{
				Node<T>* Ptr = CreateNode(Value);
				Ptr->SetNext(Head);
				Head = Ptr;
				return;
			}
			// General Sorted Insertion 
			Node<T>* Ptr = Head;
			while (Ptr->GetNext() && Sorting(Ptr->GetNext()->GetValue(), Value))
			{
				Ptr = Ptr->GetNext();
			}
			Node<T>* NewPtr = CreateNode(Value);
			NewPtr->SetNext(Ptr->GetNext());
			Ptr->SetNext(NewPtr);
		}
	}
	//_______________________________________________________________________________
	virtual void Remove(T Value)
	{
		if (!Head)
			return;
		else
			if (Head->GetValue() == Value)
			{
				Node<T>* Ptr = Head;
				Head = Head->GetNext();
				delete Ptr;
			}
			else
			{
				Node<T>* Ptr = Head;
				while (Ptr->GetNext() && Ptr->GetNext()->GetValue() != Value)
				{
					Ptr = Ptr->GetNext();
				}
				if (Ptr->GetNext())
				{
					Node<T>* DelPtr = Ptr->GetNext();
					Ptr->SetNext(DelPtr->GetNext());
					delete DelPtr;
				}
			}
	}
	//_______________________________________________________________________________
	bool gethead(T& Val)
	{
		if (!Head)
			return false;
		else
		{
			Val = Head->GetValue();
			return true;
		}
	}
	//_______________________________________________________________________________
	int GetSize()
	{
		int Size = 0;
		Node<T>* Ptr = Head;
		while (Ptr)
		{
			Size++;
			Ptr = Ptr->GetNext();
		}
		return Size;
	}
	//_______________________________________________________________________________
	T Get(int Index)
	{
		int Count = 0;
		Node<T>* Ptr = Head;
		while (Count < Index && Ptr)
		{
			Ptr = Ptr->GetNext();
			Count++;
		}
		return Ptr->GetValue();
	}
	//_______________________________________________________________________________
	bool IsEmpty()
	{
		return Head == nullptr;
	}
};