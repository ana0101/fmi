#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <climits>
using namespace std;

ifstream in("paznici.in");
ofstream out("paznici.out");

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
    void minCut(int node, vector <bool>& safe);
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

    // leg liniile de start
    for (int i = 1; i <= n; i ++) {
        edges[s].push_back(i);
        edges[i].push_back(s);
        capacity[s][i] = 1;
    }

    // leg coloanele de finish
    for (int j = n + 1; j <= n + m; j ++) {
        edges[j].push_back(t);
        edges[t].push_back(j);
        capacity[j][t] = 1;
    }

    // leg o linie de o coloana daca e 1 in matrice (vreau sa acopar punctele de interes)
    string line; 
    getline(in, line);  // pt ca ramane un \n
    for (int i = 1; i <= n; i ++) {
        getline(in, line);
        for (int j = n + 1; j <= n + m; j ++) {
            if (line[j - n - 1] == '1') {
                edges[i].push_back(j);
                edges[j].push_back(i);
                capacity[i][j] = 1;
            }
        }
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

void Graph::minCut(int node, vector <bool>& safe) {
    // luam muchiile nesaturate
    // nodurile accesibile din start = A
    // restul = B
    // orice muchie din A in B = de taietura
    queue <int> q;
    safe[node] = true;
    q.push(node);

    while (!q.empty()) {
        node = q.front();
        q.pop();
        for (int next: edges[node]) {
            if (flow[node][next] < capacity[node][next] && !safe[next]) {
                safe[next] = true;
                q.push(next);
            }
        }
    }
}

void Graph::solve() {
    int totalFlow = maxFlow();
    // flux max (cate puncte de interes pot maxim sa iau fara nicio linie sau coloana in comun) = nr min paznici
    // flux max => nu mai exista niciun drum de la s la t => nu mai exista niciun punct de interes neacoperit

    // din nodurile care sunt in muchiile cu flow aleg ori linie ori coloana
    // astfel incat sa fie toate de interes safe si sa fie cat mai multe linii
    vector <bool> safe(n + m + 2, false);
    // cu minCut vad de ce coloane am neaparat nevoie ca sa acopar toate alea de interes
    // pentru liniile din care nu am trimis flux => trebuie sa iau coloana ca sa acopar acel punct de interes
    minCut(s, safe);

    // liniile care nu sunt safe sunt cele pe care trebuie sa le iau
    for (int i = 1; i <= n; i ++) {
        if (!safe[i]) {
            out << char(i + 'A' - 1);
        }
    }

    // coloanele
    for (int j = n + 1; j <= n + m; j ++) {
        if (safe[j]) {
            out << char(j + 'a' - n - 1);
        }
    }
}

int main() {
    Graph g;
    g.readGraph();
    g.solve();
    return 0;
}
