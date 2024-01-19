#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

ifstream in("cc.in");
ofstream out("cc.out");

class Graph {
private:
    int n, s, t;
    long long totalCost;
    vector <vector <int>> edges;
    vector <vector <int>> capacity;
    vector <vector <int>> flow;
    vector <vector <int>> cost; // distanta pe care o parcurge concurentul i pana la calculatorul j
    vector <int> minCost;   // costul minim pentru a ajunge intr-un nod
    vector <int> parent;

public:
    Graph() {}
    void readGraph();
    int bfs();  // returneaza flow-ul gasit
    int maxFlow();
    void solve();
};

void Graph::readGraph() {
    in >> n;
    s = 0;
    t = 2 * n + 1;
    totalCost = 0;
    edges.resize(t + 2);
    capacity.resize(t + 2);
    flow.resize(t + 2);
    cost.resize(t + 2);
    minCost.resize(t + 2);
    for (int i = 0; i <= t; i ++) {
        capacity[i].resize(t + 2);
        fill(capacity[i].begin(), capacity[i].end(), 0);
        flow[i].resize(t + 2);
        fill(flow[i].begin(), flow[i].end(), 0);
        cost[i].resize(t + 2);
        fill(cost[i].begin(), cost[i].end(), 0);
    }
    parent.resize(t + 2);

    int d;
    for (int i = 1; i <= n; i ++) {
        // leg concurentul i de start
        edges[s].push_back(i);
        edges[i].push_back(s);
        capacity[s][i] = 1;

        for (int j = n + 1; j < t; j ++) {
            in >> d;
            // leg concurentul i de calculatorul j
            edges[i].push_back(j);
            edges[j].push_back(i);
            capacity[i][j] = 1;
            cost[i][j] = d;
            cost[j][i] = -d;
        }
    }

    for (int j = n + 1; j < t; j ++) {
        // leg calculatorul j de finish
        edges[j].push_back(t);
        edges[t].push_back(j);
        capacity[j][t] = 1;
    }
}

int Graph::bfs() {
    queue <int> q;
    fill(parent.begin(), parent.end(), -1);
    parent[s] = s;
    fill(minCost.begin(), minCost.end(), INT_MAX);
    minCost[0] = 0;
    q.push(s);
    int newFlow = INT_MAX;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int next: edges[node]) {
            // daca am gasit o muchie nesaturata catre un nod caruia pot sa ii imbunatatesc costul il adaug
            if (flow[node][next] < capacity[node][next] && minCost[next] > minCost[node] + cost[node][next]) {
                parent[next] = node;
                newFlow = min(newFlow, capacity[node][next] - flow[node][next]);
                minCost[next] = minCost[node] + cost[node][next];
                q.push(next);
            }
        }
    }

    // daca am ajuns in t => drum de augmentare (toate au flow-ul 1)
    if (parent[t] != -1)
        return 1; 
    return 0;
}

int Graph::maxFlow() {
    int totalFlow = 0;
    while (true) {
        int newFlow = bfs();
        if (!newFlow)
            break;
        totalFlow += newFlow;

        // modificam fluxul
        int node = t;
        while (node != s) {
            int nodeParent = parent[node];
            flow[nodeParent][node] += newFlow;
            flow[node][nodeParent] -= newFlow;
            node = nodeParent;
        }

        // adaugam costul drumului la costul total
        totalCost += minCost[t];
    }
    return totalFlow;
}

void Graph::solve() {
    int totalFlow = maxFlow();
    out << totalCost;
}

int main() {
    Graph g;
    g.readGraph();
    g.solve();
    return 0;
}
