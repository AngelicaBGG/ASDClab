#include <iostream>
#include <cstdlib>

enum class NivelStudii {
    Licenta,
    Masterat
};

struct Student {
    int id;
    std::string specialitatea;
    NivelStudii nivelStudii;
};

struct Node {
    Student data;
    Node* next;
};

class Queue {
private:
    Node* front; // referinta la primul node din lista
    Node* rear;  // referinta la ultimul node din lista

public:
    Queue() : front(nullptr), rear(nullptr) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void enqueue(const Student& student) {
        Node* newNode = new Node{student, nullptr};
        if (rear == nullptr) {
            // daca lista e goala, front si rear trebuie sa fie newNode
            front = rear = newNode;
        } else {
            // altfel, rear->next trebuie sa fie newNode
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (isEmpty()) {
            std::cerr << "Queue is empty" << std::endl;
            return;
        }
        Node* temp = front;
        front = front->next;

        // daca lista e goala, rear trebuie sa fie nullptr
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    Student frontStudent() const {
        if (isEmpty()) {
            std::cerr << "Queue is empty" << std::endl;
            exit(EXIT_FAILURE);
        }
        return front->data;
    }
};

int main() {
    Queue queue;

    queue.enqueue({1, "Computer Science", NivelStudii::Licenta});
    queue.enqueue({2, "Physics", NivelStudii::Masterat});

    Student s = queue.frontStudent();
    std::cout << "Front student ID: " << s.id << ", Speciality: " << s.specialitatea << std::endl;

    queue.dequeue();

    if (!queue.isEmpty()) {
        s = queue.frontStudent();
        std::cout << "Front student ID: " << s.id << ", Speciality: " << s.specialitatea << std::endl;
    }

    return 0;
}
