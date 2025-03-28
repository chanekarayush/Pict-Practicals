#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

class Graph {
    map<string, vector<string>> adjacency_list;
    int n_nodes;
    int n_edges;

public:
    // Graph() : n_nodes(0), n_edges(0) {}
    Graph(int n = 0,int e = 0) {
        n_edges = e;
        n_nodes = n;
    }

    
    void create_edge(const string& node1, const string& node2) {
        if (node1 == node2) {
            return; 
        }

        if (adjacency_list.count(node1) != 0) {
            adjacency_list[node1].push_back( node2 ); 
        }
        else {
            adjacency_list[node1] = { node2 };
        }

       
        if (adjacency_list.count(node2) != 0) {
            adjacency_list[node2].push_back( node1 );
        } else {
            adjacency_list[node2] = { node1 };
        }

        n_edges++;
    }

    // Recursive BFS implementation
    // void BFS(const string& start_node, const string& key) {
    //     vector<string> visited;
    //     queue<string> bfs_queue;
    //     bfs_queue.push(start_node);
    //     visited.push_back(start_node);

    //     recursive_BFS(visited, bfs_queue, key);
    // }

    // Recursive function for BFS
    // void recursive_BFS(vector<string>& visited, queue<string>& bfs_queue, const string& key) {
    //     if (bfs_queue.empty()) { 
    //         return;
    //     }

    //     string current_node = bfs_queue.front();
    //     bfs_queue.pop();
    //     cout << "Visited the node " << current_node << endl;

    //     if (current_node == key) {
    //         cout << "Found the node: " << current_node << endl;
    //         return;
    //     }

    //     visited.push_back(current_node);

    //     for (const string& neighbor : adjacency_list[current_node]) {
    //         if (find(visited.begin(), visited.end(), neighbor) == visited.end()) { 
    //             // iterator goes beyong last point
    //             bfs_queue.push(neighbor);
    //         }
    //     }

    //     recursive_BFS(visited, bfs_queue, key);
    // }
    void BFS(const string& start_node, const string& key) {
        vector<string> visited;
        queue<string> bfs_queue;

        bfs_queue.push(start_node);
        visited.push_back(start_node); // Mark as visited when enqueued

        recursive_BFS(visited, bfs_queue, key);
    }

    // Recursive function for BFS
    void recursive_BFS(vector<string>& visited, queue<string>& bfs_queue, const string& key) {
        if (bfs_queue.empty()) {
            return;
        }

        string current_node = bfs_queue.front();
        bfs_queue.pop();
        cout << "Visited the node " << current_node << endl;

        if (current_node == key) {
            cout << "Found the node: " << current_node << endl;
            return;
        }

        for (const string& neighbor : adjacency_list[current_node]) {
            // Only enqueue and mark nodes not already visited
            if (find(visited.begin(), visited.end(), neighbor) == visited.end()) {
                bfs_queue.push(neighbor);
                visited.push_back(neighbor); // Mark as visited here to avoid duplication
            }
        }

        recursive_BFS(visited, bfs_queue, key);
    }


    // Print the graph's adjacency list
    void print() {
        for (const auto& node_list : adjacency_list) {
            cout << node_list.first << " : ";
            for (const string& neighbor : node_list.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    void DFS(string start,string key) {
        vector<string> visited;

        recursive_DFS(start,key,visited);

    }

    bool recursive_DFS(string start_node,string key,vector<string>& visited) {
        cout << "Visited the node "<<start_node<<endl;

        if(start_node == key ) {
            cout<<"Found the target node "<<endl;
            return true;
        }

        visited.push_back(start_node);

        vector<string> neighbors = adjacency_list[start_node] ; 
        for(string &neighbor : neighbors) {
            if(find(visited.begin(),visited.end(),neighbor) == visited.end()) {
                bool found = recursive_DFS(neighbor,key,visited);
                if(found) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    Graph obj;
    int choice = 0;
    cout<<"Enter 1 to input the graph"<<endl;
    cout<<"Enter 2 to display the graph"<<endl;
    cout<<"Enter 3 for BFS"<<endl;
    cout<<"Enter 4 for DFS"<<endl;
    cout<<"Enter 5 to exit"<<endl;
    while(choice != 5) {
        cout<<"Enter your choice: ";
        cin>>choice;

        if(choice == 1) {

            int num_nodes, num_edges;
            cout << "Enter the number of nodes: ";
            cin >> num_nodes;
            cout << "Enter the number of edges: ";
            cin >> num_edges;

            for (int i = 0; i < num_edges; ++i) {
                string n1, n2;
                cout<<"For edge "<<i + 1<<endl;
                cout << "Enter node1: ";
                cin >> n1;
                cout << "Enter node2: ";
                cin >> n2;
                obj.create_edge(n1, n2);
            }
        }
        else if (choice == 2)
        {
            obj.print();
        }
        else if (choice == 3)
        {
            string start_node, target_node;
            cout << "Enter the start node for BFS: ";
            cin >> start_node;
            cout << "Enter the target node to find: ";
            cin >> target_node;
            obj.BFS(start_node, target_node);
        }
        else if (choice == 4)
        {
            string start_node, target_node;
            cout << "Enter the start node for DFS: ";
            cin >> start_node;
            cout << "Enter the target node to find: ";
            cin >> target_node;
            obj.DFS(start_node, target_node);
        }
        else if (choice == 5)
        {
            cout<<"Exiting the program "<<endl;
        }
        else
        {
            choice = 0;
            cout<<"Enter valid choice "<<endl;
        }
        
    }
    return 0;
}