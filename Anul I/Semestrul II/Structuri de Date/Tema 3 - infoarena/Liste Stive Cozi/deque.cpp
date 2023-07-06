#include <iostream>
#include <fstream>
using namespace std;

ifstream in("deque.in");
ofstream out("deque.out");

pair <int, int> deque[5000002]; // nr, index
long long r;

int main() {
    int n, k, nr, st = 0, dr = -1;
    in >> n >> k;

    for (int i = 0; i < k-1; i ++) {
        in >> nr;
        while (dr > -1 && dr >= st && nr <= deque[dr].first) {
            deque[dr] = {0, 0};
            dr --;
        }
        dr ++;
        deque[dr] = {nr, i};
    }

    for (int i = k-1; i < n; i ++) {
        in >> nr;
        while (dr >= st && nr <= deque[dr].first) {
            deque[dr] = {0, 0};
            dr --;
        }

        dr ++;
        deque[dr] = {nr, i};

        r += deque[st].first;
        // out << deque[st].first << "\n";
        if (deque[st].second <= i-k+1)
            st ++;
    }

    out << r;

    return 0;
}