#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
using namespace std;

ifstream in("paranteze.in");
ofstream out("paranteze.out");

string sir;
stack <pair<char, int>> stiva; // caracter, indice
bool valid[1000002];

int main() {
    int n, lung = 0, lungMax = 0;
    in >> n >> sir;

    for (int i = 0; i < n; i ++) {
        switch(sir[i]) {
            case '(': {
                stiva.push({'(', i});
                break;
            }

            case '[': {
                stiva.push({'[', i});
                break;
            }

            case '{': {
                stiva.push({'{', i});
                break;
            }

            case ')': {
                if (!stiva.empty()) {
                    if (stiva.top().first == '(') {
                        valid[i] = 1;
                        valid[stiva.top().second] = 1;
                        stiva.pop();
                    }
                    else {
                        while(!stiva.empty())
                            stiva.pop();
                    }
                }
                break;
            }

            case ']': {
                if (!stiva.empty()) {
                    if (stiva.top().first == '[') {
                        valid[i] = 1;
                        valid[stiva.top().second] = 1;
                        stiva.pop();
                    }
                    else {
                        while(!stiva.empty())
                            stiva.pop();
                    }
                }
                break;
            }

            case '}': {
                if (!stiva.empty()) {
                    if (stiva.top().first == '{') {
                        valid[i] = 1;
                        valid[stiva.top().second] = 1;
                        stiva.pop();
                    }
                    else {
                        while(!stiva.empty())
                            stiva.pop();
                    }
                }
                break;
            }

            default: {
                break;
            }
        }
    }

    for (int i = 0; i < n; i ++) {
        // out << valid[i] << " ";
        if (valid[i])
            lung ++;
        else {
            if (lung > lungMax)
                lungMax = lung;
            lung = 0;
        }
    }
    // out << "\n";

    out << lungMax;

    return 0;
}