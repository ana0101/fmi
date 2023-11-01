// verificam daca exista vreun ciclu
// dfs si daca ne intoarcem intr-un nod deja vizitat => exista ciclu

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

ifstream in("dfs.in");
ofstream out("dfs.out");

const int nmax = 100000;
vector <int> graf[nmax+1];
int vis[nmax+1], d[nmax+1], parent[nmax+1];
int start, stop;

void dfs(int x) {
    vis[x] = 1;
    for (auto next:graf[x]) {
        if (vis[next] == 0) {
            parent[next] = x;
            dfs(next);
        }
        else {
            if (vis[next] == 1) {
                start = x;
                stop = next;
            }
        }
    }
    vis[x] = 2;
}

int main() {
    int n, m, s, x, y;
    in >> n >> m >> s;
    for (int i = 1; i <= m; i ++) {
        in >> x >> y;
        graf[x].push_back(y);
        graf[y].push_back(x);
    }

    return 0;
}
