#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

ifstream in("proc2.in");
ofstream out("proc2.out");

int n, m, s, d;
priority_queue <int, vector<int>, greater<int>> proc_disponibile;
priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> proc_ocupate; // timp_terminare, nr_ordine

int main() {
    in >> n >> m;
    for (int i = 1; i <= n; i ++) {
        proc_disponibile.push(i);
    }

    for (int i = 0; i < m; i ++) {
        in >> s >> d;

        // mutam procesoarele care au terminat
        while (!proc_ocupate.empty() && proc_ocupate.top().first <= s) {
            proc_disponibile.push(proc_ocupate.top().second);
            proc_ocupate.pop();
        }

        // luam procesorul cel mai mic disponibil
        out << proc_disponibile.top() << "\n";
        proc_ocupate.push({s+d, proc_disponibile.top()});
        proc_disponibile.pop();
    }

    return 0;
}