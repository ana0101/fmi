// Hodivoianu Anamaria 132
// mingw64 g++
// Szmeteanca Eduard
#include <iostream>
#include <vector>
using namespace std;

class Contract {
    static int contorId;
    const int idContract;
    string nume, cif;

public:
    Contract();
    Contract(string nume, string cif);
    Contract(const Contract& obj);
    friend istream& operator>>(istream& in, Contract& obj);
    friend ostream& operator<<(ostream& out, const Contract& obj);
    string getCif() const {return cif;}
};

int Contract::contorId = 0;

Contract::Contract(): idContract(contorId ++), nume(""), cif("") {}

Contract::Contract(string n, string c): idContract(contorId ++), nume(n), cif(c) {}

Contract::Contract(const Contract& obj): idContract(contorId ++) {
    this->nume = obj.nume;
    this->cif = obj.cif;
}

istream& operator>>(istream& in, Contract& obj) {
    cout << "Nume: ";
    in >> obj.nume;
    cout << "Cif: ";
    in >> obj.cif;
    return in;
}

ostream& operator<<(ostream& out, const Contract& obj) {
    cout << "Nume: " << obj.nume << "\n";
    cout << "Cif: " << obj.cif << "\n";
    return out;
}


class Drum {
protected:
    string denumire;
    float lungime;
    int nrTronsoane;
    vector <Contract*> contracte;

public:
    Drum();
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;
    friend istream& operator>>(istream& in, Drum& obj);
    friend ostream& operator<<(ostream& out, const Drum& obj);
    float getLungime() const {return lungime;}
    void deleteContract(string cif);
    virtual float suma() const {return 0;}
    virtual ~Drum() = 0;
};

Drum::Drum(): denumire(""), lungime(0), nrTronsoane(1) {}

istream& Drum::citire(istream& in) {
    cout << "Denumire: ";
    in >> denumire;
    cout << "Lungime: ";
    in >> lungime;
    bool ok = 0;
    while (!ok) {
        try {
            cout << "Nr tronsoane: ";
            in >> nrTronsoane;
            if (nrTronsoane < 1)
                throw 2;
            else
                ok = 1;
        }
        catch(int) {
            cout << "Numar invalid\n";
        }
    }

    for (int i = 0; i < nrTronsoane; i ++) {
        cout << "Contract: 1 pt da, 0 pt nu";
        bool ok;
        in >> ok;
        if (ok) {
            contracte.push_back(new Contract());
            in >> *contracte.back();
        }
        else {
            contracte.push_back(nullptr);
        }
    }
    return in;
}

ostream& Drum::afisare(ostream& out) const {
    out << "Denumire: " << denumire << "\n";
    out << "Lungime: " << lungime << "\n";
    out << "Nr tronsoane: " << nrTronsoane << "\n";
    out << "Contracte: \n";
    for (int i = 0; i < nrTronsoane; i ++) {
        if (contracte[i] != nullptr)
            out << *contracte[i] << "\n";
        else 
            out << "Nu exista contract pt acest tronson\n";
    }
    return out;
}

istream& operator>>(istream& in, Drum& obj) {
    return obj.citire(in);
}

ostream& operator<<(ostream& out, const Drum& obj) {
    return obj.afisare(out);
}

void Drum::deleteContract(string cif) {
    for (int i = 0; i< contracte.size(); i ++) {
        if (contracte[i]->getCif() == cif) {
            delete contracte[i];
            contracte[i] = nullptr;
        }
    }
}

Drum::~Drum() {
    for (int i = 0; i < nrTronsoane; i ++) {
        if (contracte[i] != nullptr) {
            delete contracte[i];
        }
    }
    contracte.clear();
}


class National: public Drum {
    int nrJudete;

public:
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    friend istream& operator>>(istream& in, National& obj);
    friend ostream& operator<<(ostream& out, const National& obj);
    float suma() const;
    ~National() {}
};

istream& National::citire(istream& in) {
    Drum::citire(in);
    cout << "Nr judete: ";
    in >> nrJudete;
    return in;
}

ostream& National::afisare(ostream& out) const {
    Drum::afisare(out);
    out << "Nr judete: " << nrJudete << "\n";
    return out;
}

istream& operator>>(istream& in, National& obj) {
    return obj.citire(in);
}

ostream& operator<<(ostream& out, const National& obj) {
    return obj.afisare(out);
}

float National::suma() const {
    float suma = 0;
    for (int i = 0; i < contracte.size(); i ++) {
        if (contracte[i] != nullptr) {
            suma += 3000 * (lungime / nrTronsoane);
        }
    }
    return suma;
}


class European: virtual public Drum {
protected:
    int nrTari;

public:
    European();
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;
    friend istream& operator>>(istream& in, European& obj);
    friend ostream& operator<<(ostream& out, const European& obj);
    virtual float suma() const;
    virtual ~European() {}
};

European::European(): nrTari(0) {}

istream& European::citire(istream& in) {
    Drum::citire(in);
    cout << "Nr tari: ";
    in >> nrTari;
    return in;
}

ostream& European::afisare(ostream& out) const {
    Drum::afisare(out);
    out << "Nr tari: " << nrTari << "\n";
    return out;
}

istream& operator>>(istream& in, European& obj) {
    return obj.citire(in);
}

ostream& operator<<(ostream& out, const European& obj) {
    return obj.afisare(out);
}

float European::suma() const {
    float suma = 0;
    for (int i = 0; i < contracte.size(); i ++) {
        if (contracte[i] != nullptr) {
            suma += 3000 * (lungime / nrTronsoane);
        }
    }
    suma += 500 * nrTari;
    return suma;
}


class Autostrada: virtual public Drum {
protected:
    int nrBenzi;

public:
    Autostrada();
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;
    friend istream& operator>>(istream& in, Autostrada& obj);
    friend ostream& operator<<(ostream& out, const Autostrada& obj);
    virtual float suma() const;
    virtual ~Autostrada() {}
};

Autostrada::Autostrada(): nrBenzi(2) {}

istream& Autostrada::citire(istream& in) {
    Drum::citire(in);
    bool ok = 0;
    while (!ok) {
        try {
            cout << "Nr benzi: ";
            in >> nrBenzi;
            if (nrBenzi < 2) {
                throw 'a';
            }
            else {
                ok = 1;
            }
        }
        catch(char) {
            cout << "Numar invalid\n";
        }
    }
    return in;
}

ostream& Autostrada::afisare(ostream& out) const {
    Drum::afisare(out);
    out << "Nr benzi: " << nrBenzi << "\n";
    return out;
}

istream& operator>>(istream& in, Autostrada& obj) {
    return obj.citire(in);
}

ostream& operator<<(ostream& out, const Autostrada& obj) {
    return obj.afisare(out);
}

float Autostrada::suma() const {
    float suma = 0;
    for (int i = 0; i < contracte.size(); i ++) {
        if (contracte[i] != nullptr) {
            suma += 2500 * (lungime / nrTronsoane) * (nrBenzi);
        }
    }
    return suma;
}


class AutostradaEuropeana: public Autostrada, public European {
public:
    AutostradaEuropeana();
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    friend istream& operator>>(istream& in, AutostradaEuropeana& obj);
    friend ostream& operator<<(ostream& out, const AutostradaEuropeana& obj);
    float suma() const;
};

AutostradaEuropeana::AutostradaEuropeana() {}

istream& AutostradaEuropeana::citire(istream& in) {
    Autostrada::citire(in);
    cout << "Nr tari: ";
    in >> nrTari;
    return in;
}

ostream& AutostradaEuropeana::afisare(ostream& out) const {
    Autostrada::afisare(out);
    out << "Nr tari: " << nrTari << "\n";
    return out;
}

istream& operator>>(istream& in, AutostradaEuropeana& obj) {
    return obj.citire(in);
}

ostream& operator<<(ostream& out, const AutostradaEuropeana& obj) {
    return obj.afisare(out);
}

float AutostradaEuropeana::suma() const {
    float suma = 0;
    suma = Autostrada::suma();
    for (int i = 0; i < contracte.size(); i ++) {
        if (contracte[i] != nullptr) {
            suma += 500 * nrTari;
        }
    }
    return suma;
}



class Meniu {
    static Meniu* meniu;
    static int nrMeniuri;
    Meniu() = default;
    Meniu(const Meniu& obj) = delete;
    Meniu& operator=(const Meniu& obj) = delete;

    vector <Drum*> drumuri;

public:
    Meniu* getMeniu();
    void adaugaDrum();
    void afiseazaDrumuri() const;
    void lungTotala() const;
    void lungAuto() const;
    void sterge();
    void start();
    ~Meniu();
};

Meniu* Meniu::meniu = NULL;
int Meniu::nrMeniuri = 0;

Meniu* Meniu::getMeniu() {
    nrMeniuri ++;
    if (!meniu)
        meniu = new Meniu();
    return meniu;
}

void Meniu::adaugaDrum() {
    cout << "Drum national: apasa 0\n";
    cout << "Drum european: apasa 1\n";
    cout << "Autostrada: apasa 2\n";
    cout << "Autostrada europeana: apasa 3\n";

    int k;
    cin >> k;
    switch(k) {
        case 0: {
            drumuri.push_back(new National());
            break;
        }
        case 1: {
            drumuri.push_back(new European());
            break;
        }
        case 2: {
            drumuri.push_back(new Autostrada());
            break;
        }
        case 3: {
            drumuri.push_back(new AutostradaEuropeana());
            break;
        }
        default: {
            cout << "Comanda invalida\n";
            break;
        }
    }

    cin >> *drumuri.back();
}

void Meniu::afiseazaDrumuri() const {
    for (int i = 0; i < drumuri.size(); i ++) {
        cout << *drumuri[i] << "\n";
    }
}

void Meniu::lungTotala() const {
    float lung = 0;
    for (int i = 0; i < drumuri.size(); i ++) {
        lung += drumuri[i]->getLungime();
    }
    cout << "Lungime totala: " << lung << "\n";
}

void Meniu::lungAuto() const {
    float lung  = 0;
    for (int i = 0; i < drumuri.size(); i ++) {
        if (dynamic_cast<Autostrada*>(drumuri[i]) != nullptr) {
            lung += drumuri[i]->getLungime();
        }
    }
    cout << "Lungime totala autostrazi: " << lung << "\n";
}

void Meniu::sterge() {
    string cif;
    cout << "Cif: ";
    cin >> cif;
    for (int i = 0; i < drumuri.size(); i ++) {
        drumuri[i]->deleteContract(cif);
    }
}

void Meniu::start() {
    bool ok = 1;
    while (ok) {
        cout << "Adauga un drum: apasa 0\n";
        cout << "Afiseaza drumurile: apasa 1\n";
        cout << "Lungime toata drumuri: apasa 2\n";
        cout << "Lungime totala autostrazi: apasa 3\n";
        cout << "Sterge contractele cu o firma: apasa 4\n";
        cout << "Stop: apasa 5\n";

        int k;
        cin >> k;

        switch(k) {
            case 0: {
                this->adaugaDrum();
                break;
            }
            case 1: {
                this->afiseazaDrumuri();
                break;
            }
            case 2: {
                this->lungTotala();
                break;
            }
            case 3: {
                this->lungAuto();
                break;
            }
            case 4: {
                this->sterge();
                break;
            }
            case 5: {
                ok = 0;
                break;
            }
        }
    }
}

Meniu::~Meniu() {
    nrMeniuri --;
    if (nrMeniuri == 0) {
        for (int i = 0; i < drumuri.size(); i ++) {
            if (drumuri[i] != nullptr) {
                delete drumuri[i];
            }
        }
        drumuri.clear();
        delete meniu;
    }
}


int main() {
    Meniu* meniu = meniu->getMeniu();
    meniu->start();
    return 0;
}