#include <iostream>
using namespace std;

bool camere[11];

int main() {
    int n;
    string sir;
    cin >> n >> sir;

    for (int i = 0; i < n; i ++) {
        if (sir[i] == 'L') {
            for (int j = 0; j < 10; j ++) {
                if (!camere[j]) {
                    camere[j] = 1;
                    break;
                }
            }
        }
        else {
            if (sir[i] == 'R') {
                for (int j = 9; j >=0; j --) {
                    if (!camere[j]) {
                        camere[j] = 1;
                        break;
                    }
                }
            }
            else {
                camere[sir[i] - '0'] = 0;
            }
        }
    }

    for (int i = 0; i < 10; i ++)
        cout << camere[i];

    return 0;
}