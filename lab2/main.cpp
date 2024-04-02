#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

enum class NivelStudii {
    Licenta,
    Masterat
};

struct Student {
    int anul;
    std::string specialitatea;
    NivelStudii nivelStudii;
};

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
    serializeInt(out, student.anul);
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

    std::string anulStr, nivelStr;
    if (!std::getline(lineStream, anulStr, ',') ||
        !std::getline(lineStream, student.specialitatea, ',') ||
        !std::getline(lineStream, nivelStr, ',')) {
        return false;
    }

    student.anul = std::stoi(anulStr);
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

int main() {
    std::vector<Student> students = {
        {1, "Informatica", NivelStudii::Licenta},
        {2, "Matematica", NivelStudii::Masterat}
    };

    std::ofstream outFile("students.csv");
    serializeStudents(outFile, students);
    outFile.close();

    std::ifstream inFile("students.csv");
    std::vector<Student> deserializedStudents = deserializeStudents(inFile);
    inFile.close();

    for (const auto& student : deserializedStudents) {
        std::cout << "Anul: " << student.anul << ", Specialitatea: " << student.specialitatea << ", Nivelul de studii: ";
        serializeNivelStudii(std::cout, student.nivelStudii);
        std::cout << std::endl;
    }

    return 0;
}