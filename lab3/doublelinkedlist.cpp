#include <string>
#include <iostream>

using namespace std;

enum class NivelStudii {
    Licenta,
    Masterat
};

struct Student {
    int id;
    std::string specialitatea;
    NivelStudii nivelStudii;
};

class Node {
public:
    Student data;
    Node* next;
    Node* prev;

    Node(Student val) : data(val), next(nullptr), prev(nullptr) {}
};

class DualLinkedList {
public:
    Node* head;
    Node* tail;
    int length;

    DualLinkedList() : head(nullptr), tail(nullptr), length(0) {}
    ~DualLinkedList();

    Node* insertAfter(Node* node, Student value);
    Node* insertBefore(Node* node, Student value);
    Node* find(int value);
    void remove(Node* node);
    void assertNoCycles();
    void print();
};

DualLinkedList::~DualLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

Node* DualLinkedList::insertAfter(Node* node, Student value) {
    Node* newNode = new Node(value);
    if (node == nullptr) {
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    } else {
        newNode->next = node->next;
        newNode->prev = node;
        if (node->next != nullptr) {
            node->next->prev = newNode;
        } else {
            tail = newNode;
        }
        node->next = newNode;
    }
    length++;
    return newNode;
}

Node* DualLinkedList::insertBefore(Node* node, Student value) {
    if (node == nullptr || node == head) {
        return insertAfter(nullptr, value); // insereaza la head
    } else {
        Node* newNode = new Node(value);
        newNode->next = node;
        newNode->prev = node->prev;
        node->prev->next = newNode;
        node->prev = newNode;
        length++;
        return newNode;
    }
}

Node* DualLinkedList::find(int value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.id == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void DualLinkedList::remove(Node* node) {
    if (node == nullptr) return;

    if (node == head) {
        head = node->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;  //lista devine goala
        }
    } else if (node == tail) {
        tail = node->prev;
        tail->next = nullptr;
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    delete node;
    length--;
}

void DualLinkedList::assertNoCycles() {
    // For doubly linked list, simply ensure that each node's next's prev is itself and vice versa.
    Node* current = head;
    while (current != nullptr && current->next != nullptr) {
        if (current->next->prev != current || (current->prev != nullptr && current->prev->next != current)) {
            std::cerr << "inconsistenta" << std::endl;
            return;
        }
        current = current->next;
    }
}

void DualLinkedList::print() {
    Node* current = head;
    std::cout << "Lista dublu înlănțuită conține:" << std::endl;
    while (current != nullptr) {
        std::cout << "Student ID: " << current->data.id << ", Specialitatea: " << current->data.specialitatea
                  << ", Nivel Studii: " << (current->data.nivelStudii == NivelStudii::Licenta ? "Licență" : "Masterat")
                  << std::endl;
        current = current->next;
    }
}

int main() {
    DualLinkedList list;

    // Example usage
    Student s1 = {1, "Informatică", NivelStudii::Licenta};
    Student s2 = {2, "Matematică", NivelStudii::Licenta};
    Student s3 = {3, "Fizică", NivelStudii::Masterat};

    list.insertAfter(nullptr, s1);  // Insert as first element
    list.insertAfter(list.head, s2);  // Insert after first element
    list.insertBefore(list.head->next, s3);  // Insert before second element (becomes second)

    list.print();

    Node* found = list.find(2);
    if (found != nullptr) {
        std::cout << "Găsit studentul cu ID-ul: " << found->data.id << std::endl;
    } else {
        std::cout << "Studentul cu ID-ul specificat nu a fost găsit." << std::endl;
    }

    list.remove(found);
    list.print();

    return 0;
}
