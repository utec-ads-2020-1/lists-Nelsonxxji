#include <iostream>
#ifndef STACK_H
#define STACK_H

using namespace std;

#define MAX 1000

// TODO: Handle Resize
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
	if (top > this->capacity - 1)
	{
		this->capacity *= 2;
		T *newQueue = new T(capacity);
		copy(this->data, &this->data[capacity - 1], newQueue);
		delete this->data;
		this->data = newQueue;
	}
	this->data[top] = data;
}

template <typename T>
void Stack<T>::pop()
{
	if (this->empty())
	{
		throw "Error Queue::pop(): Stack is empty";
	}
	--this->top;
}

template <typename T>
T Stack<T>::peak()
{
	if (this->empty())
	{
		throw "Error Queue::peak(): Stack is empty";
	}
	return this->data[top];
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