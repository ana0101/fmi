import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class NrJucatoriThread extends Thread {
    private String numeFisier;
    private String nationalitate;
    private int nr;

    public NrJucatoriThread(String numeFisier, String nationalitate) {
        this.numeFisier = numeFisier;
        this.nationalitate = nationalitate;
        this.nr = 0;
    }

    public int getNr() {
        return this.nr;
    }

    public void run() {
        Scanner sc = null;
        try {
            sc = new Scanner(new File(numeFisier));
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        while (sc.hasNext()) {
            String[] linie = sc.nextLine().split(",");
            if (linie[1].equals(nationalitate)) {
                nr += 1;
            }
        }
    }
}

public class Ex3 {
    public static void main(String[] args) throws InterruptedException {
        Scanner sc = new Scanner(System.in);
        String nationalitate = sc.nextLine();

        NrJucatoriThread t1 = new NrJucatoriThread("C:\\Users\\anama\\Documents\\fmi\\Anul II\\Semestrul II\\Programare Avansata pe Obiecte\\Examen\\Examen 2024 S25\\src\\jucatori_1.txt", nationalitate);
        NrJucatoriThread t2 = new NrJucatoriThread("C:\\Users\\anama\\Documents\\fmi\\Anul II\\Semestrul II\\Programare Avansata pe Obiecte\\Examen\\Examen 2024 S25\\src\\jucatori_2.txt", nationalitate);

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        int nr = t1.getNr() + t2.getNr();
        System.out.println(nr);
    }
}