#include <iostream>
#include <utility>
#include <vector>

using namespace std;

void sequentialbubblesort(vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
    }
}

void parallelbubblesort(vector<int>& arr)
{
    int n = arr.size();
#pragma omp parallel
    {
        for (int i = 0; i < n; i++)
        {
            int first = i % 2;
#pragma omp for
            for (int j = first; j < n - 1; j += 2)
                if (arr[j] > arr[j + 1])
                    swap(arr[j], arr[j + 1]);
        }
    }
}
