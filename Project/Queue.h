#pragma once
#include "Node.h"
template <class T>
class Queue
{
	Node<T>* Front;
	Node<T>* Rear;
	bool (*Priority)(T, T);  // This Is A Pointer To A Function That Compare Two Variables Depending On Custom Condition
							 // It Will Be Used To Make The Priority Queue With The Queue In The Same Class
							 // As There Is No Difference Between This In Terms Of Interface Function Instead Of Enqueue
protected:
	Node<T>* CreateNode(T Value)					// Private Function That Create A New Node And Return A Pointer To It For Ease
	{
		Node<T>* Ptr = new Node<T>(Value);
		return Ptr;
	}
public:
	// Constructor, Destructor And Copy Constructor
	Queue(bool(*Compare)(T, T) = nullptr)				// Costructro
	{
		Front = nullptr;
		Rear = nullptr;
		Priority = Compare;
	}
	//_____________________________________
	// To Convert The Queue To Pri-Q
	void SetPriority(bool(*Compare)(T, T))				// Make The Priority Pointer Pointer To A Certain Boolean Function That Takes T,T Variables And Compare Them
	{
		Priority = Compare;
	}
	//_____________________________________
	~Queue()
	{
		while (Front)									// As Long As The Front Doesn't Points To Null Procceed It And Remove The Prev One
		{
			Node<T>* Ptr = Front;
			Front = Front->GetNext();
			delete Ptr;
		}
		Front = nullptr;
		Rear = nullptr;
	}
	//_____________________________________
	Queue(Queue& Q)																// Copy Constructor
	{
		Priority = Q.Priority;													// Make It Have The Same Priority
		if (Q.Front)
		{
			Front = CreateNode(Q.Front->GetValue());							// Deep Copy The Data Into New Nodes
			Rear = Front;
			Node<T>* Ptr = Q.Front->GetNext();
			while (Ptr)
			{
				Rear->SetNext(CreateNode(Ptr->GetValue()));
				Rear = Rear->GetNext();
				Ptr = Ptr->GetNext();
			}
		}
		else
		{
			Front = nullptr;
			Rear = nullptr;
		}
	}
	//_____________________________________
	void Enqueue(T Value)
	{
		if (!Front)													// Empty Queue Case, Just Make Front And Rear Point To The Same Node
		{
			Front = CreateNode(Value);
			Rear = Front;
			return;
		}
		//_____________________________________
		if (!Priority)												// If This Queue Isn't A Priority Queue	
		{
			Rear->SetNext(CreateNode(Value));						// FIFO Concept
			Rear = Rear->GetNext();
			return;
		}
		//_____________________________________
		if (Priority) // If It Is A Priority Queue " Have A Comparison That Is Used For Sorting According To Priority "
		{
			Node<T>* Prev = nullptr;
			Node<T>* Curr = Front;
			while (Curr && Priority(Curr->GetValue(), Value))				// While The Current Isn't NULL And It's Place According To The Given Value Is Valid
																			// Say We Want To Sort Ascendingly And The Curr Data Is 5 And Value Is 7
																			// This Means The Node Is In Correct Place So We Proceed And Check The Next
			{
				Prev = Curr;
				Curr = Curr->GetNext();
			}
			if (!Prev) // Should Be At The Front Of The Queue " Most Priority "
			{
				Node<T>* Ptr = CreateNode(Value);
				Ptr->SetNext(Front);
				Front = Ptr;
			}
			else if (!Curr) // Should Be At The Rear Of The Queue " Least Priority "
			{
				Rear->SetNext(CreateNode(Value));
				Rear = Rear->GetNext();
			}
			else  // General Place
			{
				Node<T>* Ptr = CreateNode(Value);
				Ptr->SetNext(Curr);
				Prev->SetNext(Ptr);
			}
			return;
		}
	}
	//_____________________________________
	bool Dequeue(T& Value)
	{
		if (!Front) // Empty Queue
			return false;
		else
		{
			Value = Front->GetValue();
			if (Front == Rear)
			{
				delete Front;
				Front = nullptr;
				Rear = nullptr;
			}
			else
			{
				Node<T>* Ptr = Front;
				Front = Front->GetNext();
				delete Ptr;
			}
			return true;
		}
	}
	//_____________________________________
	bool PeekFront(T& Value)
	{
		if (!Front)
		{
			return false;
		}
		else
		{
			Value = Front->GetValue();
			return true;
		}
	}
	//_____________________________________
	int CountQueue()
	{
		int Counter = 0;
		Node<T>* Ptr = Front;
		while (Ptr)
		{
			Counter++;
			Ptr = Ptr->GetNext();
		}
		return Counter;
	}
	//_____________________________________
	bool IsEmpty()
	{
		return Front == nullptr;
	}
};