#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>

enum class NivelStudii {
    Licenta,
    Masterat
};

struct Student {
    int id;
    std::string specialitatea;
    NivelStudii nivelStudii;
};

struct SortMetrics {
    std::chrono::milliseconds duration;
    long long comparisons = 0;
    long long swaps = 0;
};

void printMetrics(const SortMetrics& metrics) {
    std::cout << "Time: " << metrics.duration.count() << "ms, "
              << "Comparisons: " << metrics.comparisons << ", "
              << "Swaps: " << metrics.swaps << std::endl;
}

SortMetrics bubbleSort(std::vector<Student>& arr) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    SortMetrics metrics;

    bool swapped;
    do {
        swapped = false;
        for (size_t i = 1; i < arr.size(); i++) {
            metrics.comparisons++;
            if (arr[i - 1].id > arr[i].id) {
                std::swap(arr[i - 1], arr[i]);
                metrics.swaps++;
                swapped = true;
            }
        }
    } while (swapped);

    auto end = high_resolution_clock::now();
    metrics.duration = duration_cast<milliseconds>(end - start);
    return metrics;
}

SortMetrics insertionSort(std::vector<Student>& arr) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    SortMetrics metrics;

    for (size_t i = 1; i < arr.size(); i++) {
        Student key = arr[i];
        size_t j = i;
        while (j > 0 && arr[j - 1].id > key.id) {
            metrics.comparisons++;
            arr[j] = arr[j - 1];
            metrics.swaps++;
            j--;
        }
        arr[j] = key;
        if (j != i) metrics.swaps++;
    }

    auto end = high_resolution_clock::now();
    metrics.duration = duration_cast<milliseconds>(end - start);
    return metrics;
}

void quickSortHelper(std::vector<Student>& arr, int low, int high, SortMetrics& metrics) {
    if (low < high) {
        Student pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            metrics.comparisons++;
            if (arr[j].id < pivot.id) {
                i++;
                std::swap(arr[i], arr[j]);
                metrics.swaps++;
            }
        }
        std::swap(arr[i + 1], arr[high]);
        metrics.swaps++;
        quickSortHelper(arr, low, i, metrics);
        quickSortHelper(arr, i + 2, high, metrics);
    }
}

SortMetrics quickSort(std::vector<Student>& arr) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    SortMetrics metrics;

    quickSortHelper(arr, 0, arr.size() - 1, metrics);

    auto end = high_resolution_clock::now();
    metrics.duration = duration_cast<milliseconds>(end - start);
    return metrics;
}

void merge(std::vector<Student>& arr, int left, int mid, int right, SortMetrics& metrics) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<Student> L(arr.begin() + left, arr.begin() + left + n1);
    std::vector<Student> R(arr.begin() + mid + 1, arr.begin() + mid + 1 + n2);

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        metrics.comparisons++;
        if (L[i].id <= R[j].id) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
        metrics.swaps++;
    }

    while (i < n1) {
        arr[k++] = L[i++];
        metrics.swaps++;
    }

    while (j < n2) {
        arr[k++] = R[j++];
        metrics.swaps++;
    }
}

void mergeSortHelper(std::vector<Student>& arr, int left, int right, SortMetrics& metrics) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid, metrics);
        mergeSortHelper(arr, mid + 1, right, metrics);
        merge(arr, left, mid, right, metrics);
    }
}

SortMetrics mergeSort(std::vector<Student>& arr) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    SortMetrics metrics;

    mergeSortHelper(arr, 0, arr.size() - 1, metrics);
    auto end = high_resolution_clock::now();
    metrics.duration = duration_cast<milliseconds>(end - start);
    return metrics;
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


std::vector<Student> deserializeStudents(std::istream& in) {
    std::vector<Student> students;
    Student student;
    while (deserializeStudent(in, student)) {
        students.push_back(student);
    }
    return students;
}


int main() {
    std::ifstream inFile("students-shuffled-data.csv");
    if (!inFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::vector<Student> deserializedStudents = deserializeStudents(inFile);
    inFile.close();

    if (deserializedStudents.empty()) {
        std::cerr << "No data to process." << std::endl;
        return 1;
    }

    std::vector<Student> students = deserializedStudents;

    // Bubble Sort
    std::cout << "Testing Bubble Sort:" << std::endl;
    students = deserializedStudents; // Reset to original data
    SortMetrics bubbleMetrics = bubbleSort(students);
    printMetrics(bubbleMetrics);

    // Insertion Sort
    std::cout << "Testing Insertion Sort:" << std::endl;
    students = deserializedStudents; // Reset to original data
    SortMetrics insertionMetrics = insertionSort(students);
    printMetrics(insertionMetrics);

    // Quick Sort
    std::cout << "Testing Quick Sort:" << std::endl;
    students = deserializedStudents; // Reset to original data
    SortMetrics quickMetrics = quickSort(students);
    printMetrics(quickMetrics);

    // Merge Sort
    std::cout << "Testing Merge Sort:" << std::endl;
    students = deserializedStudents; // Reset to original data
    SortMetrics mergeMetrics = mergeSort(students);
    printMetrics(mergeMetrics);

    return 0;
}