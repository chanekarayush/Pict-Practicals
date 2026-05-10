/**
 * parallel_ops.cpp
 *
 * Demonstrates sequential vs. parallel array reduction using OpenMP.
 * Operations: minimum, maximum, sum, and average over a large integer array.
 *
 * Compile:
 *   g++ -O2 -fopenmp -std=c++17 -o app parallel_ops.cpp
 *
 * Run:
 *   ./app
 *   OMP_NUM_THREADS=8 ./app    <-- control thread count explicitly
 *
 * Root cause of the original bug:
 *   reduction(min : s.min_val) — OpenMP reduction clause does NOT accept
 *   struct member expressions. The compiler sees 's' as the variable,
 *   rejects the dot-access syntax, and the reduction never executes,
 *   leaving all results at their identity values (INT_MAX / INT_MIN / 0).
 *
 * Fix:
 *   Use plain local int/long long variables for the reduction clause,
 *   then copy results into the Stats struct after the parallel region.
 */

#include <iostream>
#include <vector>
#include <omp.h>     // omp_get_max_threads
#include <climits>   // INT_MAX, INT_MIN
#include <chrono>

using namespace std;
using Clock    = chrono::high_resolution_clock;
using Duration = chrono::duration<double>;

// ─────────────────────────────────────────────────────────────
// Stats — aggregates all results + elapsed time in one place.
// Returned by value so callers can compare seq vs par easily.
// ─────────────────────────────────────────────────────────────
struct Stats {
    int       min_val = INT_MAX;
    int       max_val = INT_MIN;
    long long sum     = 0;
    double    average = 0.0;
    double    elapsed = 0.0;  // wall-clock seconds
};

// ─────────────────────────────────────────────────────────────
// initialize_array
// Fills arr with (i % 1000), making results fully predictable:
//   min = 0,  max = 999,  average = 499.5
// Parallel init is race-free: each thread owns unique indices.
// ─────────────────────────────────────────────────────────────
void initialize_array(vector<int>& arr, int n) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < n; i++) {
        arr[i] = i % 1000;
    }
}

// ─────────────────────────────────────────────────────────────
// sequential_ops — single-threaded reference implementation.
// ─────────────────────────────────────────────────────────────
Stats sequential_ops(const vector<int>& arr, int n) {
    int       min_val = INT_MAX;
    int       max_val = INT_MIN;
    long long sum     = 0;

    auto start = Clock::now();

    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
        sum += arr[i];
    }

    auto end = Clock::now();

    Stats s;
    s.min_val = min_val;
    s.max_val = max_val;
    s.sum     = sum;
    s.elapsed = Duration(end - start).count();
    s.average = static_cast<double>(s.sum) / n;
    return s;
}

// ─────────────────────────────────────────────────────────────
// parallel_ops — OpenMP parallel reduction.
//
// KEY RULE: reduction() only accepts plain variables, NOT struct
// members.  Writing  reduction(min : s.min_val)  is rejected by
// the compiler (or silently ignored on older toolchains), because
// the clause cannot take a dot-expression as its operand.
//
// CORRECT PATTERN:
//   1. Declare plain local variables (min_val, max_val, sum).
//   2. Use those in the reduction clause — fully supported.
//   3. Copy into the Stats struct AFTER the parallel region ends.
//
// reduction(min : min_val)
//   -> each thread gets a private copy initialised to INT_MAX;
//      runtime takes the global minimum at the barrier.
// reduction(max : max_val)
//   -> each thread gets a private copy initialised to INT_MIN;
//      runtime takes the global maximum at the barrier.
// reduction(+ : sum)
//   -> each thread accumulates a partial sum;
//      runtime adds them all at the barrier.
//
// All three are race-condition-free with zero locking overhead.
//
// schedule(static) assigns contiguous chunks to each thread,
// maximising cache locality for a sequential memory access pattern.
// ─────────────────────────────────────────────────────────────
Stats parallel_ops(const vector<int>& arr, int n) {
    // Plain local variables — the ONLY form accepted by reduction().
    int       min_val = INT_MAX;
    int       max_val = INT_MIN;
    long long sum     = 0;

    // Timing wraps the full parallel region, including thread-creation
    // and barrier overhead, for a fair wall-clock comparison.
    auto start = Clock::now();

    #pragma omp parallel for schedule(static)   \
        reduction(min : min_val)                \
        reduction(max : max_val)                \
        reduction(+   : sum)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_val) min_val = arr[i];
        if (arr[i] > max_val) max_val = arr[i];
        sum += arr[i];
    }

    auto end = Clock::now();

    // Copy plain-variable results into the Stats struct for uniform return.
    Stats s;
    s.min_val = min_val;
    s.max_val = max_val;
    s.sum     = sum;
    s.elapsed = Duration(end - start).count();
    s.average = static_cast<double>(s.sum) / n;
    return s;
}

// ─────────────────────────────────────────────────────────────
// print_stats — formatted output helper.
// ─────────────────────────────────────────────────────────────
void print_stats(const char* label, const Stats& s) {
    cout << "\n--- " << label << " ---\n";
    cout << "  Min     : " << s.min_val << "\n";
    cout << "  Max     : " << s.max_val << "\n";
    cout << "  Sum     : " << s.sum     << "\n";
    cout << "  Average : " << s.average << "\n";
    cout << "  Time    : " << s.elapsed << " seconds\n";
}

// ─────────────────────────────────────────────────────────────
// main
// ─────────────────────────────────────────────────────────────
int main() {
    cout << "OpenMP threads available : " << omp_get_max_threads() << "\n";

    const int n = 100'000'000;  // 100 million elements (~400 MB)
    vector<int> arr(n);

    cout << "Initialising array of " << n << " elements...\n";
    initialize_array(arr, n);

    // Warmup pass: first touch of 400 MB triggers OS page faults.
    // Running once before benchmarking ensures both sequential and
    // parallel see warm memory and are compared on equal terms.
    cout << "Warming up caches...\n";
    {
        volatile long long warmup = 0;
        for (int i = 0; i < n; i++) warmup += arr[i];
        (void)warmup;
    }

    Stats seq = sequential_ops(arr, n);
    Stats par = parallel_ops  (arr, n);

    print_stats("Sequential Operations", seq);
    print_stats("Parallel Operations",   par);

    // Speedup ratio — the primary metric for parallelisation quality.
    double speedup = seq.elapsed / par.elapsed;
    cout << "\nSpeedup (seq / par)  : " << speedup << "x\n";

    // Correctness check — both paths must produce identical results.
    // If they differ, there is a reduction bug (wrong initial value,
    // missing clause, data race, etc.).
    bool ok = (seq.min_val == par.min_val) &&
              (seq.max_val == par.max_val) &&
              (seq.sum     == par.sum);
    cout << "Results match        : " << (ok ? "YES" : "NO -- BUG!") << "\n";

    return ok ? 0 : 1;  // non-zero exit on mismatch -- useful in CI
}
