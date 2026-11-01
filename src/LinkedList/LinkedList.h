#pragma once
#include "Node.h"



class LinkedList {
    public:
    Node* head;
    Node* prev;

    LinkedList() {
        head = nullptr;
        prev = nullptr;
    }
    
    void add(int data);
    void remove(int data);
    // void delete(int data); olmuyor ?
    void display();
    // int main(); -bu kullanım yok main h de oluturulmaz 
};