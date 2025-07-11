"""
    Program for Quick sort 
    But the catch this time is that we have to compare between two methods
    1. Regular QuickSort where the pivot is fixed [1st, Middle, Last] (we will take the pivot as the last element)
    2. QuickSort where the pivot is randomnly selected
"""

import sys
sys.setrecursionlimit(10**6)
import random, time 
global ctr1, ctr2
ctr1 = 0
ctr2 = 0

def partition_normal(arr: list, low: int, high: int) -> int:
    pivot = arr[high]

    i = low - 1
    for j in range(low, high):
        if arr[j] <= pivot:
            i += 1

            arr[i], arr[j] = arr[j], arr[i]
    arr[i+1], arr[high] = arr[high], arr[i+1]
    return i+1

def quicksort_normal(arr: list, low: int, high: int) -> None:
    global ctr1
    ctr1 += 1
    if low < high:
        pivot = partition_normal(arr, low, high)

        quicksort_normal(arr, low, pivot-1)
        quicksort_normal(arr, pivot+1, high)


def partition_random(arr: list, low: int, high: int) -> int:
    pivot = random.randint(low, high)
    arr[pivot], arr[high] = arr[high], arr[pivot]
    return partition_normal(arr, low, high)


def quicksort_random(arr: list, low: int, high: int) -> None:
    global ctr2 
    ctr2 += 1
    if low < high:
        pivot = partition_random(arr, low, high)
        quicksort_random(arr, low, pivot-1)
        quicksort_random(arr, pivot+1, high)


if __name__ == "__main__":
    # array1 = array2 = list(map(int, input("Enter an array to sort (space separated)").split()))
    N = int(input("Enter the last number for the array to be sorted: "))
    array1 = array2 = [x for x in range(N)]
    
    print("Sorting Using Normal QuickSort...")
    quicksort_normal(array1, 0, N-1)
    print(f"Sorted Array: {array1}")
    print(f"Normal QuickSort Performed {ctr1} Comparisons")
    print("Sorting using Random QuickSort...")
    quicksort_random(array2, 0, N-1)
    print(f"Randomized QuickSort Performed {ctr2} Comparisons")
    print(f"Sorted Array: {array2}")

