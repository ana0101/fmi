#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

ifstream in("dfs.in");
ofstream out("dfs.out");

const int nmax = 100000;
vector <int> graf[nmax+1];
int vis[nmax+1], d[nmax+1];

void dfs(int x) {
    vis[x] = 1;
    for (auto next:graf[x]) {
        if (vis[next] == 0) 
            dfs(next);
    }
}

int main() {
    int n, m, s, x, y;
    in >> n >> m >> s;
    for (int i = 1; i <= m; i ++) {
        in >> x >> y;
        graf[x].push_back(y);
        graf[y].push_back(x);
    }

    int nr = 1;
    dfs(1);
    for (int i = 1; i <= n; i ++) {
        if (vis[i] == 0) {
            nr ++;
            dfs(i);
        }
    }

    out << nr;

    return 0;
}
