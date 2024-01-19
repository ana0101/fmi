#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

ifstream in("banuti.in");
ofstream out("banuti.out");

class Compare {
public:
    bool operator()(pair <int, int> p1, pair <int, int> p2) {
        return p1.second > p2.second;
    }
};

class Graph {
private:
    int n, valMin;
    vector <int> bancnote;
    vector <int> costRest;  // (rest, cost) - pt fiecare rest 0..valMin calculam valoarea minima cu care poate fi obtinut

public:
    Graph() {}
    void readGraph();
    void initCostRest();
    void dijkstra();
    int getSMin();
};

void Graph::readGraph() {
    in >> n;
    bancnote.reserve(n);
    int x;
    for (int i = 0; i < n; i ++) {
        in >> x;
        bancnote.push_back(x);
    }
}

void Graph::initCostRest() {
    sort(bancnote.begin(), bancnote.end());
    valMin = bancnote[0];
    costRest.reserve(valMin);
    for (int i = 0; i < valMin; i ++) {
        costRest.push_back(INT_MAX);
    }

    for (int i = 0; i < n; i ++) {
        costRest[bancnote[i] % valMin] = min(costRest[bancnote[i] % valMin], bancnote[i]);
    }
}

void Graph::dijkstra() {
    vector <bool> viz(valMin, 0);
    priority_queue <pair <int, int>, vector <pair <int, int>>, Compare> heap; // (rest, cost)
    for (int i = 0; i < valMin; i ++) {
        if (costRest[i] != INT_MAX) {
            heap.push(make_pair(i, costRest[i]));
        }
    }

    while (!heap.empty()) {
        int rest = heap.top().first;
        int cost = heap.top().second;
        heap.pop();

        if (viz[rest] == 0) {
            viz[rest] = 1;
            // vedem daca putem obtine alte resturi cu cost mai bun folosindu-ne de acesta
            for (int i = 1; i < valMin; i ++) {
                if (costRest[i] != INT_MAX) {
                    int rest2 = (rest + i) % valMin;
                    if (costRest[rest2] > cost + costRest[i]) {
                        costRest[rest2] = cost + costRest[i];
                        heap.push(make_pair(rest2, costRest[rest2]));
                    }
                }
            }
        }
    }
}

int Graph::getSMin() {
    int smin = 0;
    for (int i = 0; i < valMin; i ++) {
        if (costRest[i] == INT_MAX)
            return -1;
        if (costRest[i] > smin)
            smin = costRest[i];
    }
    return smin - valMin;
}

int main() {
    Graph g;
    g.readGraph();
    g.initCostRest();
    g.dijkstra();
    out << g.getSMin();
    return 0;
}