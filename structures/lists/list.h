#ifndef LIST_H
#define LIST_H

#include <string>
#include "node.h"

// TODO: Implement all methods
template <typename T>
class List {
    protected:
        Node<T>* head;
        Node<T>* tail;
        int nodes;

    public:
        List() : head(nullptr), tail(nullptr), nodes(0) {};
        ~List();

        virtual T front() = 0;
        virtual T back() = 0;
        virtual void push_front(T) = 0;
        virtual void push_back(T) = 0;
        virtual void pop_front() = 0;
        virtual void pop_back() = 0;
        virtual T operator[](int) = 0;
        virtual bool empty() = 0;
        virtual int size() = 0;
        virtual void clear() = 0;
        virtual void sort() = 0;
        virtual void reverse() = 0;
        virtual std::string name() = 0;
};

template <typename T>
List<T>::~List(){
    Node<T> *temp = new Node<T>(0);
    temp = this->head;
    while (this->nodes)
    {
        this->head = temp->next;
        temp->killSelf();
        temp = this->head;
        --this->nodes;
    }
    delete this->head, this->tail;
}

#endif