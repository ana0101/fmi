#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

ifstream in("queue.in");
ofstream out("queue.out");

stack <int> stiva1, stiva2;
string linie;

int main() {
    int n;
    in >> n;
    for (int i = 0; i < n; i ++) {
        in >> linie;
        out << i + 1 << ": ";
        if (linie[1] == 'u') {
            int nr = 0, j = 10;
            while (linie[j] != ')') {
                nr = nr * 10 + (linie[j] - '0');
                j ++;
            }
            stiva1.push(nr);
            out << "read(" << nr << ") push(1," << nr << ")\n";
        }
        else {
            if (!stiva2.empty()) {
                int nr = stiva2.top();
                stiva2.pop();
                out << "pop(2) write(" << nr << ")\n"; 
            }
            else {
                while (stiva1.size() > 1) {
                    int nr = stiva1.top();
                    stiva1.pop();
                    stiva2.push(nr);
                    out << "pop(1) push(2," << nr << ") ";
                }
                int nr = stiva1.top();
                stiva1.pop();
                out << "pop(1) write(" << nr << ")\n";
            }
        }
    }

    return 0;
}