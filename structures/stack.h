#ifndef STACK_H
#define STACK_H

using namespace std;

#define MAX 1000 

// TODO: Implement all methods
template <typename T>
class Stack {
	T* data;
	int top;
	int capacity;

public:
	Stack(int size = MAX);
	~Stack();   		

	void push(T);
	void pop();
	T peak();

	int size();
	bool empty();
};

#endif