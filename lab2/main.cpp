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
    int anul;
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


class Cautare
{
    Students date;
public:
    Cautare(Students date)
    {
        this->date = date;
    }
    Student Cautarea_Binara_dupa_an(int an)
    {
       std::cout << "\nCautarea Binara dupa an\n";
               
       int Limita_Stanga = 0;
       int Limita_Dreapta = date.size() - 1;
       while(Limita_Stanga <= Limita_Dreapta)
       {
           int Centru = Limita_Stanga + (Limita_Dreapta - Limita_Stanga) / 2;
           int anCentru = date[Centru].anul;
           if(anCentru == an) {
               return date[Centru]; // Возвращаем найденного студента
           }
           else if(anCentru < an) {
               Limita_Stanga = Centru + 1;
           }
           else {
               Limita_Dreapta = Centru - 1;
           }
       }
        
        return date[0];
    }
    Student Cautarea_in_Metoda_lui_Fibonacci_dupa_an(int an)
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
            if(date[i].anul < an)
            {
                Fib = Fib1;
                Fib1 = Fib2;
                Fib2 = Fib-Fib1;
                Ech = i;
            }
            else if(date[i].anul > an)
            {
                Fib = Fib2;
                Fib1 = Fib1-Fib2;
                Fib2 = Fib-Fib1;
            }
            else return date[i];
        }
        if(Fib1 && date[Ech+1].anul == an) return date[Ech+1];
        return date[0];
    }
    Student Metoda_Secventiala_de_Cautare_dupa_An(int An)
    {
        cout << "\nMetoda Secventiala de Cautare dupa An\n";
        for(Student El:date)
        {
            if(El.anul == An) return El;
        }
        return date[0];
    }
    Student static Cautarea_in_Arborele_Binar_de_Cautare(Nod *Varf, int An)
    {
        while(true)
        {
            int Va1 = Varf->Date.anul;
            if(Va1 == An) return Varf->Date;
            else if(Va1 > An) Varf = Varf->min;
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
                if(LM->Date.anul < Va1.anul)
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
    std::cout << "Anul: " << student.anul << ", Specialitatea: " << student.specialitatea << ", Nivelul de studii: ";
    serializeNivelStudii(std::cout, student.nivelStudii);
    std::cout << std::endl;
}

int main() {
//    std::vector<Student> students = {
//        {1, "Informatica", NivelStudii::Licenta},
//        {2, "Matematica", NivelStudii::Masterat}
//    };
//
//    std::ofstream outFile("students.csv");
//    serializeStudents(outFile, students);
//    outFile.close();

    std::ifstream inFile("students.csv");
    std::vector<Student> deserializedStudents = deserializeStudents(inFile);
    inFile.close();
    for (const auto& student : deserializedStudents) {
        std::cout << "Anul: " << student.anul << ", Specialitatea: " << student.specialitatea << ", Nivelul de studii: ";
        serializeNivelStudii(std::cout, student.nivelStudii);
        std::cout << std::endl;
    }
    
    Cautare search(deserializedStudents);
    
    auto start = std::chrono::high_resolution_clock::now();
    
    print(search.Metoda_Secventiala_de_Cautare_dupa_An(2));
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "\nCautarea Secventiala timp: " << elapsed.count() << " ms\n";
    
    
    cout << "Arborele binar" << endl;
    auto start1 = std::chrono::high_resolution_clock::now();
    
    Arbore Cautarea_in_Arborele_Binar_de_Cautare(deserializedStudents);
    Nod *Varf = Cautarea_in_Arborele_Binar_de_Cautare.Obtine_Nod();
    
    print(Cautare::Cautarea_in_Arborele_Binar_de_Cautare(Varf, 2));
    
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed1 = end1 - start1;
    std::cout << "\nCautarea Arborele binar timp: " << elapsed1.count() << " ms\n";
    
    auto start2 = std::chrono::high_resolution_clock::now();
    
    print(search.Cautarea_Binara_dupa_an(2));
    
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed2 = end2 - start2;
    std::cout << "\nCautarea binara timp: " << elapsed2.count() << " ms\n";
    
    auto start3 = std::chrono::high_resolution_clock::now();
    
    print(search.Cautarea_in_Metoda_lui_Fibonacci_dupa_an(2));

    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed3 = end3 - start3;
    std::cout << "\nCautarea binara timp: " << elapsed3.count() << " ms\n";

    return 0;
}