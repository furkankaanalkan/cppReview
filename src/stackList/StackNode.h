#pragma once

class StackNode {

    public:
        int data;
        StackNode* next;

    StackNode(int data){
        this->data = data;
        this->next = nullptr;
    }

};