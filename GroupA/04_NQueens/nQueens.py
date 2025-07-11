"""
    # NQueens but harder.
    In this problem the user has to be able to place a Queen which CANNOT be moved. 
    We have to find a way around it. 
    If a solution doesn't exist we tell that to the user.
    Basically we have to improve the `isSafe()` function of the regular backtracking NQueens problem, such that it detects both ways on the board for threats.
"""

def isSafe(pos:tuple, board: list)->bool:
    """Determines if the given position is safe to place a queen or not."""
    
    ROW = COL = len(board)
    row, col = pos

    # Check ROW 
    for r in range(ROW):
        if r != row and board[r][col].lower() == 'q':
            return False

    # Check COL 
    for c in range(COL):
        if c != col and board[row][c].lower() == 'q':
            return False 

    # Check Upper Left Diagonal
    for r, c in zip(range(row-1, -1, -1), range(col-1, -1, -1)):
        if board[r][c].lower() == 'q':
            return False
    
    # Check Lower Left Diagonal 
    for r, c in zip(range(row+1, ROW), range(col-1, -1, -1)):
        if board[r][c].lower() == 'q':
            return False

    # Check Upper Right Diagonal
    for r, c in zip(range(row-1, -1, -1), range(col+1, COL)):
        if board[r][c].lower() == 'q':
            return False

    # Check Lower Right Diagonal
    for r, c in zip(range(row+1, ROW), range(col+1, COL)):
        if board[r][c].lower() == 'q':
            return False
    return True


def backtrack_NQueens(board: list, queens: int, col: int):
    if queens == 0 or col == len(board):
        temp = []
        for row in board:
            temp.append([x for x in row])
        solutions.append(temp)
        return

    for r in range(len(board)):
        if board[r][col] == "Q":
            if isSafe((r,col), board):
                backtrack_NQueens(board, queens-1, col+1)
            return 

    for r in range(len(board)):
        if board[r][col] == '.' and isSafe((r, col), board):

            board[r][col] = 'q'
            backtrack_NQueens(board, queens-1, col+1)
            board[r][col] = '.'
            queens += 1 


def display_board(board: list):
    """Prints the Chess Board"""
    print(f"   {' '.join([str(i) for i in range(len(board))])}")
    print(" ","_"*(2*len(board)+1))
    for i, row in enumerate(board):
        print(f"{i} |{'|'.join(row)}|")
    print(" ","‾"*(2*len(board)+1))


if __name__ == "__main__":
    global solutions
    solutions = []
    N = int(input("Please Enter the Number of Queens to be placed: "))
    board = [['.']*N for _ in range(N)]
    display_board((board))

    if N > 0:
        while(True):
            x, y = map(int, input("Please Enter the position for your Queen (x y): ").split())
            board[x][y] = "Q"
            display_board(board)
            if (input("Are you happy with your choice? (y/N): ").lower()[0] == 'y'):
                break 
            else:
                board[x][y] = "."


        backtrack_NQueens(board, N, 0)
        print(f"{len(solutions)} were found for the given choice")
        if len(solutions) != 0:
            for i, sol in enumerate(solutions, 1):
                print(f"Solution :{i}")
                display_board(sol)



