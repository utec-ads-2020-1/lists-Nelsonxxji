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

    void merge(ForwardList<T> &);
};

template <typename T>
T ForwardList<T>::front()
{
    if (this->empty())
    {
        throw "Error ForwardList::front(): List is empty";
    }
    return this->head->data;
}

template <typename T>
T ForwardList<T>::back()
{
    if (this->empty())
    {
        throw "Error ForwardList::back(): List is empty";
    }
    return this->tail->data;
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
    Node<T> *temp(0);
    temp = this->head->next;
    delete this->head;
    this->head = temp;
    --this->nodes;
}

template <typename T>
void ForwardList<T>::pop_back()
{
    if (this->empty())
    {
        throw "Error ForwardList::pop_back(): List is empty";
    }
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

template <typename T>
void ForwardList<T>::merge(ForwardList<T> &mergeList)
{
    if (this->empty() || mergeList.empty())
    {
        throw "Error ForwardList::merge(): Cannot merge empty List";
    }
    this->tail->next = mergeList.head;
    this->tail = mergeList.tail;
    this->nodes += mergeList.nodes;
    mergeList.head = nullptr;
    mergeList.tail = nullptr;
    mergeList.nodes = 0;
}
#endif