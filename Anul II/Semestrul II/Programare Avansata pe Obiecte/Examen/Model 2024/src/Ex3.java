import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class ThreadNumaraCuvant extends Thread {
    String cuvant;
    String numeFisier;

    public ThreadNumaraCuvant(String cuvant, String numeFisier) {
        this.cuvant = cuvant;
        this.numeFisier = numeFisier;
    }

    @Override
    public void run() {
        int nr = 0;
        File fisier = new File(numeFisier);
        Scanner reader = null;
        try {
            reader = new Scanner(fisier);
        }
        catch (FileNotFoundException e) {
            System.out.println("Fisierul nu exista");
            return;
        }
        while (reader.hasNextLine()) {
            String linie = reader.nextLine();
            String [] listaCuvinte = linie.split("[ ;:,.?!]");
            for (String cuv : listaCuvinte) {
                if (cuvant.equals(cuv)) {
                    nr ++;
                }
            }
        }
        System.out.println(numeFisier + ": " + nr);
    }
}

class Ex3 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String cuvant = scanner.next();

        ThreadNumaraCuvant thread1 = new ThreadNumaraCuvant(cuvant, "C:\\Users\\anama\\Documents\\fmi\\Anul II\\Semestrul II\\Programare Avansata pe Obiecte\\Model-2024\\src\\exemplu_1.txt");
        ThreadNumaraCuvant thread2 = new ThreadNumaraCuvant(cuvant, "C:\\Users\\anama\\Documents\\fmi\\Anul II\\Semestrul II\\Programare Avansata pe Obiecte\\Model-2024\\src\\exemplu_2.txt");
        ThreadNumaraCuvant thread3 = new ThreadNumaraCuvant(cuvant, "C:\\Users\\anama\\Documents\\fmi\\Anul II\\Semestrul II\\Programare Avansata pe Obiecte\\Model-2024\\src\\exemplu_3.txt");

        thread1.start();
        thread2.start();
        thread3.start();
    }
}
