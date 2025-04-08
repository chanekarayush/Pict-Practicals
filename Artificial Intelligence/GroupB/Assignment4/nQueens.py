"""
Constraints:
1. No 2 queens share the same row
2. No 2 queens share the same column
3. No 2 queens share the same diagonal

Now here we will only check the left side of the board i.e. all the rows and columns before the current one, 
as we are placing the queens left to right.
"""

def solve_n_queens_BnB(n, col, left_diag, right_diag, cols, board, solutions):
    if col >= n:
        # Store the solution when found
        solutions.append([row[:] for row in board])  # Deep copy of the board
        return  # Continue searching for other solutions

    for row in range(n):
        if not cols[row] and not left_diag[row + col] and not right_diag[row - col + n - 1]:
            # Place the queen
            board[row][col] = 1
            cols[row] = left_diag[row + col] = right_diag[row - col + n - 1] = True
            
            # Recur to place the next queen
            solve_n_queens_BnB(n, col + 1, left_diag, right_diag, cols, board, solutions)
            
            # Backtrack
            board[row][col] = 0
            cols[row] = left_diag[row + col] = right_diag[row - col + n - 1] = False

def print_board(board, N):
    print("_" * (2 * N + 1))
    for row in board:
        print('|', end="")
        for x in row:
            print('Q' if x else '.', end="|")
        print()
    print("¯" * (2 * N + 1))

def n_queens_BnB(n):
    board = [[0] * n for _ in range(n)]
    cols = [False] * n
    left_diag = [False] * (2 * n - 1)
    right_diag = [False] * (2 * n - 1)
    solutions = []  # List to store all solutions

    solve_n_queens_BnB(n, 0, left_diag, right_diag, cols, board, solutions)

    if not solutions:
        print("No solution exists.")
        return

    print(f"Total solutions found: {len(solutions)}")
    #for idx, solution in enumerate(solutions, start=1):
        #print(f"\nSolution {idx}:")
        # print_board(solution, n)

n_queens_BnB(int(input("Enter the number of squares for the N-Queens problem: ")))

time_complexity = """
Worst-Case Time Complexity: O(N!)
Average-Case Time Complexity (With Pruning): O(N²) to O(N^1.5)
Best-Case Complexity (If a Solution is Found Early): O(N)
"""

space_complexity = """
O(N²) (if storing the board) -> This implementation
O(N) (if storing only column positions and using boolean arrays for pruning)
"""

print("Time Complexity\n", time_complexity, "\nSpace Complexity\n", space_complexity)
