#include <iostream>
#ifndef STACK_H
#define STACK_H

using namespace std;

#define MAX 1000

// TODO: Implement all methods
template <typename T>
class Stack
{
	T *data;
	int top;
	int capacity;

public:
	Stack(int size = MAX);
	~Stack();

	void push(T data);
	void pop();
	T peak();

	int size();
	bool empty();
};

template <typename T>
Stack<T>::Stack(int size)
{
	this->data = new T(size);
	this->capacity = size;
	this->top = -1;
}

template <typename T>
Stack<T>::~Stack()
{
	delete this->data;
}

template <typename T>
void Stack<T>::push(T data)
{
	++this->top;
	this->data[top] = data;
}

template <typename T>
void Stack<T>::pop()
{
	try
	{
		if (this->empty())
		{
			throw "Error Queue::pop(): Stack is empty";
		}
		else
		{
			--this->top;
		}
	}
	catch (const char *msg)
	{
		cerr << msg << endl;
	}
}

template <typename T>
T Stack<T>::peak()
{
	try
	{
		if (this->empty())
		{
			throw "Error Queue::peak(): Stack is empty";
		}
		else
		{
			return this->data[top];
		}
	}
	catch (const char *msg)
	{
		cerr << msg << endl;
	}
}

template <typename T>
int Stack<T>::size()
{
	return this->top + 1;
}

template <typename T>
bool Stack<T>::empty()
{
	if (this->top == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
#endif