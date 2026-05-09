#include <iostream>
#include <vector>
#include <omp.h>
#include <algorithm>
#include <ctime>

using namespace std;

// Bubble Sort Sequential
void bubbleSortSequential(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Bubble Sort Parallel (Odd-Even Sort)
// Optimized by keeping the parallel region outside the loop to reduce overhead
void bubbleSortParallel(vector<int>& arr) {
    int n = arr.size();
    #pragma omp parallel
    {
        for (int i = 0; i < n; i++) {
            int first = i % 2;
            #pragma omp for
            for (int j = first; j < n - 1; j += 2) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

// Merge Sort Helper: Merge two sorted halves
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Merge Sort Sequential
void mergeSortSequential(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortSequential(arr, l, m);
        mergeSortSequential(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Merge Sort Parallel
void mergeSortParallel(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        // If subarray is small, sort sequentially to avoid task overhead
        if (r - l < 1000) { 
            mergeSortSequential(arr, l, m);
            mergeSortSequential(arr, m + 1, r);
        } else {
            #pragma omp parallel sections
            {
                #pragma omp section
                mergeSortParallel(arr, l, m);
                #pragma omp section
                mergeSortParallel(arr, m + 1, r);
            }
        }
        merge(arr, l, m, r);
    }
}

void resetArray(vector<int>& arr, const vector<int>& original) {
    arr = original;
}

bool isSorted(const vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

int main() {
    int n = 10000;
    int iterations = 3;
    cout << "Enter number of elements (default 10000): ";
    string input;
    getline(cin, input);
    if (!input.empty()) {
        try {
            n = stoi(input);
        } catch (...) {
            cout << "Invalid input, using default 10000" << endl;
        }
    }

    // Initialize array with random values
    srand(time(0));
    vector<int> original(n);
    for (int i = 0; i < n; i++) original[i] = rand() % 10000;

    vector<int> arr;
    double start, total_time;

    cout << "\n--- Performance Measurement (" << iterations << " iterations average) ---\n";

    // Bubble Sort Sequential
    total_time = 0;
    for (int i = 0; i < iterations; i++) {
        resetArray(arr, original);
        start = omp_get_wtime();
        bubbleSortSequential(arr);
        total_time += omp_get_wtime() - start;
    }
    cout << "Avg Sequential Bubble Sort: " << total_time / iterations << "s (Sorted: " << isSorted(arr) << ")" << endl;

    // Bubble Sort Parallel
    total_time = 0;
    for (int i = 0; i < iterations; i++) {
        resetArray(arr, original);
        start = omp_get_wtime();
        bubbleSortParallel(arr);
        total_time += omp_get_wtime() - start;
    }
    cout << "Avg Parallel Bubble Sort:   " << total_time / iterations << "s (Sorted: " << isSorted(arr) << ")" << endl;

    // Merge Sort Sequential
    total_time = 0;
    for (int i = 0; i < iterations; i++) {
        resetArray(arr, original);
        start = omp_get_wtime();
        mergeSortSequential(arr, 0, n - 1);
        total_time += omp_get_wtime() - start;
    }
    cout << "Avg Sequential Merge Sort:  " << total_time / iterations << "s (Sorted: " << isSorted(arr) << ")" << endl;

    // Merge Sort Parallel
    total_time = 0;
    for (int i = 0; i < iterations; i++) {
        resetArray(arr, original);
        start = omp_get_wtime();
        // Use parallel region to start tasks
        #pragma omp parallel
        {
            #pragma omp single
            mergeSortParallel(arr, 0, n - 1);
        }
        total_time += omp_get_wtime() - start;
    }
    cout << "Avg Parallel Merge Sort:    " << total_time / iterations << "s (Sorted: " << isSorted(arr) << ")" << endl;

    return 0;
}
