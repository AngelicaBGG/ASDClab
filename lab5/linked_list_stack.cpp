#include <iostream>

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

class Stack {
private:
    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    void push(const Student& student) {
        Node* newNode = new Node{student, top};
        top = newNode;
    }

    Student pop() {
        if (isEmpty()) {
            std::cerr << "Stack is empty" << std::endl;
            exit(EXIT_FAILURE);
        }
        Node* nodeToDelete = top;
        top = top->next;
        Student data = nodeToDelete->data;
        delete nodeToDelete;
        return data;
    }

    const Student& topStudent() const {
        if (isEmpty()) {
            std::cerr << "Stack is empty" << std::endl;
            exit(EXIT_FAILURE);
        }
        return top->data;
    }
};

int main() {
    Stack studentStack;

    // Example of pushing students into the stack
    studentStack.push({1, "Computer Science", NivelStudii::Licenta});
    studentStack.push({2, "Physics", NivelStudii::Masterat});

    // Displaying top student
    Student s = studentStack.topStudent();
    std::cout << "Top student ID: " << s.id << ", Speciality: " << s.specialitatea << std::endl;

    // Popping student
    Student s1 = studentStack.pop();
    std::cout << "Top student ID: " << s1.id << ", Speciality: " << s1.specialitatea << std::endl;
    // Popping student
    Student s2 = studentStack.pop();
    std::cout << "Top student ID: " << s2.id << ", Speciality: " << s2.specialitatea << std::endl;


    return 0;
}
