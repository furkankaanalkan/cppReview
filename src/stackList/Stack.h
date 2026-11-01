#pragma once
#include "StackNode.h"


class StackList {
    public:
        StackNode* top;
        StackNode* next;

    StackList(){
        this->next = nullptr;
        this->top = nullptr;
    }

    void push (int data);

    void pop ();

    void display ();

};