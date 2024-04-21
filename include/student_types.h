#pragma once
#include <string>
#include <vector>

// Enumeration for the level of studies
enum class NivelStudii {
    Licenta,
    Masterat
};

// Student structure
struct Student {
    int id;
    std::string specialitatea;
    NivelStudii nivelStudii;
};

// Type alias for a vector of Students
typedef std::vector<Student> Students;

// Node structure for a binary tree
struct Nod {
    Student Date;
    Nod *min;
    Nod *max;
};

// Function declarations
void serializeInt(std::ostream& out, int value);
void serializeString(std::ostream& out, const std::string& value);
void serializeNivelStudii(std::ostream& out, NivelStudii nivel);
void serializeStudent(std::ostream& out, const Student& student);
bool deserializeStudent(std::istream& in, Student& student);
void serializeStudents(std::ostream& out, const std::vector<Student>& students);
std::vector<Student> deserializeStudents(std::istream& in);