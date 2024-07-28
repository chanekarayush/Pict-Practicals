#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/** @brief Contains the structure for basic details to be collected about the process.
 *
 * @param pid   process id
 * @param at    arrival time of `pid`
 * @param bt    Burst time of process
 */
class Process
{
public:
    int pid;
    int at;
    int bt;
    int tat;
    int ct;
    int wt;
    Process()
    {
        this->pid = 0;
        this->at = 0;
        this->bt = 0;
        this->tat = 0;
        this->ct = 0;
        this->wt = 0;
    }
    Process(int pid, int at, int bt)
    {
        this->pid = pid;
        this->at = at;
        this->bt = bt;
        this->tat = 0;
        this->ct = 0;
        this->wt = 0;
    }

protected:
    void ganttChart(std::vector<Process> jobOrder)
    {
        int k = 0; // counter clock
        int length = jobOrder.size();
        for (unsigned int i = 0; k <= jobOrder[length - 1].at; i++)
        {
            if (jobOrder[i].at == k)
            {
                cout << "process" << jobOrder[i].pid << endl;
            }
            else
            {
                cout << "Idle" << endl;
                k++;
                i--;
            }
            cout << "K = " << k << endl;
        }
    }
};

class FCFS : private Process
{
    vector<Process> fcfsQueue;
    static bool compareATval(const Process &a, const Process &b)
    {
        return a.at < b.at;
    }
    void sortItems()
    {
        std::sort(fcfsQueue.begin(), fcfsQueue.end(), compareATval);
    }

public:
    FCFS(Process arr[], int n)
    {
        for (int i = 0; i < n; i++)
            fcfsQueue.push_back(arr[i]);
    }
    void display()
    {
        sortItems();
        ganttChart(fcfsQueue);
    }
};

int main()
{
    const int size = 5;
    Process arr[size] = {
        Process(1, 0, 4),
        Process(2, 2, 3),
        Process(3, 3, 2),
        Process(4, 0, 2),
        Process(5, 2, 3),
    };
    FCFS fcfs = FCFS(arr, size);
    fcfs.display();
    return 0;
}