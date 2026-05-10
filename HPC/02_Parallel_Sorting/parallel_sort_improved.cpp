/*
 * parallel_sort.cpp
 * Demonstrates sequential vs parallel sorting using OpenMP.
 * Algorithms: Bubble Sort (Odd-Even variant) and Merge Sort.
 *
 * Compile: g++ -O2 -fopenmp -o parallel_sort parallel_sort.cpp
 * Run:     ./parallel_sort
 */

#include <iostream>
#include <vector>
#include <omp.h>
#include <algorithm>
#include <ctime>
#include <iomanip>
using namespace std;

// ─────────────────────────────────────────────
// BUBBLE SORT — SEQUENTIAL
// Standard O(n²) comparison-based sort.
// Each pass bubbles the largest unsorted element to its correct position.
// ─────────────────────────────────────────────
void bubbleSortSequential(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        // After i passes, the last i elements are already in place
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ─────────────────────────────────────────────
// BUBBLE SORT — PARALLEL (Odd-Even Transposition Sort)
//
// Standard bubble sort cannot be parallelized directly because each swap
// depends on the previous one (data dependency). Odd-Even Sort resolves
// this by alternating between two independent phases per pass:
//   • Even phase: compare/swap pairs (0,1), (2,3), (4,5), ...
//   • Odd  phase: compare/swap pairs (1,2), (3,4), (5,6), ...
// Within each phase, all pairs are independent → safe to parallelize.
//
// FIX: The outer parallel region is placed OUTSIDE the loop to avoid
// repeatedly creating/destroying thread teams (high overhead).
// The implicit barrier at the end of each `#pragma omp for` ensures
// all threads finish one phase before the next begins — required for
// correctness because odd and even phases depend on each other's results.
// ─────────────────────────────────────────────
void bubbleSortParallel(vector<int>& arr) {
    int n = arr.size();

    // Launch threads once; they collaborate on every pass
    #pragma omp parallel
    {
        for (int i = 0; i < n; i++) {
            // Even pass (i even): start at index 0; Odd pass: start at index 1
            int first = i % 2;

            // Each thread handles a disjoint subset of non-overlapping pairs
            // nowait is intentionally NOT used: barrier ensures phase sync
            #pragma omp for
            for (int j = first; j < n - 1; j += 2) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
            // Implicit barrier here: all threads sync before the next phase
        }
    }
}

// ─────────────────────────────────────────────
// MERGE HELPER
// Merges two sorted sub-arrays: arr[l..m] and arr[m+1..r]
// into a single sorted segment in-place.
// ─────────────────────────────────────────────
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;   // Size of left half
    int n2 = r - m;       // Size of right half

    // Temporary copies so we can overwrite arr[] safely
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    // Merge back into arr[]
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else               arr[k++] = R[j++];
    }
    // Copy any remaining elements
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// ─────────────────────────────────────────────
// MERGE SORT — SEQUENTIAL
// Classic O(n log n) divide-and-conquer sort.
// ─────────────────────────────────────────────
void mergeSortSequential(vector<int>& arr, int l, int r) {
    if (l >= r) return;   // Base case: single element is already sorted

    int m = l + (r - l) / 2;               // Midpoint (avoids integer overflow)
    mergeSortSequential(arr, l, m);         // Sort left half
    mergeSortSequential(arr, m + 1, r);     // Sort right half
    merge(arr, l, m, r);                    // Merge sorted halves
}

// ─────────────────────────────────────────────
// MERGE SORT — PARALLEL
//
// FIX 1 — Use `#pragma omp task` instead of `#pragma omp parallel sections`.
//   `parallel sections` inside a recursive function would spawn a NEW thread
//   team on every recursive call, causing exponential thread creation and
//   extreme overhead. Tasks are lightweight units of work scheduled by an
//   existing thread pool — correct for recursive parallelism.
//
// FIX 2 — The cutoff threshold.
//   Small sub-arrays are sorted sequentially to avoid task-creation overhead
//   outweighing the benefit of parallelism. A threshold of ~2000 elements
//   works well in practice (tunable based on hardware).
//
// FIX 3 — `#pragma omp taskwait` before merge.
//   Both recursive tasks must COMPLETE before we can merge their results.
//   taskwait suspends the current task until its directly spawned child
//   tasks finish — this replaces the broken barrier from sections.
//
// Caller must wrap the initial call in:
//   #pragma omp parallel
//   { #pragma omp single
//     { mergeSortParallel(arr, 0, n-1); } }
// ─────────────────────────────────────────────
void mergeSortParallel(vector<int>& arr, int l, int r) {
    if (l >= r) return;   // Base case

    int m = l + (r - l) / 2;

    if (r - l < 2000) {
        // Sub-array small enough: sequential sort avoids task overhead
        mergeSortSequential(arr, l, m);
        mergeSortSequential(arr, m + 1, r);
    } else {
        // Spawn two independent tasks for the two halves
        #pragma omp task shared(arr)
        mergeSortParallel(arr, l, m);

        #pragma omp task shared(arr)
        mergeSortParallel(arr, m + 1, r);

        // Wait for BOTH tasks to complete before merging
        #pragma omp taskwait
    }

    merge(arr, l, m, r);
}

// ─────────────────────────────────────────────
// UTILITIES
// ─────────────────────────────────────────────

// Restore arr to its original unsorted state before each benchmark run
void resetArray(vector<int>& arr, const vector<int>& original) {
    arr = original;
}

// Verify that the array is non-decreasingly sorted
bool isSorted(const vector<int>& arr) {
    for (size_t i = 0; i + 1 < arr.size(); i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

// ─────────────────────────────────────────────
// MAIN — Benchmark driver
// ─────────────────────────────────────────────
int main() {
    int n          = 10000;   // Default array size
    int iterations = 3;       // Runs per algorithm (averaged)

    // Allow user to override array size
    cout << "Enter number of elements (default " << n << "): ";
    string input;
    getline(cin, input);
    if (!input.empty()) {
        try {
            int parsed = stoi(input);
            if (parsed > 0) {
                n = parsed;
            } else {
                cout << "Must be positive; using default " << n << ".\n";
            }
        } catch (...) {
            cout << "Invalid input; using default " << n << ".\n";
        }
    }

    // Seed and fill array with random values in [0, 9999]
    srand(static_cast<unsigned>(time(nullptr)));
    vector<int> original(n);
    for (int i = 0; i < n; i++) original[i] = rand() % 10000;

    cout << "\nThreads available : " << omp_get_max_threads() << "\n";
    cout << "Array size        : " << n << " elements\n";
    cout << "Iterations        : " << iterations << " (averaged)\n";
    cout << "\n"
         << left << setw(30) << "Algorithm"
         << right << setw(12) << "Avg Time(s)"
         << setw(10) << "Sorted?"
         << "\n"
         << string(52, '-') << "\n";

    vector<int> arr;
    double start, total_time;

    // ── Sequential Bubble Sort ──────────────────
    total_time = 0;
    for (int i = 0; i < iterations; i++) {
        resetArray(arr, original);
        start = omp_get_wtime();
        bubbleSortSequential(arr);
        total_time += omp_get_wtime() - start;
    }
    cout << left  << setw(30) << "Sequential Bubble Sort"
         << right << setw(12) << fixed << setprecision(6) << total_time / iterations
         << setw(10) << (isSorted(arr) ? "Yes" : "NO") << "\n";

    // ── Parallel Bubble Sort ────────────────────
    total_time = 0;
    for (int i = 0; i < iterations; i++) {
        resetArray(arr, original);
        start = omp_get_wtime();
        bubbleSortParallel(arr);
        total_time += omp_get_wtime() - start;
    }
    cout << left  << setw(30) << "Parallel Bubble Sort"
         << right << setw(12) << fixed << setprecision(6) << total_time / iterations
         << setw(10) << (isSorted(arr) ? "Yes" : "NO") << "\n";

    // ── Sequential Merge Sort ───────────────────
    total_time = 0;
    for (int i = 0; i < iterations; i++) {
        resetArray(arr, original);
        start = omp_get_wtime();
        mergeSortSequential(arr, 0, n - 1);
        total_time += omp_get_wtime() - start;
    }
    cout << left  << setw(30) << "Sequential Merge Sort"
         << right << setw(12) << fixed << setprecision(6) << total_time / iterations
         << setw(10) << (isSorted(arr) ? "Yes" : "NO") << "\n";

    // ── Parallel Merge Sort ─────────────────────
    // A single `parallel` region is created; one thread (`single`) kicks off
    // the recursive task tree; all threads then steal and execute tasks.
    total_time = 0;
    for (int i = 0; i < iterations; i++) {
        resetArray(arr, original);
        start = omp_get_wtime();
        #pragma omp parallel
        {
            #pragma omp single
            mergeSortParallel(arr, 0, n - 1);
        }
        total_time += omp_get_wtime() - start;
    }
    cout << left  << setw(30) << "Parallel Merge Sort"
         << right << setw(12) << fixed << setprecision(6) << total_time / iterations
         << setw(10) << (isSorted(arr) ? "Yes" : "NO") << "\n";

    cout << string(52, '-') << "\n";
    return 0;
}
