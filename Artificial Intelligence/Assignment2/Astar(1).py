import heapq as hq
from collections import defaultdict

"""
reconstruct_edges ek function 
A-star is another function
"""

def A_star(start, goal, h):
    openSet = []
    hq.heappush(openSet, start)     # This is the set of discovered nodes.
    
    cameFrom = dict()

    gScore = defaultdict(lambda:float('-inf'))
    gScore[start] = 0

    fScore = defaultdict(lambda:float('-inf'))
    fScore[start] = 0

    while len(openSet):
        current = hq.heappop(openSet)
        if current == goal:
            return reconstruct_path(cameFrom, current)
        
        neighbour = start.next
        while neighbour:

            neighbour = neighbour.next



