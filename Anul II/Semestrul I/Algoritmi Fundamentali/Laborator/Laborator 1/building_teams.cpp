// verificam daca graful e bipartit <=> e 2-colorabil <=> nu contine niciun ciclu de lungime impara
// rez: cu 2-colorabil

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

ifstream in("building_teams.in");
ofstream out("building_teams.out");

const int nmax = 100000;
vector <int> graf[nmax+1];
int vis[nmax+1], d[nmax+1];
int col[nmax+1];

bool bipartit(int x) {
    queue <int> q;
    q.push(x);
    col[x] = 1;

    while (!q.empty()) {
        x = q.front();
        q.pop();
        for (auto next:graf[x]) {
            if (!col[next]) {
                col[next] = 3 - col[x];
                q.push(next);
            }
            else {
                if (col[next] != 3-col[x]) {
                    return false;
                }
            }
        }
    }
    return true;
}


int main() {
    int n, m, s, x, y;
    in >> n >> m;
    for (int i = 1; i <= m; i ++) {
        in >> x >> y;
        graf[x].push_back(y);
    }

    bool ok = true;
    for (int i = 1; i <= n; i ++) {
        if (!col[i]) {
            ok = bipartit(i);
        }
        if (!ok)
            break;
    }

    if (!ok)
        out << "imposibil";
    else {
        for (int i = 1; i <= n; i ++) 
            out << col[i] << " ";
    }

    return 0;
}
