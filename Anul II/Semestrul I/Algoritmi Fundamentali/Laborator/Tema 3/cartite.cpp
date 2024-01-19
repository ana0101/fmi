#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <unordered_map>
using namespace std;

ifstream in("cartite.in");
ofstream out("cartite.out");

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
    int m, n, xm, ym;   // nr coloane, nr linii, coordonate cartita
    vector <vector <int>> edges;
    vector <vector <bool>> safe; // daca e atacata de vulpe => false
    vector <vector <bool>> moleHole; // daca se poate intra intr-o galerie => true
    unordered_map <pair <int, int>, bool, PairHash> used; // used[node1][node2] = true daca am folosit in ciclul eulerian muchia (node1, node2) sau (node2, node1)

public:
    Graph() {}
    void readGraph();
    void attackOfTheFox(int x, int y, int r);
    int bfs();  // rezolva prima cerinta
    void dfs(int node, vector <int>& path);
    void eulerianPath();    // rezolva a doua cerinta
};

void Graph::readGraph() {
    in >> m >> n;
    edges.resize(m * n + 2);
    safe.resize(m + 1);
    moleHole.resize(m + 1);
    for (int i = 0; i < safe.size(); i ++) {
        safe[i].resize(n + 1);
        moleHole[i].resize(n + 1);
        fill(safe[i].begin(), safe[i].end(), true);
        fill(moleHole[i].begin(), moleHole[i].end(), false);
    }

    in >> xm >> ym;

    // vulpile
    int k;
    in >> k;
    int x, y, r;
    for (int i = 0; i < k; i ++) {
        in >> x >> y >> r;
        attackOfTheFox(x, y, r);
    }

    // galeriile
    int g;
    in >> g;
    int x1, y1, x2, y2;
    for (int i = 0; i < g; i ++) {
        in >> x1 >> y1 >> x2 >> y2;
        int pos1 = (x1 - 1) * n + y1;
        int pos2 = (x2 - 1) * n + y2;
        edges[pos1].push_back(pos2);
        edges[pos2].push_back(pos1);
        moleHole[x1][y1] = true;
        moleHole[x2][y2] = true;
        used[pair <int, int>(pos1, pos2)] = false;
        used[pair <int, int>(pos2, pos1)] = false;
    }
}

void Graph::attackOfTheFox(int x, int y, int r) {
    safe[x][y] = false;

    if (r >= 1) {
        for (pair <int, int> next: {make_pair(x + 1, y), make_pair(x - 1, y), make_pair(x, y + 1), make_pair(x, y - 1)}) {
            int x2 = next.first;
            int y2 = next.second;
            if (x2 >= 1 && x2 <= m && y2 >= 1 && y2 <= n) {
                safe[x2][y2] = false;
                if (r == 2) {
                    for (pair <int, int> next2: {make_pair(x2 + 1, y2), make_pair(x2 - 1, y2), make_pair(x2, y2 + 1), make_pair(x2, y2 - 1)}) {
                        int x3 = next2.first;
                        int y3 = next2.second;
                        if (x3 >= 1 && x3 <= m && y3 >= 1 && y3 <= n) {
                            safe[x3][y3] = false;
                        }
                    }
                }
            }
        }
    }
}

int Graph::bfs() {
    // daca se afla deja intr-o intrare safe
    if (safe[xm][ym] && moleHole[xm][ym]) {
        out << xm << " " << ym << " " << 0;
        return 0;
    }

    vector <vector <int>> dist;
    dist.resize(m + 3);
    for (int i = 0; i < dist.size(); i ++) {
        dist[i].resize(n + 3);
        fill(dist[i].begin(), dist[i].end(), INT_MAX);
    }
    queue <pair <int, int>> q;

    dist[xm][ym] = 0;
    q.push(make_pair(xm, ym));

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (pair <int, int> next: {make_pair(x + 1, y), make_pair(x - 1, y), make_pair(x, y + 1), make_pair(x, y - 1)}) {
            int x2 = next.first;
            int y2 = next.second;
            if (x2 >= 1 && x2 <= m && y2 >= 1 && y2 <= n) {
                if (dist[x2][y2] == INT_MAX && safe[x2][y2]) {
                    dist[x2][y2] = dist[x][y] + 1;
                    if (moleHole[x2][y2]) {
                        out << x2 << " " << y2 << " " << dist[x2][y2];
                        return 0;
                    }
                    q.push(make_pair(x2, y2));
                }
            }
        }
    }

    return 0;
}

void Graph::dfs(int node, vector <int>& path) {
    while (!edges[node].empty()) {
        int next = edges[node].back();
        edges[node].pop_back();
        if (!used[pair <int, int>(node, next)]) {
            used[pair <int, int>(node, next)] = true;
            used[pair <int, int>(next, node)] = true;
            dfs(next, path);
        }
    }
    path.push_back(node);
}

void Graph::eulerianPath() {
    vector <int> path;
    // gasim un nod de pornire
    int startNode;
    bool ok = false;
    for (int i = 1; i <= m && !ok; i ++) {
        for (int j = 1; j <= n && !ok; j ++) {
            if (moleHole[i][j] && safe[i][j]) {
                startNode = (i - 1) * n + j;
                ok = true;
            }
        }
    }

    dfs(startNode, path);

    for (int i = 0; i < path.size(); i ++) {
        int pos = path[i];
        int x = (pos - 1) / n + 1;
        int y = (pos - 1) % n + 1;
        out << x << " " << y << "\n";
    }
}

int main() {
    int p;
    in >> p;
    Graph g;
    g.readGraph();
    if (p == 1) {
        g.bfs();
    }
    else {
        g.eulerianPath();
    }
    return 0;
}
