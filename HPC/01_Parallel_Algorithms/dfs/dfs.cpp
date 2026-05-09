#include <omp.h>
#include <bits/stdc++.h>
#include "../bfs/graphutils.cpp"

using namespace std;

void sequentialDFS(int startNode, vector<vector<int>>& graph, vector<int>& visited) {
    stack<int> s;
    s.push(startNode);
    visited[startNode] = 1;

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        for (int nei : graph[node]) {
            if (!visited[nei]) {
                visited[nei] = 1;
                s.push(nei);
            }
        }
    }
}

void parallelDFS_helper(int node, vector<vector<int>>& graph, vector<int>& visited) {
    for (int nei : graph[node]) {
        if (visited[nei] == 0) {
            if (__sync_bool_compare_and_swap(&visited[nei], 0, 1)) {
                #pragma omp task
                parallelDFS_helper(nei, graph, visited);
            }
        }
    }
}

void parallelDFS(int startNode, vector<vector<int>>& graph, vector<int>& visited) {
    visited[startNode] = 1;
    #pragma omp parallel
    {
        #pragma omp single
        {
            parallelDFS_helper(startNode, graph, visited);
        }
    }
}

int main() {
    int n_threads = 4;
    int n = 10000, degree = 5, seed = 41313;

    cout << "Enter the number of threads you would like to use (default 4): ";
    preserve_default_input(n_threads);
    omp_set_num_threads(n_threads);

    cout << "Please Enter the number of vertices for the graph (default 10000): ";
    preserve_default_input(n);
    cout << "Please Enter the Average Degree of Each Node (default 5): ";
    preserve_default_input(degree);
    cout << "Please Enter the Random Seed (default 41313): ";
    preserve_default_input(seed);

    cout << "---------- Generating Graph ----------" << endl;
    vector<vector<int>> graph = generateRandomGraph(n, degree, seed);
    cout << "Graph Successfully generated!" << endl;

    vector<int> visited_seq(n, 0);
    vector<int> visited_par(n, 0);

    cout << "---------------------------Speed Comparison-----------------------------" << endl;
    int iterations = 5;
    cout << "How many iterations? (default 5): ";
    preserve_default_input(iterations);

    double sum = 0;
    for (int i = 0; i < iterations; i++) {
        fill(visited_seq.begin(), visited_seq.end(), 0);
        double s = omp_get_wtime();
        sequentialDFS(0, graph, visited_seq);
        sum += omp_get_wtime() - s;
    }
    cout << "Average sequential time: " << sum / iterations << " sec\n";

    sum = 0;
    for (int i = 0; i < iterations; i++) {
        fill(visited_par.begin(), visited_par.end(), 0);
        double s = omp_get_wtime();
        parallelDFS(0, graph, visited_par);
        sum += omp_get_wtime() - s;
    }
    cout << "Average parallel time: " << sum / iterations << " sec\n";

    // Verification
    bool match = true;
    for (int i = 0; i < n; i++) {
        if (visited_seq[i] != visited_par[i]) {
            match = false;
            break;
        }
    }
    if (match) {
        cout << "Success: Sequential and Parallel results match!" << endl;
    } else {
        cout << "Failure: Results do not match." << endl;
    }

    return 0;
}
