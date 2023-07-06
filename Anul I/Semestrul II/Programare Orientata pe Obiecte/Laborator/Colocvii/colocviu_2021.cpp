// copil(id) - cuminte, neasptamparat
// jucarie (denumire, dimensiune, tip) - clasice(material, culoare), educative(abilitate), electronice(nr_baterii) - 
// - moderne(educative + electronice; brand, model, nr_bat = 1, abil = generala)
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <limits>
#include <time.h>
#include <typeinfo>
#include <random>
#include <type_traits>
#include <algorithm>
using namespace std;

const int MIN = numeric_limits<int>::min();
const int MAX = numeric_limits<int>::max();

template <class T>
T getInput(const string& mesaj, istream& in) {
    T input;
    bool ok = false;
    while (!ok) {
        try {
            cout << mesaj;
            in >> input;
            if (in.fail())
                throw 1;
            else
                ok = true;
        }
        catch(int) {
            in.clear();
            in.ignore(MAX, '\n');
            cout << "\nInput invalid, incercati din nou\n";
        }
    }
    return input;
}


class Jucarie {
protected:
    string denumire;
    float dimensiune;
    string tip;

public:
    Jucarie();
    Jucarie(string denumire, float dimensiune, string tip);
    Jucarie(const Jucarie& obj);

    Jucarie& operator=(const Jucarie& obj);
    friend istream& operator>>(istream& in, Jucarie& obj) {return obj.citire(in);}
    friend ostream& operator<<(ostream& out, const Jucarie& obj) {return obj.afisare(out);}

    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;

    virtual ~Jucarie() = 0;
};

Jucarie::Jucarie() {
    this->denumire = "";
    this->dimensiune = 0;
    this->tip = "";
}

Jucarie::Jucarie(string denumire, float dimensiune, string tip) {
    this->denumire = denumire;
    this->dimensiune = dimensiune;
    this->tip = tip;
}

Jucarie::Jucarie(const Jucarie& obj) {
    this->denumire = obj.denumire;
    this->dimensiune = obj.dimensiune;
    this->tip = obj.tip;
}

Jucarie& Jucarie::operator=(const Jucarie& obj) {
    if (this != &obj) {
        this->denumire = obj.denumire;
        this->dimensiune = obj.dimensiune;
        this->tip = obj.tip;
    }
    return *this;
}

istream& Jucarie::citire(istream& in) {
    this->denumire = getInput<string>("Denumire: ", in);
    this->dimensiune = getInput<float>("Dimensiune: ", in);
    this->tip = getInput<string>("Tip: ", in);
    return in;
}

ostream& Jucarie::afisare(ostream& out) const {
    out << "Denumire: " << this->denumire << "\n";
    out << "Dimensiune: " << this->dimensiune << "\n";
    out << "Tip: " << this->tip << "\n";
    return out;
}

Jucarie::~Jucarie() {}


class Clasica: public Jucarie {
private:
    string material, culoare;
public:
    Clasica();
    Clasica(string denumire, float dimensiune, string tip, string material, string culoare);
    Clasica(const Clasica& obj);

    Clasica& operator=(const Clasica& obj);
    friend istream& operator>>(istream& in, Clasica& obj) {return obj.citire(in);}
    friend ostream& operator<<(ostream& out, const Clasica& obj) {return obj.afisare(out);}

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    virtual ~Clasica() {}
};

Clasica::Clasica() {
    this->material = "";
    this->culoare = "";
}

Clasica::Clasica(string denumire, float dimensiune, string tip, string material, string culoare): Jucarie(denumire, dimensiune, tip) {
    this->material = material;
    this->culoare = culoare;
}

Clasica::Clasica(const Clasica& obj): Jucarie(obj) {
    this->material = obj.material;
    this->culoare = obj.culoare;
}

Clasica& Clasica::operator=(const Clasica& obj) {
    if (this != &obj) {
        Jucarie::operator=(obj);
        this->material = obj.material;
        this->culoare = obj.culoare;
    }
    return *this;
}

istream& Clasica::citire(istream& in) {
    Jucarie::citire(in);
    this->material = getInput<string>("Material: ", in);
    this->culoare = getInput<string>("Culoare: ", in);
    return in;
}

ostream& Clasica::afisare(ostream& out) const {
    Jucarie::afisare(out);
    out << "Material: " << this->material << "\n";
    out << "Culoare: " << this->culoare << "\n";
    return out;
}


class Educativa: virtual public Jucarie {
protected:
    string abilitate;
public:
    Educativa();
    Educativa(string denumire, float dimensiune, string tip, string abilitate);
    Educativa(const Educativa& obj);

    Educativa& operator=(const Educativa& obj);
    friend istream& operator>>(istream& in, Educativa& obj) {return obj.citire(in);}
    friend ostream& operator<<(ostream& out, const Educativa& obj) {return obj.afisare(out);}

    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;

    virtual ~Educativa() {};
};

Educativa::Educativa() {
    this->abilitate = "";
}

Educativa::Educativa(string denumire, float dimensiune, string tip, string abilitate): Jucarie(denumire, dimensiune, tip) {
    this->abilitate = abilitate;
}

Educativa::Educativa(const Educativa& obj): Jucarie(obj) {
    this->abilitate = obj.abilitate;
}

Educativa& Educativa::operator=(const Educativa& obj) {
    if (this != &obj) {
        Jucarie::operator=(obj);
        this->abilitate = obj.abilitate;
    }
    return *this;
}

istream& Educativa::citire(istream& in) {
    Jucarie::citire(in);
    this->abilitate = getInput<string>("Abilitate: ", in);
    return in;
}

ostream& Educativa::afisare(ostream& out) const {
    Jucarie::afisare(out);
    out << "Abilitate: " << this->abilitate << "\n";
    return out;
}


class Electronica: virtual public Jucarie {
protected:
    int nrBaterii;
public:
    Electronica();
    Electronica(string denumire, float dimensiune, string tip, int nrBaterii);
    Electronica(const Electronica& obj);

    Electronica& operator=(const Electronica& obj);
    friend istream& operator>>(istream& in, Electronica& obj) {return obj.citire(in);}
    friend ostream& operator<<(ostream& out, const Electronica& obj) {return obj.afisare(out);}

    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;

    virtual ~Electronica() {};
};

Electronica::Electronica() {
    this->nrBaterii = 0;
}

Electronica::Electronica(string denumire, float dimensiune, string tip, int nrBaterii): Jucarie(denumire, dimensiune, tip) {
    this->nrBaterii = nrBaterii;
}

Electronica::Electronica(const Electronica& obj): Jucarie(obj) {
    this->nrBaterii = obj.nrBaterii;
}

Electronica& Electronica::operator=(const Electronica& obj) {
    if (this != &obj) {
        Jucarie::operator=(obj);
        this->nrBaterii = obj.nrBaterii;
    }
    return *this;
}

istream& Electronica::citire(istream& in) {
    Jucarie::citire(in);
    this->nrBaterii = getInput<int>("Nr baterii: ", in);
    return in;
}

ostream& Electronica::afisare(ostream& out) const {
    Jucarie::afisare(out);
    out << "Nr baterii: " << this->nrBaterii << "\n";
    return out;
}


class Moderna: public Educativa, public Electronica {
    string brand, model;
public:
    Moderna();
    Moderna(string denumire, float dimensiune, string tip, string abilitate, int nrBaterii, string brand, string model);
    Moderna(const Moderna& obj);

    Moderna& operator=(const Moderna& obj);
    friend istream& operator>>(istream& in, Moderna& obj) {return obj.citire(in);}
    friend ostream& operator<<(ostream& out, const Moderna& obj) {return obj.afisare(out);}

    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;

    virtual ~Moderna() {}
};

Moderna::Moderna() {
    this->abilitate = "generala";
    this->nrBaterii = 1;
    this->brand = "";
    this->model = "";
}

Moderna::Moderna(string denumire, float dimensiune, string tip, string abilitate, int nrBaterii, string brand, string model): Jucarie(denumire, dimensiune, tip) {
    this->abilitate = "generala";
    this->nrBaterii = 1;
    this->brand = brand;
    this->model = model;
}

Moderna::Moderna(const Moderna& obj): Jucarie(obj) {
    this->abilitate = "generala";
    this->nrBaterii = 1;
    this->brand = obj.brand;
    this->model = obj.model;
}

Moderna& Moderna::operator=(const Moderna& obj) {
    if (this != &obj) {
        Jucarie::operator=(obj);
        Educativa::operator=(obj);
        Electronica::operator=(obj);
        this->brand = obj.brand;
        this->model = obj.model;
    }
    return *this;
}

istream& Moderna::citire(istream& in) {
    Jucarie::citire(in);
    this->brand = getInput<string>("Brand: ", in);
    this->model = getInput<string>("Model: ", in);
    return in;
}

ostream& Moderna::afisare(ostream& out) const {
    Jucarie::afisare(out);
    out << "Brand: " << this->brand << "\n";
    out << "Model: " << this->model << "\n";
    return out;
}


class Copil {
protected:
    static int contorId;
    const int idCopil;
    string nume, prenume, adresa;
    float varsta;
    int nrFapteBune;
    vector <Jucarie*> jucarii;

public:
    Copil();
    Copil(string nume, string prenume, string adresa, float varsta, int nrFapteBune, vector <Jucarie*>& jucarii);
    Copil(const Copil& obj);

    Copil& operator=(const Copil& obj);
    friend istream& operator>>(istream& in, Copil& obj) {return obj.citire(in);}
    friend ostream& operator<<(ostream& out, const Copil& obj) {return obj.afisare(out);}
    bool operator<(const Copil& obj) const;
    
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;
    void fapte(int nrFapte);

    string getNume() const {return this->nume;}
    int getNrFapteBune() const {return this->nrFapteBune;}
    static int getContorId() {return contorId;}
    const int getId() const {return this->idCopil;}

    virtual ~Copil() = 0;
};

int Copil::contorId = 0;


Copil::Copil(): idCopil(contorId++) {
    this->nume = "";
    this->prenume = "";
    this->adresa = "";
    this->varsta = 0;
    this->nrFapteBune = 0;
    this->jucarii = {};
}

Copil::Copil(string nume, string prenume, string adresa, float varsta, int nrFapteBune, vector <Jucarie*>& jucarii): idCopil(contorId++) {
    if (nrFapteBune == jucarii.size()) {
        this->nume = nume;
        this->prenume = prenume;
        this->adresa = adresa;
        this->varsta = varsta;
        this->nrFapteBune = nrFapteBune;
        for (int i = 0; i < nrFapteBune; i ++) {
            Jucarie* jucarie;
            this->jucarii.push_back(jucarie);
            *this->jucarii.back() = *jucarii[i];
        }
    }
    else {
        cout << "Numarul de fapte bune nu este acelasi cu numarul de jucarii\n";
    }
}

Copil::Copil(const Copil& obj): idCopil(contorId++) {
    this->nume = obj.nume;
    this->prenume = obj.prenume;
    this->adresa = obj.adresa;
    this->varsta = obj.varsta;
    this->nrFapteBune = obj.nrFapteBune;
    for (int i = 0; i < obj.nrFapteBune; i ++) {
        Jucarie* jucarie;
        this->jucarii.push_back(jucarie);
        *this->jucarii.back() = *obj.jucarii[i];
    }
}

Copil& Copil::operator=(const Copil& obj) {
    if (this != &obj) {
        this->nume = obj.nume;
        this->prenume = obj.prenume;
        this->adresa = obj.adresa;
        this->varsta = obj.varsta;
        this->nrFapteBune = obj.nrFapteBune;
        for (int i = 0; i < obj.nrFapteBune; i ++) {
            Jucarie* jucarie;
            this->jucarii.push_back(jucarie);
            *this->jucarii.back() = *obj.jucarii[i];
        }
    }
    return *this;
}

bool Copil::operator<(const Copil& obj) const {
    if (this->varsta < obj.varsta)
        return true;
    return false;
}

istream& Copil::citire(istream& in) {
    this->nume = getInput<string>("Nume: ", in);
    this->prenume = getInput<string>("Prenume: ", in);
    this->adresa = getInput<string>("Adresa: ", in);
    this->varsta = getInput<float>("Varsta: ", in);
    this->nrFapteBune = getInput<int>("Nr fapte bune: ", in);
    for (int i = 0; i < nrFapteBune; i ++) {
        cout << "Tipul de jucarie: \n";
        cout << "Clasica: apasa 0\n";
        cout << "Educativa: apasa 1\n";
        cout << "Electronica: apasa 2\n";
        cout << "Moderna: apasa 3\n";

        int nr;
        in >> nr;
        Jucarie* jucarie;

        switch(nr) {
            case 0: {
                jucarie = new Clasica();
                break;
            }
            case 1: {
                jucarie = new Educativa();
                break;
            }
            case 2: {
                jucarie = new Electronica();
                break;
            }
            case 3: {
                jucarie = new Moderna();
                break;
            }
            default: {
                cout << "Comanda invalida, incercati din nou";
                i --;
                break;
            }
        }

        in >> *jucarie;
        this->jucarii.push_back(jucarie);
    }
    return in;
}

ostream& Copil::afisare(ostream& out) const {
    out << "Id: " << this->idCopil << "\n";
    out << "Nume: " << this->nume << "\n";
    out << "Prenume: " << this->prenume << "\n";
    out << "Adresa: " << this->adresa << "\n";
    out << "Varsta: " << this->varsta << "\n";
    out << "Nr fapte bune: " << this->nrFapteBune << "\n";
    out << "Jucarii: \n";
    for (int i = 0; i < this->nrFapteBune; i ++) {
        out << *this->jucarii[i] << "\n";
    }
    return out;
}

void Copil::fapte(int nrFapte) {
    this->nrFapteBune += nrFapte;
    for (int i = 0; i < nrFapte; i ++) {
        cout << "Tipul de jucarie: \n";
        cout << "Clasica: apasa 0\n";
        cout << "Educativa: apasa 1\n";
        cout << "Electronica: apasa 2\n";
        cout << "Moderna: apasa 3\n";

        int nr;
        cin >> nr;
        Jucarie* jucarie;

        switch(nr) {
            case 0: {
                jucarie = new Clasica();
                break;
            }
            case 1: {
                jucarie = new Educativa();
                break;
            }
            case 2: {
                jucarie = new Electronica();
                break;
            }
            case 3: {
                jucarie = new Moderna();
                break;
            }
            default: {
                cout << "Comanda invalida, incercati din nou";
                i --;
                break;
            }
        }

        cin >> *jucarie;
        this->jucarii.push_back(jucarie);
    }
}

Copil::~Copil() {
    for (int i = 0; i < this->nrFapteBune; i ++) {
        if (this->jucarii[i] != NULL) {
            delete this->jucarii[i];
        }
    }
}


class Cuminte: public Copil {
int nrDulciuri;

public:
    Cuminte();
    Cuminte(string nume, string prenume, string adresa, float varsta, int nrFapteBune, vector <Jucarie*>& jucarii, int nrDulciuri);
    Cuminte(const Cuminte& obj);

    Cuminte& operator=(const Cuminte& obj);
    friend istream& operator>>(istream& in, Cuminte& obj) {return obj.citire(in);}
    friend ostream& operator<<(ostream& out, const Cuminte& obj) {return obj.afisare(out);}
    
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;

    virtual ~Cuminte() {}
};

Cuminte::Cuminte() {
    this->nrFapteBune = 10;
    this->nrDulciuri = 0;
}

Cuminte::Cuminte(string nume, string prenume, string adresa, float varsta, int nrFapteBune, vector <Jucarie*>& jucarii, int nrDulciuri): Copil(nume, prenume, adresa, varsta, nrFapteBune, jucarii) {
    this->nrDulciuri = nrDulciuri;
}

Cuminte::Cuminte(const Cuminte& obj): Copil(obj) {
    this->nrDulciuri = obj.nrDulciuri;
}

Cuminte& Cuminte::operator=(const Cuminte& obj) {
    if (this != &obj) {
        Copil::operator=(obj);
        this->nrDulciuri = nrDulciuri;
    }
    return *this;
}

istream& Cuminte::citire(istream& in) {
    this->nume = getInput<string>("Nume: ", in);
    this->prenume = getInput<string>("Prenume: ", in);
    this->adresa = getInput<string>("Adresa: ", in);
    this->varsta = getInput<float>("Varsta: ", in);

    bool ok = 0;
    while (!ok) {
        this->nrFapteBune = getInput<int>("Nr fapte bune: ", in);
        if (this->nrFapteBune < 10) {
            cout << "Numar prea mic de fapte bune, incercati din nou\n";
        }
        else {
            ok = 1;
        }
    }

    for (int i = 0; i < nrFapteBune; i ++) {
        cout << "Tipul de jucarie: \n";
        cout << "Clasica: apasa 0\n";
        cout << "Educativa: apasa 1\n";
        cout << "Electronica: apasa 2\n";
        cout << "Moderna: apasa 3\n";

        int nr;
        in >> nr;
        Jucarie* jucarie;

        switch(nr) {
            case 0: {
                jucarie = new Clasica();
            }
            case 1: {
                jucarie = new Educativa();
            }
            case 2: {
                jucarie = new Electronica();
            }
            case 3: {
                jucarie = new Moderna();
            }
            default: {
                cout << "Comanda invalida, incercati din nou";
                i --;
            }
        }

        in >> *jucarie;
        this->jucarii.push_back(jucarie);
    }

    this->nrDulciuri = getInput<int>("Nr dulciuri: ", in);
    return in;
}

ostream& Cuminte::afisare(ostream& out) const {
    Copil::afisare(out);
    out << "Nr dulciuri: " << this->nrDulciuri << "\n";
    return out;
}


class Neasptamparat: public Copil {
int nrCarbuni;

public:
    Neasptamparat();
    Neasptamparat(string nume, string prenume, string adresa, float varsta, int nrFapteBune, vector <Jucarie*>& jucarii, int nrCarbuni);
    Neasptamparat(const Neasptamparat& obj);

    Neasptamparat& operator=(const Neasptamparat& obj);
    friend istream& operator>>(istream& in, Neasptamparat& obj) {return obj.citire(in);}
    friend ostream& operator<<(ostream& out, const Neasptamparat& obj) {return obj.afisare(out);}
    
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;

    virtual ~Neasptamparat() {}
};

Neasptamparat::Neasptamparat() {
    this->nrFapteBune = 10;
    this->nrCarbuni = 0;
}

Neasptamparat::Neasptamparat(string nume, string prenume, string adresa, float varsta, int nrFapteBune, vector <Jucarie*>& jucarii, int nrCarbuni): Copil(nume, prenume, adresa, varsta, nrFapteBune, jucarii) {
    this->nrCarbuni = nrCarbuni;
}

Neasptamparat::Neasptamparat(const Neasptamparat& obj): Copil(obj) {
    this->nrCarbuni = obj.nrCarbuni;
}

Neasptamparat& Neasptamparat::operator=(const Neasptamparat& obj) {
    if (this != &obj) {
        Copil::operator=(obj);
        this->nrCarbuni = nrCarbuni;
    }
    return *this;
}

istream& Neasptamparat::citire(istream& in) {
    Copil::citire(in);
    this->nrCarbuni = getInput<int>("Nr carbuni: ", in);
    return in;
}

ostream& Neasptamparat::afisare(ostream& out) const {
    Copil::afisare(out);
    out << "Nr carbuni: " << this->nrCarbuni << "\n";
    return out;
}


class Meniu {
    static Meniu *meniu;
    vector <Copil*> copii;
    Meniu() = default;
    Meniu(const Meniu&) = delete;
    static int nrMeniuri;

public:
    static Meniu* getMeniu() {
        nrMeniuri ++;
        if (!meniu)
            meniu = new Meniu();
        return meniu;
    }

    void adaugaCopil();
    void afiseazaCopii();
    void gasesteCopii();
    void ordoneazaVarsta();
    void ordoneazaFapte();
    void creste();
    void start();

    ~Meniu();
};

Meniu* Meniu::meniu = NULL;
int Meniu::nrMeniuri = 0;

void Meniu::adaugaCopil() {
    Copil* copil;
    bool ok = 0;
    int nr;

    while (!ok) {
        nr = getInput<int>("Cuminte: apasa 0\nNeastamparat: apasa 1\n", cin);
        if (nr == 0 || nr == 1)
            ok = 1;
        else
            cout << "Comanda invalida, incercati din nou\n";
    }

    switch(nr) {
        case 0: {
            copil = new Cuminte();
            break;
        }
        case 1: {
            copil = new Neasptamparat();
            break;
        }
    }

    cin >> *copil;
    this->copii.push_back(copil);
}

void Meniu::afiseazaCopii() {
    for (int i = 0; i < this->copii.size(); i ++) {
        cout << *copii[i] << "\n";
    }
}

void Meniu::gasesteCopii() {
    string nume = getInput<string>("Numele copilului cautat: ", cin);
    for (int i = 0; i < this->copii.size(); i ++) {
        if (this->copii[i]->getNume().find(nume) != string::npos) {
            cout << *this->copii[i];
        }
    }
}

void Meniu::ordoneazaVarsta() {
    sort(this->copii.begin(), this->copii.end());
}

void Meniu::ordoneazaFapte() {
    for (int i = 0; i < this->copii.size(); i ++) {
        for (int j = i+1; j < this->copii.size(); i ++) {
            if (this->copii[i]->getNrFapteBune() > this->copii[j]->getNrFapteBune()) {
                Copil* c = this->copii[i];
                this->copii[i] = this->copii[j];
                this->copii[j] = c;
            }
        }
    }
}

void Meniu::creste() {
    int id = getInput<int>("Id-ul copilului: ", cin);
    if (id > Copil::getContorId()) {
        cout << "Nu exista copil\n";
    }
    else {
        for (int i = 0; i < this->copii.size(); i ++) {
            if (this->copii[i]->getId() == id) {
                int nrFapte = getInput<int>("Nr fapte: ", cin);

            }
        }
    }
}

void Meniu::start() {
    bool ok = 1;
    while (ok) {
        bool ok2 = 0;
        int nr;
        while (!ok2) {
            nr = getInput<int>("Adauga un copil: apasa 0\nAfiseaza copii: apasa 1\nStop: apasa 2\n", cin);
            if (nr < 0 || nr > 2) {
                cout << "Comanda invalida, incercati din nou\n";
            }
            else {
                ok2 = 1;
            }
        }

        switch(nr) {
            case 0: {
                this->adaugaCopil();
                break;
            }
            case 1: {
                this->afiseazaCopii();
                break;
            }
            case 2: {
                ok = 0;
                break;
            }
        }
    }
}

Meniu::~Meniu() {
    this->nrMeniuri --;
    if (this->nrMeniuri == 0) {
        if (this->meniu) {
            for (int i = 0; i < this->copii.size(); i ++)
                delete this->copii[i];
            delete this->meniu;
        }
    }
}



int main() {
    Meniu* meniu = meniu->getMeniu();
    meniu->start();
    return 0;
}