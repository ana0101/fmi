#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

ifstream in("dragoni.in");
ofstream out("dragoni.out");

class Graph {
private:
    int n, m;
    vector <vector <pair <int, int>>> edges; // (edges[node1] = [(node2, cost)])
    vector <int> dmax;  // dist max pe care o poate zbura un dragon de pe insula i

public:
    Graph() {}
    void readGraph();
    int bfs();    // rezolva prima cerinta
    int bellmanFord(); // rezolva a doua cerinta
};

void Graph::readGraph() {
    in >> n >> m;

    int d;
    dmax.push_back(0);
    for (int i = 1; i <= n; i ++) {
        in >> d;
        dmax.push_back(d);
    }

    int node1, node2, cost;
    edges.resize(n+1);
    for (int i = 0; i < m; i ++) {
        in >> node1 >> node2 >> cost;
        edges[node1].push_back(make_pair(node2, cost));
        edges[node2].push_back(make_pair(node1, cost));
    }
}

int Graph::bfs() {
    vector <bool> vis(n+1, false);
    queue <int> q;
    q.push(1);
    vis[1] = true;
    int distMax = dmax[1];

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int i = 0; i < edges[node].size(); i ++) {
            int node2 = edges[node][i].first;
            int cost = edges[node][i].second;
            if (!vis[node2] && dmax[1] >= cost) {
                q.push(node2);
                vis[node2] = true;
                if (dmax[node2] > distMax) {
                    distMax = dmax[node2];
                }
            }
        }
    }
    return distMax;
}

int Graph::bellmanFord() {
    vector <vector <int>> minCost;  // minCost[node][dragon]
    vector <vector <bool>> inq;
    queue <pair <int, int>> q; // (node, dragon)

    for (int i = 0; i <= n; i ++) {
        minCost.push_back({});
        inq.push_back({});
        for (int j = 0; j <= n; j ++) {
            minCost[i].push_back(INT_MAX);
            inq[i].push_back(false);
        }
    }

    minCost[1][1] = 0;
    q.push(make_pair(1, 1));
    inq[1][1] = true;

    while (!q.empty()) {
        int node = q.front().first;
        int dragon = q.front().second;
        q.pop();
        inq[node][dragon] = false;

        for (int i = 0; i < edges[node].size(); i ++) {
            int node2 = edges[node][i].first;
            int cost2 = edges[node][i].second;

            // daca pot sa ajung la node2 cu dragonul
            if (dmax[dragon] >= cost2) {
                // iau dragonul cel mai bun din cei doi
                int dragon2;
                if (dmax[node2] > dmax[dragon]) {
                    dragon2 = node2;
                }
                else {
                    dragon2 = dragon;
                }

                if (minCost[node2][dragon2] > minCost[node][dragon] + cost2) {
                    minCost[node2][dragon2] = minCost[node][dragon] + cost2;
                    if (!inq[node2][dragon2]) {
                        q.push(make_pair(node2, dragon2));
                        inq[node2][dragon2] = true;
                    }
                }
            }
        }
    }

    int c = INT_MAX;
    for (int i = 1; i <= n; i ++) {
        if (c > minCost[n][i])
            c = minCost[n][i];
    }
    return c;
}

int main() {
    int p;
    in >> p;
    Graph g;
    g.readGraph();

    if (p == 1) {
        out << g.bfs();
    }
    else {
        out << g.bellmanFord();
    }
    
    return 0;
}