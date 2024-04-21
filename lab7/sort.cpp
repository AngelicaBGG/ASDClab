#include "student_types.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

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

class SortingAlgorithm {
public:
    virtual ~SortingAlgorithm() {}

    // Template method that executes the sort and measures time.
    SortMetrics sort(std::vector<Student>& data) {
        auto start = std::chrono::high_resolution_clock::now();
        executeSort(data);
        auto end = std::chrono::high_resolution_clock::now();
        metrics.duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        return metrics;
    }

protected:
    virtual void executeSort(std::vector<Student>& data) = 0;
    SortMetrics metrics;
};



class BubbleSort : public SortingAlgorithm {
protected:
    void executeSort(std::vector<Student>& data) override {
        bool swapped;
        do {
            swapped = false;
            for (size_t i = 1; i < data.size(); i++) {
                metrics.comparisons++;
                if (data[i - 1].id > data[i].id) {
                    std::swap(data[i - 1], data[i]);
                    metrics.swaps++;
                    swapped = true;
                }
            }
        } while (swapped);
    }
};

class InsertionSort : public SortingAlgorithm {
protected:
    void executeSort(std::vector<Student>& data) override {
        for (size_t i = 1; i < data.size(); i++) {
            Student key = data[i];
            size_t j = i;
            while (j > 0 && data[j - 1].id > key.id) {
                metrics.comparisons++;
                data[j] = data[j - 1];
                metrics.swaps++;
                j--;
            }
            data[j] = key;
        }
    }
};


class QuickSort : public SortingAlgorithm {
protected:
    void executeSort(std::vector<Student>& data) override {
        quickSortHelper(data, 0, data.size() - 1);
    }

    void quickSortHelper(std::vector<Student>& arr, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(arr, low, high);
            quickSortHelper(arr, low, pivotIndex - 1);
            quickSortHelper(arr, pivotIndex + 1, high);
        }
    }

    int partition(std::vector<Student>& arr, int low, int high) {
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
        return i + 1;
    }
};

class MergeSort : public SortingAlgorithm {
protected:
    void executeSort(std::vector<Student>& data) override {
        mergeSortHelper(data, 0, data.size() - 1);
    }

    void mergeSortHelper(std::vector<Student>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortHelper(arr, left, mid);
            mergeSortHelper(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    void merge(std::vector<Student>& arr, int left, int mid, int right) {
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
};


int main() {
    std::ifstream inFile("lab7/students-shuffled-data.csv");
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

    BubbleSort bubbleSort;
    InsertionSort insertionSort;
    QuickSort quickSort;
    MergeSort mergeSort;

    printMetrics(bubbleSort.sort(students));
    printMetrics(insertionSort.sort(students));
    printMetrics(quickSort.sort(students));
    printMetrics(mergeSort.sort(students));

    return 0;
}