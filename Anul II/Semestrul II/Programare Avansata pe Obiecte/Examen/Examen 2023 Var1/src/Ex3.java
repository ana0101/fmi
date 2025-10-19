import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class ValTotalaThread extends Thread {
    String numeFisier;
    String firma;
    public double val;

    public ValTotalaThread(String numeFisier, String firma) {
        this.numeFisier = numeFisier;
        this.firma = firma;
        this.val = 0;
    }

    public void run() {
        Scanner sc = null;
        try {
            sc = new Scanner(new File(numeFisier));
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        while (sc.hasNextLine()) {
            String linie = sc.nextLine();
            String[] produs = linie.split(",");
            if (produs[0].equals(firma))
                val += Double.parseDouble(produs[2]) * Double.parseDouble(produs[3]);
        }
    }
}

public class Ex3 {
    public static void main(String[] args) throws InterruptedException {
        Scanner sc = new Scanner(System.in);
        String firma = sc.nextLine();

        Thread t1 = new ValTotalaThread("C:\\Users\\anama\\Documents\\fmi\\Anul II\\Semestrul II\\Programare Avansata pe Obiecte\\Examen\\Examen 2023 Var1\\src\\magazin_1.txt", firma);
        Thread t2 = new ValTotalaThread("C:\\Users\\anama\\Documents\\fmi\\Anul II\\Semestrul II\\Programare Avansata pe Obiecte\\Examen\\Examen 2023 Var1\\src\\magazin_2.txt", firma);

        t1.start();
        t2.start();
        t1.join();
        t2.join();

        System.out.println("magazin 1: " + ((ValTotalaThread) t1).val);
        System.out.println("magazin 2: " + ((ValTotalaThread) t2).val);
    }
}