"""
A star algorithm implementation in python.
"""
from typing import List, Tuple, Dict
import numpy as np
import heapq
from math import sqrt
import matplotlib.pyplot as plt

def create_node(position: Tuple[int, int], g: float = float('inf'), 
                h: float = 0.0, parent: Dict = None) -> Dict:

    return {
        'position': position,
        'g': g,
        'h': h,
        'f': g + h,
        'parent': parent
    }

def calculate_heuristic(pos1: Tuple[int, int], pos2: Tuple[int, int]) -> float:
    """
    Calculate the estimated distance between two points using Euclidean distance.
    """
    x1, y1 = pos1
    x2, y2 = pos2
    return sqrt((x2 - x1)**2 + (y2 - y1)**2)

def get_valid_neighbors(grid: np.ndarray, position: Tuple[int, int]) -> List[Tuple[int, int]]:
    """
    Get all valid neighboring positions in the grid.
    """
    x, y = position
    rows, cols = grid.shape
    
    possible_moves = [
        (x+1, y), (x-1, y),    # Right, Left
        (x, y+1), (x, y-1),    # Up, Down
        (x+1, y+1), (x-1, y-1),  # Diagonal moves also 
        (x+1, y-1), (x-1, y+1)
    ]
    
    return [
        (nx, ny) for nx, ny in possible_moves
        if 0 <= nx < rows and 0 <= ny < cols  
        and grid[nx, ny] == 0                
    ]


def reconstruct_path(goal_node: Dict) -> List[Tuple[int, int]]:
    """
    Reconstruct the path from goal to start by following parent pointers.
    """
    path = []
    current = goal_node
    
    while current is not None:
        path.append(current['position'])
        current = current['parent']
        
    return path[::-1]  



def find_path(grid: np.ndarray, start: Tuple[int, int], 
              goal: Tuple[int, int]) -> List[Tuple[int, int]]:

    start_node = create_node(
        position=start,
        g=0,
        h=calculate_heuristic(start, goal)
    )
    
    open_list = [(start_node['f'], start)]  
    open_dict = {start: start_node}         
    closed_set = set()                      
    
    while open_list:
        _, current_pos = heapq.heappop(open_list)
        current_node = open_dict[current_pos]
        
        if current_pos == goal:
            return reconstruct_path(current_node)
            
        closed_set.add(current_pos)
        print(f" Current Position -> {current_pos}")

        for neighbor_pos in get_valid_neighbors(grid, current_pos):
            if neighbor_pos in closed_set:
                continue
                
            tentative_g = current_node['g'] + calculate_heuristic(current_pos, neighbor_pos)
            
            if neighbor_pos not in open_dict:
                neighbor = create_node(
                    position=neighbor_pos,
                    g=tentative_g,
                    h=calculate_heuristic(neighbor_pos, goal),
                    parent=current_node
                )
                heapq.heappush(open_list, (neighbor['f'], neighbor_pos))
                print(f"Tentative Cost Added to Priority Queue{(neighbor['f'], neighbor_pos)}")
                open_dict[neighbor_pos] = neighbor

            elif tentative_g < open_dict[neighbor_pos]['g']:
                neighbor = open_dict[neighbor_pos]
                neighbor['g'] = tentative_g
                neighbor['f'] = tentative_g + neighbor['h']
                neighbor['parent'] = current_node
    
    return []  # No path found

grid = np.zeros((5, 5))  # 5x5 grid, all free space initially

grid[0:4, 1] = 1  # Vertical wall
grid[3:, 3] = 1
grid[1, 3:] = 1   # Horizontal wall

# Define start and goal positions
start_pos = (0, 0)
goal_pos = (0, 4)

def plot_path(grid, path) -> None:
    array = np.array([[x[0], x[1]] for x in path])
    plt.grid(True)
    plt.plot(array)
    plt.show()


# Find the path
path = find_path(grid, start_pos, goal_pos)
if path:
    print(f"Path found with {len(path)} steps!")
    print(path)


    print("This algorithm has a optimal heuristic function and uses a priority queue.")
    print("Time Complexity -> O(b^d) here branching factor will be very close to 1 due to optimal heuristic function.")
    print("Space Complexity -> O(b^d)")
    plot_path(grid, path)
else:
    print("No path found!")






