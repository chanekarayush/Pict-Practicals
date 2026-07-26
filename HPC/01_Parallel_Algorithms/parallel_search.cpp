#include <algorithm>
#include <atomic>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <omp.h>
#include <ostream>
#include <queue>
#include <random>
#include <ratio>
#include <stack>
#include <stdatomic.h>
#include <utility>
#include <vector>

using namespace std;

/*
 * Sequential DFS
 * Just written for comparison
 * Returns elements in DFS traversal order duh,
 * */

vector<int> sequentialDFS(vector<vector<int>>& graph, int source)
{
    // graph.size() returns size_t so we cast it to int
    int n = static_cast<int>(graph.size());
    vector<bool> visited(n, false);
    vector<int> order;
    order.reserve(n);

    stack<int> st;
    st.push(source);

    while (!st.empty())
    {
        int node = st.top();
        st.pop();

        if (visited[node])
            continue;
        visited[node] = true;
        order.push_back(node);

        // left most element is processed the first (stack) hence the reverse order
        for (int i = static_cast<int>(graph[node].size()) - 1; i >= 0; --i)
            if (!visited[graph[node][i]])
                st.push(graph[node][i]);
    }

    return order;
}

/*
 * Parallel DFS using OpenMP
 *
 * 1. We will have a shared atomic visited[] that avoids race over node ownership
 *
 * 2. Each thread maintains its own local stack
 *
 * 3. When a threads stack(local) is empty it will steal work from the global work
 * pool (it is a shared stack that is protected by a critical section)
 *
 * 4. Discovered nodes are appended to the per-thread result vector and
 * merged at the end
 *
 *
 * returns elements in (per-thread) DFS traversal order
 * */

vector<int> parallelDFS(vector<vector<int>>& graph, int source)
{
    int n = static_cast<int>(graph.size());

    // We use the atomic flag so that each thread and claim the nodes lock free
    vector<atomic<bool>> visited(n);

    // Global shared pool seeded with source
    vector<int> global_pool;
    global_pool.reserve(512);

    // visited[source].store(true, std::memory_order_relaxed);
    // global_pool.push_back(source);

    bool expected = false;
    if (visited[source].compare_exchange_strong(expected, true, std::memory_order_acq_rel))
        global_pool.push_back(source);

    int num_threads = omp_get_max_threads();
    vector<vector<int>> thread_results(num_threads);

#pragma omp parallel shared(graph, visited, global_pool)
    {

        int tid = omp_get_thread_num();
        stack<int> local_st;
        vector<int>& local_result = thread_results[tid];
        local_result.reserve(n / num_threads + 64);

        while (true)
        {
            // refill the local stack if empty

            if (local_st.empty())
            {
#pragma omp critical(pool_access)
                {
                    constexpr int STEAL_BATCH = 64;
                    int steal = min(STEAL_BATCH, static_cast<int>(global_pool.size()));

                    // If a thread is idle (empty stack)
                    // it will come here to refill the stack from the global pool
                    // similar to work stealing but from a global task pool

                    for (int i = 0; i < steal; i++)
                    {
                        local_st.push(global_pool.back());
                        global_pool.pop_back();
                    }
                }
            }
            if (local_st.empty())
            {
                bool anyone_working = false;
#pragma omp critical(pool_access)
                {

                    anyone_working = !global_pool.empty();
                }
                if (!anyone_working)
                    break;
                continue;
            }

            // actual parallel dfs stuff starts from here (the algorithm core)

            // process the top of the stack i.e. take out the top node
            int node = local_st.top();
            local_st.pop();

            local_result.push_back(node);

            // neighbours that are explored but not visited.
            vector<int> newly_claimed;

            for (int nei : graph[node])
            {
                bool exp = false;

                // basically checks if neighbour is not visited,
                // if yes then push to newly_claimed

                if (visited[nei].compare_exchange_strong(exp, true, std::memory_order_acq_rel))
                    newly_claimed.push_back(nei);
            }
            if (newly_claimed.empty())
                continue;

            // We use the 1st neighbour for the local thread so that it is not
            // idle and the rest of the neighbours are pushed to the global pool
            // so that other threads can use them

            // 1 nei for local thread
            local_st.push(newly_claimed[0]);

            // donate others to global_pool if any
            if (newly_claimed.size() > 1)
            {
#pragma omp critical(pool_access)
                {
                    for (int i = 1; i < static_cast<int>(newly_claimed.size()); i++)
                        global_pool.push_back(newly_claimed[i]);
                }
            }
        }
    }

    // program has ended now we merge all the results!

    vector<int> result;
    result.reserve(n);
    for (auto& tr : thread_results)
    {
        // inserts the dfs traversal in thread wise order for each thread.
        result.insert(result.end(), tr.begin(), tr.end());
    }
    return result;
}

/**
 * Sequential BFS
 * Returns level[] array: level[i] = BFS Depth from source. -2 if unreachable
 * */

vector<int> sequentialBFS(vector<vector<int>>& graph, int source)
{
    int n = static_cast<int>(graph.size());
    vector<int> level(n, -2);
    level[source] = -1;
    queue<int> q;

    q.push(source);

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (int nei : graph[node])
        {
            if (level[nei] == -1)
            {
                level[nei] = level[node] + 1;
                q.push(nei);
            }
        }
    }
    return level;
}

/**
 * Parallel BFS using OpenMP
 * Returns level[] array same as sequential
 *
 * Uses a frontier based algorithm where we put assign various small frontiers
 * to each thread which are then consolidated for next iteration
 **/

vector<int> parallelBFS(vector<vector<int>>& graph, int source)
{
    int n = static_cast<int>(graph.size());
    vector<atomic<int>> level(n);

#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        level[i].store(-1, std::memory_order_relaxed);
    }

    level[source].store(0, std::memory_order_relaxed);
    vector<int> frontier;

    frontier.push_back(source);

    int curr_level = 0;
    while (!frontier.empty())
    {
        vector<int> next_frontier;
#pragma omp parallel
        {
            vector<int> local_next;

#pragma omp for nowait
            for (size_t i = 0; i < frontier.size(); i++)
            {
                int node = frontier[i];
                for (int nei : graph[node])
                {
                    int expected = -1;
                    if (level[nei].compare_exchange_strong(expected, curr_level + 1,
                                                           std::memory_order_acq_rel))
                        local_next.push_back(nei);
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
    vector<int> result(n);
    for (int i = 0; i < n; i++)
        result[i] = level[i].load(std::memory_order_relaxed);

    return result;
}

/*
 * Testing and Benchmarking our Parallel Algorithm
 *  I will use a helper function to generate a random graph with
 *  fixed number of nodes and average degree
 * */

vector<vector<int>> generateGraph(int num_nodes, int avg_degree, unsigned seed = 42)
{
    vector<vector<int>> graph(num_nodes);
    mt19937 rng(seed);
    uniform_int_distribution<int> node_dist(0, num_nodes - 1);

    long long edge_count = static_cast<long long>(num_nodes) * avg_degree / 2;

    for (long long e = 0; e < edge_count; e++)
    {
        int u = node_dist(rng);
        int v = node_dist(rng);

        if (u == v) // prevent cycles
            continue;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

// remove duplicate edges
#pragma omp parallel for schedule(dynamic, 512)
    for (int i = 0; i < num_nodes; ++i)
    {
        auto& adj = graph[i];
        sort(adj.begin(), adj.end());
        adj.erase(unique(adj.begin(), adj.end()), adj.end());
    }

    return graph;
}

struct BenchResult
{
    vector<int> order;
    double time_ms;
};

template <typename Fn> BenchResult benchmark(Fn&& fn)
{
    auto t0 = chrono::high_resolution_clock::now();
    auto order = fn();
    auto t1 = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(t1 - t0).count();
    return {move(order), ms};
}

int main(int argc, char* argv[])
{
    cout << "----------DFS Benchmarks-----------" << endl;
    cout << "Available OpenMP Threads: " << omp_get_max_threads() << endl;
    struct Config
    {
        int nodes;
        int avg_deg;
        const char* label;
    };

    vector<Config> configs = {{100'000, 10, "Small (100K Nodes, Deg 10)"},
                              {500'000, 15, "Medium (500K Nodes, Deg 15)"},
                              {1'000'000, 20, "Large (1M Nodes, Deg 20)"}};
    for (auto& cfg : configs)
    {
        int source = 0;
        cout << cfg.label << endl;
        cout << "\n\tGenerating Graph..." << endl;
        auto graph = generateGraph(cfg.nodes, cfg.avg_deg, 20);
        cout << "\tdone" << endl;

        cout << "\n-----------------------------DFS-------------------------------" << endl;
        cout << "\n\t" << "Sequential DFS" << endl << std::flush;
        auto seq = benchmark([&] { return sequentialDFS(graph, source); });

        cout << "\t" << fixed << setprecision(2) << seq.time_ms << " ms (visited "
             << seq.order.size() << ") nodes" << endl;

        cout << "\n\tParallel DFS" << endl << std::flush;
        auto par = benchmark([&] { return parallelDFS(graph, source); });

        cout << "\t" << fixed << setprecision(2) << par.time_ms << " ms (visited "
             << par.order.size() << ") nodes" << endl;

        double speedup = seq.time_ms / par.time_ms;
        cout << "------------------------------------------------------------" << endl;
        cout << "\tSpeedup :\t\t" << setprecision(2) << speedup << "x" << endl;

        // we also need to check that the nodes that were visited are the same (to check the
        // correctness)

        vector<int> s_sorted = seq.order, p_sorted = par.order;
        sort(s_sorted.begin(), s_sorted.end());
        sort(p_sorted.begin(), p_sorted.end());
        bool same_nodes = (s_sorted == p_sorted);

        cout << "\n\tNode Set Match: \t" << (same_nodes ? "PASS" : "FAIL") << endl;

        cout << "\n-----------------------------BFS-------------------------------" << endl;

        cout << "\n\t" << "Sequential BFS" << endl << std::flush;
        seq = benchmark([&] { return sequentialBFS(graph, source); });

        cout << "\t" << fixed << setprecision(2) << seq.time_ms << " ms (visited "
             << seq.order.size() << ") nodes" << endl;

        cout << "\n\tParallel BFS" << endl << std::flush;
        par = benchmark([&] { return parallelBFS(graph, source); });

        cout << "\t" << fixed << setprecision(2) << par.time_ms << " ms (visited "
             << par.order.size() << ") nodes" << endl;

        speedup = seq.time_ms / par.time_ms;
        cout << "------------------------------------------------------------" << endl;
        cout << "\tSpeedup :\t\t" << setprecision(2) << speedup << "x" << endl;
        s_sorted = seq.order, p_sorted = par.order;
        sort(s_sorted.begin(), s_sorted.end());
        sort(p_sorted.begin(), p_sorted.end());
        same_nodes = (s_sorted == p_sorted);

        cout << "\n\tNode Set Match: \t" << (same_nodes ? "PASS" : "FAIL") << endl;
        cout << "------------------------------------------------------------" << endl;
    }
    return 0;
}
