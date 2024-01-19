#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <cmath>
#include <iomanip>
using namespace std;

ifstream in("cablaj.in");
ofstream out("cablaj.out");

double calcDist(pair <int, int> node1, pair <int, int> node2) {
    return sqrt((node1.first - node2.first) * (node1.first - node2.first) + (node1.second - node2.second) * (node1.second - node2.second));
}

class Graph {
private:
    int n;
    vector <pair <int, int>> nodes; // coordonatele

public:
    Graph() {}
    void readGraph();
    double Prim();
};

void Graph::readGraph() {
    in >> n;
    for (int i = 0; i < n; i ++) {
        int x, y;
        in >> x >> y;
        nodes.push_back(make_pair(x, y));
    }
}

double Graph::Prim() {
    vector <bool> visited(n, false);
    vector <double> dist(n, 0);   // distanta minima de la un nod neselectat pana la un nod selectat
    double s = 0;

    // alege nodul de start si calculeaza distantele fata de nodul de start
    int node = 0;
    visited[node] = true;
    dist[node] = 0;
    for (int i = 1; i < n; i ++) {
        dist[i] = calcDist(nodes[0], nodes[i]);
    }

    for (int i = 0; i < n-1; i ++) {
        // cauta nodul care inca nu a fost vizitat cu distanta minima pana la un nod care a fost selectat
        double distMin = INT_MAX;
        int node2;
        for (int j = 0; j < n; j ++) {
            if (!visited[j] && dist[j] < distMin) {
                distMin = dist[j];
                node2 = j;
            }
        }

        visited[node2] = true;
        s += distMin;

        // updateaza distantele
        for (int j = 0; j < n; j ++) {
            if (!visited[j]) {
                double d = calcDist(nodes[node2], nodes[j]);
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
    out << setprecision(4) << fixed << g.Prim();
    return 0;
}