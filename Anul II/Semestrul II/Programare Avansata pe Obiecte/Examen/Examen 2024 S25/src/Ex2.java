import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

class TenisATP {
    private String numeJucator;
    private String nationalitateJucator;
    private int pozitieATP;
    private int puncteATP;
    private int nrTurneeATP;

    public TenisATP(String numeJucator, String nationalitateJucator, int pozitieATP, int puncteATP, int nrTurneeATP) {
        this.numeJucator = numeJucator;
        this.nationalitateJucator = nationalitateJucator;
        this.pozitieATP = pozitieATP;
        this.puncteATP = puncteATP;
        this.nrTurneeATP = nrTurneeATP;
    }

    public String getNumeJucator() {
        return numeJucator;
    }

    public void setNumeJucator(String numeJucator) {
        this.numeJucator = numeJucator;
    }

    public String getNationalitateJucator() {
        return nationalitateJucator;
    }

    public void setNationalitateJucator(String nationalitateJucator) {
        this.nationalitateJucator = nationalitateJucator;
    }

    public int getPozitieATP() {
        return pozitieATP;
    }

    public void setPozitieATP(int pozitieATP) {
        this.pozitieATP = pozitieATP;
    }

    public int getPuncteATP() {
        return puncteATP;
    }

    public void setPuncteATP(int puncteATP) {
        this.puncteATP = puncteATP;
    }

    public int getNrTurneeATP() {
        return nrTurneeATP;
    }

    public void setNrTurneeATP(int nrTurneeATP) {
        this.nrTurneeATP = nrTurneeATP;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        TenisATP tenisATP = (TenisATP) o;
        return getPozitieATP() == tenisATP.getPozitieATP() && getPuncteATP() == tenisATP.getPuncteATP() && getNrTurneeATP() == tenisATP.getNrTurneeATP() && Objects.equals(getNumeJucator(), tenisATP.getNumeJucator()) && Objects.equals(getNationalitateJucator(), tenisATP.getNationalitateJucator());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getNumeJucator(), getNationalitateJucator(), getPozitieATP(), getPuncteATP(), getNrTurneeATP());
    }

    @Override
    public String toString() {
        return "TenisATP{" +
                "numeJucator='" + numeJucator + '\'' +
                ", nationalitateJucator='" + nationalitateJucator + '\'' +
                ", pozitieATP=" + pozitieATP +
                ", puncteATP=" + puncteATP +
                ", nrTurneeATP=" + nrTurneeATP +
                '}';
    }
}

public class Ex2 {
    public static void main(String[] args) {
        ArrayList<TenisATP> jucatori = new ArrayList<TenisATP>();
        jucatori.add(new TenisATP("nume3", "nationalitate1", 10, 1500, 10));
        jucatori.add(new TenisATP("nume1", "nationalitate2", 10, 500, 5));
        jucatori.add(new TenisATP("nume2", "nationalitate1", 10, 2500, 15));

        jucatori.stream().filter(j -> j.getNrTurneeATP() >= 10).sorted(Comparator.comparing(TenisATP::getNumeJucator)).forEach(System.out::println);
        System.out.println();

        jucatori.stream().map(j -> j.getNationalitateJucator()).distinct().forEach(System.out::println);
        System.out.println();

        List<TenisATP> lista = jucatori.stream().filter(j -> j.getPuncteATP() >= 1000).filter(j -> j.getPuncteATP() <= 4000).collect(Collectors.toList());
        for (TenisATP jucator : lista) {
            System.out.println(jucator);
        }
        System.out.println();

        jucatori.stream().collect(Collectors.groupingBy(TenisATP::getNationalitateJucator)).forEach((n, j) -> System.out.println(n + ": " + j.size()));
        System.out.println();

        // sau
        jucatori.stream().collect(Collectors.groupingBy(TenisATP::getNationalitateJucator, Collectors.counting())).forEach((n, count) -> System.out.println(n + ": " + count));
    }
}
