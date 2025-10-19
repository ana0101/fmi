import java.util.ArrayList;
import java.util.List;

class Adresa {
    String strada;
    int numar;
    String bloc;
    int scara;
    int etaj;
    int apartament;
    String judet;
    String localitate;

    public Adresa(String strada, int numar, String bloc, int scara, int etaj, int apartament, String judet, String localitate) {
        this.strada = strada;
        this.numar = numar;
        this.bloc = bloc;
        this.scara = scara;
        this.etaj = etaj;
        this.apartament = apartament;
        this.judet = judet;
        this.localitate = localitate;
    }

    public Adresa(Adresa adresa) {
        this.strada = adresa.strada;
        this.numar = adresa.numar;
        this.bloc = adresa.bloc;
        this.scara = adresa.scara;
        this.etaj = adresa.etaj;
        this.apartament = adresa.apartament;
        this.judet = adresa.judet;
        this.localitate = adresa.localitate;
    }

    public String getStrada() {
        return strada;
    }

    public void setStrada(String strada) {
        this.strada = strada;
    }

    public int getNumar() {
        return numar;
    }

    public void setNumar(int numar) {
        this.numar = numar;
    }

    public String getBloc() {
        return bloc;
    }

    public void setBloc(String bloc) {
        this.bloc = bloc;
    }

    public int getScara() {
        return scara;
    }

    public void setScara(int scara) {
        this.scara = scara;
    }

    public int getEtaj() {
        return etaj;
    }

    public void setEtaj(int etaj) {
        this.etaj = etaj;
    }

    public int getApartament() {
        return apartament;
    }

    public void setApartament(int apartament) {
        this.apartament = apartament;
    }

    public String getJudet() {
        return judet;
    }

    public void setJudet(String judet) {
        this.judet = judet;
    }

    public String getLocalitate() {
        return localitate;
    }

    public void setLocalitate(String localitate) {
        this.localitate = localitate;
    }

    @Override
    public String toString() {
        return "Adresa{" +
                "strada='" + strada + '\'' +
                ", numar=" + numar +
                ", bloc='" + bloc + '\'' +
                ", scara=" + scara +
                ", etaj=" + etaj +
                ", apartament=" + apartament +
                ", judet='" + judet + '\'' +
                ", localitate='" + localitate + '\'' +
                '}';
    }
}

final class Facultate {
    private final String denumire;
    private final int nrStudenti;
    private final List<String> specializari;
    private final Adresa adresa;

    public Facultate(String denumire, int nrStudenti, List<String> specializari, Adresa adresa) {
        this.denumire = denumire;
        this.nrStudenti = nrStudenti;
        this.specializari = List.copyOf(specializari);
        this.adresa = new Adresa(adresa);
    }

    public String getDenumire() {
        return denumire;
    }

    public int getNrStudenti() {
        return nrStudenti;
    }

    public List<String> getSpecializari() {
        return List.copyOf(specializari);
    }

    public Adresa getAdresa() {
        return new Adresa(adresa);
    }

    @Override
    public String toString() {
        return "Facultate{" +
                "denumire='" + denumire + '\'' +
                ", nrStudenti=" + nrStudenti +
                ", specializari=" + specializari +
                ", adresa=" + adresa +
                '}';
    }
}

public class Ex4 {
    public static void main(String[] args) {
        Adresa a = new Adresa("strada", 1, "B2", 3, 7, 35, "judet", "localitate");
        List<String> specializari = new ArrayList<String>();
        specializari.add("s1");
        specializari.add("s2");
        Facultate f = new Facultate("denumire", 100, specializari, a);
        System.out.println(f);

        specializari.clear();
        a.setApartament(20);
        System.out.println(f);
    }
}
