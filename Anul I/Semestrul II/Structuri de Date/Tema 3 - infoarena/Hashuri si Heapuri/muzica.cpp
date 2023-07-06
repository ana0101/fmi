#include <iostream>
#include <fstream>
#include <unordered_set>
using namespace std;

ifstream in("muzica.in");
ofstream out("muzica.out");

long long n, m, a, b, c, d, e, k, melodie;
unordered_set <int> vasile;

void gasit(int x) {
    if (vasile.find(x) != vasile.end()) {
        k ++;
        vasile.erase(x);
    }
}

int main() {
    in >> n >> m;
    in >> a >> b >> c >> d >> e;

    for (int i = 0; i < n; i ++) {
        in >> melodie;
        vasile.insert(melodie);
    }

    gasit(a);
    gasit(b);

    for (int i = 3; i <=m; i ++) {
        int b2 = (c * b + d * a) % e;
        gasit(b2);
        a = b;
        b = b2;
    }

    out << k;

    return 0;
}