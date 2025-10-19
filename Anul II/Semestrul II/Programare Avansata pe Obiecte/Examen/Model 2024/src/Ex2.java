import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Objects;

class Automobil {
    private String marca;
    private String model;
    private int capacitate;
    private double pret;

    public Automobil(String marca, String model, int capacitate, double pret) {
        this.marca = marca;
        this.model = model;
        this.capacitate = capacitate;
        this.pret = pret;
    }

    public String getMarca() {
        return marca;
    }

    public void setMarca(String marca) {
        this.marca = marca;
    }

    public String getModel() {
        return model;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public int getCapacitate() {
        return capacitate;
    }

    public void setCapacitate(int capacitate) {
        this.capacitate = capacitate;
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
        Automobil automobil = (Automobil) o;
        return getCapacitate() == automobil.getCapacitate() && Double.compare(getPret(), automobil.getPret()) == 0 && Objects.equals(getMarca(), automobil.getMarca()) && Objects.equals(getModel(), automobil.getModel());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getMarca(), getModel(), getCapacitate(), getPret());
    }

    @Override
    public String toString() {
        return "Automobil{" +
                "marca='" + marca + '\'' +
                ", model='" + model + '\'' +
                ", capacitate=" + capacitate +
                ", pret=" + pret +
                '}';
    }
}

public class Ex2 {
    public static void main(String[] args) {
        ArrayList<Automobil> lista = new ArrayList<Automobil>();
        lista.add(new Automobil("Audi", "model1", 1500, 4000));
        lista.add(new Automobil("Skoda", "model2", 2500, 5000));
        lista.add(new Automobil("Mercedes", "model3", 3500, 6000));
        lista.add(new Automobil("Audi", "model4", 2600, 4500));

        lista.stream()
                .filter(a -> a.getPret() >= 5000)
                .sorted(Comparator.comparing(Automobil::getPret).reversed())
                .forEach(System.out::println);

        System.out.println();

        lista.stream()
                .map(a -> a.getMarca())
                .distinct()
                .forEach(System.out::println);

        System.out.println();

        List<Automobil> listaNoua = lista.stream()
                .filter(a -> a.getCapacitate() >= 2000)
                .filter(a -> a.getCapacitate() <= 3000)
                .toList();

        for (Automobil automobil : listaNoua) {
            System.out.println(automobil);
        }

        System.out.println();

        System.out.println(lista.stream()
                .filter(a -> a.getMarca().equals("Audi"))
                .map(a -> a.getPret())
                .max(Comparator.naturalOrder()));
    }
}
