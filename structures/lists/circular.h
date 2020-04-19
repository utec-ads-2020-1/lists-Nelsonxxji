#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"

using namespace std;

// TODO: Implement Sort
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
    try
    {
        if (this->empty())
        {
            throw "Error CircularLinkedList::pop_back(): List is empty";
        }
        else
        {
            Node<T> *temp(0);
            temp = this->tail->prev;
            delete this->tail;
            temp->next = this->head;
            this->head->prev = temp;
            this->tail = temp;
            --this->nodes;
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
}

template <typename T>
T CircularLinkedList<T>::operator[](int index)
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
        cerr << "Error CircularLinkedList::[](): List index is out of range" << endl;
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
bool CircularLinkedList<T>::empty()
{
    if (this->nodes == 0)
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
    Node<T> *temp(0);
    temp = this->head;
    while (this->nodes)
    {
        this->head = temp->next;
        temp->killSelf();
        temp = this->head;
        --this->nodes;
    }
}

template <typename T>
void CircularLinkedList<T>::sort()
{
    return;
}

template <typename T>
void CircularLinkedList<T>::reverse()
{
    try
    {
        if (this->empty())
        {
            throw "Error CircularLinkedList::reverse(): List is empty";
        }
        else if (this->nodes == 1)
        {
            return;
        }
        else
        {
            Node<T> *temp1(0);
            Node<T> *temp2(0);
            Node<T> *temp3(0);

            temp3 = this->head;

            temp1 = this->head;
            temp1->prev = temp1->next;
            temp1->next = this->tail;
            temp1 = temp1->prev;
            while (temp1 != this->tail)
            {
                temp2 = temp1->prev;
                temp1->prev = temp1->next;
                temp1->next = temp2;
                temp1 = temp1->prev;
            }
            temp1->next = temp1->prev;
            temp1->prev = temp3;
            this->head = temp1;
            this->tail = temp3;
        }
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
}
#endif