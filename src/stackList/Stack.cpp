#include "Stack.h"
#include <format>
#include <iostream>
#include <string>



void StackList::push(int data){
    StackNode* newNode = new StackNode(data);

    if (top == nullptr){
        top = newNode;
    } else {
        newNode->next = top;
        top = newNode;
    }
    std::cout<< std::format("<{}>\n",(*top).data);

}

void StackList::pop(){
    if (top == nullptr){
        std::cout<< "Stack Is Empty \n";
    }
    else {
        int del = (*top).data;
        StackNode* temp = top;
        top = top->next;
        std::cout<< std::format("popped --> {}\n",del);
        delete temp;

    }
}

void StackList::display(){

    if (top == nullptr){
        std::cout<< "Stack Is Empty \n";
    }
    else {
        StackNode* temp = top;
        while (temp != nullptr){
            std::cout<< std::format(" -> {}",(*temp).data);
            temp = (*temp).next;
        }
        std::cout<< "\n";
    }

}

int main(){

    StackList myStack;

    myStack.display();

    myStack.push(1);
    myStack.push(234);
    myStack.push(17);
    myStack.push(5);

    myStack.display();

    myStack.pop();

    myStack.display();



}