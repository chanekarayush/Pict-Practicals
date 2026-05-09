#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>
#include <algorithm>
#include <chrono>

using namespace std;

/**
 * The OpenMP implementation below is correct. 
 * The 'reduction' clause handles thread-local copies and combines them safely at the end.
 * For maximum performance, compile with -O3 and -fopenmp.
 */

void initialize_array(vector<int>& arr, int n) {
    // Faster initialization for benchmarking
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        arr[i] = i % 1000; 
    }
}

void sequential_ops(const vector<int>& arr, int n) {
    int min_val = INT_MAX;
    int max_val = INT_MIN;
    long long sum = 0;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
        sum += arr[i];
    }
    double average = (double)sum / n;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "\n--- Sequential Operations ---" << endl;
    cout << "Min: " << min_val << endl;
    cout << "Max: " << max_val << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;
    cout << "Time: " << duration.count() << " seconds" << endl;
}

void parallel_ops(const vector<int>& arr, int n) {
    int min_val = INT_MAX;
    int max_val = INT_MIN;
    long long sum = 0;

    auto start = chrono::high_resolution_clock::now();
    
    // Correct usage of reduction for multiple variables
    #pragma omp parallel for reduction(min:min_val) reduction(max:max_val) reduction(+:sum)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
        sum += arr[i];
    }
    
    double average = (double)sum / n;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "\n--- Parallel Operations ---" << endl;
    cout << "Min: " << min_val << endl;
    cout << "Max: " << max_val << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;
    cout << "Time: " << duration.count() << " seconds" << endl;
}

int main() {
    // Increased n to 100 million to better observe parallel scaling
    int n = 100000000; 
    vector<int> arr(n);

    initialize_array(arr, n);

    sequential_ops(arr, n);
    parallel_ops(arr, n);

    return 0;
}
