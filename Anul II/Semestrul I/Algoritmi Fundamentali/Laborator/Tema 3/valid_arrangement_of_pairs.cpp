#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Graph {
private:
    unordered_map <int, vector <int>> edges;
    unordered_map <int, pair <int, int>> degree;    // degree[i].first = in-degree of node i
                                                    // degree[i].second = out-degree of node i
public:
    Graph(vector <vector <int>>& edges);
    void dfs(int node, vector <vector <int>>& eulerianPath);
    vector <vector <int>> solve();
};

Graph::Graph(vector <vector <int>>& edges) {
    for (auto e: edges) {
        this->edges[e[0]].push_back(e[1]);
        this->degree[e[0]].second ++;
        this->degree[e[1]].first ++;
    }
}

void Graph::dfs(int node, vector <vector <int>>& eulerianPath) {
    while (!edges[node].empty()) {
        int next = edges[node].back();
        edges[node].pop_back();
        dfs(next, eulerianPath);
        eulerianPath.push_back(vector <int> {node, next});
    }
}

vector <vector <int>> Graph::solve() {
    // start node => in-degree == out-degree - 1 (daca nu exista => oricare (e ciclu))
    int startNode = degree.begin()->first;
    for (auto i = degree.begin(); i != degree.end(); i ++) {
        if (i->second.first == i->second.second - 1) {
            startNode = i->first;
            break;
        }
    }

    vector <vector <int>> eulerianPath;
    dfs(startNode, eulerianPath);
    reverse(eulerianPath.begin(), eulerianPath.end());
    return eulerianPath;
}

class Solution {
public:
    vector <vector <int>> validArrangement(vector <vector <int>>& pairs) {
        Graph g(pairs);
        return g.solve();
    }
};
