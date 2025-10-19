import java.io.*;
import java.util.ArrayList;
import java.util.Objects;
import java.util.Scanner;

class Persoana {
    private String nume;
    private int varsta;
    private double venit;

    public Persoana(String nume, int varsta, double venit) {
        this.nume = nume;
        this.varsta = varsta;
        this.venit = venit;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public int getVarsta() {
        return varsta;
    }

    public void setVarsta(int varsta) {
        this.varsta = varsta;
    }

    public double getVenit() {
        return venit;
    }

    public void setVenit(double venit) {
        this.venit = venit;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Persoana persoana = (Persoana) o;
        return getVarsta() == persoana.getVarsta() && Double.compare(getVenit(), persoana.getVenit()) == 0 && Objects.equals(getNume(), persoana.getNume());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getNume(), getVarsta(), getVenit());
    }

    @Override
    public String toString() {
        return "Persoana{" +
                "nume='" + nume + '\'' +
                ", varsta=" + varsta +
                ", venit=" + venit +
                '}';
    }
}

class CitireScrierePersoane {
    private static String numeFisier;
    private static ArrayList<Persoana> persoane;
    private static CitireScrierePersoane citireScrierePersoane;

    private CitireScrierePersoane(String numeFisier, ArrayList<Persoana> persoane) {
        this.numeFisier = numeFisier;
        this.persoane = persoane;
    }

    public static CitireScrierePersoane getCitireScrierePersoane(String numeFisier, ArrayList<Persoana> persoane) {
        if (citireScrierePersoane == null) {
            citireScrierePersoane = new CitireScrierePersoane(numeFisier, persoane);
        }
        return citireScrierePersoane;
    }

    public void scrie() throws IOException {
        Writer wr = new FileWriter(numeFisier);
        for (Persoana p : persoane) {
            wr.write(p.getNume() + "," + String.valueOf(p.getVarsta()) + "," + String.valueOf(p.getVenit()) + "\n");
        }
        wr.close();
    }

    public void citeste() throws FileNotFoundException {
        Scanner sc = new Scanner(new File(numeFisier));
        while (sc.hasNext()) {
            String[] linie = sc.nextLine().split(",");
            String nume = linie[0];
            int varsta = Integer.parseInt(linie[1]);
            double venit = Double.parseDouble(linie[2]);
            persoane.add(new Persoana(nume, varsta, venit));
        }
    }
}


public class Ex4 {
    public static void main(String[] args) throws IOException {
        String numeFisier = "C:\\Users\\anama\\Documents\\fmi\\Anul II\\Semestrul II\\Programare Avansata pe Obiecte\\Examen\\Examen 2023 Var2\\src\\fisier4.csv";
        ArrayList<Persoana> persoane = new ArrayList<Persoana>();
        persoane.add(new Persoana("nume1", 20, 4500.5));
        persoane.add(new Persoana("nume2", 25, 5500.5));
        persoane.add(new Persoana("nume3", 30, 6500.5));

        CitireScrierePersoane citireScrierePersoane = CitireScrierePersoane.getCitireScrierePersoane(numeFisier, persoane);
        CitireScrierePersoane citireScrierePersoane1 = CitireScrierePersoane.getCitireScrierePersoane(numeFisier, persoane);
        System.out.println(citireScrierePersoane);
        System.out.println(citireScrierePersoane1);
        citireScrierePersoane.scrie();
        citireScrierePersoane.citeste();

        for (Persoana p : persoane) {
            System.out.println(p);
        }
    }
}
