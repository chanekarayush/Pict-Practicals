"""
    Program to solve the 0-1 Knapsack Problem.
"""

def brute_force(capacity:int, n:int)->int:
    print(f"Capacity = {capacity}, n = {n}")
    
    global steps
    steps += 1

    if n == 0 or capacity == 0:
        return 0
    
    elif weights[n-1] > capacity:
        return brute_force(capacity, n-1)

    else:
        include_item = values[n-1] + brute_force(capacity - weights[n-1], n-1)
        exclude_item = brute_force(capacity, n-1)

        return max(include_item, exclude_item)


def topdown_knapsack(capacity:int, n:int)->int:
    print(f"Capacity = {capacity}, n = {n}")
    
    if table[n][capacity] is not None:
        print(f"Used `table` for capacity={capacity} and n={n}")
        return table[n][capacity]

    global steps
    steps += 1
    if n == 0 or capacity == 0:
        res = 0
    
    elif weights[n-1] > capacity:
        res = brute_force(capacity, n-1)

    else:
        include_item = values[n-1] + topdown_knapsack(capacity - weights[n-1], n-1)
        exclude_item = topdown_knapsack(capacity, n-1)

        res = max(include_item, exclude_item)
    
    table[n][capacity] = res 
    return res 

values = []
weights = []
table = []

if __name__ == "__main__":
    values = [300, 200, 400, 500, 300, 200, 400, 500]
    weights = [2, 1, 5, 3, 2, 1, 5, 3]
    capacity = 20 
    global steps
    steps = 0
    print(f"Capacity of the Bag = {capacity}")
    print(f"Maximum Value of the Bag = {brute_force(capacity, len(values))}")
    print(f"Number of Steps required = {steps}")
    print(f"The Time Complexity of Brute force is O(2^n)")

    # This is our table for memoization
    table = [[None]*(capacity+1) for _ in range(len(values)+1)]

    steps = 0
    print('-'*50, "Dynamic Programming Approach", '-'*50)
    print(f"Capacity of the Bag = {capacity}")
    print(f"Maximum Value of the Bag = {topdown_knapsack(capacity, len(values))}")
    print(f"Number of Steps required = {steps}")
    print(f"The Time Complexity of Brute force is O(n*c)\nWhere n is the number of values and C is the Capacity of the Knapsack")

    

