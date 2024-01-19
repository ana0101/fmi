#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

ifstream in("camionas.in");
ofstream out("camionas.out");

class Graph {
private:
    int n, m, g;
    vector <vector <pair <int, int>>> edges;    // edges[node1] = [(node2, cost)], cost 0 sau 1

public:
    Graph() {}
    void readGraph();
    int bfs01(int nodeStart);
};

void Graph::readGraph() {
    in >> n >> m >> g;
    edges.resize(n+1);

    for (int i = 0; i < m; i ++) {
        int x, y, g1, c;
        in >> x >> y >> g1;

        if (g1 >= g) {
            c = 0;
        }
        else {
            c = 1;
        }

        edges[x].push_back(make_pair(y, c));
        edges[y].push_back(make_pair(x, c));
    }
}

int Graph::bfs01(int nodeStart) {
    vector <int> minCost(n+1, INT_MAX);
    deque <int> q;
    q.push_front(nodeStart);
    minCost[nodeStart] = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop_front();

        for (int i = 0; i < edges[node].size(); i ++) {
            int node2 = edges[node][i].first;
            int cost = edges[node][i].second;

            if (minCost[node2] > minCost[node] + cost) {
                minCost[node2] = minCost[node] + cost;
                if (cost == 0) {
                    q.push_front(node2);
                }
                else {
                    q.push_back(node2);
                }
            }
        }
    }

    return minCost[n];
}

int main() {
    Graph g;
    g.readGraph();
    out << g.bfs01(1);
    return 0;
}