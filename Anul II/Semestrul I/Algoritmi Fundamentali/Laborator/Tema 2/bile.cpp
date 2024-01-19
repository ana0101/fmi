#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
using namespace std;

ifstream in("bile.in");
ofstream out("bile.out");

class Graph {
private:
    int n, n2;
    vector <int> parent;    // numerotez nodurile de la 1 la n^2 = n * (l-1) + c
    vector <int> size;
    vector <int> maxSize;   // dimensiunea maxima a unei comp conexe la momentul i

public:
    Graph() {}
    void readGraph();
    int myUnion(int node1, int node2);  // returneaza size-ul final
    int myFind(int node);
    void addNode(int l, int c, int k);
    void solve();
};

void Graph::readGraph() {
    in >> n;
    n2 = n * n;
    parent.reserve(n2+1);
    size.reserve(n2+1);
    maxSize.reserve(n2+1);
    for (int i = 0; i <= n2; i ++) {
        parent.push_back(-1);
        size.push_back(-1);
        maxSize.push_back(-1);
    }
}

int Graph::myUnion(int node1, int node2) {
    node1 = myFind(node1);
    node2 = myFind(node2);
    if (size[node1] > size[node2])
        swap(node1, node2);
    parent[node1] = node2;
    size[node2] += size[node1]; // union by rank
    return size[node2];
}

int Graph::myFind(int node) {
    if (node == parent[node])
        return node;
    return parent[node] = myFind(parent[node]);   // path compression
}

void Graph::addNode(int l, int c, int k) {
    int node = n * (l-1) + c;
    parent[node] = node;
    size[node] = 1;
    maxSize[k] = max(1, maxSize[k]);

    // trecem prin vecini si daca exista ii unim de node (daca nu au fost deja uniti de alt vecin)
    for (tuple <int, int> coord : {make_tuple(l-1, c), make_tuple(l+1, c), make_tuple(l, c-1), make_tuple(l, c+1)}) {
        int l2 = get<0>(coord);
        int c2 = get<1>(coord);

        // verif daca se afla pe tabla
        if (l2 >= 1 && l2 <= n && c2 >= 1 && c2 <= n) {
            // verif daca exista bila in coord
            int next = n * (l2-1) + c2;
            if (parent[next] != -1) {
                if (myFind(node) != myFind(next)) {
                    int newSize = myUnion(node, next);
                    // verif daca am gasit un size mai mare
                    maxSize[k] = max(newSize, maxSize[k]);
                }
            }
        }
    }
}

void Graph::solve() {
    vector <pair <int, int>> nodes; // nodurile in ordinea in care se scot de pe tabla
    nodes.reserve(n2+1);
    int l, c;
    for (int i = 0; i < n2; i ++) {
        in >> l >> c;
        nodes.push_back(make_pair(l, c));
    }

    // parcurgem nodurile de la sfarsit la inceput si le adaugam
    maxSize[n2] = 0;
    for (int i = n2 - 1; i >= 0; i --) {
        // valoarea lui maxSize[i] e maxSize[i+1] (adica dim maxima inainte sa se mai adauge un nod)
        maxSize[i] = maxSize[i+1];

        l = nodes[i].first;
        c = nodes[i].second;
        addNode(l, c, i);
    }

    // afisam maxSize
    for (int i = 1; i <= n2; i ++) {
        out << maxSize[i] << "\n";
    }
}

int main() {
    Graph g;
    g.readGraph();
    g.solve();
    return 0;
}