#include <iostream>
#include <vector>

enum class NivelStudii {
    Licenta,
    Masterat
};

struct Student {
    int id;
    std::string specialitatea;
    NivelStudii nivelStudii;
};

class Stack {
private:
    std::vector<Student> elements;

public:
    bool isEmpty() const {
        return elements.empty();
    }

    void push(const Student& student) {
        elements.push_back(student);
    }

    Student pop() {
        if (isEmpty()) {
            std::cerr << "Stack is empty" << std::endl;
            exit(EXIT_FAILURE);
        }
        Student top = elements.back();
        elements.pop_back();
        return top;
    }

    const Student& getLastElement() const {
        if (isEmpty()) {
            std::cerr << "Stack is empty" << std::endl;
            exit(EXIT_FAILURE);
        }
        return elements.back();
    }
};

int main() {
    Stack studentStack;

    studentStack.push({1, "Computer Science", NivelStudii::Licenta});
    studentStack.push({2, "Physics", NivelStudii::Masterat});

    Student s = studentStack.getLastElement();
    std::cout << "Top student ID: " << s.id << ", Speciality: " << s.specialitatea << std::endl;

    Student s1 = studentStack.pop();
    std::cout << "Top student ID: " << s1.id << ", Speciality: " << s1.specialitatea << std::endl;

    Student s2 = studentStack.pop();
    std::cout << "Top student ID: " << s2.id << ", Speciality: " << s2.specialitatea << std::endl;

    return 0;
}
