#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Produs {
protected:
    static int contorId;
    const int idProdus;
    float pret;
    int cantitate;

public:
    Produs(): idProdus(contorId ++), pret(0), cantitate(0) {}

    Produs(float p, int c): idProdus(contorId ++), pret(p), cantitate(c) {}

    Produs(const Produs& obj): idProdus(contorId ++) {
        this->pret = obj.pret;
        this->cantitate = obj.cantitate;
    }

    Produs& operator=(const Produs& obj) {
        if (this != &obj) {
            this->pret = obj.pret;
            this->cantitate = obj.cantitate;
        }
        return *this;
    }

    virtual istream& citire(istream& in) {
        cout << "Pret: ";
        in >> pret;
        cout << "Cantitate: ";
        in >> cantitate;
        return in;
    }

    virtual ostream& afisare(ostream& out) const {
        out << "Pret: " << pret << "\n";
        out << "Cantitate: " << cantitate << "\n";
        return out;
    }

    friend istream& operator>>(istream& in, Produs& obj) {
        return obj.citire(in);
    }

    friend ostream& operator<<(ostream& out, const Produs& obj) {
        return obj.afisare(out);
    }

    int getCantitate() const {
        return cantitate;
    }

    float getPret() const {
        return pret;
    }

    virtual ~Produs() = 0;
};

int Produs::contorId = 0;

Produs::~Produs() {}


class Carte: public Produs {
    string titlu;
    vector <string> autori;
    string editura;

public:
    Carte(): titlu(""), autori({""}), editura("") {}

    Carte(float p, int c, string ti, vector <string> a, string e): Produs(p, c), titlu(ti), autori(a), editura(e) {}

    Carte(const Carte& obj): Produs(obj) {
        this->titlu = obj.titlu;
        this->autori = obj.autori;
        this->editura = obj.editura;
    }

    Carte& operator=(const Carte& obj) {
        if (this != &obj) {
            Produs::operator=(obj);
            this->titlu = obj.titlu;
            this->autori = obj.autori;
            this->editura = obj.editura;
        }
        return *this;
    }

    virtual istream& citire(istream& in) {
        Produs::citire(in);
        cout << "Titlu: ";
        in >> titlu;

        bool ok = 0;
        int n;
        while (!ok) {
            try {
                ok = 1;
                cout << "Nr autori: ";
                in >> n;
                if (n < 1)
                    throw 2;
            }
            catch(int) {
                cout << "Numar prea mic de autori, incercati din nou\n";
                ok = 0;
            }
        }

        for (int i = 0; i < n; i ++) {
            cout << "Autor: ";
            autori.push_back(*(new string));
            in >> autori.back();
        }

        cout << "Editura: ";
        in >> editura;
        return in;
    }

    virtual ostream& afisare(ostream& out) const {
        out << "Tip: carte\n";
        Produs::afisare(out);
        out << "Titlu: " << titlu << "\n";
        out << "Autori: \n";
        for (int i = 0; i < autori.size(); i ++) {
            out << autori[i] << " ";
        }
        out << "\n";
        out << "Editura: " << editura << "\n";
        return out;
    }

    friend istream& operator>>(istream& in, Carte& obj) {
        return obj.citire(in);
    }

    friend ostream& operator<<(ostream& out, const Carte& obj) {
        return obj.afisare(out);
    }

    string getTitlu() const {
        return titlu;
    }

    virtual ~Carte() {};
};


class Dvd: public Produs {
protected:
    float nrMinute;

public:
    Dvd(): nrMinute(0) {}

    Dvd(float p, int c, int n): Produs(p, c), nrMinute(n) {}

    Dvd(const Dvd& obj): Produs(obj) {
        this->nrMinute = obj.nrMinute;
    }

    Dvd& operator=(const Dvd& obj) {
        if (this != &obj) {
            Produs::operator=(obj);
            this->nrMinute = obj.nrMinute;
        }
        return *this;
    }

    virtual istream& citire(istream& in) {
        Produs::citire(in);
        cout << "Nr minute: ";
        in >> nrMinute;
        return in;
    }

    virtual ostream& afisare(ostream& out) const {
        Produs::afisare(out);
        out << "Nr minute: " << nrMinute << "\n";
        return out;
    }

    friend istream& operator>>(istream& in, Dvd& obj) {
        return obj.citire(in);
    }

    friend ostream& operator<<(ostream& out, const Dvd& obj) {
        return obj.afisare(out);
    }

    virtual ~Dvd() = 0;
};

Dvd::~Dvd() {}


class Muzica: public Dvd {
    string numeAlbum;
    vector <string> interpreti;

public:
    Muzica(): numeAlbum(""), interpreti({""}) {}

    Muzica(float p, int c, int n, string na, vector <string> i): Dvd(p, c, n), numeAlbum(na), interpreti(i) {}

    Muzica(const Muzica& obj): Dvd(obj) {
        this->numeAlbum = obj.numeAlbum;
        this->interpreti = obj.interpreti;
    }

    Muzica& operator=(const Muzica& obj) {
        if (this != &obj) {
            Dvd::operator=(obj);
            this->numeAlbum = obj.numeAlbum;
            this->interpreti = obj.interpreti;
        }
        return *this;
    }

    virtual istream& citire(istream& in) {
        Dvd::citire(in);
        cout << "Nume album: ";
        in >> numeAlbum;

        bool ok = 0;
        int n;
        while (!ok) {
            try {
                ok = 1;
                cout << "Nr interpreti: ";
                in >> n;
                if (n < 1)
                    throw 2;
            }
            catch(int) {
                cout << "Numar prea mic de interpreti, incercati din nou\n";
                ok = 0;
            }
        }

        for (int i = 0; i < n; i ++) {
            cout << "Interpret: ";
            interpreti.push_back(*(new string));
            in >> interpreti.back();
        }

        return in;
    }

    virtual ostream& afisare(ostream& out) const {
        out << "Tip: dvd cu muzica\n";
        Dvd::afisare(out);
        out << "Nume album: " << numeAlbum << "\n";
        out << "Interpreti:\n";
        for (int i = 0; i < interpreti.size(); i ++) {
            out << interpreti[i] << " ";
        }
        out << "\n";
        return out;
    }

    friend istream& operator>>(istream& in, Muzica& obj) {
        return obj.citire(in);
    }

    friend ostream& operator<<(ostream& out, const Muzica& obj) {
        return obj.afisare(out);
    }

    virtual ~Muzica() {};
};


class Film: public Dvd {
    string numeFilm;
    string gen;

public:
    Film(): numeFilm(""), gen("") {}

    Film(float p, int c, int n, string nf, string g): Dvd(p, c, n), numeFilm(nf), gen(g) {}

    Film(const Film& obj): Dvd(obj) {
        this->numeFilm = obj.numeFilm;
        this->gen = obj.gen;
    }

    Film& operator=(const Film& obj) {
        if (this != &obj) {
            Dvd::operator=(obj);
            this->numeFilm = obj.numeFilm;
            this->gen = obj.gen;
        }
        return *this;
    }

    virtual istream& citire(istream& in) {
        Dvd::citire(in);
        cout << "Nume film: ";
        in >> numeFilm;
        cout << "Gen: ";
        in >> gen;
        return in;
    }

    virtual ostream& afisare(ostream& out) const {
        out << "Tip: dvd cu film\n";
        Dvd::afisare(out);
        out << "Nume film: " << numeFilm << "\n";
        out << "Gen:" << gen << "\n";
        return out;
    }

    friend istream& operator>>(istream& in, Film& obj) {
        return obj.citire(in);
    }

    friend ostream& operator<<(ostream& out, const Film& obj) {
        return obj.afisare(out);
    }

    virtual ~Film() {};
};


class ObiectColectie: public Produs {
protected:
    string denumire;

public:
    ObiectColectie(): denumire("") {}

    ObiectColectie(float p, int c, string d): Produs(p, c), denumire(d) {}

    ObiectColectie(const ObiectColectie& obj): Produs(obj) {
        this->denumire = obj.denumire;
    }

    ObiectColectie& operator=(const ObiectColectie& obj) {
        if (this != &obj) {
            Produs::operator=(obj);
            this->denumire = obj.denumire;
        }
        return *this;
    }

    virtual istream& citire(istream& in) {
        Produs::citire(in);
        cout << "Denumire: ";
        in >> denumire;
        return in;
    }

    virtual ostream& afisare(ostream& out) const {
        Produs::afisare(out);
        out << "Denumire: " << denumire << "\n";
        return out;
    }

    friend istream& operator>>(istream& in, ObiectColectie& obj) {
        return obj.citire(in);
    }

    friend ostream& operator<<(ostream& out, const ObiectColectie& obj) {
        return obj.afisare(out);
    }

    virtual ~ObiectColectie() = 0;
};

ObiectColectie::~ObiectColectie() {}


class Figurina: public ObiectColectie {
    string categorie, brand, material;

public:
    Figurina(): categorie(""), brand({""}), material("") {}

    Figurina(float p, int c, string d, string cat, string b, string m): ObiectColectie(p, c, d), categorie(cat), brand(b), material(m) {}

    Figurina(const Figurina& obj): ObiectColectie(obj) {
        this->categorie = obj.categorie;
        this->brand = obj.brand;
        this->material = obj.material;
    }

    Figurina& operator=(const Figurina& obj) {
        if (this != &obj) {
            ObiectColectie::operator=(obj);
            this->categorie = obj.categorie;
            this->brand = obj.brand;
            this->material = obj.material;
        }
        return *this;
    }

    virtual istream& citire(istream& in) {
        ObiectColectie::citire(in);
        cout << "Categorie: ";
        in >> categorie;

        cout << "Brand: ";
        in >> brand;

        cout << "material: ";
        in >> material;
        return in;
    }

    virtual ostream& afisare(ostream& out) const {
        out << "Tip: figurina\n";
        ObiectColectie::afisare(out);
        out << "Categorie: " << categorie << "\n";
        out << "Brand: " << brand << "\n";
        out << "Material: " << material << "\n";
        return out;
    }

    friend istream& operator>>(istream& in, Figurina& obj) {
        return obj.citire(in);
    }

    friend ostream& operator<<(ostream& out, const Figurina& obj) {
        return obj.afisare(out);
    }

    virtual ~Figurina() {};
};


class Poster: public ObiectColectie {
    string format;

public:
    Poster(): format("") {}

    Poster(float p, int c, string d, string f): ObiectColectie(p, c, d), format(f) {}

    Poster(const Poster& obj): ObiectColectie(obj) {
        this->format = obj.format;
    }

    Poster& operator=(const Poster& obj) {
        if (this != &obj) {
            ObiectColectie::operator=(obj);
            this->format = obj.format;
        }
        return *this;
    }

    virtual istream& citire(istream& in) {
        ObiectColectie::citire(in);
        cout << "Format: ";
        in >> format;
        return in;
    }

    virtual ostream& afisare(ostream& out) const {
        out << "Tip: poster\n";
        ObiectColectie::afisare(out);
        out << "Format: " << format << "\n";
        return out;
    }

    friend istream& operator>>(istream& in, Poster& obj) {
        return obj.citire(in);
    }

    friend ostream& operator<<(ostream& out, const Poster& obj) {
        return obj.afisare(out);
    }

    virtual ~Poster() {};
};


class Meniu {
    static Meniu* meniu;
    static int nrMeniuri;
    Meniu() = default;
    Meniu(const Meniu& obj) = delete;

    vector <Produs*> produse;

public:
    static Meniu* getMeniu() {
        nrMeniuri ++;
        if (!meniu) 
            meniu = new Meniu();
        return meniu;
    }

    void citesteProduse() {
        int n;
        cout << "Nr produse: ";
        cin >> n;
        for (int i = 0; i < n; i ++) {
            cout << "Tip produs: \n";
            cout << "Carte: apasa 0\n";
            cout << "Dvd cu muzica: apasa 1\n";
            cout << "Dvd cu film: apasa 2\n";
            cout << "Figurina: apasa 3\n";
            cout << "Poster: apasa 4\n";

            int k;
            cin >> k;

            switch(k) {
                case 0: {
                    produse.push_back(new Carte());
                    break;
                }
                case 1: {
                    produse.push_back(new Muzica());
                    break;
                }
                case 2: {
                    produse.push_back(new Film());
                    break;
                }
                case 3: {
                    produse.push_back(new Figurina());
                    break;
                }
                case 4: {
                    produse.push_back(new Poster());
                    break;
                }
                default: {
                    cout << "Comanda invalida\n";
                    i --;
                    break;
                }
            }

            cin >> *produse.back();
        }
    }

    void afiseazaProduse() const {
        for (int i = 0; i < produse.size(); i ++)
            cout << *produse[i] << "\n";
    }

    void editeazaProdus() {
        int i;
        cout << "Indicele produsului: ";
        cin >> i;
        if (i < 0 || i > produse.size() - 1) {
            cout << "Nu exista produs cu acest indice\n";
        }
        else {
            cin >> *produse[i];
        }
    }

    void ordoneaza() {
        for (int i = 0; i < produse.size(); i ++) {
            for (int j = i+1; j < produse.size(); j ++) {
                if (produse[i]->getPret() > produse[j]->getPret()) {
                    Produs* p = produse[i];
                    produse[i] = produse[j];
                    produse[j] = p;
                }
            }
        }
    }

    void cauta() {
        bool ok = 0;
        string titlu;
        cout << "Titlu: ";
        cin >> titlu;

        for (int i = 0; i < produse.size(); i ++) {
            if (dynamic_cast<Carte*>(produse[i]) != nullptr) {
                if (dynamic_cast<Carte*>(produse[i])->getTitlu() == titlu) {
                    cout << *produse[i] << "\n";
                    ok = 1;
                }
            }
        }

        if (!ok)
            cout << "Nu exista\n";
    }

    void afisMaxCant() {
        int maxim = 0;
        for (int i = 0; i < produse.size(); i ++) {
            if (produse[i]->getCantitate() > maxim)
                maxim = produse[i]->getCantitate();
        }

        for (int i = 0; i < produse.size(); i ++) {
            if (produse[i]->getCantitate() == maxim)
                cout << *produse[i] << "\n";
        }
    }

    void start() {
        bool ok = 1;
        while (ok) {
            cout << "Citeste n produse: apasa 0\n";
            cout << "Afiseaza produsele: apasa 1\n";
            cout << "Editeaza un produs: apasa 2\n";
            cout << "Ordoneaza produsele dupa pret: apasa 3\n";
            cout << "Cauta o carte dupa titlu: apasa 4\n";
            cout << "Afiseaza produsul cu cea mai mare cantitate disponibila: apasa 5\n";
            cout << "Stop: apasa 6\n";

            int k;
            cin >> k;

            switch(k) {
                case 0: {
                    this->citesteProduse();
                    break;
                }
                case 1: {
                    this->afiseazaProduse();
                    break;
                }
                case 2: {
                    this->editeazaProdus();
                    break;
                }
                case 3: {
                    this->ordoneaza();
                    break;
                }
                case 4: {
                    this->cauta();
                    break;
                }
                case 5: {
                    this->afisMaxCant();
                    break;
                }
                case 6: {
                    ok = 0;
                    break;
                }
                default: {
                    cout << "Comanda invalida\n";
                    break;
                }
            }
        }
    }

    ~Meniu() {
        nrMeniuri --;
        if (nrMeniuri == 0) {
            if (meniu) {
                delete meniu;
            }
        }
    }
};

Meniu* Meniu::meniu = NULL;
int Meniu::nrMeniuri = 0;


int main() {
    Meniu* meniu = meniu->getMeniu();
    meniu->start();
    return 0;
}