import java.util.Arrays;

//class A {
//    int dată_membră_non_statică = 1;
//    static int dată_membră_statică = 1000;
//    void metoda1() {
//        System.out.println("Metoda non-statică 1 din clasa A!");
//    }
//    static void metoda2() {
//        System.out.println("Metoda statică 2 din clasa A!");
//    }
//}
//
//class B extends A {
//    int dată_membră_non_statică = 2;
//    static int dată_membră_statică = 2000;
//    void metoda1() {
//        System.out.println("Metoda non-statică 1 din clasa B!");
//    }
//    static void metoda2() {
//        System.out.println("Metoda statică 2 din clasa B!");
//    }
//}

//class A{
//    int intA;
//    public A met1(){
//        return new A();
//    }
//    private void met2(){}
//    public void met3(){}
//    public static void met4(){}
//    private int met5(int i){return 5;}
//}
//
//class B extends A{
//    int intB;
//    public B met1(){    // overrding
//        return new B();
//    }
//    public void met2(){}
//    private void met3(){}   // eroare (trebuia acces public)
//    static void met4(){}    // eroare (trebuia acces public)
//    private int met5(){return 5;}   // overloading???
//}

class Fir implements Runnable {
    int x;

    public Fir(int x) {this.x = x;}

    public void run() {
        new Thread(() -> {System.out.print(x);}).start();
    }

    public static void main(String[] args) throws InterruptedException {
        Fir obj1 = new Fir(1);
        Fir obj2 = new Fir(2);
        Thread t1 = new Thread(obj1);
        Thread t2 = new Thread(obj2);
        t1.start();
        t2.start();
        t1.join();
        t2.join();
        System.out.print(3);
    }
}

public class Main {

    static void modificare(int v[]) {
        System.out.println(v);
        v[0] = 100;
        v = new int[10];
        System.out.println(v);
        for (int i = 0; i < v.length; i ++) {
            System.out.println(v[i]);
        }
        v[1] = 1000;
    }

    public static void main(String[] args) {
//        int a[];
//        a = new int[5];
//
//        System.out.println(a);
//        for (int elem : a) {
//            System.out.println(elem);
//        }

//        int v[] = {1, 2, 3, 4, 5};
//        System.out.println(v);
//        modificare(v);
//        System.out.println(Arrays.toString(v));

//        A ob = new B(); //polimorfism
//        System.out.println("Data membră non-statică = " + ob.dată_membră_non_statică);
//        System.out.println("Data membră statică = " + ob.dată_membră_statică);
//        ob.metoda1();
//        ob.metoda2();

        // Datele membre (statice si non-statice) se acceseaza dupa tipul declarat, nu real
        // Metodele non-statice se acceseaza dupa tipul real (la rulare se decide)
        // Metodele statice se acceseaza dupa tipul declarat pentru ca nu se redefinesc
    }
}
