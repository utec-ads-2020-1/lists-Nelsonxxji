#ifndef FORWARD_H
#define FORWARD_H

#include "list.h"
#include "iterators/forward_iterator.h"

template <typename T>
class ForwardList : public List<T>
{
private:
    void MergeSort(Node<T> **);
    void FrontBackSplit(Node<T> *, Node<T> **, Node<T> **);
    Node<T> *SortedMerge(Node<T> *&, Node<T> *&);

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
ForwardIterator<T> ForwardList<T>::begin()
{
    return ForwardIterator<T>(this->head);
}

template <typename T>
ForwardIterator<T> ForwardList<T>::end()
{
    return ForwardIterator<T>(this->tail->next);
}

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
    if (!this->empty())
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
    if (!this->empty())
    {
        Node<T> *temp(0);
        temp = this->head;
        while (temp->next != this->tail)
        {
            temp = temp->next;
        }
        delete this->tail;
        temp->next = nullptr;
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
    return !this->head;
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
    this->MergeSort(&this->head);
    this->tail = this->head;
    while (this->tail->next){
        this->tail = this->tail->next;
    }
}

template <typename T>
void ForwardList<T>::MergeSort(Node<T> **headPtr)
{
    Node<T> *head = *headPtr;
    Node<T> *a, *b;
    if ((head == nullptr) || (head->next == nullptr))
    {
        return;
    }
    FrontBackSplit(head, &a, &b);
    this->MergeSort(&a);
    this->MergeSort(&b);
    *headPtr = this->SortedMerge(a, b);
}

template <typename T>
void ForwardList<T>::FrontBackSplit(Node<T> *list,
                                    Node<T> **frontSubList, Node<T> **backSubList)
{
    Node<T> *fast;
    Node<T> *slow;
    slow = list;
    fast = list->next;
    while (fast != nullptr)
    {
        fast = fast->next;
        if (fast != nullptr)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *frontSubList = list;
    *backSubList = slow->next;
    slow->next = nullptr;
}

template <typename T>
Node<T> *ForwardList<T>::SortedMerge(Node<T> *&a, Node<T> *&b)
{
    Node<T> *res = nullptr;
    if (!a)
    {
        return b;
    }
    else if (!b)
    {
        return a;
    }
    if (a->data <= b->data)
    {
        res = a;
        res->next = this->SortedMerge(a->next, b);
    }
    else
    {
        res = b;
        res->next = this->SortedMerge(a, b->next);
    }
    return (res);
}

template <typename T>
void ForwardList<T>::reverse()
{
    if (!this->empty())
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

template <typename T>
void ForwardList<T>::merge(ForwardList<T> &mergeList)
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
        this->tail = mergeList.tail;
        this->nodes += mergeList.nodes;
    }
    mergeList.head = nullptr;
    mergeList.tail = nullptr;
    mergeList.nodes = 0;
}
#endif