#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

ifstream in("stramosi.in");
ofstream out("stramosi.out");

int n, m, p, q, nr;
int s[19][250002];

int main() {
    in >> n >> m;
    nr = log2(n);
    nr ++;

    for (int j = 1; j <= n; j ++) {
        in >> s[0][j];
    }

    for (int i = 1; i <= nr; i ++) {
        for (int j = 1; j <= n; j ++) {
            s[i][j] = s[i-1][s[i-1][j]];
        }
    }

    // for (int i = 1; i <= nr; i ++) {
    //     for (int j = 1; j <= n; j ++) {
    //         cout << s[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    for (int k = 0; k < m; k ++) {
        in >> p >> q;
        for (int i = nr; i >= 0; i --) {
            if ((1 << i) <= q) {
                q -= (1 << i);
                p = s[i][p];
            }
        }
        out << p << "\n";
    }

    return 0;
}