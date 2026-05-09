# Parallel Graph Traversal (BFS & DFS)

This project implements parallel versions of Breadth-First Search (BFS) and Depth-First Search (DFS) using OpenMP.

## Algorithms

### 1. Parallel Breadth-First Search (BFS)
The implementation uses a **level-synchronous** approach:
- **Frontier-based:** Traversal proceeds level by level.
- **Parallelization:** The current frontier is processed in parallel using `#pragma omp for`.
- **Thread Safety:** `__sync_bool_compare_and_swap` (atomic CAS) ensures that each node is added to the next frontier only once.
- **Local Frontiers:** Threads collect discovered neighbors in private vectors (`local_next`) to minimize contention, merging them into the global `next_frontier` using a `#pragma omp critical` section.

### 2. Parallel Depth-First Search (DFS)
The implementation uses **OpenMP Tasks**:
- **Task-based Recursion:** Each unvisited neighbor triggers a new `#pragma omp task`.
- **Parallel Region:** The traversal starts within a `#pragma omp single` block inside a `#pragma omp parallel` region to ensure only one thread initiates the recursion while others help execute spawned tasks.
- **Thread Safety:** `__sync_bool_compare_and_swap` is used to atomically mark nodes as visited.

## Compilation and Execution

### Prerequisites
- GCC compiler with OpenMP support.

### Compile
```bash
g++ -fopenmp parallel_traversal.cpp -o parallel_traversal
```

### Run
```bash
./parallel_traversal
```

## Implementation Details
- **Graph Generation:** Includes a utility to generate random graphs with a specified average degree for testing.
- **Verification:** Automatically compares parallel results against sequential implementations to ensure correctness.
- **Performance:** Prints execution times for both sequential and parallel versions.

## Usage
When executed, the program prompts for:
1. **Vertices:** Number of nodes in the graph (default: 10,000).
2. **Threads:** Number of OpenMP threads to use (default: 4).
