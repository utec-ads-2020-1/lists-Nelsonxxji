#include <iostream>
#ifndef QUEUE_H
#define QUEUE_H

using namespace std;

#define MAX 1000

// TODO: Core Dumped Error in Destructor
template <typename T>
class Queue
{
	T *data;
	int top;
	int capacity;

public:
	Queue(int size = MAX);
	~Queue();

	void push(T data);
	void pop();
	T front();
	T back();
	int size();
	bool empty();
};

template <typename T>
Queue<T>::Queue(int size)
{
	this->data = new T(size);
	this->capacity = size;
	this->top = -1;
}

template <typename T>
Queue<T>::~Queue()
{
	delete this->data;
}

template <typename T>
void Queue<T>::push(T data)
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
void Queue<T>::pop()
{
	if (this->empty())
	{
		throw "Error Queue::pop(): Queue is empty";
	}
	++this->data;
	this->top--;
}

template <typename T>
T Queue<T>::front()
{
	if (this->empty())
	{
		throw "Error Queue::front(): Queue is empty";
	}
	return *this->data;
}

template <typename T>
T Queue<T>::back()
{
	if (this->empty())
	{
		throw "Error Queue::back(): Queue is empty";
	}
	return this->data[top];
}

template <typename T>
int Queue<T>::size()
{
	return this->top + 1;
}

template <typename T>
bool Queue<T>::empty()
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
