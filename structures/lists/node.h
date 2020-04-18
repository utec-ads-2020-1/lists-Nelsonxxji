#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(T data)
    {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }

    void killSelf();
};

template <typename T>
void Node<T>::killSelf(){
    delete this;
}

#endif