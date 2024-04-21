#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

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

typedef vector<Student> Students;

struct Nod
{
    Student Date;
    Nod *min;
    Nod *max;
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


class Cautare
{
    Students date;
public:
    Cautare(Students date)
    {
        this->date = date;
    }
    Student* Cautarea_Binara_dupa_id(int an)
    {
    std::cout << "\nCautarea Binara dupa id\n";
            
    int Limita_Stanga = 0;
    int Limita_Dreapta = date.size() - 1;
    while(Limita_Stanga <= Limita_Dreapta)
    {
        int Centru = Limita_Stanga + (Limita_Dreapta - Limita_Stanga) / 2;
        int anCentru = date[Centru].id;

        if(anCentru == an) {
            return &date[Centru]; // Return a pointer to the found student
        }
        else if(anCentru < an) {
            Limita_Stanga = Centru + 1;
        }
        else {
            Limita_Dreapta = Centru - 1;
        }
    }
        
        return nullptr; // Return nullptr if not found
    }
    Student* Cautarea_in_Metoda_lui_Fibonacci_dupa_id(int id)
    {
        cout << "\nCautarea in Metoda lui Fibonacci dupa ID\n";
        int Lun = date.size();
        int Fib1 = 1;
        int Fib2 = 0;
        int Fib = 1;
        int Ech = -1;
        while(Fib < Lun)
        {
            Fib2 = Fib1;
            Fib1 = Fib;
            Fib = Fib2+Fib1;
        }
        while(Fib > 1)
        {
            int i = (Ech+Fib2 < Lun-1) ? Ech+Fib2 : Lun-1;
            if(date[i].id < id)
            {
                Fib = Fib1;
                Fib1 = Fib2;
                Fib2 = Fib-Fib1;
                Ech = i;
            }
            else if(date[i].id > id)
            {
                Fib = Fib2;
                Fib1 = Fib1-Fib2;
                Fib2 = Fib-Fib1;
            }
            else return &date[i];
        }
        if(Fib1 && date[Ech+1].id == id) return &date[Ech+1];
        return nullptr;
    }
    Student* Metoda_Secventiala_de_Cautare_dupa_id(int id)
    {
        cout << "\nMetoda Secventiala de Cautare dupa id\n";
        for(Student El:date)
        {
            if(El.id == id) return &El;
        }
        return nullptr;
    }
    Student static Cautarea_in_Arborele_Binar_de_Cautare(Nod *Varf, int id)
    {
        while(true)
        {
            int Va1 = Varf->Date.id;
            if(Va1 == id) return Varf->Date;
            else if(Va1 > id) Varf = Varf->min;
            else Varf = Varf->max;
        }
    }
};

class Arbore
{
    Students Date;
    Nod *Varf;
public:
    Arbore(Students Date)
    {
        this->Date = Date;
        Sarcina();
    }
    void Sarcina()
    {
        Varf = new Nod;
        Varf->Date = Date[0];
        Varf->min = NULL;
        Varf->max = NULL;
        for(int i = 1; i < Date.size(); i++)
        {
            Nod * LM = Varf;
            Student Va1 = Date[i];
            while(true)
            {
                if(LM->Date.id < Va1.id)
                {
                    if(LM->max == NULL)
                    {
                        LM->max = new Nod;
                        LM = LM->max;
                        LM->Date = Va1;
                        LM->min = NULL;
                        LM->max = NULL;
                        break;
                    }
                    else LM = LM->max;
                }
                else
                {
                    if(LM->min == NULL)
                    {
                        LM->min = new Nod;
                        LM = LM->min;
                        LM->Date = Va1;
                        LM->min = NULL;
                        LM->max = NULL;
                        break;
                    }
                    else LM = LM->min;
                }
            }
        }
    }
    Nod *Obtine_Nod()
    {
        return Varf;
    }
};

void print_Antet()
{
    cout << "\nAnul\tSpecialiatea\tNivelulDeStudii\n";
}

void print(Student student){
    std::cout << "Id-ul: " << student.id << ", Specialitatea: " << student.specialitatea << ", Nivelul de studii: ";
    serializeNivelStudii(std::cout, student.nivelStudii);
    std::cout << std::endl;
}

int main() {
    std::ifstream inFile("students-shuffled-data.csv");
    std::vector<Student> notSortedStudents = deserializeStudents(inFile);
    inFile.close();
    
    Cautare search(notSortedStudents);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    Student* res = search.Metoda_Secventiala_de_Cautare_dupa_id(2);

    if (res != nullptr) {
        // If the student is found, print details
        std::cout << "Student found: ID = " << res->id << std::endl;
    } else {
        // If not found, print a message
        std::cout << "No student found with ID " << 2 << "." << std::endl;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "\nCautarea Secventiala timp: " << elapsed.count() << " ms\n";
    
    
    cout << "Arborele binar" << endl;
    auto start1 = std::chrono::high_resolution_clock::now();
    
    Arbore Cautarea_in_Arborele_Binar_de_Cautare(notSortedStudents);
    Nod *Varf = Cautarea_in_Arborele_Binar_de_Cautare.Obtine_Nod();
    
    print(Cautare::Cautarea_in_Arborele_Binar_de_Cautare(Varf, 2));
    
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed1 = end1 - start1;
    std::cout << "\nCautarea Arborele binar timp: " << elapsed1.count() << " ms\n";
    
    //// sorted
    std::ifstream inFileSorted("students_sorted_data.csv");
    std::vector<Student> sortedStudents = deserializeStudents(inFileSorted);
    inFileSorted.close();

    Cautare searchSorted(sortedStudents);
    
    Student* result = searchSorted.Cautarea_Binara_dupa_id(2);

    if (result != nullptr) {
        // If the student is found, print details
        std::cout << "Student found: ID = " << result->id << std::endl;
    } else {
        // If not found, print a message
        std::cout << "No student found with ID " << 2 << "." << std::endl;
    }
    

    Student* newResult = searchSorted.Cautarea_in_Metoda_lui_Fibonacci_dupa_id(2);

    if (newResult != nullptr) {
        // If the student is found, print details
        std::cout << "Student found: ID = " << newResult->id << std::endl;
    } else {
        // If not found, print a message
        std::cout << "No student found with ID " << 2 << "." << std::endl;
    }

    return 0;
}