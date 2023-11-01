#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Graph {
    int n;
    vector <vector <int>> edges;
    vector <bool> visited;
    vector <bool> visited2; // retine daca un nod a fost vizitat in parcurgerea curenta
    vector <bool> safe;

public:
    Graph(int n, vector<vector<int>>& edges);
    bool dfs(int node);
    vector <int> getSafeNodes();
};

Graph::Graph(int n, vector<vector<int>>& edges) {
    this->n = n;
    this->edges = edges;
    for (int i = 0; i < n; i ++) {
        this->visited.push_back(0);
    }
    for (int i = 0; i < n; i ++) {
        this->visited2.push_back(0);
    }
    for (int i = 0; i < n; i ++) {
        this->safe.push_back(0);
    }
}

bool Graph::dfs(int node) {
    visited[node] = 1;
    visited2[node] = 1;
    
    for (int i = 0; i < edges[node].size(); i ++) {
        int next = edges[node][i];
        // daca nu am vizitat nodul, il vizitam
        if (!visited[next]) {
            bool ok = dfs(next);
            if (!ok) {
                safe[node] = 0;
                return 0;
            }
        }
        else {
            // daca am vizitat nodul in parcurgerea curenta => ciclu
            if (visited2[next]) {
                safe[node] = 0;
                return 0;
            }
        }
    }

    visited2[node] = 0;
    safe[node] = 1;
    return 1;
}

vector <int> Graph::getSafeNodes() {
    for (int i = 0; i < n; i ++) {
        if (!visited[i])
            dfs(i);
    }
    vector <int> safeNodes;
    for (int i = 0; i < n; i ++) {
        if (safe[i])
            safeNodes.push_back(i);
    }
    sort(safeNodes.begin(), safeNodes.end());
    return safeNodes;
}

class Solution {
public:
    vector <int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        Graph g(n, graph);
        return g.getSafeNodes();
    }
};