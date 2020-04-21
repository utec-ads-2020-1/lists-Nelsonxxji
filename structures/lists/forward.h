#ifndef FORWARD_H
#define FORWARD_H

#include "list.h"
#include "iterators/forward_iterator.h"

// TODO: Implement Sort
template <typename T>
class ForwardList : public List<T>
{

public:
    ForwardList() : List<T>() {}

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

    ForwardIterator<T> begin();
    ForwardIterator<T> end();

    std::string name()
    {
        return "Forward List";
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
    void merge(ForwardList<T> &);
};

template <typename T>
T ForwardList<T>::front()
{
    if (this->empty())
    {
        throw "Error ForwardList::front(): List is empty";
    }
    else
    {
        return this->head->data;
    }
}

template <typename T>
T ForwardList<T>::back()
{
    if (this->empty())
    {
        throw "Error ForwardList::back(): List is empty";
    }
    else
    {
        return this->tail->data;
    }
}

template <typename T>
void ForwardList<T>::push_front(T data)
{
    Node<T> *newNode = new Node<T>(data);
    if (this->empty())
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        newNode->next = this->head;
        this->head = newNode;
    }
    this->nodes++;
}

template <typename T>
void ForwardList<T>::push_back(T data)
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
        this->tail = newNode;
    }
    this->nodes++;
}

template <typename T>
void ForwardList<T>::pop_front()
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

template <typename T>
void ForwardList<T>::pop_back()
{
    if (this->empty())
    {
        throw "Error ForwardList::pop_back(): List is empty";
    }
    else
    {
        Node<T> *temp(0);
        temp = this->head;
        while (temp != this->tail->next)
        {
            temp = temp->next;
        }
        temp->next = nullptr;
        delete this->tail;
        this->tail = temp;
        --this->nodes;
    }
}

template <typename T>
T ForwardList<T>::operator[](int index)
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
        throw "Error ForwardList::[](): List index is out of range";
    }
    else
    {
        int tempIndex = 0;
        Node<T> *temp(0);
        temp = this->head;
        while (tempIndex != index)
        {
            temp = temp->next;
            ++tempIndex;
        }
        return temp->data;
    }
}

template <typename T>
bool ForwardList<T>::empty()
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
int ForwardList<T>::size()
{
    return this->nodes;
}

template <typename T>
void ForwardList<T>::clear()
{
    Node<T> *temp = new Node<T>(0);
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
void ForwardList<T>::sort()
{
    if (this->empty() || this->nodes == 1)
    {
        return;
    }
    else
    {
    }
}

template <typename T>
void ForwardList<T>::reverse()
{
    if (this->empty())
    {
        throw "Error ForwardList::reverse(): List is empty";
    }
    else
    {
        Node<T> *temp = new Node<T>(0);
        for (int i = 0; i < this->nodes - 1; i++)
        {
            temp = this->head;
            for (int j = 0; j < this->nodes - 2 - i; j++)
            {
                temp = temp->next;
            }
            temp->next->next = temp;
        }
        temp = this->head;
        this->head = this->tail;
        this->tail = temp;
        this->tail->next = nullptr;
    }
}
#endif