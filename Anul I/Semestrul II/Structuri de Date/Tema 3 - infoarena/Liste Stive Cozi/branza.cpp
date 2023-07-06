#include <iostream>
#include <fstream>
#include <deque>
using namespace std;

ifstream in("branza.in");
ofstream out("branza.out");

deque <pair <long long, long long>> branza; // cost, saptamana

int main() {
    long long n, s, t, c, p, cost = 0;
    in >> n >> s >> t;

    in >> c >> p;
    branza.push_back({c, 0});
    cost += c * p;

    for (int i = 1; i < n; i ++) {
        in >> c >> p;
        // daca prima branza ar expira o scoatem
        if (branza[0].second + t < i)
            branza.pop_front();

        // eliminam branzele care nu ar fi mai ieftine
        while (!branza.empty() && s * (i - branza.back().second) + branza.back().first >= c)
            branza.pop_back();

        branza.push_back({c, i});
        // out << i << " " << branza[0].first << " ";

        cost += s * p * (i - branza[0].second) + p * branza[0].first;
        // out << cost << "\n";
    }

    out << cost;

    return 0;
}