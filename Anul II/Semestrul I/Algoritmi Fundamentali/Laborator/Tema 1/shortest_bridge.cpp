#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Graph {
    int n;
    vector <vector <int>> grid;
    queue <vector <int>> q;

public:
    Graph(vector <vector <int>>& grid);
    vector <int> findLand();    // returns the coordinates of the first land it finds
    void dfs(int x, int y);     // marks with 2 the first island
    int bfs();     // return the shortest distance between island 1 and 2
    int getDistance();
};

Graph::Graph(vector<vector<int>>& grid) {
    this->n = grid.size();
    this->grid = grid;
}

vector <int> Graph::findLand() {
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            if (grid[i][j]) {
                vector <int> land;
                land.push_back(i);
                land.push_back(j);
                return land;
            }
        }
    }
    return {};
} 

void Graph::dfs(int x, int y) {
    // put the land in the queue for bfs
    vector <int> land;
    land.push_back(x);
    land.push_back(y);
    q.push(land);

    grid[x][y] = 2;
    if (x > 0) {
        if (grid[x-1][y] == 1)
            dfs(x-1, y);
    }
    if (x < n-1) {
        if (grid[x+1][y] == 1)
            dfs(x+1, y);
    }
    if (y > 0) {
        if (grid[x][y-1] == 1)
            dfs(x, y-1);
    }
    if (y < n-1) {
        if (grid[x][y+1] == 1)
            dfs(x, y+1);
    }
}

int Graph::bfs() {
    int d = 0;
    while (!q.empty()) {
        queue <vector <int>> newQ;
        while (!q.empty()) {
            int x = q.front()[0];
            int y = q.front()[1];
            q.pop();

            if (x > 0) {
                if (grid[x-1][y] == 1)
                    return d;
                else {
                    if (grid[x-1][y] == 0) {
                        vector <int> water;
                        water.push_back(x-1);
                        water.push_back(y);
                        newQ.push(water);
                        grid[x-1][y] = -1;  // mark as visited
                    }
                }
            }

            if (x < n-1) {
                if (grid[x+1][y] == 1)
                    return d;
                else {
                    if (grid[x+1][y] == 0) {
                        vector <int> water;
                        water.push_back(x+1);
                        water.push_back(y);
                        newQ.push(water);
                        grid[x+1][y] = -1;  // mark as visited
                    }
                }
            }

            if (y > 0) {
                if (grid[x][y-1] == 1)
                    return d;
                else {
                    if (grid[x][y-1] == 0) {
                        vector <int> water;
                        water.push_back(x);
                        water.push_back(y-1);
                        newQ.push(water);
                        grid[x][y-1] = -1;  // mark as visited
                    }
                }
            }

            if (y < n-1) {
                if (grid[x][y+1] == 1)
                    return d;
                else {
                    if (grid[x][y+1] == 0) {
                        vector <int> water;
                        water.push_back(x);
                        water.push_back(y+1);
                        newQ.push(water);
                        grid[x][y+1] = -1;  // mark as visited
                    }
                }
            }
        }

        d ++;
        q = newQ;
    }
    return d;
}

int Graph::getDistance() {
    vector <int> land = findLand();
    dfs(land[0], land[1]);
    return bfs();
}

class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        Graph g(grid);
        return g.getDistance();
    }
};