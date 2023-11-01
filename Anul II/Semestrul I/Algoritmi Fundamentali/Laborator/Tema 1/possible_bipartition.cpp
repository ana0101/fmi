#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Graph {
    int n;
    vector <vector <int>> edges;
    vector <int> color;

public:
    Graph(int n, vector<vector<int>>& edges);
    bool bfs(int node);
    bool bipartite();
};

Graph::Graph(int n, vector<vector<int>>& edges) {
    this->n = n;
    for (int i = 0; i <= n; i ++) {
        this->edges.push_back({});
    }
    for (int i = 0; i <= n; i ++) {
        this->color.push_back(0);
    }
    for (int i = 0; i < edges.size(); i ++) {
        this->edges[edges[i][0]].push_back(edges[i][1]);
        this->edges[edges[i][1]].push_back(edges[i][0]);
    }
}

bool Graph::bfs(int node) {
    queue <int> q;
    q.push(node);
    color[node] = 1;

    while (!q.empty()) {
        node = q.front();
        q.pop();
        for (int i = 0; i < edges[node].size(); i ++) {
            int next = edges[node][i];
            if (!color[next]) {
                color[next] = 3 - color[node];
                q.push(next);
            } 
            else {
                if (color[next] == color[node]) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Graph::bipartite() {
    for (int i = 1; i <= n; i ++) {
        if (!color[i]) {
            if (!bfs(i))
                return false;
        }
    }
    return true;
}

class Solution {
public:
    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        Graph g(n, dislikes);
        return g.bipartite();
    }
};


int main() {
    Solution s;
    return 0;
}