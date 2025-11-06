def pagerank(graph, damping_factor=0.85, max_iterations=100, tol=1.0e-6):
    nodes = list(graph.keys())
    N = len(nodes)
    rank = dict.fromkeys(nodes, 1.0 / N)

    for iteration in range(max_iterations):
        new_rank = dict.fromkeys(nodes, (1 - damping_factor) / N)

        for node in nodes:
            neighbors = graph[node]
            if not neighbors:
                for target in nodes:
                    new_rank[target] += damping_factor * rank[node] / N
            else:
                for neighbor in neighbors:
                    new_rank[neighbor] += damping_factor * rank[node] / len(neighbors)
        diff = sum(abs(new_rank[node] - rank[node]) for node in nodes)
        rank = new_rank
        if diff < tol:
            break

    return rank

if __name__ == "__main__":
    web_graph = {
        'A': ['B', 'C'],
        'B': ['C'],
        'C': ['A', 'E'],
        'D': ['C'],
        'E': ['A']
    }
    ranks = pagerank(web_graph)
    print("PageRank Scores:")
    for page, score in ranks.items():
        print(f"{page}: {score:.4f}")
