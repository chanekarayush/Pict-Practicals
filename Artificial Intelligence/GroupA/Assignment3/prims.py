"""
Prims MST Algorithm
Input is going to be using an Adjacency List.
"""
import heapq
from collections import defaultdict

import readfile


def primsMst(adjList: dict):
    totalcost = 0
    mst = defaultdict(list)
    edgecost = []
    visited = set()
    min_edge = (-1, 0, 0)

    # push the min edge to the heap and then start with adding sequential level ke nodes

    def add_edges(node):
        """Adds all edges from node to a min heap"""
        visited.add(node)
        for nei, cost in adjList[node]:
            if nei not in visited:
                heapq.heappush(edgecost, (cost, node, nei))
    print("Added all nodes and their cost to min heap -> O(nlogn)")
    heapq.heappush(edgecost, min_edge)
    while edgecost:
        cost, node, nei = heapq.heappop(edgecost)
        if nei not in visited:
            add_edges(nei)
            if cost != -1:
                mst[node].append(nei)
                totalcost += cost
                print(f"({node}->{nei})->", end="")

    print("end")
    print(f"Total Cost of MST is: {totalcost}")
    print("Visited all nodes and edges -> O(nlog(n)) or O(V+Elog(V))\nDue to the min heap we saved on a O(n) iterations in finding the min per node")
    return mst


adjList = readfile.readfileinput()
MST = primsMst(adjList)

for x in MST:
    print(f'{x}:', end=" ")
    for nei in MST[x]:
        print(f'{nei},', end=" ")
    print()
