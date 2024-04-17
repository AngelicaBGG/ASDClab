#include <string>
#include <iostream>
#include <cassert>

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

    Node(Student val) : data(val), next(nullptr) {}
};

struct FindNodeResult {
    Node* foundNode;
    Node* previousNode;
};

class LinkedList {
public:
    Node* head;
    Node* tail;
    int length;

    LinkedList() : head(nullptr), tail(nullptr), length(0) {}
    ~LinkedList();

    Node* insertAfter(Node* node, Student value);
    FindNodeResult find(int id);
    void removeAfter(Node* node);
    void assertNoCycles();
    void print();
};

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
}

Node* LinkedList::insertAfter(Node* node, Student value) {
    Node* newNode = new Node(value);
    if (node == nullptr) { // insereaza la inceput
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) {
            tail = head;
        }
    } else {
        newNode->next = node->next;
        node->next = newNode;
        if (node == tail) {
            tail = newNode;
        }
    }
    length++;
    return newNode;
}

FindNodeResult LinkedList::find(int id) {
    Node* current = head;
    Node* previous = nullptr;
    while (current != nullptr) {
        if (current->data.id == id) {
            return {current, previous};
        }
        previous = current;
        current = current->next;
    }
    return {nullptr, nullptr};
}

void LinkedList::removeAfter(Node* node) {
    if (node == nullptr && head != nullptr) { //sterge head
        Node* toDelete = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete toDelete;
    } else if (node != nullptr && node->next != nullptr) {
        Node* toDelete = node->next;
        node->next = toDelete->next;
        if (toDelete == tail) {
            tail = node;
        }
        delete toDelete;
    }
    length--;
}

void LinkedList::assertNoCycles() {
    int count = 0;
    Node* slow = head;
    Node* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            assert(false && "Ciclu detectat");
        }
        count++;
        if (count > length) {
            assert(false && "Ciclu detectat in baza depasirii lungimii");
        }
    }
}

void LinkedList::print() {
    Node* current = head;
    while (current != nullptr) {
        std::cout << "Student ID: " << current->data.id << ", Speciality: " << current->data.specialitatea << ", Level: ";
        if (current->data.nivelStudii == NivelStudii::Licenta) {
            std::cout << "Bachelor";
        } else {
            std::cout << "Master";
        }
        std::cout << std::endl;
        current = current->next;
    }
}

int main() {
    LinkedList list;

    // Ceva date
    Student s1 = {1, "Informatica", NivelStudii::Licenta};
    Student s2 = {2, "Matematica", NivelStudii::Licenta};
    Student s3 = {3, "Fizica", NivelStudii::Masterat};

    // Adaugare student
    list.insertAfter(nullptr, s1); // head
    list.insertAfter(list.head, s2); // dupa head
    list.insertAfter(list.head, s3); // dupa head, s3 al doilea, s2 devine al treilea

    // Print lista
    std::cout << "Initial list:" << std::endl;
    list.print();

    // Gaseste student
    auto result = list.find(2);
    if (result.foundNode != nullptr) {
        std::cout << "Found Student ID: " << result.foundNode->data.id << std::endl;
    } else {
        std::cout << "Student with ID 2 not found." << std::endl;
    }

    // sterge dupa al doilea student
    if (result.previousNode != nullptr) {
        list.removeAfter(result.previousNode);
    } else {
        // daca precedentul este null, prezentul este head
        list.removeAfter(nullptr);
    }

    // Print lista dupa stergere
    std::cout << "Lista dupa stergere la al doilea element:" << std::endl;
    list.print();

    // Demonstrare assertNoCycles
    list.assertNoCycles();

    return 0;
}
