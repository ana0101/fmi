#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <tuple>
#include <climits>
using namespace std;

ifstream in("padure.in");
ofstream out("padure.out");

class Graph {
private:
    int n, m;
    vector <vector <int>> forest;
    vector <vector <int>> cost;

public:
    Graph(int n, int m, vector <vector <int>> forest);
    void bfs(tuple <int, int> init);
    int getCost(tuple <int, int> pos);
};

Graph::Graph(int n, int m, vector <vector <int>> forest) {
    this->n = n;
    this->m = m;
    this->forest = forest;
    for (int i = 0; i < n; i ++) {
        cost.push_back({});
        for (int j = 0; j < m; j ++)
            cost[i].push_back(INT_MAX);
    }
}

void Graph::bfs(tuple <int, int> init) {
    // put the first node in the queue
    deque <tuple <int, int>> q;
    cost[get<0>(init)][get<1>(init)] = 0;
    q.push_front(init);

    while (!q.empty()) {
        // get the coordinates of the first node in the queue
        int x = get<0>(q.front());
        int y = get<1>(q.front());

        // eliminate the node from the queue
        q.pop_front();

        for (tuple <int, int> next : {make_tuple(x-1, y), make_tuple(x+1, y), make_tuple(x, y-1), make_tuple(x, y+1)}) {
            int x2 = get<0>(next);
            int y2 = get<1>(next);

            // check if the neighbour exists
            if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < m) {
                // see if the weight is 0 or 1
                int c;
                if (forest[x][y] == forest[x2][y2])
                    c = 0;
                else
                    c = 1;

                // check if the current cost of the path to the neighbour is greater than the cost of the path that goes through the node
                if (cost[x2][y2] > cost[x][y] + c) {
                    cost[x2][y2] = cost[x][y] + c;
                    // put the neighbour in the queue
                    // the 0s go to the front, the 1s to the back because we want to choose as many 0 nodes as possible
                    if (c == 0)
                        q.push_front(make_tuple(x2, y2));
                    else
                        q.push_back(make_tuple(x2, y2));
                }
            }
        }
    }
}

int Graph::getCost(tuple <int, int> pos) {
    return cost[get<0>(pos)][get<1>(pos)];
}

int main() {
    int n, m, pl, pc, cl, cc;
    vector <vector <int>> forest;

    in >> n >> m >> pl >> pc >> cl >> cc;
    for (int i = 0; i < n; i ++) {
        forest.push_back({});
        for (int j = 0; j < m; j ++) {
            int x;
            in >> x;
            forest[i].push_back(x);
        }
    }

    pl --;
    pc --;
    cl --;
    cc --;

    Graph g(n, m, forest);
    g.bfs(make_tuple(pl, pc));
    out << g.getCost(make_tuple(cl, cc));

    return 0;
}