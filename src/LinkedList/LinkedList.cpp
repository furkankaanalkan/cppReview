#pragma once
#include "LinkedList.h"

void LinkedList::add(int data) {
    Node* newNode = new Node(data);
    if (head == nullptr) {
        head = prev = newNode;
    } else {
        Node* current = head;

        while (current->next != nullptr) {
            current = current->next;
        }
        
        (*current).next = newNode;
        newNode->prev = current;
    }
}