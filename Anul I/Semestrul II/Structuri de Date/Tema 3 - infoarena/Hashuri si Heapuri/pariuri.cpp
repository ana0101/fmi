#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

ifstream in("pariuri.in");
ofstream out("pariuri.out");

int n, m, timp, bani;
unordered_map <int, int> pariuri; // timp, bani

int main() {
    in >> n;
    for (int i = 0; i < n; i ++) {
        in >> m;
        for (int j = 0; j < m; j ++) {
            in >> timp >> bani;
            if (pariuri.find(timp) != pariuri.end()) {
                pariuri[timp] += bani;
            }
            else {
                pariuri[timp] = bani;
            }
        }
    }

    out << pariuri.size() << "\n";
    for (auto itr = pariuri.begin(); itr != pariuri.end(); itr ++) {
        out << itr->first << " " << itr->second << " ";
    }

    return 0;
}