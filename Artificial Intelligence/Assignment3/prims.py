"""
Prims MST Algorithm
Input is going to be using an Adjacency List.
"""
import heapq
from collections import defaultdict


def primsMst(adjList: dict):
    totalcost = 0
    mst = defaultdict(list)
    edgecost = []
    visited = set()

    min_edge = None

    for node in adjList:
        for cost, nei in adjList[node]:
            if not min_edge or cost < min_edge[0]:
                min_edge = (cost, node, nei)
    # push the min edge to the heap and then start with adding sequential level ke nodes
    heapq.heappush(edgecost, min_edge)

    def add_edges(node):
        """Adds all edges from node to a min heap"""
        visited.add(node)
        for nei, cost in adjList[node]:
            if nei not in visited:
                heapq.heappush(edgecost, (cost, node, nei))

    while edgecost:
        cost, node, nei = heapq.heappop(edgecost)
        if nei not in visited:
            mst[node].append(nei)
            mst[nei].append(node)
            totalcost += cost
            print(f"{node}->{nei}->", end="")
            add_edges(nei)

    print("end")
    print(f"Total Cost of MST is: {totalcost}")

    return mst


adjList = {
    1: [(4, 3), (8, 7)],
    3: [(8, 5), (6, 3), (7, 4)],
    4: [(1, 3), (6, 2), (7, 3)],
    6: [(4, 2), (7, 1), (8, 2)],
    7: [(4, 3), (3, 4), (6, 1)],
    8: [(1, 7), (3, 5), (6, 2)]
}

primsMst(adjList)
