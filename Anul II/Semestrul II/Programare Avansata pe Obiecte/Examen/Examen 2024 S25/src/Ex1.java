import java.util.HashSet;

// 1
class A {
    public A met1() { return new A(); }
    final void met2() {}
    public void met3() {}
    public void met4() {}
    int met5(int i) { return 5; }
    public static void met6() {}
    public static void met7() {}
    public static void met8() {
        System.out.println("met8 din A");
    }
}

class B extends A {
    public B met1() { return new B(); } // suprascriere
    public void met2() {}   // eroare (metodele final nu pot fi suprascrise)
    void met3() {} // eroare (trebuia acces public)
    public static void met4() {}    // eroare (metoda statica nu poate supascrie metoda de instanta)
    int met5() { return 5; }    // supraincarcare
    public void met6() {}   // eroare (metoda de instanta nu poate suprascrie metoda statica)
    public void met7(int i) {}  // supraincarcare merge
    public static void met8() {
        System.out.println("met8 din B");
    }    // nu da eroare dar nici suprascriere nu e (nu e nimic)
}

class Test1 {
    public static void main(String[] args) {
        A b1 = new B();
        B b2 = new B();
        b1.met8();
        b2.met8();
    }
}

// d


// 2
class A2 {
    int val;
    public A2(int val) {
        this.val = val;
    }
    public boolean equals(Object obj) {
        return val != ((A2)obj).val;
    }
    public int hashCode() {
        return val / 100;
    }
}

class Test2 {
    public static void main(String[] args) {
        HashSet<A2> hs = new HashSet();
        hs.add(new A2(100));
        hs.add(new A2(10));
        hs.add(new A2(1));
        hs.add(new A2(10));
        hs.add(new A2(100));
        System.out.println(hs.size());
        for (A2 a : hs) {
            System.out.println(a.val);
        }
    }
}

// c
// hash set mai intai calculeaza hash code-ul
// daca e deja un element cu acelasi hash code, atunci se apeleaza metoda equals
// daca equals returneaza true, atunci elementul nu se adauga


// 3
class A3 {
    int x =  10;
    int f(int t) {
        return x + t;
    }
}

class B3 extends A3 {
    int x = 30;
    int f(int t) {
        return x + 10 * t;
    }
}

class Test3 {
    public static void main(String[] args) {
        A3 ob = new B3();
        System.out.println(ob.f(ob.x)); // 130

        B3 ob2 = new B3();
        System.out.println(ob2.f(ob2.x)); // 330
    }
}

// b
// 130
// datele membre se iau din tipul declarat
// metodele (nestatice) se iau din tipul real


// 4
class Test4 {
    static String sir = "E";

    void A4() {
        try {
            sir = sir + "A";
            B4();
        }
        catch (Exception e) {
            sir = sir + "B";
        }
    }

    void B4() throws Exception {
        try {
            sir = sir + "C";
            C4();
        }
        catch (Exception e) {
            throw new Exception();
        }
        finally {
            sir = sir + "D";
        }
    }

    void C4() throws Exception {
        throw new Exception();
    }

    public static void main(String[] args) {
        Test4 ob = new Test4();
        ob.A4();
        System.out.println(sir);
    }
}

// a
// EACDB


// 5
interface Functie {
    int f(double x);
    default boolean eval(double x) {
        return f(x) == x;
    }
}

class Test5 {
    Functie rf;
    public Test5(Functie rf) {
        this.rf = rf;
    }
    public boolean eval(double x) {
        return rf.f(x) == x;
    }

    public static void main(String[] args) {
        boolean b1 = new Test5(x -> 10).eval(10);   // corect (da true)
        System.out.println(b1);

//        boolean b2 = new Test5(x -> x/100).eval(10);    // eroare pt ca f returneaza int, aici returneaza double

        boolean b3 = new Functie() {
            public int f(double x) {
                return (int) (x/10);
            }
        }.eval(10);
        System.out.println(b3); // corect (da false)
    }
}

// d
// a, b, c, e, f => 5


public class Ex1 {

}
