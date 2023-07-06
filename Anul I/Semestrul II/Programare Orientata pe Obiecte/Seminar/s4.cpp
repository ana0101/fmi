// // 1
// #include <iostream>
// using namespace std;

// class A {
// public:
//     A(int x) {
//         cout << "A" << x;
//     }
//     ~A() {
//         cout << "~A";
//     }
// };

// class B: public A {
// public:
//     B(int y = 3) {      // nu exista constructor default pt clasa A: rezolvare: facem unul
//         cout << "B" << 4;
//     }
// };

// class C: public B {
//     C(): B(10) {
//         cout << "C";
//     }
// };

// int main() {
//     A* pa = new C();    // constructorul pt C e privat; rezolvare: il facem public
//     delete pa;
//     return 0;
// }


// // 2
// #include <iostream>
// using namespace std;

// class A {
//     int y;
// public:
//     A(int x = 2020): y(x) {
//         cout << "A ";
//     }
//     ~A() {
//         cout << "~A ";
//     }
//     ostream& operator<<(ostream& out) const {
//         out << this->y << " ";
//         return out;
//     }
// };

// int main() {
//     A a(2), b;
//     a << (b << cout);
//     return 0;
// }


// // 3
// #include <iostream>
// using namespace std;

// class C {
//     int * const p;
// public:
//     C(int x): p(&x) {
//         (*p) += 3;
//     }
//     void set(int x) {
//         p = &x;     // p e const, nu poate fi modificat; rezolvare: taiem const
//     }
//     friend ostream& operator<<(ostream& o, C x) {
//         o << *x.p << " ";
//         return o;
//     }
// };

// int main() {
//     cout << C(3);
//     return 0;
// }


// // 4
// #include <iostream>
// using namespace std;
// #define ltlt <<

// class B {
// public:
//     virtual void f() = 0;
// };

// void B::f() {
//     cout ltlt "B ";
// }

// class C: public B {};

// int main() {
//     B* pb = new C();    // nu se poate crea un obiect de clasa abstracta (C); rezolvare: definim f in C
//     return 0;
// }


// // 5
// #include <iostream>
// using namespace std;

// class A {
// public:
//     A() {
//         cout << "A ";
//     }
//     virtual ~A() = 0;
// };
// A::~A() {
//     cout << "~A ";
// }

// class B: public A {
// public:
//     B() {
//         cout << "B ";
//     }
//     ~B() {
//         cout << "~B ";
//     }
// };

// class C: public B {
// public:
//     C() {
//         cout << "C ";
//     }
//     ~C() {
//         cout << "~C ";
//     }
// };

// int main() {
//     C c;
//     B &pb = c;

//     // B b;
//     // C& pc = b;
//     // asta nu merge
//     return 0;
// }
// // A B C ~C ~B ~A


#include <iostream>
using namespace std;

class A {
    int x;
public:
    friend ostream& operator<<(ostream& out, const A& obj) {
        out << obj.x;
        return out;
    }
};

int main() {
    A a;
    A b;
    b = a;
    cout << a << " " << b;
    return 0;
}