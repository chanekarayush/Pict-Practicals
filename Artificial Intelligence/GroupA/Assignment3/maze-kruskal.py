from PIL import Image
import random
import numpy as np

global GRAPH_SIZE, CELL_THICKNESS, WALL_THICKNESS

## Maze generation parameters. Change as desired.
GRAPH_SIZE = 10
CELL_THICKNESS = 20
WALL_THICKNESS = 5

nodes = [(i,j) for j in range(GRAPH_SIZE) for i in range(GRAPH_SIZE)]
neighbors = lambda n : [(n[0]+dx,n[1]+dy) for dx,dy in ((-1,0),(1,0),(0,-1),(0,1))
                       if n[0]+dx >= 0 and n[0]+dx < GRAPH_SIZE and n[1]+dy >= 0 and n[1]+dy < GRAPH_SIZE]

## Somewhat naive implementation, as it doesn't do rank balancing,
class DisjointSet:
    def __init__(self, nodes):
        self.node_mapping = {}
        for i,val in enumerate(nodes):
            n = self.DSNode(val, i)
            self.node_mapping[val] = n

    def find(self, node):
        return self.find_node(node).parent

    def find_node(self, node):
        if type(self.node_mapping[node].parent) is int:
            return self.node_mapping[node]
        else:
            parent_node = self.find_node(self.node_mapping[node].parent.val)
            self.node_mapping[node].parent = parent_node
            return parent_node

    def union(self, node1, node2):
        parent1 = self.find_node(node1)
        parent2 = self.find_node(node2)
        if parent1.parent != parent2.parent:
            parent1.parent = parent2

    class DSNode:
        def __init__(self, val, parent):
            self.val = val
            self.parent = parent

## Kruskal's 
edges = [(node, nbor) for node in nodes for nbor in neighbors(node)]
maze = []
ds = DisjointSet(nodes)

while len(maze) < len(nodes)-1:
    edge = edges.pop(random.randint(0, len(edges)-1))
    if ds.find(edge[0]) != ds.find(edge[1]):
        ds.union(edge[0], edge[1])
        maze.append(edge)

## Now convert to an image
img = np.zeros((GRAPH_SIZE * (CELL_THICKNESS + WALL_THICKNESS) + WALL_THICKNESS,
                GRAPH_SIZE * (CELL_THICKNESS + WALL_THICKNESS) + WALL_THICKNESS),dtype=np.uint8)

for edge in maze:
    min_x = WALL_THICKNESS+min(edge[0][0],edge[1][0])*(CELL_THICKNESS + WALL_THICKNESS)
    max_x = WALL_THICKNESS+max(edge[0][0],edge[1][0])*(CELL_THICKNESS + WALL_THICKNESS)
    min_y = WALL_THICKNESS+min(edge[0][1],edge[1][1])*(CELL_THICKNESS + WALL_THICKNESS)
    max_y = WALL_THICKNESS+max(edge[0][1],edge[1][1])*(CELL_THICKNESS + WALL_THICKNESS)
    img[min_x:max_x+CELL_THICKNESS,min_y:max_y+CELL_THICKNESS] = 255

im = Image.fromarray(img)
im.show()

## Save maze (include extension!)
im.save("./mazes/maze.png")
