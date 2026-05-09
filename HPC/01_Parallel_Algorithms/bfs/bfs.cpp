#include <omp.h>
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <fstream>
#include "./graphutils.cpp"


using namespace std;


vector<int> sequentialBFS(vector<vector<int>> &graph, int source){
    vector<int> level = vector(graph.size(), -1); 
    level[source] = 0;
    int curr_level = 0;

    vector<int> frontier;
    frontier.push_back(source);

    while (!frontier.empty()){
        vector<int> next_local_frontier;
        for(auto node : frontier){
            for (auto nei : graph[node]){
                if (level[nei] == -1){
                    next_local_frontier.push_back(nei);
                    level[nei] = curr_level + 1;
                }
            }
        }
        frontier = next_local_frontier;
        curr_level++;
    }
    return level;
    
}


vector<int> parallelBFS(vector<vector<int>> &graph, int source){
    vector<int> level = vector(graph.size(), -1); 
    level[source] = 0;
    int curr_level = 0;

    vector<int> frontier;
    frontier.push_back(source);

    while (!frontier.empty()){
        vector<int> next_frontier;

        #pragma omp parallel
        {
            int tid = omp_get_thread_num(), nthreads = omp_get_num_threads();
            vector<int> next_local_frontier;
            for(int i=tid; i<frontier.size(); i+=nthreads){
                int node = frontier[i];

                for (int nei : graph[node]){
                    if(__sync_bool_compare_and_swap(&level[nei], -1, curr_level+1)){
                        next_local_frontier.push_back(nei);
                    }
                }
            }

            #pragma omp critical 
            {
                next_frontier.insert(next_frontier.end(), next_local_frontier.begin(), next_local_frontier.end());
            }
        }
        frontier = next_frontier;
        curr_level++;
    }
    return level;
    
}


int main (int argc, char *argv[]) {

    // Defaults
    int n_threads=4;
    int n = 100000, degree = 10, seed = 41313;


    string input;
    cout<<"Enter the number of threads you would like to use (default 4): ";
    preserve_default_input(n);

    omp_set_num_threads(n_threads);


    // Graph Generation
    cout<<"Please Enter the number of vertices for the graph to be generated: ";
    preserve_default_input(n, true);

    cout<<"Please Enter the Average Degree of Each Node: ";
    preserve_default_input(degree, true);

    cout<<"Please Enter the Random Seed (default = 41313)";
    preserve_default_input(seed);

    cout<<"---------- Generating Graph ----------"<<endl;
    // vector<vector<int>> graph = generateRandomGraph(n, degree, seed);

    vector<vector<int>> graph = {
        {1, 2},           // 0 -> 1, 2
        {0, 2, 5},        // 1 -> 0, 2, 5
        {0, 1, 3},        // 2 -> 0, 1, 3
        {2, 4},           // 3 -> 1, 2, 4
        {3, 7},           // 4 -> 3, 5
        {4, 6},           // 5 -> 4, 6
        {5, 7},           // 6 -> 5, 7
        {6, 7}            // 7 -> 6
    };
    
    cout<<"Graph Successfully generated!"<<endl;
   

    // Comparison
    cout<<"Do you want perform an accuracy comparison? [Sequential vs Parallel] (Y/n)";
    char ch = 'n';
    cin>>ch;
    if (ch != 'Y' || ch != 'y'){
        if (n < 100){
            cout << "---------------------------Accuracy Comparison-----------------------------"<<endl;
            vector<int> bfs_level_seq = sequentialBFS(graph, 0);
            printgraph(bfs_level_seq);
            cout << "----------------------------------------------------------------------"<<endl;
            vector<int> bfs_level_par = parallelBFS(graph, 0);
            printgraph(bfs_level_par);
            cout << "----------------------------------------------------------------------"<<endl;
            cout<<"Original Graph"<<endl;
            printgraph(graph);
        }else{
            cout<<"The output generated contains "<<n<<" lines!"<<endl<<"Not all of us are proficient readers like you :/\nThe Result will be written to a file you can compare them using a simple shell command."<<endl;
            
            ofstream seq_file("sequential_output.txt");
            ofstream par_file("parallel_output.txt");
            
            vector<int> bfs_level_seq = sequentialBFS(graph, 0);
            printgraph(bfs_level_seq, &seq_file);
            
            vector<int> bfs_level_par = parallelBFS(graph, 0);
            printgraph(bfs_level_par, &par_file);
            
            seq_file.close();
            par_file.close();
            
            cout << "Results written to sequential_output.txt and parallel_output.txt" << endl;
            cout << "Run Command this command to check if the files are same or not: \ndiff sequential_output.txt parallel_output.txt"<<endl;
        }
    }

    
    cout << "---------------------------Speed Comparison-----------------------------"<<endl;

    int iterations=5;
    cout<<"How many iterations would you like to run the algorithm for?(default: 5)";
    preserve_default_input(iterations);

    double sum = 0;
    for (int i = 0; i < iterations; i++) {
        double s = omp_get_wtime();
        sequentialBFS(graph, 0);
        sum += omp_get_wtime() - s;
    }
    cout << "Average sequential time: " << sum / iterations << " sec\n";

    sum=0;
    for (int i = 0; i < iterations; i++) {
        double s = omp_get_wtime();
        parallelBFS(graph, 0);
        sum += omp_get_wtime() - s;
    }
    cout << "Average parallel time: " << sum / iterations << " sec\n";
    return 0;
}
