#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

ifstream in("bfs.in");
ofstream out("bfs.out");

const int nmax = 100000;
vector <int> graf[nmax+1];
int vis[nmax+1], d[nmax+1];

void bfs(int x) {
    queue <int> q;
    q.push(x);
    vis[x] = 1;
    d[x] = 0;
    while (!q.empty()) {
        x = q.front();
        q.pop();
        for (auto next:graf[x]) {
            if (vis[next] == 0) {
                vis[next] = 1;
                d[next] = d[x] + 1;
                q.push(next);
            }
        }
    }
}

int main() {
    int n, m, s, x, y;
    in >> n >> m >> s;
    for (int i = 1; i <= m; i ++) {
        in >> x >> y;
        graf[x].push_back(y);
    }

    bfs(s);
    for (int i = 1; i <= n; i ++) {
        if (vis[i] == 0 && i != s)
            out << -1 << " ";
        else
            out << d[i] << " ";
    }

    return 0;
}
