#include <iostream>
#include <fstream>
#include <set>
#include <queue>
using namespace std;

ifstream in("zeap.in");
ofstream out("zeap.out");

struct Zeap {
    set <int> elem;
    priority_queue <pair <int, pair <int, int>>> minime;

    void insert(int x);
    int remove(int x);
    bool search(int x);
    int max_dif();
    int min_dif();
};

void Zeap::insert(int x) {
    elem.insert(x);
    auto i = elem.find(x);
    // verificam daca exista vecin stang
    if (i != elem.begin()) {
        i --;
        minime.push({*i - x, {x, *i}});
        i ++;
    }
    i ++;
    // verificam daca exista vecin drept
    if (i != elem.end()) {
        minime.push({x - *i, {x, *i}});
    }
}

int Zeap::remove(int x) {
    int ok = -1;
    auto i = elem.find(x);
    if (i != elem.end()) {
        ok = 1;
        // verificam daca are vecini
        auto j = i;
        j ++;
        if (i != elem.begin() && j != elem.end()) {
            i --;
            minime.push({*i - *j, {*i, *j}});
        }
        elem.erase(x);
    }
    return ok;
}

bool Zeap::search(int x) {
    if (elem.find(x) != elem.end())
        return 1;
    return 0;
}

int Zeap::max_dif() {
    if (elem.size() < 2)
        return -1;
    auto end = elem.end();
    end --;
    return *(end) - *(elem.begin());
}

int Zeap::min_dif() {
    if (elem.size() < 2)
        return -1;
    // stergem diferentele la care unul din membri a fost sters
    while (elem.find(minime.top().second.first) == elem.end() || elem.find(minime.top().second.second) == elem.end()) {
        minime.pop();
    }
    return -minime.top().first;
}


int main() {
    Zeap z;
    string k;
    while (in >> k) {
        if (k == "I") {
            int x;
            in >> x;
            z.insert(x);
        }
        else if (k == "S") {
            int x;
            in >> x;
            int ok = z.remove(x);
            if (ok == -1)
                out << ok << "\n";
        }
        else if (k == "C") {
            int x;
            in >> x;
            out << z.search(x) << "\n";
        }
        else if (k == "MAX") {
            out << z.max_dif() << "\n";
        }
        else if (k == "MIN") {
            out << z.min_dif() << "\n";
        }
    }
    return 0;
}