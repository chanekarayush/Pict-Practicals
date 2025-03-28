"""
Contraints:
1. No 2 queens share the same row
2. No 2 queens share the same column
3. No 2 queens share the same diagonal

Now here we will only check the left side of the board i.e. all the rows and columns before the current one, 
as we are placing the queens left to right.
"""

def solve_n_queens_BnB(n, col, left_diag, right_diag, cols, board):
    if col >= n:
        return True  # Solution found

    for row in range(n):
        if not cols[row] and not left_diag[row + col] and not right_diag[row - col + n - 1]:
            # Place the queen
            board[row][col] = 1
            cols[row] = left_diag[row + col] = right_diag[row - col + n - 1] = True
            
            if solve_n_queens_BnB(n, col + 1, left_diag, right_diag, cols, board):
                return True
            
            # Backtrack
            board[row][col] = 0
            cols[row] = left_diag[row + col] = right_diag[row - col + n - 1] = False

    return False

def n_queens_BnB(n):
    board = [[0] * n for _ in range(n)]
    cols = [False] * n
    left_diag = [False] * (2 * n - 1)
    right_diag = [False] * (2 * n - 1)

    if not solve_n_queens_BnB(n, 0, left_diag, right_diag, cols, board):
        print("No solution exists.")
        return
    
    for row in board:
        print(row)


n_queens_BnB(int(input("Enter the number of square for N queens problem")))

