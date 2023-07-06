#include <iostream>
#include <fstream>
using namespace std;

ifstream in("farfurii.in");
ofstream out("farfurii.out");

long long n, k, inv;

int main() {
    in >> n >> k;

    // numaram pana la ce farfurie putem sa le punem in ordine ca sa mai ramana destule inversiuni pt tacamuri
    long long f;
    for (f = 1; f <= n && k <= (n-f) * (n-f-1) / 2; f ++)
        out << f << " ";
    f --;

    // daca avem mai multe inversiuni decat ne trebuie mai punem o farfurie
    long long f2 = n - (n-f) * (n-f-1) / 2 + k;
    out << f2 << " ";

    // le punem si pe restul (descresc pt inv)
    for (long long f3 = n; f3 > f; f3 --)
        if (f3 != f2)
            out << f3 << " ";

    return 0;
}