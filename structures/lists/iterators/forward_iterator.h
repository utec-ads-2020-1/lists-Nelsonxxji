#ifndef FORWARD_ITERATOR_H
#define FORWARD_ITERATOR_H

#include "../node.h"

template <typename T>
class ForwardIterator
{
private:
    Node<T> *current;

public:
    ForwardIterator();
    ForwardIterator(Node<T> *);

    ForwardIterator<T> operator=(ForwardIterator<T>);

    bool operator!=(ForwardIterator<T>);

    ForwardIterator<T> operator++();

    T operator*();
};

template <typename T>
ForwardIterator<T>::ForwardIterator()
{
    this->current = nullptr;
}

template <typename T>
ForwardIterator<T>::ForwardIterator(Node<T> *node)
{
    this->current = node;
}

template <typename T>
ForwardIterator<T> ForwardIterator<T>::operator=(ForwardIterator<T> itr)
{
    this->current = itr.current;
    return itr;
}

template <typename T>
bool ForwardIterator<T>::operator!=(ForwardIterator<T> itr)
{
    if (this->current == itr.current)
    {
        return false;
    }
    else
    {
        return true;
    }
}

template <typename T>
ForwardIterator<T> ForwardIterator<T>::operator++()
{
    if(!this->current){
        throw "Error ForwardIterator::operator++(): Iterator is NULL";
    }
    this->current = this->current->next;
}

template <typename T>
T ForwardIterator<T>::operator*()
{
    if(!this->current){
        throw "Error ForwardIterator::operator*(): Iterator is NULL";
    }
    return this->current->data;
}

#endif