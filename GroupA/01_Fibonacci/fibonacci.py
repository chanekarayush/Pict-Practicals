"""
Program to write Fibonacci numbers in python.
Also find their step count.
"""

def fibn(x: int, y: int, step: int, i: int) -> None:
    """
        A simple function which finds out the next in fibonbacci series
    """
    if step == 0:
        return
    print(f"{y} -> step={i}")
    fibn(y, x+y, step-1, i+1)


global dp
dp = [0,1]


def fibfast(step: int) -> None:
    """
        A function which finds out the next in fibonbacci series using dynamic programming.
    """
    if step == 0:
        return
    global dp 
    if step < len(dp):
        for i, x in enumerate(dp):
            print(f"{x} -> step={i+1}")
    else:
        i = 0
        while i < len(dp):
            print(f"{dp[i]} -> step={i+1}")
            i += 1 
        

        x, y = dp[-2], dp[-1]

        while i < step:
            x, y = y, x+y
            print(f"{y} -> step={i+1}")
            if i >= len(dp):
                dp.append(y)
            i += 1
    

if __name__ == "__main__":
    x: int = 0
    y: int = 1
    while (True):
        steps: int = int(input("Please Enter the Number of Steps for the Series: "))
        print(f"{x} -> step={1}")
        fibn(0, 1, steps-1, 2)
        print("The Time Complexity for this program is O(n!) and the Space Complexity is O(1)")
        print("We can improve this by using an array to store the previously found out values.")
        
        fibfast(steps)


        if (input("Do you want to continue? (y/N)").strip()[0] not in ['y',"Y"]):
            break


