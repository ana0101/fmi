#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Graph {
    int n;
    vector <vector <int>> edges;
    vector <bool> visited;
    vector <int> level; // level of a node in the dfs tree
    vector <int> low;   // lowest level a node can go with a back-edge
    vector <int> parent;
    vector <vector <int>> bridges;

public:
    Graph(int n, vector<vector<int>>& edges);
    void dfs(int node);
    void findBridges();
    vector <vector <int>> getBridges() {return bridges;}
};

Graph::Graph(int n, vector<vector<int>>& edges) {
    this->n = n;
    for (int i = 0; i < n; i ++) {
        this->edges.push_back({});
    }
    for (int i = 0; i < edges.size(); i ++) {
        this->edges[edges[i][0]].push_back(edges[i][1]);
        this->edges[edges[i][1]].push_back(edges[i][0]);
    }
    for (int i = 0; i < n; i ++) {
        visited.push_back(0);
        level.push_back(0);
        low.push_back(0);
        parent.push_back(-1);
    }
}

void Graph::dfs(int node) {
    visited[node] = 1;
    
    for (int i = 0; i < edges[node].size(); i ++) {
        int next = edges[node][i];
        if (!visited[next]) {
            parent[next] = node;
            level[next] = level[node] + 1;
            low[next] = level[next];

            dfs(next);

            // update the low value for node because a back-edge to an ancestor of node might have been found through next
            low[node] = min(low[node], low[next]);

            // if the level value of node is smaller than the low value of next that means there was no back-edge discovered
            // through next to an ancestor of node or node (because otherwise the low value of next would have been updated)
            // and so this edge is a bridge
            if (level[node] < low[next]) {
                vector <int> b;
                b.push_back(node);
                b.push_back(next);
                bridges.push_back(b);
            }
        }
        else {
            // if next is already visited
            if (next != parent[node]) {
                // update the low value of node - possible new low
                low[node] = min(low[node], level[next]);
            }
        }
    }
}

void Graph::findBridges() {
    for (int i = 0; i < n; i ++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
}

class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        Graph g(n, connections);
        g.findBridges();
        return g.getBridges();
    }
};