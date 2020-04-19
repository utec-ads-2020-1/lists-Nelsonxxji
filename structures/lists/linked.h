#ifndef LINKED_H
#define LINKED_H

#include <iostream>
#include "list.h"
#include "iterators/bidirectional_iterator.h"

using namespace std;

// TODO: Implement all methods
template <typename T>
class LinkedList : public List<T>
{
public:
    LinkedList() : List<T>() {}

    T front();
    T back();
    void push_front(T);
    void push_back(T);
    void pop_front();
    void pop_back();
    T operator[](int);
    bool empty();
    int size();
    void clear();
    void sort();
    void reverse();

    BidirectionalIterator<T> begin();
    BidirectionalIterator<T> end();

    string name()
    {
        return "Linked List";
    }

    /**
         * Merges x into the list by transferring all of its elements at their respective 
         * ordered positions into the container (both containers shall already be ordered).
         * 
         * This effectively removes all the elements in x (which becomes empty), and inserts 
         * them into their ordered position within container (which expands in size by the number 
         * of elements transferred). The operation is performed without constructing nor destroying
         * any element: they are transferred, no matter whether x is an lvalue or an rvalue, 
         * or whether the value_type supports move-construction or not.
        */
    void merge(LinkedList<T> &);
};

template <typename T>
T LinkedList<T>::front()
{
    return 1;
}

template <typename T>
T LinkedList<T>::back()
{
    return 1;
}

template <typename T>
void LinkedList<T>::push_front(T data)
{
    Node<T> *newNode = new Node<T>(data);
    if (this->empty())
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        this->head->prev = newNode;
        newNode->next = this->head;
        this->head = newNode;
    }
    this->nodes++;
}

template <typename T>
void LinkedList<T>::push_back(T data)
{
    Node<T> *newNode = new Node<T>(data);
    if (this->empty())
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        this->tail->next = newNode;
        newNode->prev = this->tail;
        this->tail = newNode;
    }
    this->nodes++;
}

template <typename T>
void LinkedList<T>::pop_front()
{
    try
    {
        if (this->empty())
        {
            throw "Error ForwardList::pop_front(): List is empty";
        }
        else
        {
            Node<T> *temp(0);
            temp = this->head->next;
            delete this->head;
            this->head = temp;
            --this->nodes;
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
}

template <typename T>
void LinkedList<T>::pop_back()
{
    Node<T> *temp(0);
    temp = this->tail->prev;
    delete this->tail;
    temp->next = nullptr;
    this->tail = temp;
    --this->nodes;
}

template <typename T>
T LinkedList<T>::operator[](int index)
{
    if (index == 0 && !this->empty())
    {
        return this->head->data;
    }
    else if (index == this->nodes - 1)
    {
        return this->tail->data;
    }
    else if (index >= this->nodes)
    {
        cerr << "Error LinkedList::[](): List index is out of range" << endl;
    }
    else
    {
        Node<T> *temp(0);
        if (index <= (this->nodes - 1) / 2)
        {
            int tempIndex = 0;
            temp = this->head;
            while (tempIndex != index)
            {
                temp = temp->next;
                ++tempIndex;
            }
        }
        else
        {
            int tempIndex = this->nodes - 1;
            temp = this->tail;
            while (tempIndex != index)
            {
                temp = temp->prev;
                --tempIndex;
            }
        }
        return temp->data;
    }
}

template <typename T>
bool LinkedList<T>::empty()
{
    if (!this->head)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
int LinkedList<T>::size()
{
    return this->nodes;
}

template <typename T>
void LinkedList<T>::clear()
{
    Node<T> *temp(0);
    temp = this->head;
    while (this->head)
    {
        this->head = temp->next;
        temp->killSelf();
        temp = this->head;
    }
    this->nodes = 0;
}

template <typename T>
void LinkedList<T>::sort()
{
}

template <typename T>
void LinkedList<T>::reverse()
{
    Node<T>* temp(0);
    
}
#endif