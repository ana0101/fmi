#include <iostream>
#include <fstream>
using namespace std;

ifstream in("heapuri.in");
ofstream out("heapuri.out");

int v[200002], h[200002], pos[200002], lv, lh;

void up(int nod) {
    while (nod/2 && v[h[nod/2]] > v[h[nod]]) {
        swap(h[nod/2], h[nod]);
        pos[h[nod/2]] = nod/2;
        pos[h[nod]] = nod;
        nod /= 2;
    }
}

void down(int nod) {
    bool ok = 0;
    while (nod * 2 <= lh && !ok) {
        ok = 1;
        int fiu_st = nod * 2;
        int fiu_dr = nod * 2 + 1;
        int minim = nod;

        if (v[h[fiu_st]] < v[h[minim]]) {
            minim = fiu_st;
            ok = 0;
        }

        if (fiu_dr <= lh && v[h[fiu_dr]] < v[h[minim]]) {
            minim = fiu_dr;
            ok = 0;
        }

        if (!ok) {
            swap(h[nod], h[minim]);
            pos[h[nod]] = nod;
            pos[h[minim]] = minim;
            nod = minim;
        }
    }
}


int main() {
    int n, op, x;
    in >> n;
    
    for (int i = 0; i < n; i ++) {
        in >> op;

        switch(op) {
            case 1: {
                in >> x;
                lv ++;
                v[lv] = x;

                lh ++;
                h[lh] = lv;
                pos[lv] = lh;

                up(lh);
                break;
            }

            case 2: {
                in >> x;
                v[x] = 0;
                up(pos[x]);

                h[1] = h[lh];
                lh --;
                pos[h[1]] = 1;
                down(1);
                break;
            }

            case 3: {
                out << v[h[1]] << "\n";
                break;
            }

            default: {
                break;
            }
        }
    }

    return 0;
}