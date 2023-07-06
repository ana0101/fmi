#include <iostream>
#include <fstream>
#include <deque>
using namespace std;

ifstream in("vila2.in");
ofstream out("vila2.out");

deque <pair<int, int>> minime; //(varsta, index)
deque <pair<int, int>> maxime; //(varsta, index)

int main() {
    int n, k, varsta, difMax = 0;
    in >> n >> k;

    for (int i = 0; i < n; i ++) {
        // out << difMax << "\n";
        in >> varsta;

        // scoatem varstele celor care sunt prea departe
        while (!minime.empty() && i-minime[0].second > k)
            minime.pop_front();
        while (!maxime.empty() && i-maxime[0].second > k)
            maxime.pop_front();

        // verificam daca updatam difMax
        if (i) {
            if (abs(varsta - minime[0].first) > difMax)
                difMax = abs(varsta - minime[0].first);
            if (abs(maxime[0].first - varsta) > difMax)
                difMax = abs(maxime[0].first - varsta);
        }

        // vedem unde inseram noua varsta
        while (!minime.empty() && varsta < minime.back().first)
            minime.pop_back();
        minime.push_back({varsta, i});

        while (!maxime.empty() && varsta > maxime.back().first)
            maxime.pop_back();
        maxime.push_back({varsta, i});
    }
    
    out << difMax;

    return 0;
}