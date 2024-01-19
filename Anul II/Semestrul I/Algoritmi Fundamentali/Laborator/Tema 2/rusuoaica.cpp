#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream in("rusuoaica.in");
ofstream out("rusuoaica.out");

bool compare(vector <int> e1, vector <int> e2) {
    return e1[2] < e2[2];
}

class Graph {
private:    
    int n, m, a, minCost;
    vector <vector <int>> edges;    // [[node1, node2, cost]]
    vector <int> parent;
    vector <int> size;

public:
    Graph();
    void readGraph();
    void myUnion(int node1, int node2);
    int myFind(int node);
    int kruskal();
};

Graph::Graph() {
    minCost = 0;
}

void Graph::readGraph() {
    in >> n >> m >> a;
    for (int i = 0; i <= n; i ++) {
        parent.push_back(i);
        size.push_back(1);
    }

    for (int i = 0; i < m; i ++) {
        int t1, t2, t3;
        in >> t1 >> t2 >> t3;
        // daca costul tunelului e mai mare ca a => il vand si eventual il construiesc cu a
        if (t3 <= a) {
            vector <int> v{t1, t2, t3};
            edges.push_back(v);
        }
        else {
            minCost -= t3;
        }
    }
}

void Graph::myUnion(int node1, int node2) {
    node1 = myFind(node1);
    node2 = myFind(node2);
    if (size[node1] > size[node2])
        swap(node1, node2);
    parent[node1] = node2;
    size[node2] += size[node1]; // union by rank
}

int Graph::myFind(int node) {
    if (node == parent[node])
        return node;
    return parent[node] = myFind(parent[node]);   // path compression
}

int Graph::kruskal() {
    sort(edges.begin(), edges.end(), compare);
    // parcurgem edges in care sunt muchiile cu cost mai mic decat a si le luam pe cele mai ieftine necesare
    // daca nu luam n-1 muchii => inca nu e conex si restul o sa coste a

    int nrEdges = n-1;
    for (int i = 0; i < edges.size(); i ++) {
        int node1 = edges[i][0];
        int node2 = edges[i][1];
        int cost = edges[i][2];

        // daca sunt in comp conexe diferite luam muchia
        // daca sunt in aceeasi comp conexa o vindem
        if (myFind(node1) != myFind(node2)) {
            myUnion(node1, node2);
            minCost += cost;
            nrEdges --;
        }
        else {
            minCost -= cost;
        }
    }

    minCost += nrEdges * a;
    return minCost;
}

int main() {
    Graph g;
    g.readGraph();
    out << g.kruskal();
    return 0;
}