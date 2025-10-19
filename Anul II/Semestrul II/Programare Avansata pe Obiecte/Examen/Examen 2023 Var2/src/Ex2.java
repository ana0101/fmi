import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

import static java.util.stream.Collectors.groupingBy;
import static java.util.stream.Collectors.mapping;

class Carte {
    String titlu;
    String autor;
    String editura;
    int nrExemplare;
    double pret;

    public Carte(String titlu, String autor, String editura, int nrExemplare, double pret) {
        this.titlu = titlu;
        this.autor = autor;
        this.editura = editura;
        this.nrExemplare = nrExemplare;
        this.pret = pret;
    }

    public String getTitlu() {
        return titlu;
    }

    public void setTitlu(String titlu) {
        this.titlu = titlu;
    }

    public String getAutor() {
        return autor;
    }

    public void setAutor(String autor) {
        this.autor = autor;
    }

    public String getEditura() {
        return editura;
    }

    public void setEditura(String editura) {
        this.editura = editura;
    }

    public int getNrExemplare() {
        return nrExemplare;
    }

    public void setNrExemplare(int nrExemplare) {
        this.nrExemplare = nrExemplare;
    }

    public double getPret() {
        return pret;
    }

    public void setPret(double pret) {
        this.pret = pret;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Carte carte = (Carte) o;
        return getNrExemplare() == carte.getNrExemplare() && Double.compare(getPret(), carte.getPret()) == 0 && Objects.equals(getTitlu(), carte.getTitlu()) && Objects.equals(getAutor(), carte.getAutor()) && Objects.equals(getEditura(), carte.getEditura());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getTitlu(), getAutor(), getEditura(), getNrExemplare(), getPret());
    }

    @Override
    public String toString() {
        return "Carte{" +
                "titlu='" + titlu + '\'' +
                ", autor='" + autor + '\'' +
                ", editura='" + editura + '\'' +
                ", nrExemplare=" + nrExemplare +
                ", pret=" + pret +
                '}';
    }
}

public class Ex2 {
    public static void main(String[] args) {
        List<Carte> lista = new ArrayList<Carte>();
        lista.add(new Carte("titlu1", "autor1", "editura1", 10, 50));
        lista.add(new Carte("titlu2", "autor3", "editura2", 15, 50));
        lista.add(new Carte("titlu3", "autor3", "editura2", 8, 50));
        lista.add(new Carte("titlu3", "autor2", "ABC", 8, 60));
        lista.add(new Carte("titlu3", "autor2", "ABC", 8, 30));
        lista.add(new Carte("titlu3", "autor3", "ABC", 8, 80));

        lista.stream().filter(c -> c.getNrExemplare() <= 10).sorted(Comparator.comparing(Carte::getAutor)).forEach(System.out::println);
        System.out.println();

        lista.stream().map(c -> c.getEditura()).distinct().forEach(System.out::println);
        System.out.println();

        List<Carte> l1 = lista.stream().filter(c -> c.getEditura().equals("ABC")).filter(c -> c.getPret() >= 50).filter(c -> c.getPret() <= 100).collect(Collectors.toList());
        System.out.println(l1);
        System.out.println();

        lista.stream().collect(groupingBy(Carte::getAutor)).forEach((autor, carte) -> {
            System.out.println("Autor " + autor + ": " + carte);
        });
    }
}
