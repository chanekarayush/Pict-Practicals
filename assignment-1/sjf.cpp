#include <iostream>
#include "fcfs.cpp"
using namespace std;

class SJF : Process
{
    vector<Process> sjftemp, sjfQueue;

public:
    SJF(Process arr[], int n)
    {
        for (int i = 0; i < n; i++)
            sjftemp.push_back(arr[i]);
    }
};
