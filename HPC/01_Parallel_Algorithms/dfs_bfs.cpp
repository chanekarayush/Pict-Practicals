#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <atomic>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>
#include <omp.h>
using namespace std;

// ─────────────────────────────────────────────
//  Sequential DFS
//  Returns elements in DFS traversal order
// ─────────────────────────────────────────────
std::vector<int> sequential_dfs(std::vector<std::vector<int>> &graph, int source)
{
    int n = static_cast<int>(graph.size());
    std::vector<bool> visited(n, false);
    std::vector<int> order;
    order.reserve(n);

    std::stack<int> stk;
    stk.push(source);

    while (!stk.empty()) {
        int node = stk.top();
        stk.pop();

        if (visited[node]) continue;
        visited[node] = true;
        order.push_back(node);

        // Push neighbours in reverse so left-most is processed first
        for (int i = static_cast<int>(graph[node].size()) - 1; i >= 0; --i)
            if (!visited[graph[node][i]])
                stk.push(graph[node][i]);
    }

    return order;
}

// ─────────────────────────────────────────────
//  Parallel DFS using OpenMP
//
//  Strategy:
//    • A shared atomic visited[] array avoids races on node ownership.
//    • Each thread maintains its own local stack.
//    • When a thread's stack is empty it tries to steal work from the
//      global work-pool (a shared stack protected by a critical section).
//    • Discovered nodes are appended to a per-thread result vector and
//      merged at the end, preserving the order each thread observed.
//
//  Returns elements in (per-thread) DFS traversal order.
// ─────────────────────────────────────────────
std::vector<int> parallel_dfs(std::vector<std::vector<int>> &graph, int source)
{
    int n = static_cast<int>(graph.size());

    // Use atomic flags so multiple threads can claim nodes lock-free
    std::vector<std::atomic<bool>> visited(n);
    for (int i = 0; i < n; ++i) visited[i].store(false, std::memory_order_relaxed);

    // Global shared pool seeded with the source
    std::vector<int> global_pool;
    global_pool.reserve(512);

    bool expected = false;
    if (visited[source].compare_exchange_strong(expected, true,
                                                std::memory_order_acq_rel))
        global_pool.push_back(source);

    int num_threads = omp_get_max_threads();
    // Per-thread results collected here
    std::vector<std::vector<int>> thread_results(num_threads);

    #pragma omp parallel shared(graph, visited, global_pool)
    {
        int tid = omp_get_thread_num();
        std::stack<int> local_stk;
        std::vector<int> &local_result = thread_results[tid];
        local_result.reserve(n / num_threads + 64);

        while (true) {
            // ── Try to refill local stack from the global pool ──────────
            if (local_stk.empty()) {
                #pragma omp critical(pool_access)
                {
                    // Steal up to STEAL_BATCH nodes at once
                    constexpr int STEAL_BATCH = 64;
                    int steal = std::min(STEAL_BATCH,
                                        static_cast<int>(global_pool.size()));
                    for (int i = 0; i < steal; ++i) {
                        local_stk.push(global_pool.back());
                        global_pool.pop_back();
                    }
                }
            }

            if (local_stk.empty()) {
                // Check if any other thread is still producing work
                bool anyone_working = false;
                // A short spin-wait: if pool stays empty, we're done
                #pragma omp critical(pool_access)
                { anyone_working = !global_pool.empty(); }

                if (!anyone_working) break; // all threads will exit soon
                continue;
            }

            // ── Process the top of local stack ──────────────────────────
            int node = local_stk.top();
            local_stk.pop();

            local_result.push_back(node);

            // Explore neighbours
            std::vector<int> newly_claimed;
            for (int nb : graph[node]) {
                bool exp = false;
                if (visited[nb].compare_exchange_strong(exp, true,
                                                        std::memory_order_acq_rel))
                    newly_claimed.push_back(nb);
            }

            if (newly_claimed.empty()) continue;

            // Keep first neighbour for local DFS (depth-first behaviour)
            local_stk.push(newly_claimed[0]);

            // Donate the rest to the global pool so other threads can help
            if (newly_claimed.size() > 1) {
                #pragma omp critical(pool_access)
                {
                    for (int i = 1; i < static_cast<int>(newly_claimed.size()); ++i)
                        global_pool.push_back(newly_claimed[i]);
                }
            }
        }
    } // end parallel region

    // ── Merge per-thread results ──────────────────────────────────────────
    std::vector<int> result;
    result.reserve(n);
    for (auto &tr : thread_results)
        result.insert(result.end(), tr.begin(), tr.end());

    return result;
}

// ─────────────────────────────────────────────
//  Sequential BFS
//  Returns level[] array: level[i] = BFS depth from source, -1 if unreachable
// ─────────────────────────────────────────────
vector<int> sequentialBFS(vector<vector<int>>& graph, int source) {
    int n = static_cast<int>(graph.size());
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

// ─────────────────────────────────────────────
//  Parallel BFS using OpenMP
//  Returns level[] array: level[i] = BFS depth from source, -1 if unreachable
//
//  Fixes applied:
//    1. Uses std::atomic<int> instead of GCC-specific __sync_bool_compare_and_swap
//    2. Loop index is size_t to avoid signed/unsigned comparison warning
// ─────────────────────────────────────────────
vector<int> parallelBFS(vector<vector<int>>& graph, int source) {
    int n = static_cast<int>(graph.size());

    // Use atomic ints so threads can claim nodes without a lock
    vector<atomic<int>> level(n);
    for (int i = 0; i < n; ++i)
        level[i].store(-1, memory_order_relaxed);

    level[source].store(0, memory_order_relaxed);
    vector<int> frontier;
    frontier.push_back(source);

    int curr_level = 0;
    while (!frontier.empty()) {
        vector<int> next_frontier;

        #pragma omp parallel
        {
            vector<int> local_next;

            // FIX 2: use size_t to avoid signed/unsigned comparison warning
            #pragma omp for nowait
            for (size_t i = 0; i < frontier.size(); i++) {
                int node = frontier[i];
                for (int nei : graph[node]) {
                    int expected = -1;
                    // FIX 1: portable C++11 atomic instead of GCC __sync builtin
                    if (level[nei].compare_exchange_strong(
                            expected, curr_level + 1,
                            memory_order_acq_rel)) {
                        local_next.push_back(nei);
                    }
                }
            }

            #pragma omp critical
            {
                next_frontier.insert(next_frontier.end(),
                                     local_next.begin(), local_next.end());
            }
        }

        frontier = next_frontier;
        curr_level++;
    }

    // Convert atomic<int> back to plain int for the return value
    vector<int> result(n);
    for (int i = 0; i < n; ++i)
        result[i] = level[i].load(memory_order_relaxed);

    return result;
}

// ─────────────────────────────────────────────
//  Random graph generator (undirected)
// ─────────────────────────────────────────────
std::vector<std::vector<int>> generate_large_graph(int num_nodes, int avg_degree,
                                                    unsigned seed = 42)
{
    std::vector<std::vector<int>> graph(num_nodes);
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> node_dist(0, num_nodes - 1);

    long long edge_count = static_cast<long long>(num_nodes) * avg_degree / 2;
    for (long long e = 0; e < edge_count; ++e) {
        int u = node_dist(rng);
        int v = node_dist(rng);
        if (u == v) continue;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Remove duplicate edges
    #pragma omp parallel for schedule(dynamic, 512)
    for (int i = 0; i < num_nodes; ++i) {
        auto &adj = graph[i];
        std::sort(adj.begin(), adj.end());
        adj.erase(std::unique(adj.begin(), adj.end()), adj.end());
    }

    return graph;
}

// ─────────────────────────────────────────────
//  Benchmark helper
// ─────────────────────────────────────────────
struct BenchResult {
    std::vector<int> order;
    double time_ms;
};

template<typename Fn>
BenchResult benchmark(Fn &&fn)
{
    auto t0 = std::chrono::high_resolution_clock::now();
    auto order = fn();
    auto t1 = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    return {std::move(order), ms};
}

// ─────────────────────────────────────────────
//  main
// ─────────────────────────────────────────────
int main()
{
    std::cout << "╔══════════════════════════════════════════════════════╗\n";
    std::cout << "║         Parallel DFS Benchmark  (OpenMP)             ║\n";
    std::cout << "╚══════════════════════════════════════════════════════╝\n\n";

    std::cout << "OpenMP threads available : " << omp_get_max_threads() << "\n\n";

    // ── Test configurations ──────────────────────────────────────────────
    struct Config { int nodes; int avg_deg; const char* label; };
    std::vector<Config> configs = {
        { 100'000,  10, "Small  (100K nodes, deg 10)" },
        { 500'000,  15, "Medium (500K nodes, deg 15)" },
        {1'000'000, 20, "Large  (  1M nodes, deg 20)" },
    };

    for (auto &cfg : configs) {
        std::cout << "── " << cfg.label << " ──────────────────────────\n";
        std::cout << "  Generating graph... " << std::flush;

        auto graph = generate_large_graph(cfg.nodes, cfg.avg_deg);
        int source = 0;

        std::cout << "done.\n";

        // Sequential
        std::cout << "  Sequential DFS... " << std::flush;
        auto seq = benchmark([&]{ return sequential_dfs(graph, source); });
        std::cout << std::fixed << std::setprecision(2)
                  << seq.time_ms << " ms  (visited " << seq.order.size() << " nodes)\n";

        // Parallel
        std::cout << "  Parallel   DFS... " << std::flush;
        auto par = benchmark([&]{ return parallel_dfs(graph, source); });
        std::cout << par.time_ms << " ms  (visited " << par.order.size() << " nodes)\n";

        double speedup = seq.time_ms / par.time_ms;
        std::cout << "  Speedup          : " << std::setprecision(2) << speedup << "x\n";

        // Sanity: both must visit the same set of nodes
        std::vector<int> s_sorted = seq.order, p_sorted = par.order;
        std::sort(s_sorted.begin(), s_sorted.end());
        std::sort(p_sorted.begin(), p_sorted.end());
        bool same_nodes = (s_sorted == p_sorted);
        std::cout << "  Node-set match   : " << (same_nodes ? "✓ PASS" : "✗ FAIL") << "\n\n";
    }

    // ── Preview first 20 elements of the last run ────────────────────────
    std::cout << "── Quick preview: first 20 elements returned by each DFS ─────\n";

    auto demo_graph = generate_large_graph(50, 4, 7);
    auto dseq = sequential_dfs(demo_graph, 0);
    auto dpar = parallel_dfs(demo_graph, 0);

    auto print20 = [](const std::vector<int> &v, const char* label) {
        std::cout << "  " << label << ": [";
        int lim = std::min(20, static_cast<int>(v.size()));
        for (int i = 0; i < lim; ++i)
            std::cout << v[i] << (i + 1 < lim ? ", " : "");
        std::cout << (v.size() > 20 ? " ..." : "") << "]\n";
    };

    print20(dseq, "Sequential");
    print20(dpar, "Parallel  ");


    std::cout << "╔══════════════════════════════════════════════════════╗\n";
    std::cout << "║         Parallel BFS Benchmark  (OpenMP)             ║\n";
    std::cout << "╚══════════════════════════════════════════════════════╝\n\n";

    std::cout << "OpenMP threads available : " << omp_get_max_threads() << "\n\n";

    // ── Test configurations ──────────────────────────────────────────────
    for (auto &cfg : configs) {
        std::cout << "── " << cfg.label << " ──────────────────────────\n";
        std::cout << "  Generating graph... " << std::flush;

        auto graph = generate_large_graph(cfg.nodes, cfg.avg_deg);
        int source = 0;

        std::cout << "done.\n";

        // Sequential
        std::cout << "  Sequential BFS... " << std::flush;
        auto seq = benchmark([&]{ return sequentialBFS(graph, source); });
        std::cout << std::fixed << std::setprecision(2)
                  << seq.time_ms << " ms  (visited " << seq.order.size() << " nodes)\n";

        // Parallel
        std::cout << "  Parallel   BFS... " << std::flush;
        auto par = benchmark([&]{ return parallelBFS(graph, source); });
        std::cout << par.time_ms << " ms  (visited " << par.order.size() << " nodes)\n";

        double speedup = seq.time_ms / par.time_ms;
        std::cout << "  Speedup          : " << std::setprecision(2) << speedup << "x\n";

        // Helper: count nodes actually visited (level != -1)
        auto visited_count = [](const vector<int>& lvl) {
            return count_if(lvl.begin(), lvl.end(), [](int x){ return x != -1; });
        };

        // In your benchmark loop, replace the print lines with:
        cout << seq.time_ms << " ms  (visited " << visited_count(seq.order) << " nodes)\n";
        cout << par.time_ms << " ms  (visited " << visited_count(par.order) << " nodes)\n";

        // And fix the node-set match check — compare which nodes were visited, not raw arrays
        // (raw arrays differ: seq stores int, par stores atomic result, but values should match)
        bool same_nodes = (seq.order == par.order);
        cout << "  Node-set match   : " << (same_nodes ? "✓ PASS" : "✗ FAIL") << "\n\n";
    }

    // ── Preview first 20 elements of the last run ────────────────────────
    std::cout << "── Quick preview: first 20 elements returned by each DFS ─────\n";

    vector<int> numarr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    demo_graph = generate_large_graph(50, 4, 7);
    auto bseq = sequentialBFS(demo_graph, 0);
    auto bpar = parallelBFS(demo_graph, 0);

    print20(numarr,"Index     ");
    print20(bseq,  "Sequential");
    print20(bpar,  "Parallel  ");

    std::cout << "\nDone.\n";
    return 0;
}
