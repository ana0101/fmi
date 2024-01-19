#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream in("apm2.in");
ofstream out("apm2.out");

bool compare(vector <int> e1, vector <int> e2) {
    return e1[2] < e2[2];
}

class Graph {
private:
    int n, m, q;
    vector <vector <int>> edges;    // [[node1, node2, cost]]
    vector <int> parent;
    vector <int> size;

public:
    Graph() {}
    void readGraph();
    void myUnion(int node1, int node2);
    int myFind(int node);
    int kruskal(int a, int b);
    void reset();   // resets parent and size
    void solve();
};

void Graph::readGraph() {
    in >> n >> m >> q;
    edges.reserve(m);
    parent.resize(n+1);
    size.resize(n+1);

    int x, y, t;
    for (int i = 0; i < m; i ++) {
        in >> x >> y >> t;
        edges.emplace_back(vector <int>{x, y, t});
    }

    sort(edges.begin(), edges.end(), compare);
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

int Graph::kruskal(int a, int b) {
    for (int i = 0; i < edges.size(); i ++) {
        int node1 = edges[i][0];
        int node2 = edges[i][1];
        int cost = edges[i][2];

        // daca sunt in comp conexe diferite luam muchia
        if (myFind(node1) != myFind(node2)) {
            myUnion(node1, node2);
        }

        // daca dupa ce am luat muchia cele doua noduri a si b sunt in aceeasi comp conexa =>
        // => trebuie costul (a, b) strict mai mic decat costul muchiei pt a fi luat
        if (myFind(a) == myFind(b)) {
            return cost - 1;
        }
    }
}

void Graph::reset() {
    for (int i = 1; i <= n; i ++) {
        parent[i] = i;
        size[i] = 1;
    }
}

void Graph::solve() {
    int a, b;
    for (int i = 0; i < q; i ++) {
        in >> a >> b;
        reset();
        int c = kruskal(a, b);
        out << c << "\n";
    }
}

int main() {
    Graph g;
    g.readGraph();
    g.solve();
    return 0;
}