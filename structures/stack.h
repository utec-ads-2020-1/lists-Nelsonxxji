#ifndef STACK_H
#define STACK_H

using namespace std;

#define MAX 1000 

// TODO: Implement all methods
template <typename T>
class stack {
	T* data;
	int top;
	int capacity;

public:
	stack(in	t size = MAX);
	~stack();   		

	void push(T);
	void pop();
	T peak();

	int size();
	bool empty();
};

#endif