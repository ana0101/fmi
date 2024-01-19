#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

ifstream in("oracol.in");
ofstream out("oracol.out");

class Graph {
private:
    int n;
    vector <vector <int>> adj;

public:
    Graph() {}
    void readGraph();
    int Prim();
};

void Graph::readGraph() {
    in >> n;
    adj.resize(n+1);
    for (int i = 0; i <= n; i ++)
        adj[i].resize(n+1);

    for (int i = 0; i < n; i ++) {
        int c;
        for (int j = i+1; j <= n; j ++) {
            in >> c;
            adj[i][j] = c;
            adj[j][i] = c;
        }
    }
}

int Graph::Prim() {
    vector <bool> visited(n+1, false);
    vector <int> dist(n+1, 0);  // distanta minima de la un nod neselectat pana la un nod selectat
    int s = 0;

    // alege nodul de start si calculeaza distantele fata de nodul de start
    int node = 0;
    visited[node] = true;
    dist[node] = 0;
    for (int i = 1; i <= n; i ++) {
        dist[i] = adj[i][0];
    }

    for (int i = 0; i < n; i ++) {
        // cauta nodul care inca nu a fost vizitat cu distanta minima pana la un nod care a fost selectat
        int distMin = INT_MAX;
        int node2;
        for (int j = 0; j <= n; j ++) {
            if (!visited[j] && dist[j] < distMin) {
                distMin = dist[j];
                node2 = j;
            }
        }

        visited[node2] = true;
        s += distMin;

        // updateaza distantele
        for (int j = 0; j <= n; j ++) {
            if (!visited[j]) {
                int d = adj[node2][j];
                if (d < dist[j]) {
                    dist[j] = d;
                }
            }
        }
    }
    return s;
}

int main() {
    Graph g;
    g.readGraph();
    out << g.Prim();
    return 0;
}