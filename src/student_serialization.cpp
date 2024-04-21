#include "student_types.h"
#include <sstream>

void serializeInt(std::ostream& out, int value) {
    out << value;
}

void serializeString(std::ostream& out, const std::string& value) {
    out << value;
}

void serializeNivelStudii(std::ostream& out, NivelStudii nivel) {
    switch (nivel) {
        case NivelStudii::Licenta: out << "Licenta"; break;
        case NivelStudii::Masterat: out << "Masterat"; break;
    }
}

void serializeStudent(std::ostream& out, const Student& student) {
    serializeInt(out, student.id);
    out << ",";
    serializeString(out, student.specialitatea);
    out << ",";
    serializeNivelStudii(out, student.nivelStudii);
    out << "\n";
}

bool deserializeStudent(std::istream& in, Student& student) {
    std::string line;
    if (!std::getline(in, line)) {
        return false;
    }

    std::istringstream lineStream(line);
    std::string idStr, nivelStr;
    if (!std::getline(lineStream, idStr, ',') ||
        !std::getline(lineStream, student.specialitatea, ',') ||
        !std::getline(lineStream, nivelStr, ',')) {
        return false;
    }

    student.id = std::stoi(idStr);
    if (nivelStr == "Licenta") student.nivelStudii = NivelStudii::Licenta;
    else if (nivelStr == "Masterat") student.nivelStudii = NivelStudii::Masterat;
    else return false;

    return true;
}

void serializeStudents(std::ostream& out, const std::vector<Student>& students) {
    for (const auto& student : students) {
        serializeStudent(out, student);
    }
}

std::vector<Student> deserializeStudents(std::istream& in) {
    std::vector<Student> students;
    Student student;
    while (deserializeStudent(in, student)) {
        students.push_back(student);
    }
    return students;
}