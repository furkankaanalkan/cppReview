#include "LinkedList.h"
#include "Node.h"
#include <format>
#include <iostream>
#include <string>

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
        current = newNode;
        std::cout << std::format("added --> {}\n",data);

    }
};

void LinkedList::remove(int data){
    Node* current = head;
    
    if (head == nullptr) {
        std::cout<< "you cant remove in empty list" << std::endl;
        return;
    }
    else  {
        while (current->next != nullptr) {

            if (current->data == data){

                 if (current == head) {
                    current->prev = nullptr;
                    current->next = nullptr;
                    return;
                } 
                else{
                    current->prev->next = current->next;
                    if (current->next != nullptr) {
                        current->next->prev = current->prev;
                    }
                }

                std::cout << std::format("delted --> {}",data);
                delete current;
                return;
            }
           
           current = (*current).next;
        }  
    }
};

void LinkedList::display(){
    Node* current = head;

    if (head == nullptr){
        std::cout<< "the list is empty" << std::endl;
    }
    else {
        while (current->next != nullptr){
            std::cout << std::format("delted --> {}",current->data);
            
            current = current->next;
        }
    }
}


int main(){

    LinkedList myList;

    myList.display();

    myList.remove(12);

    myList.add(17);
    myList.add(43);
    myList.add(74);
    myList.add(56);
    myList.add(1000);

    myList.display();

    myList.remove(74);

    myList.display();
};