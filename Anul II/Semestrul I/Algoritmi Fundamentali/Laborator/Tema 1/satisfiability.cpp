#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Graph {
private:
    int n;
    vector <int> parent;
    vector <int> h; // the height of the tree 
    vector <string> equations;

public:
    Graph(vector <string>& equations);
    int getRoot(int node);  // returns the root of the tree in which node is in
    void equalityTrees();   // for every two nodes that are equal, it merges them (and their trees)
    bool checkInequalities();   // for every two nodes that are not equal, it checks if they are in different trees
};

Graph::Graph(vector <string>& equations) {
    this->n = 26;
    this->equations = equations;
    for (int i = 0; i < this->n; i ++)
        this->parent.push_back(i);
    for (int i = 0; i < this->n; i ++)
        this->h.push_back(0);
}

int Graph::getRoot(int node) {
    if (node == parent[node])
        return node;
    return getRoot(parent[node]);
}

void Graph::equalityTrees() {
    for (int i = 0; i < equations.size(); i ++) {
        string e = equations[i];
        if (e[1] == '=') {
            int node1 = e[0] - 'a';
            int node2 = e[3] - 'a';
            int root1 = getRoot(node1);
            int root2 = getRoot(node2);

            // if the nodes are in different trees, merge the trees
            if (root1 != root2) {
                // merge the smaller tree to the bigger one
                if (h[root1] < h[root2]) {
                    parent[root1] = root2;
                    if (h[root1] + 1 > h[root2])
                        h[root2] = h[root1] + 1; 
                }
                else {
                    parent[root2] = root1;
                    if (h[root2] + 1 > h[root1])
                        h[root1] = h[root2] + 1;
                }
            }
        }
    }
}

bool Graph::checkInequalities() {
    for (int i = 0; i < equations.size(); i ++) {
        string e = equations[i];
        if (e[1] == '!') {
            int node1 = e[0] - 'a';
            int node2 = e[3] - 'a';
            int root1 = getRoot(node1);
            int root2 = getRoot(node2);
            // if they are in the same tree => not ok
            if (root1 == root2)
                return false;
        }
    }
    return true;
}

class Solution {
public:
    bool equationsPossible(vector <string>& equations) {
        Graph g(equations);
        g.equalityTrees();
        return g.checkInequalities();
    }
};