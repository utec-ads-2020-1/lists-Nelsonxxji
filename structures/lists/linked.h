#ifndef LINKED_H
#define LINKED_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"

// TODO: Implement all methods
template <typename T>
class LinkedList : public List<T> {
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

        string name() {
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
        void merge(LinkedList<T>&);
};

template <typename T>
T LinkedList<T>::front(){
    return 1;
}

template <typename T>
T LinkedList<T>::back(){
    return 1;
}

template <typename T>
void LinkedList<T>::push_front(T data){
    return;
}

template <typename T>
void LinkedList<T>::push_back(T data){
    return;
}

template <typename T>
void LinkedList<T>::pop_front(){

}

template <typename T>
void LinkedList<T>::pop_back(){
    
}

template <typename T>
T LinkedList<T>::operator[](int index){
    return 1;
}

template <typename T>
bool LinkedList<T>::empty(){
    return true;
}

template <typename T>
int LinkedList<T>::size(){
    return 1;
}

template <typename T>
void LinkedList<T>::clear(){

}

template <typename T>
void LinkedList<T>::sort(){

}

template <typename T>
void LinkedList<T>::reverse(){

}
#endif