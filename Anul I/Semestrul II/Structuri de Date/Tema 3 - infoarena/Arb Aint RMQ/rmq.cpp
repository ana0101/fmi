#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

ifstream in("rmq.in");
ofstream out("rmq.out");

int n, m, rmq[17][100001];

int main() {
    in >> n >> m;

    for (int i = 0; i < n; i ++) {
        in >> rmq[0][i];
    }

    for (int i = 1; i < 17; i ++) {
        for (int j = 0; j + (1 << i) <= n; j ++) {
            rmq[i][j] = min(rmq[i-1][j], rmq[i-1][j + (1 << (i-1))]);
        }
    }

    // for (int i = 0; i < 17; i ++) {
    //     for (int j = 0; j + (1 << i) <= n; j ++)
    //         cout << rmq[i][j] << " ";
    //     cout << "\n";
    // }

    int x, y;
    for (int i = 0; i < m; i ++) {
        in >> x >> y;
        x --;
        y --;
        int p = log2(y-x+1);
        out << min(rmq[p][x], rmq[p][y - (1 << p) + 1]) << "\n";
    }

    return 0;
}