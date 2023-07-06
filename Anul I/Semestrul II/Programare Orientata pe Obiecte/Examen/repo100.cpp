/* 1.cpp 
#include <iostream>
using namespace std;
int f(int y)
{
    if (y < 0)
        throw y;
    return y / 2;
}
int f(int y, int z)
{
    if (y < z)
        throw z - y;
    return y / 2;
}
float f(int& y)
{
    cout <<" y este referinta";
    return (float)y / 2;
}
int main()
{
    int x;
    try {
        cout <<"Da - mi un numar par : ";
        cin >> x;
        if (x % 2)
            x = f(x, 0);
        else
            x = f(x);      // ambiguitate cu float f, nu se poate face diferenta doar dupa
                           // tipul parametrului sau intre tipuri care par diferite (int si int&)
        cout <<"Numarul "<< x <<" e bun !"<< endl;
    }
    catch (int i) {
        cout <<"Numarul "<< i <<" nu e bun !"<< endl;
    }
    return 0;
}
*/

/* 2.cpp
#include <iostream>
using namespace std;
class A {
    static int x;

public:
    A(int i = 0) { x = i; }
    int get_x() { return x; }
    int& set_x(int i) { x = i; }
    A operator=(A a1)
    {
        set_x(a1.get_x());
        return a1;
    }
};

int A::x;

int main()
{
    A a(212), b;
    cout << (b = a).get_x(); // 0 ca b updateaza valoarea lui x
    return 0;
}
*/


/* 3.cpp
#include<iostream>
using namespace std;
class A
{ int i;
  public: A(int x=2):i(x+1) {}
  virtual int get_i() { return i; }};
class B: public A
{ int j;
  public: B(int x=20):j(x-2) {}
  virtual int get_j() {return A::get_i()+j; }};
int main()
{ A o1(5);
  B o2;
  cout<<o1.get_i()<<" ";  
  cout<<o2.get_j()<<" ";
  cout<<o2.get_i();   // 6 21 3
  return 0;
}
*/

/* 4.cpp
#include <iostream>
class problema {
    int i;

public:
    problema(int j = 5) { i = j; }
    void schimba() { i++; }
    void afiseaza() { std::cout << "starea curenta " << i << "\n"; }
};
problema mister1() { return problema(6); }
void mister2(problema&& o) // eroare, vrea adresa unui rvalue, sterge & sau pune && pentru a lua adresa unui rvalue
{
    o.afiseaza();
    o.schimba();
    o.afiseaza();
}
int main()
{
    mister2(mister1());
    return 0;
}
*/

/* 5.cpp
 B D D2 MM

#include <iostream>
using namespace std;
class B {
    int i;

public:
    B() { i = 1; }
    virtual int get_i() { return i; }
};
class D : virtual public B {
    int j;

public:
    D() { j = 2; }
    int get_i() { return B::get_i() + j; }
};
class D2 : virtual public B {
    int j2;

public:
    D2() { j2 = 3; }
    int get_i() { return B::get_i() + j2; }
};
class MM : public D, public D2 {
    int x;

public:
    MM() { x = D::get_i() + D2::get_i(); }
    int get_i() { return x; }
};
int main()
{
    B* o = new MM();
    cout << o->get_i() << "\n";
    MM* p = dynamic_cast<MM*>(o);
    if (p)
        cout << p->get_i() << "\n";
    D* p2 = dynamic_cast<D*>(o);      // Face pointer ul de tip B* in D*, nu se schimba obiectul care e MM
    if (p2)
        cout << p2->get_i() << "\n";  // 7 7 7 
    return 0;
}
*/

/* 6.cpp
#include <iostream>
using namespace std;
class B {
    int x;   // merge si cu char, ori la una ori la ambele

public:
    B(int i = 7) { x = i; }
    int get_x() { return x; }
    operator int() { return x; }  // merge si cu char
};
class D : public B {
public:
    D(int i = -12)
        : B(i)
    {
    }
    D operator+(D a) { return get_x() + a.get_x() + 1; }
};
int main()
{
    D a;
    int b = 18;
    b += a;
    cout << b;  // 6
    return 0;
}
*/


/* 7.cpp 
#include <iostream>
#include <typeinfo>
using namespace std;

class B {
    int i;

public:
    B() { i = 1; }
    int get_i() { return i; }
};
// Mostenire private inseamna ca D nu poate fi considerat extensie a lui B
class D : B {
    int j;

public:
    D() { j = 2; }
    int get_j() { return j; }
};
int main()
{
    B* p = new D;    // Nu poate sa creeze new D (doar D d poate), tre public B la mostenire
    cout << p->get_i();
    if (typeid((B*)p).name() == "D*")
        cout << ((D*)p)->get_j();    
    return 0;
}
*/


/* 8.cpp  ???????????????????????????????????????????????????????????????????????????????????????
#include <iostream>
using namespace std;
class B {
protected:
    int x;

public:
    B(int i = 28) { x = i; }
    virtual B f(B ob) { return x + ob.x + 1; }   ?????
    void afisare() { cout << x; }
};
class D : public B {
public:
    D(int i = -32)
        : B(i)
    {
    }
    B f(B ob) { return x + ob.x - 1; }    // Nu are acces la x pt ca ob e de tip B, tre de tip D ca sa l mosteneasca protected
};
int main()
{
    B *p1 = new D, *p2 = new B, *p3 = new B(p1->f(*p2));
    p3->afisare();
    return 0;
}
*/


/* 9.cpp
#include <iostream>
using namespace std;
class B {
protected:
    static int x;
    int i;

public:
    B()
    {
        x++;
        i = 1;
    }
    ~B() { x--; }
    static int get_x() { return x; }
    int get_i() { return i; }
};
int B::x;
class D : public B {
public:
    D() { x++; }
    ~D() { x--; }
};
int f(B* q)
{
    return (q->get_x()) + 1;
}
int main()
{
    B* p = new B[10];
    cout << f(p) << ' ';
    delete[] p;
    p = new D;
    cout << f(p) << ' ';
    delete p;
    cout << D::get_x() << ' ';
    return 0;
}
*/

/* 10.cpp
#include <iostream>
using namespace std;
template <class T, class U>
T f(T x, U y)
{
    return x + y;
}
int f(int x, int y)
{
    return x - y;
}
int main()
{
    int *a = new int(3), b(23);
    cout << *f(a, b);     // Ceva random, se duce la o adresa cu 23 de bytes mai mare decat era a
    return 0;
}
*/

// // 11.cpp
// #include <iostream>
// using namespace std;
// class A {
//     int x;

// public:
//     A(int i = 0) { x = i; }
//     A operator+(const A& a) { return x + a.x; }
//     template <class T>
//     ostream& operator<<(ostream&);
// };
// template <class T>
// ostream& A::operator<<(ostream& o)
// {
//     o << x;
//     return o;
// }
// int main()
// {
//     A a1(33), a2(-21);
//     cout << a1 + a2;         // nu i bine definit operatorul <<
//     // (a1+a2).operator<<<A>(cout);  rezolvare
//     return 0;
// }


// // 12.cpp
// #include <iostream>
// using namespace std;
// class cls {
//     int x;

// public:
//     //cls() {x = 0;}
//     cls(int i) { x = i; }
//     int set_x(int i)
//     {
//         int y = x;
//         x = i;
//         return y;
//     }
//     int get_x() { return x; }
// };
// int main()
// {
//     cls* p = new cls[10];     // nu exista constructor default; rezolvare: punem cls(i = 0) {...}
//     int i = 0;
//     for (; i < 10; i++)
//         p[i].set_x(i);
//     for (i = 0; i < 10; i++)
//         cout << p[i].get_x();
//     return 0;
// }


/* 13.cpp
#include <iostream>
using namespace std;
int f(int y)
{
    try {
        if (y > 0)
            throw y;
    }
    catch (int i) {
        throw;
    }
    return y - 2;
}
int f(int y, int z)
{
    try {
        if (y < z)
            throw z - y;
    }
    catch (int i) {
        throw;
    }
    return y + 2;
}
float f(float& y)
{
    cout << " y este referinta";
    return (float)y / 2;
}
int main()
{
    int x;
    try {
        cout << "Da-mi un numar par: ";
        cin >> x;
        if (x % 2)
            x = f(x, 0);
        else
            x = f(x);
        cout << "Numarul " << x << " e bun!" << endl;
    }
    catch (int i) {
        cout << "Numarul " << i << " nu e bun!" << endl;
    }
    return 0;
}
// par > 0 nu e bun, par < 0 e bun, impar > 0 e bun, impar < 0 nu e bun
*/

// // 14.cpp 
// #include <iostream>
// using namespace std;
// class A {
//     int x;

// public:
//     A(int i) { x = i; }
//     int get_x() { return x; }
//     int& set_x(int i) { x = i; }
//     A operator=(A a1)
//     {
//         set_x(a1.get_x());
//         return a1;
//     }
// };
// class B : public A {
//     int y;

// public:
//     B(int i)
//         : A(i)
//     {
//         y = i;
//     }
//     void afisare() { cout << y; }
// };
// int main()
// {
//     B a(112), b, *c;          // nu exista constructori default => nu se poate crea b
//     cout << (b = a).get_x();
//     (c = &a)->afisare();     // dupa ce facem constructori default: 112112
//     return 0;
// }

/* 15.cpp
#include <iostream>
using namespace std;
struct cls {
    int x;

public:
    int set_x(int i)
    {
        int y = x;
        x = i;
        return x;
    }
    int get_x() { return x; }
};
int main()
{
    cls* p = new cls[100];
    int i = 0;
    for (; i < 50; i++)
        p[i].set_x(i);
    for (i = 5; i < 20; i++)
        cout << p[i].get_x() << " ";     // 5 6 ... 19
    return 0;
}
*/

/* 16.cpp
#include <iostream>
using namespace std;
class A {
protected:
    int x;

public:
    A(int i = 14) { x = i; }
};
class B : A {
public:
    B()
        : A(2)
    {
    }
    B(B& b) { x = b.x - 14; }
    void afisare() { cout << x; }
};
int main()
{
    B b1, b2(b1);       // b1 o sa aiba x = 2 si b2 x = 2 - 14 = -12
    b2.afisare();       // -12
    return 0;
}
*/

/* 17.cpp
#include <iostream>
using namespace std;
class A {
protected:
    static int x;

public:
    A(int i = 0) { x = i;}
    virtual A schimb() { return (7 - x); }
};
class B : public A {
public:
    B(int i = 0) { x = i; }
    void afisare() { cout << x; }
};
int A::x = 5;
int main()
{
    A* p1 = new B(18);
    *p1 = p1->schimb(); 
    ((B*)p1)->afisare();        // -11
    return 0; 
}
*/

// // 18.cpp
// #include <iostream>
// using namespace std;
// template <class T, class U>
// T fun(T x, U y)         // intra aici si aduna y la x (care e pointer)
// {
//     return x + y;
// }
// int fun(int x, int y)
// {
//     return x - y;
// }
// int fun(int x)
// {
//     return x + 1;
// }
// int main()
// {
//     int *a = new int(10), b(5);
//     cout << fun(a, b);            // o adresa 
//     return 0;
// }

/* 19.cpp
p1 x = -16, x = -15
p2 x = 12
p3 x = -17

#include <iostream>
using namespace std;
class B {
protected:
    int x;

public:
    B(int i = 12) { x = i; }
    virtual B f(B ob) { return x + ob.x + 1; }
    void afisare() { cout << x; }
};
class D : public B {
public:
    D(int i = -15)
        : B(i - 1)
    {
        x++;
    }
    B f(B ob) { return x - 2; }        // returneaza x ul lui this nu al lui ob
};
int main()
{
    B *p1 = new D, *p2 = new B, *p3 = new B(p1->f(*p2));
    p3->afisare();         // -17
    return 0;
}
*/

// // 20.cpp 
// #include <iostream>
// using namespace std;
// struct B {
//     int i;

// public:
//     B() { i = 1; }
//     virtual int get_i() { return i; }
// } a;
// class D : virtual public B {
//     int j;

// public:
//     D() { j = 2; }
//     int get_i() { return B::get_i() + j; }
// };
// class D2 : virtual public B {
//     int j2;

// public:
//     D2() { j2 = 3; }
//     int get_i() { return B::get_i() + j2; }
// };
// class MM : public D2, public D {
//     int x;

// public:
//     MM() { x = D::get_i() + D2::get_i(); }
//     int get_i() { return x; }
// };
// {
//     MM b;                         // eroare aici, ori stergem {} ori tot
// }
// int main()
// {
//     B* o = new MM();
//     cout << o->get_i() << "\n";
//     MM* p = dynamic_cast<MM*>(o);
//     if (p)
//         cout << p->get_i() << "\n";
//     D* p2 = dynamic_cast<D*>(o);
//     if (p2)
//         cout << p2->get_i() << "\n";       // dupa corectare: 7 7 7
//     return 0; 
// }

// // 21.cpp
// // e1
// // A x = -13
// // B x = 10
// // D x = 5
// // C x = -17
// // E y = -17 + 5 + 10 = -2

// // e2
// // x = -17
// // y = -15

// #include <iostream>
// using namespace std;
// class A {
// public:
//     int x;
//     A(int i = -13) { x = i; cout << "A "; }
// };
// class B : virtual public A {
// public:
//     B(int i = -15) { x = i; cout << "B "; }
// };
// class C : virtual public A {
// public:
//     C(int i = -17) { x = i; cout << "C "; }
// };
// class D : virtual public A {
// public:
//     D(int i = -29) { x = i; cout << "D "; }
// };
// class E : public B, public D, public C {
// public:
//     int y;
//     E(int i, int j)
//         : D(i)
//         , B(j)
//     {
//         y = x + i + j;
//         cout << "E ";
//     }
//     E(E& ob) { y = ob.x - ob.y; }
// };
// int main()
// {
//     E e1(5, 10), e2 = e1;
//     cout << e2.y;         // -15
//     return 0;
// }


/* 22.cpp
#include <iostream>
#include <typeinfo>
using namespace std;
class B {
    int i;

public:
    B(int x) { i = x + 1; }
    int get_i() { return i; }
};
class D : public B {
    int j;

public:
    D()
        : B(1)
    {
        j = i + 2;                // i e privat, il facem protected
    }
    int get_j() { return j; }
};
int main()
{
    B* p = new D[10];
    cout << p->get_i();                 // 2
    if (typeid((B*)p).name() == "D*")   // aici n o sa intre niciodata
        cout << ((D*)p)->get_j(); 
    return 0;
}
*/

/* 23.cpp 
#include <iostream>
using namespace std;
class B {
protected:
    static int x;
    int i;

public:
    B()
    {
        x++;
        i = 1;
    }
    ~B() { x--; }
    static int get_x() { return x; }
    int get_i() { return i; }
};
int B::x;
class D : public B {
public:
    D()
    {
        x++;
        i++;
    }
    ~D()
    {
        x--;
        i--;
    }
    int f1(B o) { return 5 + get_i(); }
};
int f(B* q)
{
    return (q->get_x()) + 1;
}
int main()
{
    B* p = new B[10];
    cout << f(p);
    delete[] p;
    p = new D;
    //cout << ((D*)p)->f1(*p);
    cout << p->f1(p);            // B nu are f1
    delete p;
    cout << D::get_x();         // dupa corectat 1170
    return 0;
}
*/

/* 26.cpp 
#include <iostream>
using namespace std;
class A {
protected:
    int x;

public:
    A(int i = 14) { x = i; }
};
class B : A {
public:
    B()
        : A(2)
    {
    }
    B(B& b) { x = b.x - 14; }
    void afisare() { cout << x; }
};
int main()
{
    B b1, b2(b1);
    b2.afisare();      // -12
    return 0;
}
*/

/* 27.cpp 
#include <iostream>
using namespace std;
class B {
    int i;

public:
    B() { i = 1; }
    virtual int get_i() { return i; }
};
class D : public B {
    int j;

public:
    D() { j = 2; }
    int get_i() { return B::get_i() + j; }
};
int main()
{
    const int i = cin.get();
    if (i % 3) {
        D o;
        //cout << o.get_i();
    }
    else {
        B o;
        //cout << o.get_i();
    }
    cout << o.get_i();  // iese o din scope
    return 0;
}
*/

/* 32.cpp 
#include <iostream>
using namespace std;
class B {
protected:
    int x;

public:
    B(int i = 28) { x = i; }
    virtual B f(B ob) { return x + ob.x + 1; }
    void afisare() { cout << x; }
};
class D : public B {
public:
    D(int i = -32)
        : B(i)
    {
    }
    B f(B ob) { return x + ob.x - 1; }  // inaccesibil
    // D f(D ob) { return x + ob.x - 1; } sau public la int x
};
int main()
{
    B *p1 = new D, *p2 = new B, *p3 = new B(p1->f(*p2));
    p3->afisare();
    return 0;
}
*/

/* 35.cpp 
#include <iostream>
using namespace std;
class A {
    int x;

public:
    A(int i = 0) { x = i; }
    A operator+(const A& a) { return x + a.x; }
    template <class T>
    ostream& operator<<(ostream&);
};
template <class T>
ostream& A::operator<<(ostream& o)
{
    o << x;
    return o;
}
int main()
{
    A a1(33), a2(-21);
    cout << a1 + a2;
    //(a1+a2).operator<< <A>(cout);       // 12    
    return 0;
}
*/

/* 36.cpp 
#include <iostream>
using namespace std;
class cls {
    int x;

public:
    // cls(int i = 0) { x = i; } 0123456789
    cls(int i) { x = i; }
    int set_x(int i)
    {
        int y = x;
        x = i;
        return y;
    }
    int get_x() { return x; }
};
int main()
{
    cls* p = new cls[10]; 
    int i = 0;
    for (; i < 10; i++)
        p[i].set_x(i);
    for (i = 0; i < 10; i++)
        cout << p[i].get_x();
    return 0;
}
*/

/* 37.cpp 
#include<iostream>
using namespace std;
class A
{
    int i;
    protected: static int x;
    public: A(int j=7) {i=j;x=j;}
    int get_x() {return x;}
    int set_x(int j) {int y=x; x=j; return y;}
    A operator=(A a1) {set_x(a1.get_x()); return a1;}
};
int A::x=15;
int main()
{
    A a(212),b;
    cout<<(b=a).get_x();        // 7 ca e static
    return 0;
}
*/ 

/* 38.cpp 
#include<iostream>
using namespace std;
template<class X, class Y>
X f(X x, Y y)
{
    return x+y;
}
int* f(int *x,int y)
{
    return x-y;
}
int main()
{
    int *a=new int(200), *b=a; // b = *a sau *f(a, *b)

    cout<< *f(a,b);  // nu poti sa aduni pointeri, faci sa intre pe a doua functie
    return 0;
}
*/

/* 39.cpp 
#include<iostream>
using namespace std;
template<class X>void test(X &a, X &b)
{
    X temp;
    temp=a;
    a=b;
    b=temp;
    cout<<"ttest\n";
}
void test(int &c,int &d)
{
    int temp;
    temp=c;
    c=d;
    d=temp;
    cout<<"test 1\n";
}
void test(int e,int f)
{
    int temp;
    temp=e;
    e=f;
    f=temp;
    cout<<"test 2\n";
}
void test(int g,int *h)
{
    int temp;
    temp=g;
    g=*h;
    *h=temp;
    cout<<"test 3\n";
}
int main()
{
    int a=5,b=15,c=25,*d=&a;
    test(a,b);        // ambiguitate, stergem test 2 => test 1 test 3
    test(c,d);
    return 0;
}
*/

/* 40.cpp 
#include<iostream>
using namespace std;
class A
{
    int valoare;
    public: A(int param1=3):valoare(param1){}
    int getValoare(){return this->valoare;}
};
int main()
{
    A vector[]={*(new A(3)),*(new A(4)),*(new A(5)),*(new A(6)) };
    cout<<vector[2].getValoare();
    return 0;
}
*/

/* 44.cpp 
#include<iostream>
using namespace std;
class cls
{
    int x;
public:
        cls(int i=0) {cout<<" c1 "; x=i;}
        ~cls() {cout<<" d 1 ";}
};
class cls1
{
    int x; 
    cls xx;
public:
        cls1(int i=0){cout<<" c2 ";x=i;}
        ~cls1(){cout<<" d2 ";}
}c;
class cls2
{
    int x;
    cls1 xx;
    cls xxx;
public:
    cls2(int i=0) {cout<<" c3 ";x=i;}
    ~cls2(){ cout<<" d3 ";}
};
int main()
{
    cls2 s;
    return 0;
}
// c1  c2  c1  c2  c1  c3  d3  d 1  d2  d 1  d2  d 1 
*/ 

/* 45.cpp 
#include<iostream>
using namespace std;
class cls
{
    int x;
public: cls(int i=3) {x=i;}
    int &f() const{ return x;}   // metoda const => x const, nu poti sa iei cu & pt ca ulterior ar
                                 // putea sa l schimbe
    // int f() const{ return x;}
    // const int &f() const{ return x;}
};
int main()
{
    const cls a(-3);
    int b=a.f();
    cout<<b;
    return 0;
}
*/

/* 46.cpp
#include<iostream>
using namespace std;
class B
{
    protected: int x;
    public: B(int i=0) {x=i;}
    virtual B minus() {return (1-x);}
};
class D: public B
{
    public: D(int i=0):B(i) {}
    void afisare() {cout<<x;}
};
int main()
{
    D *p1=new D(18);
    //B *p1 = new D(18);
    *p1=p1->minus();   // Nu exista operator = dintre D si B, il facem pe p1 B* => -17
    p1->afisare();
    // ((D*)p1)->afisare();
    return 0;
}
*/

/* 47.cpp  
#include <iostream>
using namespace std;
class cls1 {
  int x;
public:
  cls1 () {
    x = 13;
  }
  int g() {
    static int i; i++; 
    return (i+x);
  }
};

class cls2 {
  int x;
public:
  cls2() {
    x = 27;
  }
  cls1& f() {
     cls1 ob; return ob;
  }
};

int main() {
  cls2 ob;
  cout << ob.f().g();   // da warning to reference to temporary si moare in timp ce se
                        // executa ca se sterge obiectul, returnam cls1 in loc de cls1& => 14
  return 0;
}
*/

/* 48.cpp 
#include <iostream>
using namespace std;
class cls1
{ protected: int x;
public:    cls1(int i=10) { x=i; }
	int get_x() { return x;} };
class cls2: cls1    // nu merge ca i mostenirea privata, o facem publica => 37
{ public: cls2(int i):cls1(i) {} }; int main()
{ cls2 d(37);
	cout<<d.get_x();
	return 0; }
*/

/* 49.cpp
#include <iostream>
using namespace std; 
class cls
{ int x;
public: 
    cls(int y) {x=y; }
	friend int operator*(cls a,cls b){return (a.x*b.x); } };  // e friend nu membru deci sunt ok 2 parametri
int main()
{ cls m(100),n(15);
	cout << m*n;     // 1500
return 0; }
*/


// // 50
// #include <iostream>
// using namespace std;
// class B
// { int i;
// public: B() { i=1; cout<<"B ";}
//     virtual int get_i() { return i; } };
// class D: virtual public B
// { int j;
// public: D() { j=2; cout<<"D ";}
//     int get_i() {return B::get_i()+j; } };
// class D2: virtual public B
// { int j2;
// public: D2() { j2=3; cout<<"D2 "; }
//     int get_i() {return B::get_i()+j2; } };
// class MM: public D, public D2
// { int x;
// public: MM() { x=D::get_i()+D2::get_i();cout<<"MM \n"; }
//     int get_i() {return x; } };
// int main()
// { B *o= new MM();
//     cout<<o->get_i()<<"\n";
//     MM *p= dynamic_cast<MM*>(o);
//     if (p) cout<<p->get_i()<<"\n";
//     D *p2= dynamic_cast<D*>(o);
//     if (p2) cout<<p2->get_i()<<"\n";
//     return 0;
// }
// // B D D2 MM
// // 7 7 7


// // 51
// #include <iostream>
// #include <typeinfo>
// using namespace std;

// class B
// { int i;
//   public: B() { i=1; }
//           int get_i() { return i; }
// };
// class D: public B
// { int j;
//   public: D() { j=2; }
//           int get_j() {return j; }
// };
// int main()
// { B *p=new D;
//   cout<<p->get_i();
//   if (typeid((B*)p).name()=="B") cout<<((D*)p)->get_j();
//   return 0;
// }
// // 1


// // 52
// #include <iostream>
// using namespace std;
// class B
// { protected: static int x;
//              int i;
//   public: B() { x++; i=1; }
//           ~B() { x--; cout << "b";}
//           int get_x() { return x; }
//           int get_i() { return i; } };
// int B::x;
// class D: public B
// { public: D() { x++; }
//           ~D() { x--; cout << "d";} };
// int f(B *q)
// { return (q->get_x())+1; }
// int main()
// { B *p=new B[10];
//   cout<<f(p);
//   delete[] p;
//   p=new D;
//   cout<<f(p);
//   delete p;
  
//   cout<<D::get_x();     // o functie nestatica trebuie apelata dintr-un obiect
//                         // rezolvare: facem static int get_x()
//   return 0;
// }


// // 53
// #include <iostream>
// using namespace std;
// class cls
// { int x;
//   public: cls(int i) { x=i; }
//   int set_x(int i) { int y=x; x=i; return y; }
//   int get_x(){ return x; } };
// int main()
// { cls *p=new cls[10];   	// nu exista constructorul default
//                             // rezolvare: facem cls(int i = 0)
//   int i=0;
//   for(;i<10;i++) p[i].set_x(i);
//   for(i=0;i<10;i++) cout<<p[i].get_x();
//   return 0;
// }


// // 56
// #include <iostream>
// using namespace std;
// class cls1 {
//   int x;
// public:
//   cls1 () {
//     x = 13;
//   }
//   int g() {
//     static int i; i++; 
//     return (i+x);   // aici da segfault
//   }
// };

// class cls2 {
//   int x;
// public:
//   cls2() {
//     x = 27;
//   }
//   cls1 f() {
//      cls1 ob; return ob;
//   }
// };

// int main() {
//   cls2 ob;
//   cout << ob.f().g();   // f returneaza o referinta catre un obiect creat in f care dupa ce f se termina se sterge
//                         // funcia g se cheama dintr-o "dangling reference" => comportament nedefinit
//                         // rezolvare: facem f sa returneza un obiect cls1 f() {...}
//   return 0;
// }


// // 57
// #include <iostream>
// using namespace std;

// class D;

// class B {
//     int x;
//     friend void f(B, D);

// public:
//     B(int i = 0) { x = i; }
// };

// class D : public B {
// public:
//     int y;
//     D(int i = 0, int j = 0)
//         : B(i)
//     {
//         y = j;
//     }
// };

// void f(B b, D d) { cout << b.x << " " << d.y; }

// void main()     // main trebuie sa returneze int
// {
//     B b;
//     D d;
//     f(b, d);    // merge pt ca funtiile friend pot fi declarate si private si protected si public
//                 // afiseaza 0 0
// }


// 58 - exact la fel ca 57


// // 59 ????????????????????????????????????????????????????????????????????????????? - da ciudat dupa corecturi
// #include <iostream>
// using namespace std;

// class B {
// protected:
//     int x;

// public:
//     B(int v) { v = x; }
//     int get_x() { return x; }
// };

// class D : private B {
//     int y;

// public:
//     D(int v)
//         : B(v)
//     {
//     }
//     int get_x() { return x; }   // x e inaccesibil pt ca e private in B
//                                 // rezolvare: il facem pe x protected in B
// };

// int main()
// {
//     D d(10);
//     cout << d.get_x();
// }


// // 60
// #include <iostream>
// using namespace std;

// class cls {
// public:
//     float sa;
//     cls(float s = 0) { sa = s; }
//     operator float() { return sa; }
//     float f(float c) { return (sa * (1 + c / 100)); }
// };

// int main()
// {
//     cls p(100);
//     cout << p.f(p);
// }
// // 200


// // 61
// #include <iostream>
// using namespace std;

// class cls {
//     int vi;

// public:
//     cls(int v = 18) { vi = v; }
//     operator int() { return vi; }
//     cls operator++()
//     {
//         vi++;
//         return *this;
//     }
//     cls operator++(int);
// };

// cls cls::operator++(int)
// {
//     cls aux = *this;
//     vi++;
//     return aux;
// }

// int main()
// {
//     cls p(20);
//     int x = p++, y = ++p;
//     cout << "x=" << x << ", y=" << y << endl;
// }
// // 20 22


// 62 - la fel ca 61


// // 63
// #include <iostream>
// using namespace std;

//     class cls {
// public:
//     int x;
//     cls() { x = 3; }
//     void f( cls& c) { cout << c.x; }
// };

// int main()
// {
//     const cls d;
//     f(d);   // nu asa se apeleaza f - f is undefined
//             // rezolvare: void f(const cls& c) const { cout << c.x; } ca sa putem apela din obiect const cu parametru ob const
//             // apelare: d.f(d);
//     // d.f(d);
// }


// // 64
// #include <iostream>
// using namespace std;

// class cls {
// public:
//     int x, y;
//     cls(int i = 0, int j = 0)
//     {
//         x = i;
//         y = j;
//     }
// };

// int main()
// {
//     cls a, b, c[3] = { cls(1, 1), cls(2, 2), a };
//     cout << c[2].x;
// }
// // 0


// // 65
// #include <iostream>
// using namespace std;

// class vector {
//     int *p, nr;

// public:
//     operator int() { return nr; }
//     vector(int);
// };

// vector::vector(int n)
// {
//     p = new int[n];
//     nr = n;
//     while (n--)
//         p[n] = n;
// }

// void f(int i)
// {
//     while (i--)
//         cout << i << endl;
// }

// int main()
// {
//     vector x(10);
//     f(x);
// }
// // 9 8 ... 0


// // 67
// #include <iostream>
// using namespace std;

// class Y;

// class Z;

// class X {
//     int x;

// public:
//     X(int n = 0) { x = n; }
//     friend Y;
// };

// class Y {
//     int y;
//     friend Z;
// };

// class Z {
// public:
//     void f(X u) { cout << u.x; }    // x e privat 
//                                     // rezolvare: facem pe x public
// };

// int main()
// {
//     X a;
//     Z b;
//     b.f(a);
// }


// // 68
// #include <iostream>
// using namespace std;

// class cls2;

// class cls1 {
// public:
//     int vi;
//     cls1(int v = 30) { vi = v; }
//     cls1(cls2 p) { vi = p.vi; }     // p has incomplete type - trebuie toata definitia clasei cls2 inainte sa declari un ob de tip cls2
// };

// class cls2 {
// public:
//     int vi;
//     cls2(int v = 20) { vi = v; }
// };

// cls1 f(cls1 p)
// {
//     p.vi++;
//     return p;
// }

// int main()
// {
//     cls1 p;
//     f(p);
//     cout << endl
//          << p.vi;
//     cls2 r;
//     f(r);
//     cout << endl
//          << r.vi;
// }


// // 70
// #include <iostream>
// using namespace std;
// class cls1 {
// protected:
//     int x;

// public:
//     cls1() { x = 13; }
// };
// class cls2 : public cls1 {
//     int y;

// public:
//     cls2() { y = 15; }
//     int f(cls2 ob) { return (ob.x + ob.y); }
// };
// int main()
// {
//     cls2 ob;
//     cout << ob.f(ob);
//     return 0;
// }
// // 28


// // 71
// #include <iostream>
// using namespace std;
// class cls1 {
//     int x;

// public:
//     cls1() { x = 13; }
//     int g()
//     {
//         static int i;
//         i++;
//         return (i + x);
//     }
// };
// class cls2 {
//     int x;

// public:
//     cls2() { x = 27; }
//     cls1& f()
//     {
//         static cls1 ob;
//         return ob;
//     }
// };
// int main()
// {
//     cls2 ob;
//     cout << ob.f().g();     // aici merge si sa returnezi referinta din f pt ca ob e static
//     return 0;
// }
// // 14


// // 72
// #include <iostream>
// using namespace std;
// class cls1 {
// protected:
//     int x;

// public:
//     cls1(int i = 10) { x = i; }
//     int get_x() { return x; }
// };
// class cls2 : cls1 {
// public:
//     cls2(int i)
//         : cls1(i)
//     {
//     }
// };
// int main()
// {
//     cls2 d(37);  // cls? probabil cls2
//     cout << d.get_x();  // get_x e privat - nu se poate accesa
//                         // rezolvare: facem mostenirea public
//     return 0;
// } 


// // 73
// #include <iostream>
// using namespace std;

// class B {
// public:
// 	int x;
// 	B(int i = 16) { x = i; }
// 	B(){}
// 	B f(B ob) { return x + ob.x; }
// };
// class D : public B {
// public:
// 	D(int i = 25) { x = i; }    // eroare
// 	B f(B ob) { return x + ob.x + 1; }
// 	void afisare() { cout << x; }
// };
// int main()
// {
// 	B *p1 = new D, *p2 = new B, *p3 = new B(p1->f(*p2));    // eroare - B are mai multi constructori default
//                                                             // rezolvare: B(int i)
// 	cout << p3->x;
// 	return 0;
// }


// // 74 ??????????????????????????????????????????????????????????????????????????????????????? - cum corectez
// #include <iostream>
// using namespace std;
// class cls {
//     int vi;

// public:
//     cls(int v = 37) { vi = v; }
//     friend int& f(cls);
// };
// int& f(cls c) { return c.vi; }
// int main()
// {
//     const cls d(15);
//     f(d) = 8;   // segfault - intoarce referinta catre obiect temporar
//     cout << f(d);
//     return 0;
// }


// // 75
// #include <iostream>
// using namespace std;
// class cls1 {
// public:
//     int x;
//     cls1(int i = 20) { x = i; }
// };
// class cls2 {
// public:
//     int y;
//     cls2(int i = 30) { y = i; }
//     operator cls1()
//     {
//         cls1 ob;
//         ob.x = y;
//         return ob;
//     }
// };
// cls1 f(cls1 ob)
// {
//     ob.x++;
//     return ob;
// }
// int main()
// {
//     cls1 ob1;
//     f(ob1);
//     cout << ob1.x;
//     cls2 ob2;
//     f(ob2);
//     cout << ob2.y;
//     return 0;
// }
// // 20 30


// // 76
// #include <iostream>
// using namespace std;
// class cls {
//     int x;

// public:
//     cls(int i = 25) { x = i; }
//     int f();
// };
// int cls::f() { return x; }
// int main()
// {
//     const cls d(15);
//     cout << d.f();  // un ob const nu poate apela o functie neconst
//                     // rezolvare: facem f const
//     return 0;
// }


// // 77
// #include <iostream>
// using namespace std;
// template <class tip>
// tip dif(tip x, tip y)
// {
//     return x - y;
// }
// unsigned dif(unsigned x, unsigned y)
// {
//     return x >= y ? x - y : y - x;
// }
// int main()
// {
//     unsigned i = 7, j = 8;
//     cout << dif(i, j);
//     return 0;
// }
// // 1


// 78 - nu exista


// // 79
// #include <iostream>
// using namespace std;
// class B {
//     int x;

// public:
//     B(int i = 2)
//         : x(i)
//     {
//     }
//     int get_x() const { return x; }
// };
// class D : public B {
//     int* y;

// public:
//     D(int i = 2)
//         : B(i)
//     {
//         y = new int[i];
//         for (int j = 0; j < i; j++)
//             y[j] = 1;
//     }
//     D(D& a)
//     {
//         y = new int[a.get_x()];
//         for (int i = 0; i < a.get_x(); i++)
//             y[i] = a[i];
//     }
//     int& operator[](int i) const { return y[i]; }
// };
// ostream& operator<<(ostream& o, const D& a)
// {
//     for (int i = 0; i < a.get_x(); i++)
//         o << a[i];  // ob const a nu poate apela operatorul neconst []
//                     // rezolvare: facem const [] => 11111
//     return o;
// }
// int main()
// {
//     D ob(5);
//     cout << ob;
//     return 0;
// }


// // 80
// #include <iostream>
// using namespace std;
// class B {
//     int x;

// public:
//     B(int i = 10) { x = i; }
//     int get_x() { return x; }
// };
// class D : public B {
// public:
//     D(int i)
//         : B(i)
//     {
//     }
//     D operator+(const D& a) { return x + a.x; }     // x e privat, nu poate fi accesat
//                                                     // rezolvare: facem x public/protected => -5
// };
// int main()
// {
//     D ob1(7), ob2(-12);
//     cout << (ob1 + ob2).get_x();
//     return 0;
// }


// // 81
// #include <iostream>
// using namespace std;
// class B {
// public:
//     int x;
//     B(int i = 16) { x = i; }
//     B f(B ob) { return x + ob.x; }
// };
// class D : public B {
// public:
//     D(int i = 25) { x = i; }
//     B f(B ob) { return x + ob.x + 1; }
//     void afisare() { cout << x; }
// };
// int main()
// {
//     B *p1 = new D, *p2 = new B, *p3 = new B(p1->f(*p2));
//     cout << p3->x;
//     return 0;
// }
// // 41


// // 82
// #include <iostream>
// using namespace std;
// class cls {
//     int *v, nr;

// public:
//     cls(int i)
//     {
//         nr = i;
//         v = new int[i];
//         for (int j = 1; j < nr; j++)
//             v[j] = 0;
//     }
//     int size() { return nr; }
//     int& operator[](int i) { return *(v + i); }
// };
// int main()
// {
//     cls x(10);
//     x[4] = -15;
//     for (int i = 0; i < x.size(); i++)
//         cout << x[i] << " ";
//     return 0;
// }
// // random 0 0 0 -15 0 0 0 0 0


// // 83
// #include <iostream>
// using namespace std;
// class cls {
//     int x;

// public:
//     cls(int i = -20) { x = i; }
//     const int& f() { return x; }
// };
// int main()
// {
//     cls a(14);
//     int b = a.f()++;    // nu putem modifica const int&
//                         // rezolvareL a.f() + 1 => 15 sau scoatem const
//     cout << b;
//     return 0;
// }


// // 84
// #include <iostream>
// using namespace std;
// class B {
//     static int x;
//     int i;

// public:
//     B()
//     {
//         x++;
//         i = 1;
//     }
//     ~B() { x--; }
//     static int get_x() { return x; }
//     int get_i() { return i; }
// };
// int B::x;
// class D : public B {
// public:
//     D() { x++; }    // x e privat, nu poate fi accesat de D
//                     // rezolvare: facem x protected => 221
//     ~D() { x--; }
// };
// int f(B* q)
// {
//     return (q->get_i()) + 1;
// }
// int main()
// {
//     B* p = new B;
//     cout << f(p);
//     delete p;
//     p = new D;
//     cout << f(p);
//     delete p;
//     cout << D::get_x();
//     return 0;
// }


// // 85
// #include <iostream>
// using namespace std;
// class B {
//     int x;

// public:
//     B(int i = 17) { x = i; }
//     int get_x() { return x; }
//     operator int() { return x; }
// };
// class D : public B {
// public:
//     D(int i = -16)
//         : B(i)
//     {
//     }
// };
// int main()
// {
//     D a;
//     cout << 27 + a;
//     return 0;
// }
// // 11

// // 86
// #include <iostream>
// using namespace std;
// class cls {
//     static int x;

// public:
//     cls(int i = 1) { x = i; }
//     cls f(cls a) { return x + a.x; }
//     static int g() { return f() / 2; }  // o metoda statica nu poate folosi o metota nestatica
//                                         // rezolvare: stergem static, apelam ob.g(), apoi sunt problemele ca nu avem cast
// };
// int cls::x = 7;
// int main()
// {
//     cls ob;
//     cout << cls::g();
//     return 0;
// }


// // 87
// #include <iostream>
// using namespace std;
// class cls {
//     int *v, nr;

// public:
//     cls(int i = 0)
//     {
//         nr = i;
//         v = new int[i];
//         for (int j = 0; j < size(); j++)
//             v[j] = 3 * j;
//     }
//     ~cls() { delete[] v; }  // segfault pt ca se sterge de 2 ori aceeasi memorie
//     int size() { return nr; }
//     int& operator[](int i) { return v[i]; }
//     cls operator+(cls);
// };
// cls cls::operator+(cls y)
// {
//     cls x(size());
//     for (int i = 0; i < size(); i++)
//         x[i] = v[i] + y[i];
//     return x;
// }
// int main()
// {
//     cls x(10), y = x, z;
//     x[3] = y[6] = -15;
//     z = x + y;
//     for (int i = 0; i < x.size(); i++)
//         cout << z[i] << " ";
//     return 0;
// }
// // operatorul de atribuire e cel default => bit cu bit
// // x+y este un obiect temporar care se distruge dupa ce e returnat o copie a lui si pt ca z copiaza bit cu bit
// // o sa fie 10 chestii random in v-ul lui z


// // 88
// #include <iostream>
// using namespace std;
// class B {
//     int i;

// public:
//     B() { i = 1; }
//     int get_i() { return i; }
// };
// class D : public B {
//     int j;

// public:
//     D() { j = 2; }
//     int get_j() { return j; }
// };
// int main()
// {
//     B* p;
//     int x = 0;
//     if (x)
//         p = new B;
//     else
//         p = new D;
//     if (typeid(p).name() == "D*")
//         cout << ((D*)p)->get_j();
//     return 0;
// }
// // nu afiseaza nimic


// // 89
// #include <iostream>
// using namespace std;
// class cls {
//     int x;

// public:
//     cls(int i) { x = i; }
//     int set_x(int i)
//     {
//         int y = x;
//         x = i;
//         return y;
//     }
//     int get_x() { return x; }
// };
// int main()
// {
//     cls* p = new cls[10];   // nu exista constr default
//     int i = 0;
//     for (; i < 10; i++)
//         p[i].set_x(i);
//     for (i = 0; i < 10; i++)
//         cout << p[i].get_x(i);
//     return 0;
// }


// // 90
// #include <iostream>
// using namespace std;
// template <class T>
// int f(T x, T y)
// {
//     return x + y;
// }
// int f(int x, int y)
// {
//     return x - y;
// }
// int main()
// {
//     int a = 5;
//     float b = 8.6;
//     cout << f(a, b);
//     return 0;
// }
// // -3


// // 91
// #include <iostream>
// using namespace std;

// class A
// {
// 	int x;
// public:
// 	A(int i = 25) { x = i; }
// 	int& f() const { return x; }    // x e const aici, nu poate fi returnata o referinta la x
//                                     // rezolvare: scoatem & sau const sau punem const int&
// };
// int main()
// {
// 	A ob(5);
// 	cout << ob.f();
// 	return 0;
// }


// // 92
// #include <iostream>
// using namespace std;

// class A
// {
// 	int x;
// public:
// 	A(int i = 0):x(i){}
// 	int get_x() const { return x; }
// };
// class B : public A
// {
// 	int *y;
// public:
// 	B(int i) :A(i)
// 	{
// 		y = new int[i];
// 		for (int j = 0; j < i; j++) y[j] = 1;
// 	}
// 	B(B&);
// 	int &operator[](int i) { return y[i]; }
// };
// B::B(B& a)      // nu exista constr default pt A
//                 // rezolvare: il facem i = 0 => nu afiseaza nimic pt ca in op << B e transmis prin valoare si se
//                 // face o copie si atunci e folosit constr de copiere care foloseste constr default pt A
// {
// 	y = new int[a.get_x()]; 
// 	for (int i = 0; i < a.get_x(); i++) y[i] = a[i];
// }
// ostream &operator<<(ostream& o, B a)
// {
// 	for (int i = 0; i < a.get_x(); i++)o << a[i];
// 	return o;
// }
// int main()
// {
// 	B b(5);
// 	cout << b;
// 	return 0;
// }


// // 93
// #include <iostream>
// #include <typeinfo>
// using namespace std;

// class A
// {
// 	int i;
// public: A() { i = 1; }
// 		int get_i() { return i; }
// };
// class B: public A
// {
// 	int j;
// public: B() { j = 2; }
// 		int get_j() { return j; }
// };
// int main()
// {
// 	A *p;
// 	int x = 0;
// 	if (x) p = new A;
// 	else p = new B;
// 	if (typeid(p).name() == typeid(B*).name()) cout << ((B*)p)->get_j();
// 	else cout << "tipuri diferite";
// 	return 0;
// }
// // tipuri diferite - primul e P1A, al doilea e P1B


// // 94
// #include <iostream>
// using namespace std;

// class A
// {
// 	int x;
// public: A(int i = 17) { x = i; }
// 		int get_x() { return x; }
// };
// class B
// {
// 	int x;
// public: B(int i = -16) { x = i; }
// 		operator A() { return x; }
// 		int get_x() { return x; }
// };
// int main()
// {
// 	B a;
// 	A b = a;
// 	cout << b.get_x();
// 	return 0;
// }
// // -16


// 95 - nu exista


// // 96
// #include <iostream>
// using namespace std;

// class A
// {
// protected: int x;
// public: A(int i = -16) { x = i; }
// 		virtual A f(A a) { return x + a.x; }
// 		void afisare() { cout << x; }
// };
// class B: public A
// {
// public: B(int i=3):A(i){}
// 		A f(A a) { return x + a.x + 1; }    // x e protected, nu poate fi accesat
//                                             // rezolvare: il facem public => -12
// };
// int main()
// {
// 	A *p1 = new B, *p2 = new A, *p3 = new A(p1->f(*p2));
// 	p3->afisare();
// 	return 0;
// }


// // 97
// #include <iostream>
// using namespace std;

// class A
// {
// protected: int x;
// public: A(int i = -16) { x = i; }
// 		virtual A f(A a) { return x + a.x; }
// 		void afisare() { cout << x; }
// };
// class B: public A
// {
// public: B(int i=3):A(i){}
// 		A f(A a) { return x + 1; }
// 		B operator+ (B a) { return x + a.x; }
// };
// int main()
// {
// 	B a; int b = -21;
// 	a += b;     // nu exista operatorul +=
//                 // rezolvare: ori facem B operator+= ori facem a = a + b => -21
// 	cout << b;
// 	return 0;

// }


// // 98 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// #include <iostream>
// using namespace std;

// class A {
//     int x;

// public:
//     A(int i = 2)
//         : x(i)
//     {
//     }
//     int get_x() const { return x; }
// };
// class B : public A {

//     int* y;

// public:
//     B(int i = 2)
//         : A(i)
//     {
//         y = new int[i];
//         for (int j = 0; j < i; j++)
//             y[j] = 1;
//     }
//     B(B& b)
//     {
//         y = new int[b.get_x()];
//         for (int i = 0; i < b.get_x(); i++)
//             y[i] = b[i];
//     }
//     int& operator[](int i) const { return y[i]; }
// };
// ostream& operator<<(ostream& o, const B b)
// {
//     for (int i = 0; i < b.get_x(); i++)
//         o << b[i];
//     return o;
// }

// int main()
// {
//     const B b(5);
//     cout << b;      // nu merge cu const B, trebuie const& B pt ca incearca ca sa faca copie dar nu o face bine
//                     // alta rezolvare: stergem copy constr si il lasam pe cel default => 11111
//     return 0;
// }


// // 99
// // x = 20, y = -16
// // 4
// #include <iostream>
// using namespace std;
// class A
// {   protected: static int x;
//     private: int y;
//     public: A(int i) { x=i; y=-i+4; }
//         int put_x(A a) { return a.x+a.y; } };
// int A::x=7;
// int main()
// {   A a(10);
// cout<<a.put_x(20);
//     return 0;
// }
// // 4


// // 100
// #include <iostream>
// using namespace std;
// class A
// { int x;
//   static int y;
//   public: A(int i,int j):x(i),y(j){}      // variabilele statice nu pot fi initializate in lista de initializare
//                                           // rezolvare: stergem y(j) => 0
// 	int f() const;};
// int A::y;
// int A::f() const {return y;}
// int main()
// { const A a(21,2);
//   cout<<a.f();
// return 0;
// }


// // 101
// #include <iostream>
// using namespace std;

// class A {
// 	int x;

// public:
// 	A(int i = 2)
// 		: x(i)
// 	{
// 	}
// 	int get_x() const { return x; }
// };
// class B : public A {

// 	int* y;

// public:
// 	B(int i = 2)
// 		: A(i)
// 	{
// 		y = new int[i];
// 		for (int j = 0; j < i; j++)
// 			y[j] = 1;
// 	}
// 	int& operator[](int i) const { return y[i]; }
// };
// ostream& operator<<(ostream& o, const B &b)
// {
// 	for (int i = 0; i < b.get_x(); i++)
// 		o << b[i];
// 	return o;
// }
// int main()
// {
// 	const B b(5);
// 	b[2] = 3; b[4] = 5;
// 	cout << b;
// 	return 0;
// }
// // 11315


// // 102
// #include<iostream>
// using namespace std;
// template<class X>
// int functie(X x, X y)
// { return x+y;
// }
// int functie(int & x, int *y)
// { return x-*y;
// }
// int main()
// { int a=7, *b=new int(4);
//   cout<<functie(a,b);
//   return 0;
// }
// // 3


// // 103
// #include <iostream>
// using namespace std;
// class B
// { int i;
//   public: B() { i=80; }
//           virtual int get_i() { return i; }
// };
// class D: public B
// { int j;
//   public: D() { j=27; }
//           int get_j() {return j; }
// };
// int main()
// { D *p=new B;   // nu pot pune un obiect de tip B intr-un pointer de tip D
//                 // rezolvare: new D => 80 27
//   cout<<p->get_i();
//   cout<<((D*)p)->get_j();
//   return 0;
// }


// // 104
// #include <iostream>
// using namespace std;
// class B
// { protected: int i;
//   public: B(int j=5) {cout << " cb "; i=j-2; }
//           ~B(){ cout << " db ";}
//           int get_i() { return i; } };

// class D1: public B
// { int j;
//   public: D1(int k=10) {cout << " cd1 "; j=i-k+3; }
//           ~D1(){ cout << " dd1 ";} };

//  class D2: public D1
// { int k;
//   public: D2(int l=15) {cout << " cd2 "; k=i-l+3; }
//            ~D2(){ cout << " dd2 ";}  };
// D1 f(D1 d1, D2 d2) {return d1.get_i()+d2.get_i(); }
// int main()
// { D2 ob2; D1 ob1(3);
//   cout<<f(ob1,ob2).get_i()+ob2.get_i();
//   return 0;
// }
// // cb cd1 cd2 cb cd1 cb cd1 6 dd1 db dd1 db dd2 dd1 db dd1 db dd2 dd1 db
// // ob2: i = 3, j = -4, k = -9
// // ob1: i = 3, j = 3
// // f(ob1, ob2): D1(6) => i = 3, j = 6


// // 105
// #include <iostream>
// using namespace std;
// class A
// {   static int *x;
//     public: A() {}
//             int get_x() { return (++(*x))++; } };     // ++(*x)++ nu merge - eroare
//                                                       // nici ++((*x)++)
// int *A::x(new int(19));
// int main()
// {   A *p=new A,b;
//     cout<<b.get_x()<<" ";
//     cout<<p->get_x();
//     return 0;
// }
// // 20 22


// // 106
// #include <iostream>
// using namespace std;
// class X {   int i;
// public:   X(int ii = 5) { i = ii; cout<< i<< " ";};
//           const int tipareste(int j) const { cout<<i<< " "; return i+j; }; };
// int main()
// { X O (7);
//   O.tipareste(5);
//   X &O2=O;
//   O2.tipareste(6);
//   const X* p=&O;
//   cout<<p->tipareste(7);
//   return 0;
// }
// // 7 7 7 7 14


// // 107
// #include <iostream>
// using namespace std;
// class A
// {   protected: int x;
//     public: A(int i):x(i){}
//             int get_x(){ return x; } };
// class B: A
// {   protected: int y;
//     public: B(int i,int j):y(i),A(j){}
//             int get_y(){ return get_x()+y; } };
// class C: protected B
// {   protected: int z;
//     public: C(int i,int j,int k):z(i),B(j,k){}
//             int get_z(){ return get_x()+get_y()+z; } };     // get_x() e privat, nu are acces
//                                                             // rezolvare: facem mostenirea B-A public => 25
// int main()
// {   C c(5,6,7);
//     cout<<c.get_z();
//     return 0;
// }


// // 108
// #include <iostream>
// using namespace std;
// class cls
// {	int x;
// public: cls(int i=2) { x=i; }
// int set_x(int i) { int y=x; x=i; return y; }
// int get_x(){ return x; } };
// int main()
// { cls *p=new cls[15];
//       for(int i=2;i<8;i++) p[i].set_x(i);
// 	  for(int i=1;i<6;i++) cout<<p[i].get_x();
//   return 0;
// }
// //22345


// // 109
// #include <iostream>
// using namespace std;
// struct X {   int i;
// public:   X(int ii ) { i = ii; };
//      int f1() { return i; }
// X f2() const {   int i=this->f1(); return X(34-i); }};  // un ob const (this) nu poate apela o metoda neconst (f1)4
//                                                         // rezolvare: facem f1 const => 23
// const X f3() {   return X(16); }
// int f4(const X& x) { return x.f1(); }
// int main() {X ob(11);
//     cout<<f4(ob.f2().f1());
//     return 0;
// }


// // 110 - IN METODELE CLASEI MERGE SA APELEZI METODE FARA THIS CI DIRECT
// #include <iostream>
// using namespace std;
// class A
// { protected: static int x;  // var statica x nu e initializata
//   public: A(int i=1) {x=i; }
//   int get_x() { return x; }
//   int& set_x(int i) { int y=x; x=i; return y;}  // returneaza referinta la var temporara
//   A operator=(A a1) { set_x(a1.get_x()); return a1;}
// } a(33);
// // int A::x;
// int main()
// { A a(18), b(7);
//   cout<<(b=a).set_x(27);
//   return 0;
// }
// // dupa rezolvari => 7


// // 111
// #include <iostream>
// using namespace std;

// class B {
// public:
// 	int x;
// 	B(int i = 16) { x = i; }
// 	B f(B ob) { return x + ob.x; }
// };
// class D : public B {
// public:
// 	D(int i = 25) { x = i; }
// 	D f(D ob) { return x + ob.x + 1; }
// 	void afisare() { cout << x; }
// };
// int main()
// {
// 	D *p1 = new D, *p2 = new B, *p3 = new D(p1->f(*p2));    // nu se poate pune ob B in pointer D
//                                                             // rezolvare: new D => 51
// 	cout << p3->x;
// 	return 0;
// }


// // 112
// #include <iostream>
// using namespace std;
// class cls {
//     int x;

// public:
//     cls(int y) { x = y; }
//     int operator*(cls a, cls b) { return (a.x * b.x); }     // nu e bine definit operatorul - sunt prea multi param
// };
// int main()
// {
//     cls m(100), n(15);
//     cout << m * n; 
//     cout << m.
//     return 0;
// }