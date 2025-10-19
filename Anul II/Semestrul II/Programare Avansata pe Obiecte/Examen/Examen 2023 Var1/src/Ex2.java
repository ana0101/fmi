import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Objects;

import static java.util.stream.Collectors.averagingDouble;

class Produs {
    String firma;
    String produs;
    float cantitate;
    float pretUnitar;

    public Produs(String firma, String produs, float cantitate, float pretUnitar) {
        this.firma = firma;
        this.produs = produs;
        this.cantitate = cantitate;
        this.pretUnitar = pretUnitar;
    }

    public String getFirma() {
        return firma;
    }

    public void setFirma(String firma) {
        this.firma = firma;
    }

    public String getProdus() {
        return produs;
    }

    public void setProdus(String produs) {
        this.produs = produs;
    }

    public float getCantitate() {
        return cantitate;
    }

    public void setCantitate(float cantitate) {
        this.cantitate = cantitate;
    }

    public float getPretUnitar() {
        return pretUnitar;
    }

    public void setPretUnitar(float pretUnitar) {
        this.pretUnitar = pretUnitar;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Produs produs1 = (Produs) o;
        return Float.compare(getCantitate(), produs1.getCantitate()) == 0 && Float.compare(getPretUnitar(), produs1.getPretUnitar()) == 0 && Objects.equals(getFirma(), produs1.getFirma()) && Objects.equals(getProdus(), produs1.getProdus());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getFirma(), getProdus(), getCantitate(), getPretUnitar());
    }

    @Override
    public String toString() {
        return "Produs{" +
                "firma='" + firma + '\'' +
                ", produs='" + produs + '\'' +
                ", cantitate=" + cantitate +
                ", pretUnitar=" + pretUnitar +
                '}';
    }
}

public class Ex2 {
    public static void main(String[] args) {
        List<Produs> lista = new ArrayList<Produs>();
        lista.add(new Produs("firma1", "produs1", 50, 20));
        lista.add(new Produs("firma3", "produs2", 80, 50));
        lista.add(new Produs("firma3", "produs3", 100, 5));
        lista.add(new Produs("firma2", "produs4", 150, 140));

        lista.stream().filter(p -> p.getPretUnitar() >= 100).sorted(Comparator.comparing(Produs::getCantitate).reversed()).forEach(System.out::println);
        System.out.println();

        lista.stream().map(p -> p.getFirma()).distinct().sorted(Comparator.naturalOrder()).forEach(System.out::println);
        System.out.println();

        List<Produs> l1 = lista.stream().filter(p -> p.getCantitate() * p.getPretUnitar() <= 1000).toList();
        System.out.println(l1);
        System.out.println();

        System.out.println(lista.stream().collect(averagingDouble(Produs::getPretUnitar)));
    }
}
