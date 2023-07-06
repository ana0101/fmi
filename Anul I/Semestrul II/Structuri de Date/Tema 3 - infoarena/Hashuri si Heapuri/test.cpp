#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("heapuri.in");
ofstream fout("heapuri.out");

int Len, nr;
int v[200010], heap[200010], poz[200010];

void Citire();
void Optiune1();
void Optiune2();
void Optiune3();
void push(int len);
void pop(int len);

int main()
{
    Citire();

    return 0;
}

void Citire()
{
    int n, optiune;
    fin >> n;
    for(int i = 1; i <= n; i++)
    {
        fin >> optiune;
        switch(optiune)
        {
            case 1:
                Optiune1();
                break;
            case 2:
                Optiune2();
                break;
            case 3:
                Optiune3();
                break;
        }
    }
}

void Optiune1()
{
    int x;
    fin >> x;
    Len++;
    nr++;
    v[nr] = x;
    heap[Len] = nr;
    poz[nr] = Len;
    push(Len);
}

void Optiune2()
{
    int x;
    fin >> x;
    v[x] = -1;
    push(poz[x]);
    poz[heap[1]] = 0;
    heap[1] = heap[Len--];
    poz[heap[1]] = 1;
    if(Len > 1)
        pop(1);
}

void Optiune3()
{
    fout << v[heap[1]] << "\n";
}

void push(int len)
{
    while(len / 2 && v[heap[len]] < v[heap[len / 2]])
    {
        swap(heap[len], heap[len / 2]);
        poz[heap[len]] = len;
        poz[heap[len / 2]] = len / 2;
        len /= 2;
    }
}

void pop(int len)
{
    int lg = 0;
    while(len != lg)
    {
        lg = len;
        if(lg * 2 <= Len &&v[heap[len]] > v[heap[lg * 2]])
            len = lg * 2;
        if(lg * 2 + 1 <= Len && v[heap[len]] > v[heap[lg * 2 + 1]])
            len = lg * 2 + 1;
        swap(heap[len], heap[lg]);
        poz[heap[len]] = len;
        poz[heap[lg]] = lg;
    }
}