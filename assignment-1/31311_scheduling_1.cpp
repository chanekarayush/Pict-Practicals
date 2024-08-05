#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric>

using namespace std;

/**
 * @brief Class representing a Process Scheduler for handling various scheduling algorithms.
 */
class ProcessScheduler
{
private:
    int number;                 ///< Number of processes
    vector<int> pid;            ///< Process IDs
    vector<int> AT;             ///< Arrival Times
    vector<int> BT;             ///< Burst Times
    vector<int> CT;             ///< Completion Times
    vector<int> RT;             ///< Remaining Times
    vector<int> TAT;            ///< Turnaround Times
    vector<int> WT;             ///< Waiting Times
    vector<int> priority;       ///< Priorities
    vector<int> executionOrder; ///< Execution order of processes
    int quantum;                ///< Time quantum for Round Robin scheduling

public:
    /**
     * @brief Constructor to initialize the Process Scheduler with a number of processes.
     * @param n Number of processes
     */
    ProcessScheduler(int n) : number(n)
    {
        pid.resize(n);
        AT.resize(n);
        BT.resize(n);
        CT.resize(n);
        RT.resize(n);
        TAT.resize(n);
        WT.resize(n);
        priority.resize(n);
    }

    /**
     * @brief Retrieves process details (PID, Arrival Time, Burst Time, Priority) from user input.
     */
    void getProcesses()
    {
        for (int i = 0; i < number; ++i)
        {
            cout << "Enter PID for process " << i + 1 << ": ";
            cin >> pid[i];
            cout << "Enter Arrival Time for process " << i + 1 << ": ";
            cin >> AT[i];
            cout << "Enter Burst Time for process " << i + 1 << ": ";
            cin >> BT[i];
            cout << "Enter Priority for process " << i + 1 << " (lower number means higher priority): ";
            cin >> priority[i];
            RT[i] = BT[i]; // Initial remaining time is the burst time
        }
    }

    /**
     * @brief Displays the details of all processes including PID, Arrival Time, Burst Time, Completion Time, Turnaround Time, and Waiting Time.
     */
    void displayProcesses() const
    {
        cout << "PID\tAT\tBT\tCT\tTAT\tWT" << endl;
        for (int i = 0; i < number; ++i)
        {
            cout << pid[i] << "\t" << AT[i] << "\t" << BT[i] << "\t" << CT[i] << "\t" << TAT[i] << "\t" << WT[i] << endl;
        }
    }

    /**
     * @brief Displays the execution order of processes based on the last scheduling operation.
     */
    void displayExecutionOrder() const
    {
        cout << "Execution Order of Processes:" << endl;
        for (int i = 0; i < executionOrder.size(); ++i)
        {
            cout << "Process " << executionOrder[i] + 1 << " (PID: " << pid[executionOrder[i]] << ")" << endl;
        }
    }

    /**
     * @brief Sorts processes based on their Arrival Time using a stable sorting algorithm.
     */
    void sortProcessesByArrivalTime()
    {
        vector<int> indices(number);
        iota(indices.begin(), indices.end(), 0); // Fill with 0, 1, 2, ..., number-1
        sort(indices.begin(), indices.end(), [&](int i, int j)
             { return AT[i] < AT[j]; });

        reorderProcesses(indices);
    }

    /**
     * @brief Reorders processes based on a given order of indices.
     * @param indices Vector of indices representing the new order of processes
     */
    void reorderProcesses(const vector<int> &indices)
    {
        vector<int> tempPID(number), tempAT(number), tempBT(number), tempRT(number), tempPriority(number);

        for (int i = 0; i < number; ++i)
        {
            tempPID[i] = pid[indices[i]];
            tempAT[i] = AT[indices[i]];
            tempBT[i] = BT[indices[i]];
            tempRT[i] = RT[indices[i]];
            tempPriority[i] = priority[indices[i]];
        }

        pid = tempPID;
        AT = tempAT;
        BT = tempBT;
        RT = tempRT;
        priority = tempPriority;
    }

    /**
     * @brief Calculates and displays the average Turnaround Time and Waiting Time for all processes.
     */
    void calculateAverage() const
    {
        int totalWT = 0, totalTAT = 0;
        for (int i = 0; i < number; ++i)
        {
            totalTAT += TAT[i];
            totalWT += WT[i];
        }
        cout << "Average Turnaround Time: " << static_cast<double>(totalTAT) / number << endl;
        cout << "Average Waiting Time: " << static_cast<double>(totalWT) / number << endl;
    }

    // Scheduling algorithms

    /**
     * @brief Implements the First Come First Serve (FCFS) scheduling algorithm.
     */
    void fcfs();

    /**
     * @brief Implements the Shortest Job First (SJF) preemptive scheduling algorithm.
     */
    void sjf_preemptive();

    /**
     * @brief Implements the Priority Scheduling non-preemptive scheduling algorithm.
     */
    void priorityScheduling();

    /**
     * @brief Implements the Round Robin preemptive scheduling algorithm with a specified quantum.
     * @param quantum Time quantum for Round Robin
     */
    void roundRobin(int quantum);

    // Additional utility functions if needed
};

/**
 * @brief Implements the First Come First Serve (FCFS) scheduling algorithm.
 */
void ProcessScheduler::fcfs()
{
    executionOrder.clear(); // Clear previous execution order
    CT[0] = AT[0] + BT[0];
    executionOrder.push_back(0);

    for (int i = 1; i < number; ++i)
    {
        CT[i] = max(CT[i - 1], AT[i]) + BT[i];
        executionOrder.push_back(i);
    }

    for (int i = 0; i < number; ++i)
    {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
    }
}

/**
 * @brief Implements the Shortest Job First (SJF) preemptive scheduling algorithm.
 */
void ProcessScheduler::sjf_preemptive()
{
    executionOrder.clear(); // Clear previous execution order
    vector<int> remainingTime = BT;

    int complete = 0, time = 0;
    while (complete != number)
    {
        int shortest = -1, minm = INT_MAX;
        for (int i = 0; i < number; ++i)
        {
            if (AT[i] <= time && remainingTime[i] < minm && remainingTime[i] > 0)
            {
                minm = remainingTime[i];
                shortest = i;
            }
        }

        if (shortest == -1)
        {
            ++time;
            continue;
        }

        executionOrder.push_back(shortest);
        --remainingTime[shortest];

        if (remainingTime[shortest] == 0)
        {
            ++complete;
            CT[shortest] = time + 1;
            TAT[shortest] = CT[shortest] - AT[shortest];
            WT[shortest] = TAT[shortest] - BT[shortest];
        }

        ++time;
    }
}

/**
 * @brief Implements the Priority Scheduling non-preemptive scheduling algorithm.
 */
void ProcessScheduler::priorityScheduling()
{
    executionOrder.clear(); // Clear previous execution order
    vector<bool> isCompleted(number, false);

    int complete = 0, time = 0;
    while (complete != number)
    {
        int highestPriority = INT_MAX, selectedProcess = -1;

        for (int i = 0; i < number; ++i)
        {
            if (AT[i] <= time && !isCompleted[i] && priority[i] < highestPriority)
            {
                highestPriority = priority[i];
                selectedProcess = i;
            }
        }

        if (selectedProcess == -1)
        {
            ++time;
            continue;
        }

        executionOrder.push_back(selectedProcess);
        time += BT[selectedProcess];
        CT[selectedProcess] = time;
        TAT[selectedProcess] = CT[selectedProcess] - AT[selectedProcess];
        WT[selectedProcess] = TAT[selectedProcess] - BT[selectedProcess];
        isCompleted[selectedProcess] = true;
        ++complete;
    }
}

/**
 * @brief Implements the Round Robin preemptive scheduling algorithm with a specified quantum.
 * @param quantum Time quantum for Round Robin
 */
void ProcessScheduler::roundRobin(int quantum)
{
    executionOrder.clear(); // Clear previous execution order

    vector<int> remainingBT = BT;
    int time = 0, complete = 0;

    while (complete != number)
    {
        bool done = true;
        for (int i = 0; i < number; ++i)
        {
            if (remainingBT[i] > 0)
            {
                executionOrder.push_back(i);
                if (remainingBT[i] > quantum)
                {
                    time += quantum;
                    remainingBT[i] -= quantum;
                }
                else
                {
                    time += remainingBT[i];
                    CT[i] = time;
                    TAT[i] = CT[i] - AT[i];
                    WT[i] = TAT[i] - BT[i];
                    remainingBT[i] = 0;
                    ++complete;
                }
                done = false;
            }
        }
        if (done)
            break;
    }
}

/**
 * @brief Main function to interact with the Process Scheduler and choose scheduling algorithms.
 */
int main()
{
    int choice, n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    ProcessScheduler scheduler(n);
    scheduler.getProcesses();
    scheduler.sortProcessesByArrivalTime();

    cout << "Enter the time quantum for Round Robin scheduling: ";
    cin >> quantum;

    do
    {
        cout << "\nChoose the scheduling algorithm:\n";
        cout << "1. First Come First Serve (FCFS)\n";
        cout << "2. Shortest Job First (Preemptive)\n";
        cout << "3. Priority Scheduling (Non-Preemptive)\n";
        cout << "4. Round Robin (Preemptive)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            scheduler.fcfs();

            break;
        case 2:
            scheduler.sjf_preemptive();
            break;
        case 3:
            scheduler.priorityScheduling();
            break;
        case 4:
            scheduler.roundRobin(quantum);

            break;
        case 5:
            cout << "Exited Program Successfully" << endl;
            break;
        default:
            cout << "Invalid choice! Please choose again." << endl;
            continue;
        }
        if (choice < 5 && choice > 0)
        {
            scheduler.displayProcesses();
            scheduler.calculateAverage();
            scheduler.displayExecutionOrder();
        }

    } while (choice != 5);

    return 0;
}
