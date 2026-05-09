#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <omp.h>
#include <bits/stdc++.h>

using namespace std;

// --- Graph Utilities ---

vector<vector<int>> generateRandomGraph(int n, int avg_degree, int seed) {
    vector<vector<int>> graph(n);
    mt19937 gen(seed);
    uniform_int_distribution<int> dist(0, n - 1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < avg_degree; j++) {
            int nei = dist(gen);
            if (nei != i) {
                graph[i].push_back(nei);
                graph[nei].push_back(i);
            }
        }
    }
    return graph;
}

// --- BFS Implementations ---

vector<int> sequentialBFS(int n, vector<vector<int>>& graph, int source) {
    vector<int> level(n, -1);
    level[source] = 0;
    queue<int> q;
    q.push(source);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int nei : graph[node]) {
            if (level[nei] == -1) {
                level[nei] = level[node] + 1;
                q.push(nei);
            }
        }
    }
    return level;
}

vector<int> parallelBFS(int n, vector<vector<int>>& graph, int source) {
    vector<int> level(n, -1);
    level[source] = 0;
    vector<int> frontier;
    frontier.push_back(source);

    int curr_level = 0;
    while (!frontier.empty()) {
        vector<int> next_frontier;
        #pragma omp parallel
        {
            vector<int> local_next;
            #pragma omp for nowait
            for (int i = 0; i < frontier.size(); i++) {
                int node = frontier[i];
                for (int nei : graph[node]) {
                    if (__sync_bool_compare_and_swap(&level[nei], -1, curr_level + 1)) {
                        local_next.push_back(nei);
                    }
                }
            }
            #pragma omp critical
            {
                next_frontier.insert(next_frontier.end(), local_next.begin(), local_next.end());
            }
        }
        frontier = next_frontier;
        curr_level++;
    }
    return level;
}

// --- DFS Implementations ---

void sequentialDFS(int node, vector<vector<int>>& graph, vector<int>& visited) {
    stack<int> s;
    s.push(node);
    visited[node] = 1;

    while (!s.empty()) {
        int curr = s.top();
        s.pop();

        for (int nei : graph[curr]) {
            if (!visited[nei]) {
                visited[nei] = 1;
                s.push(nei);
            }
        }
    }
}

void parallelDFS_task(int node, vector<vector<int>>& graph, vector<int>& visited) {
    for (int nei : graph[node]) {
        if (visited[nei] == 0) {
            if (__sync_bool_compare_and_swap(&visited[nei], 0, 1)) {
                #pragma omp task
                parallelDFS_task(nei, graph, visited);
            }
        }
    }
}

void parallelDFS(int n, vector<vector<int>>& graph, int source, vector<int>& visited) {
    visited[source] = 1;
    #pragma omp parallel
    {
        #pragma omp single
        {
            parallelDFS_task(source, graph, visited);
        }
    }
}

// --- Main ---

int main() {
    int n = 10000, degree = 5, seed = 42, n_threads = 4;
    
    cout << "Enter vertices (default 10000): ";
    string input;
    getline(cin, input);
    if (!input.empty()) n = stoi(input);

    cout << "Enter threads (default 4): ";
    getline(cin, input);
    if (!input.empty()) n_threads = stoi(input);
    omp_set_num_threads(n_threads);

    cout << "Generating graph..." << endl;
    auto graph = generateRandomGraph(n, degree, seed);

    // BFS Timing
    cout << "\n--- BFS Performance ---" << endl;
    double start = omp_get_wtime();
    vector<int> bfs_seq = sequentialBFS(n, graph, 0);
    cout << "Sequential BFS: " << omp_get_wtime() - start << "s" << endl;

    start = omp_get_wtime();
    vector<int> bfs_par = parallelBFS(n, graph, 0);
    cout << "Parallel BFS:   " << omp_get_wtime() - start << "s" << endl;

    // DFS Timing
    cout << "\n--- DFS Performance ---" << endl;
    vector<int> visited_seq(n, 0);
    start = omp_get_wtime();
    sequentialDFS(0, graph, visited_seq);
    cout << "Sequential DFS: " << omp_get_wtime() - start << "s" << endl;

    vector<int> visited_par(n, 0);
    start = omp_get_wtime();
    parallelDFS(n, graph, 0, visited_par);
    cout << "Parallel DFS:   " << omp_get_wtime() - start << "s" << endl;

    // Verification
    bool bfs_match = (bfs_seq == bfs_par);
    bool dfs_match = (visited_seq == visited_par);
    
    cout << "\n--- Verification ---" << endl;
    cout << "BFS Results Match: " << (bfs_match ? "YES" : "NO") << endl;
    cout << "DFS Results Match: " << (dfs_match ? "YES" : "NO") << endl;

    return 0;
}
