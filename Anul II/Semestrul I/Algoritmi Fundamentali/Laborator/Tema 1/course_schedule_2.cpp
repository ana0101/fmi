#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Graph {
    int n;
    vector <vector <int>> edges;
    vector <int> order;

public:
    Graph(int n, vector<vector<int>>& edges);
    bool topologicalSort();    // true is possible, false if not

    vector <int> getOrder() {return order;}
};

Graph::Graph(int n, vector<vector<int>>& edges) {
    this->n = n;
    for (int i = 0; i < n; i ++) {
        this->edges.push_back({});
    }
    for (int i = 0; i < edges.size(); i ++) {
        this->edges[edges[i][1]].push_back(edges[i][0]);
    }
}

bool Graph::topologicalSort() {
    // compute in degree for each node
    vector <int> inDegree;
    for (int i = 0; i < n; i ++) {
        inDegree.push_back(0);
    }
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < edges[i].size(); j ++) {
            inDegree[edges[i][j]] ++;
        }
    }

    int nrVisited = 0;   // number of visited nodes
    queue <int> q;

    // put all the nodes with in degree 0 in queue
    for (int i = 0; i < n; i ++) {
        if (inDegree[i] == 0)
            q.push(i);
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        nrVisited ++;
        order.push_back(node);
        
        for (int i = 0; i < edges[node].size(); i ++) {
            int next = edges[node][i];
            inDegree[next] --;
            if (inDegree[next] == 0) {
                q.push(next);
            }
        }
    }

    if (nrVisited == n)
        return true;
    else
        return false;
}

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        Graph g(numCourses, prerequisites);
        bool ok = g.topologicalSort();
        if (ok)
            return g.getOrder();
        else
            return {};
    }
};