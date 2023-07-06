#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

ifstream in("hashuri.in");
ofstream out("hashuri.out");

const int p = 666013;

vector <int> h[p+2];

void insert(int x) {
    int r = x % p;
    bool exista = 0;
    for (int i = 0; i < h[r].size(); i ++) {
        if (h[r][i] == x) {
            exista = 1;
            break;
        }
    }
    if (!exista)
        h[r].push_back(x);
}

void remove(int x) {
    int r = x % p;
    for (int i = 0; i < h[r].size(); i ++) {
        if (h[r][i] == x) {
            h[r].erase(h[r].begin() + i);
            break;
        }
    }
}

bool search(int x) {
    int r = x % p;
    for (int i = 0; i < h[r].size(); i ++) {
        if (h[r][i] == x)
            return 1;
    }
    return 0;
}


int main() {
    int n, op, x;
    in >> n;

    for (int i = 0; i < n; i ++) {
        in >> op >> x;
        switch(op) {
            case 1: {
                insert(x);
                break;
            }

            case 2: {
                remove(x);
                break;
            }

            case 3: {
                out << search(x) << "\n";
                break;
            }
        }
    }

    return 0;
}