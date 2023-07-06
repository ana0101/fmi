#include <iostream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

class Pacient {
protected:
    string nume, prenume;
    int varsta;
    string adresa;
    pair <float, string> colesterol;
    pair <float, string> tensiune;

public:
    Pacient(): nume(""), prenume(""), varsta(0), adresa(""), colesterol({0, ""}), tensiune({0, ""}) {}

    Pacient(string n, string p, int v, string a, pair <float, string> c, pair <float, string> t): nume(n), prenume(p), varsta(v), adresa(a), colesterol(c), tensiune(t) {}

    Pacient(const Pacient& obj) {
        this->nume = obj.nume;
        this->prenume = obj.prenume;
        this->varsta = obj.varsta;
        this->adresa = obj.adresa;
        this->colesterol = obj.colesterol;
        this->tensiune = obj.tensiune;
    }

    Pacient& operator=(const Pacient& obj) {
        if (this != &obj) {
            this->nume = obj.nume;
            this->prenume = obj.prenume;
            this->varsta = obj.varsta;
            this->adresa = obj.adresa;
            this->colesterol = obj.colesterol;
            this->tensiune = obj.tensiune;
        }
        return *this;
    }

    virtual istream& citire(istream& in) {
        cout << "nume: ";
        in >> nume;
        cout << "prenume: ";
        in >> prenume;
        cout << "varsta: ";
        in >> varsta;
        cout << "adresa: ";
        in.get();
        getline(in, adresa);
        cout << "nivel colesterol: ";
        in >> colesterol.first;
        cout << "data colesterol: ";
        in >> colesterol.second;
        cout << "nivel tensiune: ";
        in >> tensiune.first;
        cout << "data tensiune: ";
        in >> tensiune.second;
        return in;
    }

    virtual ostream& afisare(ostream& out) const {
        cout << "nume: " << nume << "\n";
        cout << "prenume: " << prenume << "\n";
        cout << "varsta: " << varsta << "\n";
        cout << "adresa: " << adresa << "\n";
        cout << "colesterol :" << colesterol.first << " " << colesterol.second << "\n";
        cout << "tensiune: " << tensiune.first << " " << tensiune.second << "\n";
        return out;
    }

    friend istream& operator>>(istream& in, Pacient& obj) {
        return obj.citire(in);
    }

    friend ostream& operator<<(ostream& out, const Pacient& obj) {
        return obj.afisare(out);
    }

    virtual ~Pacient() = 0;
};

Pacient::~Pacient() {}


class Adult: public Pacient {
public:
    Adult() {}

    Adult(string n, string p, int v, string a, pair <float, string> c, pair <float, string> t): Pacient(n, p, v, a, c, t) {}

    Adult(const Adult& obj): Pacient(obj) {}

    Adult& operator=(const Adult& obj) {
        if (this != &obj) {
            Pacient::operator=(obj);
        }
        return *this;
    }

    virtual istream& citire(istream& in) {
        Pacient::citire(in);
        return in;
    }

    virtual ostream& afisare(ostream& out) const {
        Pacient::afisare(out);
        return out;
    }

    friend istream& operator>>(istream& in, Adult& obj) {
        return obj.citire(in);
    }

    friend ostream& operator<<(ostream& out, Adult& obj) {
        return obj.afisare(out);
    }

    virtual ~Adult() = 0;
};

Adult::~Adult() {}


class Sub40: public Adult {
public:
    Sub40() {}

    Sub40(string n, string p, int v, string a, pair <float, string> c, pair <float, string> t): Adult(n, p, v, a, c, t) {}

    Sub40(const Sub40& obj): Adult(obj) {}

    Sub40& operator=(const Sub40& obj) {
        if (this != &obj) {
            Adult::operator=(obj);
        }
        return *this;
    }

    virtual istream& citire(istream& in) {
        Adult::citire(in);
        return in;
    }

    virtual ostream& afisare(ostream& out) const {
        Adult::afisare(out);
        return out;
    }

    friend istream& operator>>(istream& in, Sub40& obj) {
        return obj.citire(in);
    }

    friend ostream& operator<<(ostream& out, Sub40& obj) {
        return obj.afisare(out);
    }

    ~Sub40() {}
};


class Peste40: public Adult {
    bool fumator;
    string sedentarism;

public:
    Peste40(): fumator(0), sedentarism("") {}

    Peste40(string n, string p, int v, string a, pair <float, string> c, pair <float, string> t, bool f, string s): Adult(n, p, v, a, c, t), fumator(f), sedentarism(s) {}

    Peste40(const Peste40& obj): Adult(obj) {}

    Peste40& operator=(const Peste40& obj) {
        if (this != &obj) {
            Adult::operator=(obj);
            this->fumator = obj.fumator;
            this->sedentarism = obj.sedentarism;
        }
        return *this;
    }

    virtual istream& citire(istream& in) {
        Adult::citire(in);
        cout << "fumator: (0 pt nu, 1 pt da): ";
        bool ok = 0;
        in >> fumator;
        while (!ok) {
            cout << "sedentarism: (scazaut mediu ridicat) " << sedentarism << "\n";
            in >> sedentarism;
            if (sedentarism != "scazut" && sedentarism != "mediu" && sedentarism != "ridicat") {
                cout << "input invalid, incercati din nou\n";
            }
            else {
                ok = 1;
            }
        }
        return in;
    }

    virtual ostream& afisare(ostream& out) const {
        Adult::afisare(out);
        out << "fumator: " << fumator << "\n";
        out << "sedentarism: " << sedentarism << "\n";
        return out;
    }

    friend istream& operator>>(istream& in, Peste40& obj) {
        return obj.citire(in);
    }

    friend ostream& operator<<(ostream& out, Peste40& obj) {
        return obj.afisare(out);
    }

    ~Peste40() {}
};


class Copil: public Pacient {
    vector <pair <string, string>> parinti;
    float proteina;

public:
    Copil(): parinti({}), proteina(0) {}

    Copil(string n, string p, int v, string a, pair <float, string> c, pair <float, string> t, vector <pair <string, string>> par, float pr): 
        Pacient(n, p, v, a, c, t), parinti(par), proteina(pr) {}

    Copil(const Copil& obj): Pacient(obj) {
        this->parinti = obj.parinti;
        this->proteina = obj.proteina;
    }

    Copil& operator=(const Copil& obj) {
        if (this != &obj) {
            Pacient::operator=(obj);
            this->parinti = obj.parinti;
            this->proteina = obj.proteina;
        }
        return *this;
    }

    istream& citire(istream& in, Copil& obj) {
        Pacient::citire(in);
        bool ok = 0;
        int nr;
        while (!ok) {
            cout << "nr parinti afectati: ";
            in >> nr;
            if (nr < 0 || nr > 2) 
                cout << "numar invalid, incercati din nou\n";
            else
                ok = 1;
        }
        for (int i = 0; i < nr; i ++) {
            
            cout << "nume: ";

        }
    }
};



int main() {
    return 0;
}