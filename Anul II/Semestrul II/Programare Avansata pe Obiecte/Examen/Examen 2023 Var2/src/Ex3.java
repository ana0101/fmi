import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class StocThread extends Thread {
    private String numeFisier;
    private String titlu;
    private String autor;
    private double stoc;

    public StocThread(String numeFisier, String titlu, String autor) {
        this.numeFisier = numeFisier;
        this.titlu = titlu;
        this.autor = autor;
        this.stoc = 0;
    }

    public double getStoc() {
        return stoc;
    }

    public void run() {
        Scanner sc = null;
        try {
            sc = new Scanner(new File(numeFisier));
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
        while (sc.hasNext()) {
            String linie = sc.nextLine();
            String[] carte = linie.split(",");
            if (carte[0].equals(titlu) && carte[1].equals(autor)) {
                stoc += Integer.parseInt(carte[3]) * Double.parseDouble(carte[4]);
            }
        }
    }
}

public class Ex3 {
    public static void main(String[] args) throws InterruptedException {
        Scanner sc = new Scanner(System.in);
        String titlu = sc.nextLine();
        String autor = sc.nextLine();

        StocThread t1 = new StocThread("C:\\Users\\anama\\Documents\\fmi\\Anul II\\Semestrul II\\Programare Avansata pe Obiecte\\Examen\\Examen 2023 Var2\\src\\librarieCLB_1.txt", titlu, autor);
        StocThread t2 = new StocThread("C:\\Users\\anama\\Documents\\fmi\\Anul II\\Semestrul II\\Programare Avansata pe Obiecte\\Examen\\Examen 2023 Var2\\src\\librarieCLB_2.txt", titlu, autor);

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        System.out.println("Stoc 1: " + t1.getStoc());
        System.out.println("Stoc 2: " + t2.getStoc());
        System.out.println("Stoc total: " + (t1.getStoc() + t2.getStoc()));
    }
}