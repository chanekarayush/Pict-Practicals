import heapq

import readfile


def prims_mst(graph, num_nodes):
    visited = [False] * num_nodes
    min_heap = [(float('inf'), 0, 0)]  # (weight, node, parent)
    mst_cost = 0
    mst_edges = []

    for x in graph:
        for y, cost in graph[x]:
            if cost < min_heap[0][0]:
                min_heap = [(cost, x, y)]

    while min_heap:
        weight, u, parent = heapq.heappop(min_heap)
        if visited[u]:
            continue

        visited[u] = True
        mst_cost += weight
        if parent != -1:
            mst_edges.append((parent, u, weight))

        for v, w in graph[u]:
            if not visited[v]:
                heapq.heappush(min_heap, (w, v, u))

    return mst_edges, mst_cost


# Example graph as an adjacency list
graph = {
    0: [(1, 2), (3, 6)],
    1: [(0, 2), (2, 3), (3, 8), (4, 5)],
    2: [(1, 3), (4, 7)],
    3: [(0, 6), (1, 8), (4, 9)],
    4: [(1, 5), (2, 7), (3, 9)]
}

graph = dict(readfile.readfileinput())
num_nodes = len(graph)

mst_edges, mst_cost = prims_mst(graph, num_nodes)
print("Minimum Spanning Tree Edges:", mst_edges)
print("Total Cost of MST:", mst_cost)
