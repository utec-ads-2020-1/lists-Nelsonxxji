#ifndef LINKED_H
#define LINKED_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"

template <typename T>
class LinkedList : public List<T>
{
private:
    Node<T> *MergeSort(Node<T> *);
    Node<T> *Split(Node<T> *);
    Node<T> *SortedMerge(Node<T> *&, Node<T> *&);

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
    //void updateSentinel();

    BidirectionalIterator<T> begin();
    BidirectionalIterator<T> end();

    std::string name()
    {
        return "Linked List";
    }

    void merge(LinkedList<T> &);
};

template <typename T>
BidirectionalIterator<T> LinkedList<T>::begin()
{
    //return BidirectionalIterator<T>(this->sentinel->next);
    return BidirectionalIterator<T>(this->head);
}

template <typename T>
BidirectionalIterator<T> LinkedList<T>::end()
{
    //return BidirectionalIterator<T>(this->sentinel->prev);
    return BidirectionalIterator<T>(this->tail->next);
}

template <typename T>
T LinkedList<T>::front()
{
    if (this->empty())
    {
        throw "Error LinkedList::front(): List is empty";
    }
    return this->head->data;
}

template <typename T>
T LinkedList<T>::back()
{
    if (this->empty())
    {
        throw "Error LinkedList::back(): List is empty";
    }
    return this->tail->data;
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
    //this->updateSentinel();
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
    //this->updateSentinel();
}

template <typename T>
void LinkedList<T>::pop_front()
{
    if (!this->empty())
    {
        Node<T> *temp(0);
        temp = this->head->next;
        delete this->head;
        this->head = temp;
        --this->nodes;
        //this->updateSentinel();
    }
}

template <typename T>
void LinkedList<T>::pop_back()
{
    if (!this->empty())
    {
        Node<T> *temp(0);
        temp = this->tail->prev;
        delete this->tail;
        temp->next = nullptr;
        this->tail = temp;
        --this->nodes;
        //this->updateSentinel();
    }
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
        throw "Error LinkedList::[](): List index is out of range";
    }
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

template <typename T>
bool LinkedList<T>::empty()
{
    return !this->head;
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
    this->head = this->MergeSort(this->head);
    this->tail = this->head;
    while (this->tail->next){
        this->tail = this->tail->next;
    }
    //this->updateSentinel();
}

template <typename T>
Node<T> *LinkedList<T>::MergeSort(Node<T> *headPtr)
{
    if (!headPtr || !headPtr->next)
    {
        return headPtr;
    }
    Node<T> *b = this->Split(headPtr);
    headPtr = this->MergeSort(headPtr);
    b = this->MergeSort(b);
    return this->SortedMerge(headPtr, b);
}

template <typename T>
Node<T> *LinkedList<T>::Split(Node<T> *headPtr)
{
    Node<T> *fast = headPtr;
    Node<T> *slow = headPtr;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node<T> *temp = slow->next;
    slow->next = nullptr;
    return temp;
}

template <typename T>
Node<T> *LinkedList<T>::SortedMerge(Node<T> *&a, Node<T> *&b)
{
    if (!a)
    {
        return b;
    }
    if (!b)
    {
        return a;
    }
    if (a->data < b->data)
    {
        a->next = this->SortedMerge(a->next, b);
        a->next->prev = a;
        a->prev = nullptr;
        return a;
    }
    else
    {
        b->next = this->SortedMerge(a, b->next);
        b->next->prev = b;
        b->prev = nullptr;
        return b;
    }
}

template <typename T>
void LinkedList<T>::reverse()
{
    if (!this->empty())
    {
        if (this->nodes == 1)
        {
            return;
        }
        Node<T> *temp1(0);
        Node<T> *temp2(0);
        Node<T> *temp3(0);

        temp3 = this->head;

        temp1 = this->head;
        temp1->prev = temp1->next;
        temp1->next = nullptr;
        temp1 = temp1->prev;
        while (temp1 != this->tail)
        {
            temp2 = temp1->prev;
            temp1->prev = temp1->next;
            temp1->next = temp2;
            temp1 = temp1->prev;
        }
        temp1->next = temp1->prev;
        temp1->prev = nullptr;
        this->head = temp1;
        this->tail = temp3;
        //this->updateSentinel();
    }
}

template <typename T>
void LinkedList<T>::merge(LinkedList<T> &mergeList)
{
    if (this->empty())
    {
        this->head = mergeList.head;
        this->tail = mergeList.tail;
        this->nodes = mergeList.nodes;
    }
    else if (mergeList.empty())
    {
        return;
    }
    else
    {
        this->tail->next = mergeList.head;
        mergeList.head->prev = this->tail;
        this->tail = mergeList.tail;
        this->nodes += mergeList.nodes;
    }
    mergeList.head = nullptr;
    mergeList.tail = nullptr;
    mergeList.nodes = 0;
    //this->updateSentinel();
}

/*
template <typename T>
void LinkedList<T>::updateSentinel(){
    this->sentinel->next = this->head;
    this->sentinel->prev = this->tail;
}
*/
#endif