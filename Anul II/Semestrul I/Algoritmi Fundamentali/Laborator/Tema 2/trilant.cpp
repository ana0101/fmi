#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

ifstream in("trilant.in");
ofstream out("trilant.out");

class Compare {
public:
    bool operator()(pair <int, long long> p1, pair <int, long long> p2) {
        return p1.second > p2.second;
    }
};

class Graph {
private:
    int n, m, a, b, c;
    vector <vector <pair <int, long long>>> edges; // (edges[node1] = [(node2, cost)])
    vector <long long> aCost, bCost, cCost;
    vector <int> aParent, bParent, cParent;

public:
    Graph() {}
    void readGraph();
    void dijkstra(int node, vector <long long>& cost, vector <int>& parent); 
    void solve();  
    void printRoad(int x, int node, vector <int>& parent);   // printeaza drumul x..node
};

void Graph::readGraph() {
    in >> n >> m;
    in >> a >> b >> c;

    edges.resize(n+1);
    int node1, node2;
    long long cost;
    for (int i = 0; i < m; i ++) {
        in >> node1 >> node2 >> cost;
        edges[node1].push_back(make_pair(node2, cost));
        edges[node2].push_back(make_pair(node1, cost));
    }

    aParent.reserve(n+1);
    bParent.reserve(n+1);
    cParent.reserve(n+1);

    for (int i = 0; i <= n; i ++) {
        aCost.push_back(LONG_MAX);
        bCost.push_back(LONG_MAX);
        cCost.push_back(LONG_MAX);
    }
}

void Graph::dijkstra(int startNode, vector <long long>& cost, vector <int>& parent) {
    vector <bool> vis(n+1, false);
    priority_queue <pair <int, long long>, vector <pair <int, long long>>, Compare> heap; // (node, cost)

    for (int i = 1; i <= n; i ++) {
        parent[i] = 0;
    }
    
    cost[startNode] = 0;
    parent[startNode] = startNode;
    heap.push(make_pair(startNode, 0));
    
    while (!heap.empty()) {
        int node = heap.top().first;
        long long c = heap.top().second;
        heap.pop();

        if (!vis[node]) {
            vis[node] = true;
            for (int i = 0; i < edges[node].size(); i ++) {
                int node2 = edges[node][i].first;
                long long c2 = edges[node][i].second;

                if (cost[node2] > cost[node] + c2) {
                    cost[node2] = cost[node] + c2;
                    parent[node2] = node;
                    heap.push(make_pair(node2, cost[node2]));
                }
            }
        }
    }
}

void Graph::solve() {
    dijkstra(a, aCost, aParent);
    dijkstra(b, bCost, bParent);
    dijkstra(c, cCost, cParent);

    long long minCost = LONG_MAX;
    int x;

    for (int i = 1; i <= n; i ++) {
        if (minCost > aCost[i] + bCost[i] + cCost[i]) {
            minCost = aCost[i] + bCost[i] + cCost[i];
            x = i;
        }
    }
    
    out << minCost << "\n";
    printRoad(x, a, aParent);
    printRoad(x, b, bParent);
    printRoad(x, c, cParent);
}

void Graph::printRoad(int x, int node, vector <int>& parent) {
    vector <int> road;
    while (x != parent[x]) {
        road.push_back(x);
        x = parent[x];
    }
    road.push_back(node);
    out << road.size() << " ";
    
    for (int i = 0; i < road.size(); i ++) {
        out << road[i] << " ";
    }
    out << "\n";
}

int main() {
    Graph g;
    g.readGraph();
    g.solve();
    return 0;
}