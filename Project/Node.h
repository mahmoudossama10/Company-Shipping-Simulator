#pragma once
template <class T>
class Node
{
	T Data;
	Node<T>* Next;
public:
	Node(T Value)
	{
		Data = Value;
		Next = nullptr;
	}
	//_____________________________________
	void SetValue(T Val)
	{
		Data = Val;
	}
	//_____________________________________
	void SetNext(Node<T>* N)
	{
		Next = N;
	}
	//_____________________________________
	inline T GetValue()
	{
		return Data;
	}
	//_____________________________________
	inline Node<T>* GetNext()
	{
		return Next;
	}
};