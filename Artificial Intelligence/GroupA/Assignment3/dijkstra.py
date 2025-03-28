import heapq
import readfile
import sys

def dijkstra(graph, start):
    # Number of vertices in the graph
    n = len(graph)
    
    # Distances dictionary: initialize with infinity
    distances = {node: float('inf') for node in graph}
    distances[start] = 0
    
    # Min-heap priority queue to select the next vertex with the smallest distance
    pq = [(0, start)]  # (distance, node)
    
    while pq:
        # Get the node with the smallest distance
        current_distance, current_node = heapq.heappop(pq)
        
        # If this distance is greater than the recorded, skip it
        if current_distance > distances[current_node]:
            continue
        
        # Traverse the neighbors of the current node
        for neighbor, weight in graph[current_node]:
            distance = current_distance + weight
            
            # Only consider this new path if it's better (smaller distance)
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(pq, (distance, neighbor))
            else:
                print(f"Path rejected:{current_node}->{neighbor}, {distance}")
    
    return distances

def main():
    verbose = False
    if len(sys.argv) > 2:
        for arg in sys.argv[1:]:
            if arg == "--verbose":
                print("Verbose enabled")
                verbose = True

    # Find shortest paths from '1'
    adjList = dict(readfile.readfileinput(verbose=verbose))
    print(adjList.keys())
    start_node = int(input("Enter the source node:")) 
    shortest_paths = dijkstra(adjList, start_node)

    # Print the shortest paths
    print(f"Shortest paths from {start_node}:")
    for node, distance in shortest_paths.items():
        print(f"Distance to {node}: {distance}")
    print("Overall Time Complexity -> O(nlog(n)) or O(V + Elog(V))")

if __name__ == "__main__":
    main()
