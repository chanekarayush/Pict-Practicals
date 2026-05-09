#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <iterator>
#include <mpi.h>

using namespace std;

// vector<int> sequentialDFS(vector<vector<int>> &graph, int source){
//     vector<int> level = vector(graph.size(), -1);
//     level[source] = 0;
//     stack<int> st;
// 
//     st.push(source);
// 
//     while (!st.empty()){
//         int node = st.top();
//         st.pop();
//         if (level[node] == -1){
// 
// 
//         }
//     }
// }

int main (int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int token = 0;

    MPI_Status status;
    cout<<"----------------------------------------------------------"<<endl;
    cout<<"Hello from process: "<<rank<<" of size: "<<size<<endl; 
    if (rank == 0){
        MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&token, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, &status);
        std::cout << "Got message; "<<token<<" from process "<< status.MPI_SOURCE <<endl;
    }
    if (rank != 0){
        MPI_Recv(&token, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
        std::cout << "Got message; "<<token<<" from process "<< status.MPI_SOURCE <<endl;
        token += rank;
        MPI_Send(&token, 1, MPI_INT, (rank+1)%4, 0, MPI_COMM_WORLD);
    }
    cout<<"----------------------------------------------------------"<<endl;


    MPI_Finalize();
    return 0;
}
