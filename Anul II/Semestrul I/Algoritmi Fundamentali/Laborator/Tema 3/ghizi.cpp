#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

ifstream in("ghizi.in");
ofstream out("ghizi.out");

class Graph {
private:
    int n, k, s, t;
    vector <vector <int>> edges;
    vector <vector <int>> capacity;
    vector <vector <int>> flow;
    vector <int> parent;
    vector <pair <int, int>> vol;   // vol[i] = (x, y) - intervalul fiecarui voluntar

public:
    Graph() {}
    void readGraph();
    int bfs();  // returneaza flow-ul gasit
    int maxFlow();
    void solve();
};

void Graph::readGraph() {
    in >> n >> k;
    s = 0;
    t = 101;
    edges.resize(t + 2);
    capacity.resize(t + 2);
    flow.resize(t + 2);
    vol.resize(n + 2);
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
        vol[i] = make_pair(x, y);
        // interval de la x la y => leg nodul x de nodul y
        edges[x].push_back(y);
        edges[y].push_back(x);
        capacity[x][y] ++;
    }

    // leg nodul 100 de t cu capacitate k (flux k => k drumuri de la 1 la 100)
    edges[100].push_back(t);
    edges[t].push_back(100);
    capacity[100][t] = k;
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
    vector <int> guides;
    for (int i = 1; i <= n; i ++) {
        int x = vol[i].first;
        int y = vol[i].second;
        // daca muchia x y are flux => am folosit intervalul si luam voluntarul
        if (flow[x][y]) {
            guides.push_back(i);
            flow[x][y] --;
        }
    }

    out << guides.size() << "\n";
    for (int g: guides) {
        out << g << " ";
    }
}

int main() {
    Graph g;
    g.readGraph();
    g.solve();
    return 0;
}
