#ifndef LINKEDLIST_CPP
#define LINKEDLIST_CPP

#include "LinkedList.h"
#include <iostream>

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

template <typename T>
LinkedList<T>::~LinkedList(){
    clear();    
}

template <typename T>
void LinkedList<T>::add_back(T data){

    Node<T>* newNode = new Node(data);

    // head is nullptr, assign to head
    if(head == nullptr){
        head = newNode;
        tail = newNode;
        return;
    }
    
    Node<T>* current = head;
    Node<T>* last = tail;

    last->next = newNode;
    newNode->prev = tail;
    newNode->next = head; //circular LinkedList
    tail = newNode;
    head->prev = tail;
}

template <typename T>
void LinkedList<T>::insert(T data, int position){
    //do nothing yet
}

template <typename T>
void LinkedList<T>::display(){
    std::cout << "display" << std::endl;
}

template <typename T>
void LinkedList<T>::clear(){
    if(head == nullptr){
        return; //empty
    }
    
    Node<T>* current = head;

    while(current != nullptr && current->next != head){
        Node<T>* next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
}

#endif