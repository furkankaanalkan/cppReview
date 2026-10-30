#pragma once
#include "Node.h"


class LinkedList {
    public:
    Node* head;
    Node* prev;
    Node* current;
    void add(int data);
    
    void remove(int data);
    // void delete(int data); olmuyor ?
};