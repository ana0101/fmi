#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <climits>
using namespace std;

ifstream in("senat.in");
ofstream out("senat.out");

class Graph {
private:
    int n, m, s, t;
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
    in >> n >> m;
    s = 0;
    t = n + m + 1;
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

    // leg toti senatorii de start
    for (int i = 1; i <= n; i ++) {
        edges[s].push_back(i);
        edges[i].push_back(s);
        capacity[s][i] = 1;
    }

    int com = n;
    string line;
    getline(in, line);  // pt ca ramane un \n
    for (int i = 0; i < m; i ++) {
        getline(in, line);
        com ++;
        int sen = 0;
        for (int i = 0; i < line.size(); i ++) {
            if (line[i] != ' ') {
                sen = sen * 10 + (line[i] - '0');
            }
            else {
                // leg senatorul de comisie
                edges[sen].push_back(com);
                edges[com].push_back(sen);
                capacity[sen][com] = 1;
                sen = 0;
            }
        }
        if (sen != 0) {
            edges[sen].push_back(com);
            edges[com].push_back(sen);
            capacity[sen][com] = 1;
        }

        // leg comisia de finish
        edges[com].push_back(t);
        edges[t].push_back(com);
        capacity[com][t] = 1;
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
    if (totalFlow != m) {
        out << 0;
    }
    else {
        int com = n;
        for (int i = 0; i < m; i ++) {
            com ++;
            for (int sen = 1; sen <= n; sen ++) {
                if (flow[sen][com]) {
                    out << sen << "\n";
                }
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
