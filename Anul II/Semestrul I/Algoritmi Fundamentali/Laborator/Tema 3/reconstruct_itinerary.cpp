#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

class Graph {
private:
    map <string, vector <string>> edges;
public:
    Graph(vector <vector <string>>& edges);
    void dfs(string node, vector <string>& eulerianPath);
    vector <string> solve();
};

Graph::Graph(vector <vector <string>>& edges) {
    for (auto e: edges) {
        this->edges[e[0]].push_back(e[1]);
    }
    // sortez descrecator aeroporturile pt a le lua in ordine crescatoare in dfs
    for (auto e: this->edges) {
        sort(e.second.begin(), e.second.end(), greater <string>());
    }
}

void Graph::dfs(string node, vector <string>& eulerianPath) {
    while (!edges[node].empty()) {
        string next = edges[node].back();
        edges[node].pop_back();
        dfs(next, eulerianPath);
    }
    eulerianPath.push_back(node);
}

vector <string> Graph::solve() {
    vector <string> eulerianPath;
    dfs("JFK", eulerianPath);
    reverse(eulerianPath.begin(), eulerianPath.end());
    return eulerianPath;
}

class Solution {
public:
    vector <string> findItinerary(vector <vector <string>>& tickets) {
        Graph g(tickets);
        return g.solve();
    }
};
