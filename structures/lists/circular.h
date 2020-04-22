#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"

// TODO: Implement end()
template <typename T>
class CircularLinkedList : public List<T>
{
private:
    Node<T> *MergeSort(Node<T> *);
    Node<T> *Split(Node<T> *);
    Node<T> *SortedMerge(Node<T> *&, Node<T> *&);

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

    std::string name()
    {
        return "Circular Linked List";
    }

    void merge(CircularLinkedList<T> &);
};

template <typename T>
BidirectionalIterator<T> CircularLinkedList<T>::begin(){
    return BidirectionalIterator<T>(this->head);
}

template <typename T>
BidirectionalIterator<T> CircularLinkedList<T>::end(){
    Node<T>* temp = new Node<T>(0);
    this->tail->next = temp;
    this->head->prev = temp;
    return BidirectionalIterator<T>(temp->next);
}

template <typename T>
T CircularLinkedList<T>::front()
{
    if (this->empty())
    {
        throw "Error CircularLinkedList::front(): List is empty";
    }
    return this->head->data;
}

template <typename T>
T CircularLinkedList<T>::back()
{
    if (this->empty())
    {
        throw "Error CircularLinkedList::back(): List is empty";
    }
    return this->tail->data;
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
    if (this->empty())
    {
        throw "Error CircularLinkedList::pop_front(): List is empty";
    }
    Node<T> *temp(0);
    temp = this->head->next;
    delete this->head;
    temp->prev = this->tail;
    this->tail->next = temp;
    this->head = temp;
    --this->nodes;
}

template <typename T>
void CircularLinkedList<T>::pop_back()
{
    if (this->empty())
    {
        throw "Error CircularLinkedList::pop_back(): List is empty";
    }
    Node<T> *temp(0);
    temp = this->tail->prev;
    delete this->tail;
    temp->next = this->head;
    this->head->prev = temp;
    this->tail = temp;
    --this->nodes;
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
        throw "Error CircularLinkedList::[](): List index is out of range";
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
    this->head->prev = nullptr;
    this->tail->next = nullptr;
    this->head = this->MergeSort(this->head);
    this->head->prev = this->tail;
    this->tail->next = this->head;
}

template <typename T>
Node<T> *CircularLinkedList<T>::MergeSort(Node<T> *headPtr)
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
Node<T> *CircularLinkedList<T>::Split(Node<T> *headPtr)
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
Node<T> *CircularLinkedList<T>::SortedMerge(Node<T> *&a, Node<T> *&b)
{
    if (!a)
    {
        this->tail = b;
        return b;
    }
    if (!b)
    {
        this->tail = a;
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
void CircularLinkedList<T>::reverse()
{
    if (this->empty())
    {
        throw "Error CircularLinkedList::reverse(): List is empty";
    }
    else if (this->nodes == 1)
    {
        return;
    }
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

template <typename T>
void CircularLinkedList<T>::merge(CircularLinkedList<T> &mergeList)
{
    if (this->empty() || mergeList.empty())
    {
        throw "Error CircularLinkedList::merge(): Cannot merge empty List";
    }
    this->tail->next = mergeList.head;
    mergeList.head->prev = this->tail;
    this->tail = mergeList.tail;
    this->tail->next = this->head;
    this->head->prev = this->tail;
    this->nodes += mergeList.nodes;
    mergeList.head = nullptr;
    mergeList.tail = nullptr;
    mergeList.nodes = 0;
}
#endif