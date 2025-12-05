#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
struct Node;


template <typename T>
class LinkedList {
public:
    Node<T>* head;
    Node<T>* tail;
    LinkedList();
    ~LinkedList();
    
    void add_back(T data);
    void insert(T data, int position);
    void clear();
    void display();
};

template <typename T>
struct Node
{
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(T val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

#include "LinkedList.cpp"


#endif