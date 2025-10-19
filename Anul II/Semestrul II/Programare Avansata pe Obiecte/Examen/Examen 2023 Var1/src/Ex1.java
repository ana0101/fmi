import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;

// 1
class Test1 {
    public static void main(String[] args) {
        LinkedHashMap m = new LinkedHashMap();
        m.put("a",  null);
        m.put("b", "JavaSE");
        m.put("c", "JavaSE");
        m.put("c", "Python");
        m.put(null, "PHP");
        m.put(null, null);
        System.out.println(m);
    }
}

// a
// {a=null, b=JavaSE, c=Python, null=null}
// aparent merge sa fie si chei si valori null
// le retine in ordinea in care au fost adaugate cheile


// 2
class A {
    int x = 10;
    static int y = 20;
}

class B extends A {
    int x = 30;
    static int y = 40;
}

class Test2 {
    public static void main(String[] args) {
        A ob = new B();
        System.out.println(ob.x + " " + ob.y);
    }
}

// d
// 10 20


// 3
class Test3 {
    static String sir = "A";

    void A() {
        try {
            sir = sir + "B";
            B();
        }
        catch (Exception e) { sir = sir + "C"; }
    }

    void B() throws Exception {
        try {
            sir = sir + "D";
            C();
        }
        catch (Exception e) { throw new Exception(); }
        finally { sir = sir + "E"; }
    }

    void C() throws Exception { throw new Exception(); }

    public static void main(String[] args) {
        Test3 ob = new Test3();
        ob.A();
        System.out.println(sir);
    }
}

// c
// ABDEC


// 4
class Test4 {
    public static void main(String[] args) {
        List<Integer> numere = new ArrayList<Integer>();

        for (int i = 0; i < 11; i ++)
            numere.add(i);

        Iterator<Integer> itr = numere.iterator();
        while (itr.hasNext()) {
            Integer nr = itr.next();
            if (nr % 2 == 0)
                numere.remove(nr);
        }
        System.out.println(numere);
    }
}

// c
// exceptie la executare


// 5
class A2 {
    int intA;

    public A met1() { return new A(); }
    final void met2() {}
    public void met3() {}
    public static void met4() {}
    private int met5(int i) { return 5; }
}

//class B2 extends A2 {
//    int intB;
//
//    public B met1() { return new B(); } // suprascriere
//    public void met2() {}   // eroare (e final => nu poate fi suprascrisa)
//    private void met3() {} // eroare (trebuia public)
//    static void met4() {}   // eroare (trebuia public)
//    private int met5() { return 5; }    // supraincarcare
//}

// b

public class Ex1 {

}
