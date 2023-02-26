#include <iostream>
using namespace std;

int main()
{
    int b = 100;
    int *a = new int[3];
    for(int i=0; i<3; i++)
    {
        *(a+i) = i;
        cout << *(a+i) << endl;
    }

    delete [] a;

    a = &b;
    cout << *a;
        
    /*int *a = new int();
    *a = b;
    //a = &b;
    *a = 99;

    cout << &a << endl << a << endl << *a << endl << &b << endl << b;

    if(a != NULL)
        delete a;
    a = NULL;*/
    
    return 0;
}