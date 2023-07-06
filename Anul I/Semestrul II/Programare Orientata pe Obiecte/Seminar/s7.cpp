// // 1
// #include <iostream>

// struct Integer {
//     int x;
//     Integer(const int val = 0): x(val) {}
//     friend Integer operator+(Integer& i, Integer& j) {
//         return Integer(j.x + i.x);
//     }
//     friend std::ostream& operator<<(std::ostream& o, Integer i) {
//         o << i.x;
//         return o;
//     }
// };

// int main() {
//     Integer i(26), j(5),  k(2020);
//     std::cout << (i + j + k);   // cannot bind non-const lvalue reference of type 'Integer&' to an rvalue of type 'Integer'
//     // i + j returneaza un obiect temporar, nu poate fi trimis ca parametru la o referinta
//     // rezolvare: friend Integer operator+(Integer i, Integer j)
// }


// // 2
// #include <iostream>
// #include <string>

// struct A {
//     A(int i = 0) {
//         std::cout << "A " << i << " ";
//     }
//     ~A() {
//         std::cout << "~A ";
//     }
// };

// struct B: public A {
//     A a;
//     B(): a(25) {
//         std::cout << "B ";
//     }
//     virtual ~B() {
//         std::cout << "~B ";
//     }
//     // A a;
// };

// struct C: public B {
//     C() {
//         std::cout << "C ";
//     }
//     ~C() {
//         std::cout << "~C ";
//     }
// };

// int main() {
//     A* a = new C();
//     delete a;
// }
// // A 0 A 25 B C ~A


// // 3
// #include <iostream>

// struct A {
//     virtual void foo() {}
// };

// struct B: public A {
//     void foo() {};
// };

// class D: public B {
// public:
//     void foo() {};
//     std::string br() {
//         return "bar";
//     }
// };

// int main() {
//     A* p = new D();
//     if (dynamic_cast<B*>(p)) {
//         std::cout << "B";
//     }
//     else if (dynamic_cast<D*>(p)) {
//         std::cout << "D";
//     }
//     else {
//         std::cout << "fail";
//     }
// }
// // B


// A 0 A 0 A 25 B C ~C ~B ~A ~A ~A

// #include <iostream>
// #include <string>
// using namespace std;

// struct A {
//     A() {cout << "A ";}
//     ~A() {cout << "~A ";}
// };

// struct B: public A {
//     A a;
//     B() {cout << "B ";}
//     ~B() {cout << "~B ";}
// };

// struct C: public A, public B {
//     C() {cout << "C ";}
//     ~C() {cout << "~C ";}
// };

// int main() {
//     // A* c = new C();
//     C c;
// }

// #include <iostream>
// class A {
//     int x;
// public:
//     A(int& a = 0): x(a) {}
// };

// int main() {
//     A a(5);
// }


#include <iostream>
using namespace std;

class B {
public:
    int x;
    B(int y = 2020): x(y) {}
};

class D: public B {
public:
    D() = default;
    D(int y): B(y) {}
    D operator+(const B& b) {
        return D(x + b.x);
    }
    operator int() const {return x;}
};

int main() {
    D d = (D(22) + D(5));
    std::cout << d;

    B* p = new D;
    if (typeid(p).name() == "") {
        
    }
}
