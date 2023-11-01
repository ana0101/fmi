#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
using namespace std;

class Graph {
private:
    int n, k;
    vector <vector <int>> edges;
    vector <bool> marked;

public:
    void readGraph();
    void printGraph();
    vector <int> bfs(int node);  // returns the marked node that is the farthest away from node and the distance
    int minMaxDist();
};

void Graph::readGraph() {
    cin >> n >> k;

    for (int i = 0; i <= n; i ++) {
        edges.push_back({});
        marked.push_back(0);
    }

    int x, y;
    for (int i = 0; i < k; i ++) {
        cin >> x;
        marked[x] = 1;
    }

    for (int i = 0; i < n-1; i ++) {
        cin >> x >> y;
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
}

void Graph::printGraph() {
    cout << "n = " << n << "\n";
    cout << "k = " << k << "\n";

    cout << "edges\n";
    for (int i = 0; i <= n; i ++) {
        cout << i << ": ";
        for (int j = 0; j < edges[i].size(); j ++)
            cout << edges[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";

    cout << "marked\n";
    for (int i = 0; i <= n; i ++) 
        cout << i << ": " << marked[i] << "\n";
}

vector <int> Graph::bfs(int node) {
    vector <bool> visited;
    for (int i = 0; i <= n; i ++)
        visited.push_back(0);

    vector <int> distance;  // distance from a start node to another node
    for (int i = 0; i <= n; i ++)
        distance.push_back(INT_MAX);

    queue <int> q;
    q.push(node);
    visited[node] = 1;
    distance[node] = 0;
    int markedNode, maxd = 0;

    while (!q.empty()) {
        node = q.front();
        q.pop();
        for (int i = 0; i < edges[node].size(); i ++) {
            int next = edges[node][i];
            if (!visited[next]) {
                visited[next] = 1;
                distance[next] = distance[node] + 1;
                q.push(next);

                if (marked[next] && distance[next] > maxd) {
                    markedNode = next;
                    maxd = distance[next];
                }
            }
        }
    }
    return {markedNode, maxd};
}

int Graph::minMaxDist() {
    // we need the minimum of the maximum distances
    // we find the two marked nodes that are in the extremities
    // because these will give the maximum distances
    // the minimum of those will be from a node that is in the middle =>
    // the distance between the two marked nodes / 2

    // special case: only one marked node => min max dist = 0
    if (k == 1)
        return 0;

    // find the first marked node
    int node1 = bfs(1)[0];

    // find the second marked node and the distance between the two
    float d = bfs(node1)[1];
    d = ceil(d/2);
    return d;
}


int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i ++) {
        Graph g;
        g.readGraph();
        cout << g.minMaxDist() << "\n";
    }
    return 0;
}