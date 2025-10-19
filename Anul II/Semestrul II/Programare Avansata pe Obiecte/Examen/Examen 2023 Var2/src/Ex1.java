import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.TreeMap;

// 1
class Test1 {
    public static void main(String[] args) {
        TreeMap m = new TreeMap();
        m.put("c", "JavaSE");
        m.put("a", null);
        m.put("b", "JavaSE");
        m.put("c", "Python");
        m.put("a", "C++");
//        m.put(null, null); // asta ar da eroare (null pointer exception)
        // deci merge null doar pt valori nu si pt chei
        // logic ca ordonarea e dupa chei
        System.out.println(m);
    }
}

// c
// {a=C++, b=JavaSE, c=Python}


// 2
class A {
    int x = 0;
    public A(int n) { x = n; }
}

class B extends A {
    int x = 1;
    public B(int n) { super(n); }
}

class Test2 {
    public static void main(String[] args) {
        A a = new A(5);
        B b = new B(7);
        A ba = new B(7);
        System.out.println(a.x + " " + b.x + " " + ba.x);
    }
}

// b
// 5 1


// 3
class Test3 {
    public static void main(String[] args) {
        try {
            int a[] = {1, 2, 3, 4};
            for (int i = 1; i <= 4; i++) {
                System.out.print(a[i] / (3 - i) + " ");
            }
        }
        catch (ArrayIndexOutOfBoundsException e) {
            System.out.print("E1 ");
        }
        catch (Exception e) {
            System.out.print("E2 ");
        }
    }
}

// b
// 1 3 E2


// 4
class Test4 {
    public static void main(String[] args) {
        List<Integer> numere = new ArrayList<Integer>();
        for (int i = 0; i < 11; i ++) {
            numere.add(i);
        }
        Iterator<Integer> itr = numere.iterator();
        while (itr.hasNext()) {
            Integer nr = itr.next();
            if (nr % 2 == 0) {
                itr.remove();
            }
        }
        System.out.println(numere);
    }
}

// a
// doar nr impare
// [1, 3, 5, 7, 9]

public class Ex1 {
}
