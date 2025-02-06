"""
Kruskal's MST Algorithm
It takes inputs and returns an adjacency List and returns ab MST according to Kruskal
"""
import heapq
from collections import defaultdict


class UnionFind:
    def __init__(self, nodes):
        # each node is a parent of itself
        self.parent = {node: node for node in nodes}
        # each node has a rank of 0 initially
        self.rank = {node: 0 for node in nodes}

    def find(self, node):
        if self.parent[node] != node:
            self.parent[node] = self.find(self.parent[node])
        return self.parent[node]

    def union(self, node1, node2):
        root1 = self.find(node1)
        root2 = self.find(node2)

        if root1 != root2:
            if self.rank[root1] > self.rank[root2]:
                self.parent[root2] = root1
            elif self.rank[root1] < self.rank[root2]:
                self.parent[root1] = root2
            else:
                self.parent[root2] = root1
                self.rank[root1] += 1


def kruskal(adjList: dict) -> dict:
    mst = defaultdict(list)
    edge_cost = []
    totalcost = 0
    component = UnionFind(list(adjList.keys()))

    for node in adjList:
        for nei, cost in adjList[node]:
            heapq.heappush(edge_cost, (cost, node, nei))
    while edge_cost:
        cost, node1, node2 = heapq.heappop(edge_cost)

        if component.find(node1) != component.find(node2):
            component.union(node1, node2)
            mst[node1].append((node2, cost))
            mst[node2].append((node1, cost))
            totalcost += cost
            print(f"{node1}->{node2}->", end="")
    print("end")
    print(f"totalcost={totalcost}")
    return mst


adjList = {
    1: [(4, 3), (8, 7)],
    3: [(8, 5), (6, 3), (7, 4)],
    4: [(1, 3), (6, 2), (7, 3)],
    6: [(4, 2), (7, 1), (8, 2)],
    7: [(4, 3), (3, 4), (6, 1)],
    8: [(1, 7), (3, 5), (6, 2)]
}


kruskal(adjList)
