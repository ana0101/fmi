#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
using namespace std;

class Compare {
public:
    bool operator()(vector <int> e1, vector <int> e2) {
        if (e1[1] > e2[1])
            return true;
        return false;
    }
};

struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator() (const std::pair <T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;  
    }
};

class Graph {
private:
    int n, src, dst, k;
    vector <vector <pair <int, int>>> edges; 

public:
    Graph(int n, vector <vector <int>>& edges, int src, int dst, int k);
    int dijkstra();
};

Graph::Graph(int n, vector <vector <int>>& edges, int src, int dst, int k) {
    this->n = n;
    this->edges.resize(n);
    for (int i = 0; i < edges.size(); i ++) {
        int node1 = edges[i][0];
        int node2 = edges[i][1];
        int cost = edges[i][2];
        this->edges[node1].push_back(make_pair(node2, cost));
    }
    this->src = src;
    this->dst = dst;
    this->k = k;
}

int Graph::dijkstra() {
    unordered_map <pair <int, int>, int, PairHash> dist;  // dist[i][j] = distanta minima pana la nodul i cu j stopuri ramase

    priority_queue <vector <int>, vector <vector <int>>, Compare> heap;   // {nod, dist minima pana la nod, nr stopuri ramase}
    vector <int> v{src, 0, k};
    heap.push(v);

    while (!heap.empty()) {
        vector <int> e(3, 0);
        // parcurge nodurile - il ia pe cel cu distanta minima
        e = heap.top();
        heap.pop();

        int node1 = e[0];
        int d = e[1];
        int stops = e[2];

        // daca am ajuns la dst
        if (node1 == dst)
            return d;

        // daca mai avem stopuri
        if (stops >= 0) {
            for (int i = 0; i < edges[node1].size(); i ++) {
                int node2 = edges[node1][i].first;
                int cost = edges[node1][i].second;

                // verifica daca a gasit distanta mai buna pana la node2 cu stops-1 stopuri ramase
                // 2 cazuri - daca exista si daca nu exista deja
                pair <int, int> p = make_pair(node2, stops-1);
                if (dist.find(p) == dist.end() || dist[p] > d + cost) {
                    dist[p] = d + cost;
                    vector <int> v{node2, dist[p], stops-1};
                    heap.push(v);
                }
            }
        }
    }

    return -1;
}

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>> flights, int src, int dst, int k) {
        Graph g(n, flights, src, dst, k);
        return g.dijkstra();
    }
};