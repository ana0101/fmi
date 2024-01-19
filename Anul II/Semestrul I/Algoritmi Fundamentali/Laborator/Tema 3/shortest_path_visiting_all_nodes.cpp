#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Graph {
private:
    int n;
    vector <vector <int>> edges;
public:
    Graph(vector <vector <int>>& edges);
    int bfs();  
};

Graph::Graph(vector <vector <int>>& edges) {
    n = edges.size();
    this->edges.resize(n+1);
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < edges[i].size(); j ++) {
            this->edges[i].push_back(edges[i][j]);
        }
    }
}

int Graph::bfs() {
    int finalMask = (1 << n) - 1;   // 111..11 => toate vizitate
    vector <vector <bool>> visited; // visited[node][mask]
    visited.resize(n+1);
    for (int i = 0; i < n; i ++) {
        visited[i].resize(finalMask + 1);
        fill(visited[i].begin(), visited[i].end(), false);
    }

    queue <vector <int>> q; // (node, mask, length)
    // punem toate nodurile in coada
    for (int i = 0; i < n; i ++) {
        int mask = 1 << i;
        visited[i][mask] = true;
        q.push({i, mask, 0});
    }  

    while (!q.empty()) {
        int node = q.front()[0];
        int mask = q.front()[1];
        int length = q.front()[2];
        q.pop();

        for (int next: edges[node]) {
            int mask2 = mask | (1 << next); // il adaug pe next in masca
            if (mask2 == finalMask) {
                return length + 1;
            }
            if (!visited[next][mask2]) {
                visited[next][mask2] = true;
                q.push({next, mask2, length + 1});
            }
        }
    }
    return 0;
}

class Solution {
public:
    int shortestPathLength(vector <vector <int>>& graph) {
        Graph g(graph);
        return g.bfs();
    }
};
