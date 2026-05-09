#include <algorithm>
#include<iostream>
#include <random>
#include <exception>
#include <sstream>
#include <stdexcept>

using namespace std;

/*
 * This function allows you to call a file thing as well as cout 
 * did't know file buffer and console buffer were so easy to manage.
 * */
void printgraph(vector<int> &graph, ostream* output = nullptr){
    if (output == nullptr) output = &cout;
    for(int i=0; i<graph.size(); i++)
        *output << i << " ----> " << graph[i] << endl;
}

void printgraph(vector<vector<int>> &graph){
    int i = 0;
    for(auto row : graph){
        cout<<"Row "<<i++<<" --> ";
        for(int x : row){
            cout<<" "<<x;
        }
        cout<<endl;
    }
}

vector<vector<int>> generateRandomGraph(int n, int avg_degree, int seed){
    vector<vector<int>> graph(n);
    // random_device rd;
    // mt19937 gen(rd());
    mt19937 gen(seed);
    uniform_int_distribution<int> dist(0, n-1);

    for(int i = 0; i<n; i++){
        for (int j=0; j<avg_degree; j++){
            int nei = dist(gen);
            
            if(nei != i){
                graph[i].push_back(nei);
                graph[nei].push_back(i);
            }
        }
    }
    return graph;
}


template<typename T>
void preserve_default_input(T &var, bool error=false){
    try {
        string input;
        getline(cin, input);
        if(input.empty() && error)
                throw runtime_error("Empty Input Value where Input Required");
        else{
            stringstream ss(input);
            T temp;
            if (ss >> temp)
                var = temp;
            else
                throw runtime_error("Using Default Value as user gave an invalid input");
        }
    } catch (const exception &e) {
        cerr<< e.what() <<endl;
    }
}
