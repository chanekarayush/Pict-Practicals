# Parallel Reduction (Min, Max, Sum, Average)

This project implements Parallel Reduction operations using OpenMP in C++. It compares the performance of sequential and parallel algorithms for finding the minimum, maximum, sum, and average of a large array.

## Implementation Details
- **Min/Max/Sum:** Computed using `#pragma omp parallel for reduction`.
- **Average:** Derived from the parallel sum.
- **Optimization:** Compiling with `-O3` ensures maximum performance via vectorization and improved memory handling.

## Prerequisites
- GCC compiler with OpenMP support.
- OpenMP library installed on your system.

## How to Compile
Use the following command to compile the program with OpenMP support and high-level optimizations:

```bash
g++ -O3 -fopenmp min_max_avg.cpp -o min_max_avg
```

## How to Run
Execute the compiled binary:

```bash
./min_max_avg
```

## Expected Output
The program will output results for both sequential and parallel operations, including execution times. For an array of 100 million elements, you should observe a significant speedup in the parallel version.

```text
--- Sequential Operations ---
Min: 0
Max: 999
Sum: 49950000000
Average: 499.5
Time: ~0.05 seconds

--- Parallel Operations ---
Min: 0
Max: 999
Sum: 49950000000
Average: 499.5
Time: ~0.02 seconds
```
