# The number of rows and columns forming an NxN grid for the chess pieces to move in
def is_safe(board: list[list], pos: tuple) -> bool:
    """
    This function decides whether the queen is at a safe position or not.
    """
    row, col = pos

    # Check the current row
    for c in range(len(board)):
        if board[row][c] == 'Q':
            return False

    # Check upper-left diagonal
    for r, c in zip(range(row, -1, -1), range(col, -1, -1)):
        if board[r][c] == 'Q':
            return False

    # Check lower-left diagonal
    for r, c in zip(range(row, len(board), 1), range(col, -1, -1)):
        if board[r][c] == 'Q':
            return False

    return True


def backtrack(board: list[list], col: int, queens: int, solutions: list):
    """
    This function uses backtracking to find all possible solutions for the N-Queens problem.
    """
    if queens == 0:
        # Store a deep copy of the current board as a solution
        solutions.append(["".join(row) for row in board])
        return

    for r in range(len(board)):
        if is_safe(board, (r, col)):
            # Place the queen
            board[r][col] = 'Q'
            queens -= 1

            # Recur to place the next queen
            backtrack(board, col + 1, queens, solutions)

            # Backtrack: Remove the queen
            board[r][col] = '.'
            queens += 1


def print_board(board: list[str]):
    """
    Prints a single solution board.
    """
    print("_" * (2 * len(board) + 1))
    for row in board:
        print('|', end="")
        for x in row:
            print(x, end="|")
        print()
    print("¯" * (2 * len(board) + 1))


if __name__ == "__main__":
    # Take input for the size of the board
    N = int(input("Enter the number of squares for the N-Queens problem: "))
    board = [['.'] * N for _ in range(N)]
    solutions = []

    # Solve the N-Queens problem
    backtrack(board, 0, N, solutions)

    # Display all solutions
    if not solutions:
        print("No Solution Exists")
    else:
        print(f"Total solutions found: {len(solutions)}")
        for idx, solution in enumerate(solutions, start=1):
            print(f"\nSolution {idx}:")
            print_board(solution)
