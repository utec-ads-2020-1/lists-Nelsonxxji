#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H

#include "../node.h"

// TODO: Implement all methods
template <typename T> 
class BidirectionalIterator {
    private:
        Node<T> *current;

    public:
        BidirectionalIterator();
        BidirectionalIterator(Node<T>*);

        BidirectionalIterator<T> operator=(BidirectionalIterator<T>);

        bool operator!=(BidirectionalIterator<T>);

        BidirectionalIterator<T> operator++();

        BidirectionalIterator<T> operator--();

        T operator*();
};

template <typename T>
BidirectionalIterator<T>::BidirectionalIterator()
{
    this->current = nullptr;
}

template <typename T>
BidirectionalIterator<T>::BidirectionalIterator(Node<T> *node)
{
    this->current = node;
}

template <typename T>
BidirectionalIterator<T> BidirectionalIterator<T>::operator=(BidirectionalIterator<T> itr)
{
    this->current = itr.current;
    return itr; // mejor retornar *this
}

template <typename T>
bool BidirectionalIterator<T>::operator!=(BidirectionalIterator<T> itr)
{
    if (this->current == itr.current) // Podrías hacerlo en una línea, igual no es que esté mal
    {
        return false;
    }
    else
    {
        return true;
    }
}

template <typename T>
BidirectionalIterator<T> BidirectionalIterator<T>::operator++()
{
    if(!this->current){
        throw "Error BidirectionalIterator::operator++(): Iterator is NULL";
    }
    this->current = this->current->next;
    // Faltaría retornar el iterador
}

template <typename T>
BidirectionalIterator<T> BidirectionalIterator<T>::operator--()
{
    if(!this->current){
        throw "Error BidirectionalIterator::operator--(): Iterator is NULL";
    }
    this->current = this->current->prev;
    // Faltaría retornar el iterador
}

template <typename T>
T BidirectionalIterator<T>::operator*()
{
    if(!this->current){
        throw "Error BidirectionalIterator::operator*(): Iterator is NULL";
    }
    return this->current->data;
}
#endif