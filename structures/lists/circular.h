#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"

using namespace std;

// TODO: Implement all methods
template <typename T>
class CircularLinkedList : public List<T>
{
public:
    CircularLinkedList() : List<T>() {}

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
        return "Circular Linked List";
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
    void merge(CircularLinkedList<T> &);
};

template <typename T>
T CircularLinkedList<T>::front()
{
    try
    {
        if (this->empty())
        {
            throw "Error CircularLinkedList::front(): List is empty";
        }
        else
        {
            return this->head->data;
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
}

template <typename T>
T CircularLinkedList<T>::back()
{
    try
    {
        if (this->empty())
        {
            throw "Error CircularLinkedList::back(): List is empty";
        }
        else
        {
            return this->tail->data;
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
}

template <typename T>
void CircularLinkedList<T>::push_front(T data)
{

    Node<T> *newNode = new Node<T>(data);
    if (this->empty())
    {
        this->head = newNode;
        this->head->next = newNode;
        this->head->prev = newNode;
        this->tail = newNode;
    }
    else
    {
        this->head->prev = newNode;
        this->tail->next = newNode;
        newNode->next = this->head;
        newNode->prev = this->tail;
        this->head = newNode;
    }
    ++this->nodes;
}

template <typename T>
void CircularLinkedList<T>::push_back(T data)
{
    Node<T> *newNode = new Node<T>(data);
    if (this->empty())
    {
        this->head = newNode;
        this->head->next = newNode;
        this->head->prev = newNode;
        this->tail = newNode;
    }
    else
    {
        this->tail->next = newNode;
        this->head->prev = newNode;
        newNode->prev = this->tail;
        newNode->next = this->head;
        this->tail = newNode;
    }
    ++this->nodes;
}

template <typename T>
void CircularLinkedList<T>::pop_front()
{
    try
    {
        if (this->empty())
        {
            throw "Error CircularLinkedList::pop_front(): List is empty";
        }
        else
        {
            Node<T> *temp(0);
            temp = this->head->next;
            delete this->head;
            temp->prev = this->tail;
            this->tail->next = temp;
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
void CircularLinkedList<T>::pop_back()
{
    return;
}

template <typename T>
T CircularLinkedList<T>::operator[](int index)
{
    return 1;
}

template <typename T>
bool CircularLinkedList<T>::empty()
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
int CircularLinkedList<T>::size()
{
    return this->nodes;
}

template <typename T>
void CircularLinkedList<T>::clear()
{
    return;
}

template <typename T>
void CircularLinkedList<T>::sort()
{
    return;
}

template <typename T>
void CircularLinkedList<T>::reverse()
{
    return;
}
#endif