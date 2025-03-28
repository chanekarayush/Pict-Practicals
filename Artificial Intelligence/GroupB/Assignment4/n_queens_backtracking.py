
# The number of rows and Columns forming an NxN grid for the chess pieces to move in 
N = 10 
 
ROWS = COLS = N

queens = N 
board = [['.'] * N for _ in range(N)] 

def is_safe(board : list[list], pos : tuple) -> bool:
    """
    This function decides whether the queen is at a safe position or not.
    """
    row, col = pos

    for c in range(COLS):
        if board[row][c] == 'Q':
            return False

    
    # This loop checks both diagonals
    # Check upper-left diagonal
    for r, c in zip(range(row, -1, -1), range(col, -1, -1)):
        if board[r][c] == 'Q':
            return False

    # Check lower-left diagonal
    for r, c in zip(range(row, N, 1), range(col, -1, -1)):
        if board[r][c] == 'Q':
            return False
    return True

def backtrack(board : list[list], col : int, queens : int):
    
    """
    This function uses backtracking to find out which can be played to secure the queen. 
    If there is no move then it will backtrack to the last move made and move ahead from there.
    """


    if queens == 0:
        return True

    for r in range(ROWS):
        # if the queen is safe oke
        # else back track
        if is_safe(board,(r,col)):
            board[r][col] = 'Q'
            queens -= 1
            
            if backtrack(board, col + 1, queens):
                return True
            # It did not return True so we have to reverse the move made above.
            board[r][col] = '.'
            queens += 1
    
    return False
                
if __name__ == "__main__":
    
    if not backtrack(board, 0, queens):
        print('No Solution Exists')

    else:
        print("_"*(2*N+1))
        for row in board:
            print('|', end="")
            for x in row:
                print(x, end="|")
            #print(f"\n{'-'*(2*N+1)}")
            print()
        print("¯"*(2*N+1))
