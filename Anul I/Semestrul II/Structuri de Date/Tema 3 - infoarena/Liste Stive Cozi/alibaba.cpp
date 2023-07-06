#include <iostream>
#include <fstream>
#include <deque>
using namespace std;

ifstream in("alibaba.in");
ofstream out("alibaba.out");

deque <int> nrFinal;
string nr;

int main() {
    int n, k;
    in >> n >> k;
    in >> nr;

    for (int i = 0; i < nr.length(); i ++) {
        int cf = nr[i] - '0';
        while (!nrFinal.empty() && cf > nrFinal.back() && k) {
            k --;
            nrFinal.pop_back();
        }
        nrFinal.push_back(cf);
    }

    while (k) {
        k --;
        nrFinal.pop_back();
    }

    while (!nrFinal.empty()) {
        out << nrFinal.front();
        nrFinal.pop_front();
    }

    return 0;
}