#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
using namespace std;

class Graph {
private:
    int n, finalNode;
    vector <string> words;
    vector <vector <int>> edges;    // edges[i][j] = len j - nr comune (cate litere se adauga la ce e deja)
    vector <vector <int>> parent;   // parent[i][j] = nodul dinaintea lui j cu setul i

public:
    Graph(const vector <string>& words);
    int appendWordLength(string w1, string w2);
    int tsp();
    string minPath();
};

Graph::Graph(const vector <string>& words) {
    n = words.size();
    edges.resize(n + 1);
    this->words = words;
    for (int i = 0; i < n; i ++) {
        edges[i].resize(n + 1);
        for (int j = 0; j < n; j ++) {
            edges[i][j] = appendWordLength(words[i], words[j]);
        }
    }
}

int Graph::appendWordLength(string w1, string w2) {
    if (w1 == w2) {
        return w2.length();
    }
    // parcurge primul cuvant si verifica pt fiecare pozitie daca al doilea cuvant incepe cu ce a ramas din primul
    for (int i = 1; i < w1.length(); i ++) {
        bool ok = true;
        int m = w1.length() - i;
        if (w2.length() > m) {
            for (int j = i; j < w1.length() && ok; j ++) {
                if (w1[j] != w2[j - i]) {
                    ok = false;
                }
            }
        }
        else {
            ok = false;
        }

        if (ok) {
            return w2.length() - (w1.length() - i);
        }
    }

    return w2.length();
}

int Graph::tsp() {
    vector <vector <int>> length; 
    // length[i][j] = lungimea minima daca parcurgem toate nodurile din i si j este ultimul nod parcurs
    // i = bit-mask (1 daca nodul e in set (daca e parcurs), 0 daca nu)

    int finalMask = (1 << n) - 1; // 11...1
    length.resize(finalMask + 2);
    parent.resize(finalMask + 2);
    for (int i = 0; i <= finalMask; i ++) {
        length[i].resize(n + 1);
        parent[i].resize(n + 1);
        fill(length[i].begin(), length[i].end(), INT_MAX);
        fill(parent[i].begin(), parent[i].end(), -1);
    }

    int minLength = INT_MAX;

    // luam toate combinatiile de noduri
    for (int i = 1; i <= finalMask; i ++) {
        for (int j = 0; j < n; j ++) {
            // daca nodul e in set => vrem sa il parcurgem
            if (i & (1 << j)) {
                if (i == (1 << j)) {
                    // daca nodul e singurul din set => length[i][j] = lungimea lui j
                    length[i][j] = edges[j][j];
                }
                else {
                    // daca mai sunt si alte noduri in set => vedem daca vreun drum care se termina cu unul din noduri
                    // poate fi folosit sa imbunatateasca length[i][j]
                    // il scoatem pe j din set
                    int mask = i - (1 << j);  
                    for (int k = 0; k < n; k ++) {
                        // daca nodul se afla in setul ramas
                        if (mask & (1 << k)) {
                            // daca am gasit o lungime mai buna
                            if (length[mask][k] != INT_MAX && length[i][j] > length[mask][k] + edges[k][j]) {
                                length[i][j] = length[mask][k] + edges[k][j];
                                parent[i][j] = k;
                            }
                        }
                    }
                }
            }

            if (i == finalMask && minLength > length[i][j]) {
                // daca am parcurs toate nodurile si am gasit o lungime mai buna
                minLength = length[i][j];
                finalNode = j;
            }
        }
    }
    return minLength;
}

string Graph::minPath() {
    vector <int> path;
    int node = finalNode;
    int mask = (1 << n) - 1;

    int k = 0;
    while (k < n) {
        path.push_back(node);
        int newNode = parent[mask][node];
        mask -= (1 << node); 
        node = newNode;
        k ++;
    }

    reverse(path.begin(), path.end());

    string sol = words[path[0]];
    for (int i = 1; i < n; i ++) {
        int pos = words[path[i]].length() - edges[path[i-1]][path[i]];
        for (int j = pos; j < words[path[i]].length(); j ++) {
            sol = sol + words[path[i]][j];
        }
    }
    return sol;
}

class Solution {
public:
    string shortestSuperstring(const vector <string>& words) {
        Graph g(words);
        g.tsp();
        return g.minPath();
    }
};
