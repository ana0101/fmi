#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

ifstream in("harta.in");
ofstream out("harta.out");

class Graph {
private:
    int n, s, t;
    vector <vector <int>> edges;
    vector <vector <int>> capacity;
    vector <vector <int>> flow;
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
    edges.resize(t + 2);
    capacity.resize(t + 2);
    flow.resize(t + 2);
    for (int i = 0; i <= t; i ++) {
        capacity[i].resize(t + 2);
        fill(capacity[i].begin(), capacity[i].end(), 0);
        flow[i].resize(t + 2);
        fill(flow[i].begin(), flow[i].end(), 0);
    }
    parent.resize(t + 2);

    int x, y;
    for (int i = 1; i <= n; i ++) {
        in >> x >> y;
        // leg nodul de start
        edges[s].push_back(i);
        edges[i].push_back(s);
        capacity[s][i] = x; // din i pleaca x drumuri

        // leg nodul de celelalte noduri (in stanga 1..n in dreapta n+1..2*n)
        for (int j = 1; j <= n; j ++) {
            if (i != j) {
                edges[i].push_back(j + n);
                edges[j + n].push_back(i);
                capacity[i][j + n] = 1;
            }
        }

        // leg nodul de finish
        edges[i + n].push_back(t);
        edges[t].push_back(i + n);
        capacity[i + n][t] = y; // in i ajung y drumuri
    }
}

int Graph::bfs() {
    queue <int> q;
    fill(parent.begin(), parent.end(), -1);
    parent[s] = s;
    q.push(s);
    int newFlow = INT_MAX;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int next: edges[node]) {
            // daca am gasit o muchie nesaturata catre un nod in care nu am mai fost il adaug
            if (flow[node][next] < capacity[node][next] && parent[next] == -1) {
                parent[next] = node;
                newFlow = min(newFlow, capacity[node][next] - flow[node][next]);
                // daca am ajuns in t => am gasit drum de augmentare
                if (next == t)
                    return newFlow;
                q.push(next);
            }
        }
    }

    // daca am ajuns aici => nu mai exista drum de augmentare
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
    }
    return totalFlow;
}

void Graph::solve() {
    int totalFlow = maxFlow();
    out << totalFlow << "\n";
    // daca exista flux intre 2 noduri => exsita muchie
    for (int i = 1; i <= n; i ++) {
        for (int j = n + 1; j <= 2 * n; j ++) {
            if (flow[i][j]) {
                out << i << " " << j - n << "\n";
            }
        }
    }
}

int main() {
    Graph g;
    g.readGraph();
    g.solve();
    return 0;
}
