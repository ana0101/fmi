#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

ifstream in("loto.in");
ofstream out("loto.out");

int n, s;
int nr[101];
map <int, vector <int>> h;

bool sume() {
    bool ok = 0;
    for (int i = 0; i < n && !ok; i ++) {
        for (int j = i; j < n && !ok; j ++) {
            for (int k = j; k < n && !ok; k ++) {
                h[nr[i] + nr[j] + nr[k]] = {nr[i], nr[j], nr[k]};
                int s2 = s - nr[i] - nr[j] - nr[k];
                if (h.find(s2) != h.end()) {
                    ok = 1;
                    out << nr[i] << " " << nr[j] << " " << nr[k] << " " << h[s2][0] << " " << h[s2][1] << " " << h[s2][2];
                }
            }
        }
    }
    return ok;
}


int main() {
    in >> n >> s;
    for (int i = 0; i < n; i ++) {
        in >> nr[i];
    }

    if (!sume())
        out << -1;

    return 0;
}