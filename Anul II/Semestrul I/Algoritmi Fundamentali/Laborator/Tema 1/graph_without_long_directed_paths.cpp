#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Graph {
    int n, m;
    vector <vector <int>> edges;
    vector <vector <int>> ordered_edges;    // the edges in the input order
    vector <int> color; // 0 for not visited, 1 for 1st color (with incoming edges), 2 for 2nd color (with outgoing edges)

public:
    void readGraph();
    void printGraph();
    bool bfs(int node); // true is bipartite, false if not
    void solution();    // prints the solution
};

void Graph::readGraph() {
    cin >> n;
    cin >> m;
    int x, y;
    for (int i = 0; i < m; i ++) {
        cin >> x >> y;
        ordered_edges.push_back({x, y});
    }

    for (int i = 0; i <= n; i ++) {
        edges.push_back({});
    }
    for (int i = 0; i < m; i ++) {
        edges[ordered_edges[i][0]].push_back(ordered_edges[i][1]);
        edges[ordered_edges[i][1]].push_back(ordered_edges[i][0]);
    }

    for (int i = 0; i <= n; i ++) {
        color.push_back(0);
    }
}

void Graph::printGraph() {
    cout << "n = " << n << "\n";
    cout << "m = " << m << "\n";

    cout << "ord edges\n";
    for (int i = 0; i < m; i ++) {
        cout << ordered_edges[i][0] << " " << ordered_edges[i][1] << "\n";
    }
    cout << "\n";

    cout << "edges\n";
    for (int i = 0; i <= n; i ++) {
        cout << i << ": ";
        for (int j = 0; j < edges[i].size(); i ++)
            cout << edges[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";

    cout << "colors\n";
    for (int i = 0; i <= n; i ++) 
        cout << i << ": " << color[i] << "\n";
}

bool Graph::bfs(int node) {
    queue <int> q;
    q.push(node);
    color[node] = 1;

    while (!q.empty()) {
        node = q.front();
        q.pop();
        for (int i = 0; i < edges[node].size(); i ++) {
            int next = edges[node][i];
            if (!color[next]) {
                color[next] = 3 - color[node];
                q.push(next);
            } 
            else {
                if (color[next] == color[node]) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Graph::solution() {
    for (int i = 0; i < ordered_edges.size(); i ++) {
        if (color[ordered_edges[i][0]] == 1)
            cout << 0;
        else
            cout << 1;
    }
}


int main() {
    Graph g;
    g.readGraph();
    bool ok = g.bfs(1);

    if (ok) {
        cout << "YES\n";
        g.solution();
    }
    else {
        cout << "NO";
    }

    return 0;
}