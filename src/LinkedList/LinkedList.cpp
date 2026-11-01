#include "LinkedList.h"
#include "Node.h"
#include <format>
#include <iostream>
#include <string>

void LinkedList::add(int data) {
    Node* newNode = new Node(data);

    if (head == nullptr) {
        head = newNode; 
    } else {
        Node* current = head;
        
        // Ekleme işleminde son düğümde durmamız gerektiği için current->next kontrolü DOĞRUDUR.
        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = newNode;
        newNode->prev = current;
    }
    
    // Hem ilk eleman eklendiğinde hem de sonrakilerde ekrana yazması için dışarı alındı
    std::cout << std::format("added --> {}\n", data); 
}

void LinkedList::remove(int data) {
    Node* current = head;

    if (head == nullptr) {
        std::cout << "you cant remove in empty list\n";
        return;
    }

    // Son elemanı da kontrol edebilmek için current->next yerine current kontrol edilmeli
    while (current != nullptr) {
        if (current->data == data) {
            if (current == head) {
                // Eğer silinen baştaki elemansa head'i bir sonrakine kaydır
                head = current->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
            } 
            else {
                // Ortadan veya sondan siliniyorsa
                current->prev->next = current->next;
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                }
            }

            std::cout << std::format("deleted --> {}\n", data);
            delete current; // Düğümü bellekten temizle (ÇOK ÖNEMLİ)
            return;
        }
        current = current->next;
    }
    
    std::cout << std::format("{} not found in the list\n", data);
}

void LinkedList::display() {
    Node* current = head;

    if (head == nullptr) {
        std::cout << "the list is empty\n";
    } 
    else {
        std::cout << "List: ";
        while (current != nullptr) {
            std::cout << std::format("{} ", current->data);
            current = current->next;
        }
        std::cout << "\n";
    }
}

int main() {

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
    
    return 0;
}
