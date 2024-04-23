#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void parallelDFSUtil(vector<vector<int>>& adj, int v, vector<bool>& visited) {
    #pragma omp critical
    {
        if (!visited[v]) {
            visited[v] = true;
            cout << v << " ";
        }
    }

    #pragma omp parallel for
    for (int i = 0; i < adj[v].size(); ++i) {
        if (!visited[adj[v][i]])
            parallelDFSUtil(adj, adj[v][i], visited);
    }
}

void parallelDFS(vector<vector<int>>& adj, int startVertex) {
    int V = adj.size();
    vector<bool> visited(V, false);
    parallelDFSUtil(adj, startVertex, visited);
}

int main() {
    int numVertices, numEdges;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    vector<vector<int>> adj(numVertices);

    cout << "Enter the edges (vertex pairs):" << endl;
    for (int i = 0; i < numEdges; ++i) {
        int v, w;
        cin >> v >> w;
        adj[v].push_back(w); // Directly add the edge to the adjacency list
    }

    int startVertex;
    cout << "Enter the start vertex for DFS: ";
    cin >> startVertex;

    cout << "Depth-First Search (DFS): ";
    parallelDFS(adj, startVertex);
    cout << endl;

    return 0;
}
