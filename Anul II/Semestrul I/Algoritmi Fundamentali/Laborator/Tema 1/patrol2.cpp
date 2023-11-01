#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

ifstream in("patrol2.in");
ofstream out("patrol2.out");

class Graph {
private:
    int n, m, k, cycleTime;
    vector <vector <int>> tunnels;
    vector <vector <bool>> occupied;   // 0 if no police in tunnels[i][t], 1 if police
    vector <vector <int>> patrols;
    vector <int> l; // number of manholes for patrol i
    vector <vector <int>> minTime;  // minTime[i][j] = current minimum time from start to i at cycle time j

public:
    void readGraph();
    void precalcOccupied();
    void bfs(int node);
    int getMinTimeEscape();
};

void Graph::readGraph() {
    in >> n >> m >> k;
    for (int i = 0; i < n; i ++)
        tunnels.push_back({});
    int x, y;
    for (int i = 0; i < m; i ++) {
        in >> x >> y;
        tunnels[x].push_back(y);
        tunnels[y].push_back(x);
    }

    for (int i = 0; i < k; i ++) {
        patrols.push_back({});
    }
    for (int i = 0; i < k; i ++) {
        in >> x;
        l.push_back(x);
        for (int j = 0; j < x; j ++) {
            in >> y;
            patrols[i].push_back(y);
        }
    }

    cycleTime = 420;    // cmmmc (1,2,..,7)

    for (int i = 0; i < n; i ++) {
        occupied.push_back({});
        for (int j = 0; j < cycleTime; j ++)
            occupied[i].push_back(0);
    }

    for (int i = 0; i < n; i ++) {
        minTime.push_back({});
        for (int j = 0; j < cycleTime; j ++)
            minTime[i].push_back(INT_MAX);
    }
}

void Graph::precalcOccupied() {
    for (int i = 0; i < cycleTime; i ++) {
        for (int j = 0; j < k; j ++) {
            int t = i % l[j];
            occupied[patrols[j][t]][i] = 1;
        }
    }
}

void Graph::bfs(int node) {
    queue <vector <int>> q; // q[i] = [node, time (cycle)]
    q.push({node, 0});
    minTime[node][0] = 0;

    while (!q.empty()) {
        node = q.front()[0];
        int time = q.front()[1];
        q.pop();

        int newTime = (time + 1) % cycleTime;

        // check current manhole - stay
        if (!occupied[node][newTime]) {
            if (minTime[node][newTime] > minTime[node][time] + 1) {
                minTime[node][newTime] = minTime[node][time] + 1;
                q.push({node, newTime});
            }
        }
        
        // check neighbour manholes - move
        for (int i = 0; i < tunnels[node].size(); i ++) {
            int next = tunnels[node][i];
            if (!occupied[next][newTime]) {
                if (minTime[next][newTime] > minTime[node][time] + 1) {
                    minTime[next][newTime] = minTime[node][time] + 1;
                    q.push({next, newTime});
                }
            }
        }
    }
}

int Graph::getMinTimeEscape() {
    int t = INT_MAX;
    for (int i = 0; i < cycleTime; i ++) {
        if (minTime[n-1][i] < t) 
            t = minTime[n-1][i];
    }

    if (t != INT_MAX)
        return t;
    else
        return -1;
}


int main() {
    Graph g;
    g.readGraph();
    g.precalcOccupied();
    g.bfs(0);
    out << g.getMinTimeEscape();
    return 0;
}