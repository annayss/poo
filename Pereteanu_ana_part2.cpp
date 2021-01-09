#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include<fstream>
using namespace std;


class Inregistrare
{
    string valoare;
public:
    string getValoare()
    {
        return this->valoare;
    }
    Inregistrare()
    {

        this->valoare = "";
    }
    Inregistrare(string valoare)
    {
        this->valoare = valoare;
    }
    Inregistrare(const Inregistrare& in)
    {

        this->valoare = in.valoare;
    }
    ~Inregistrare()
    {

    }
    Inregistrare& operator=(const Inregistrare& in)
    {
        if (this != &in)
        {
            this->valoare = in.valoare;
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Inregistrare& i)
    {
        out << i.valoare << endl;
        return out;
    }
    friend ofstream& operator<<(ofstream& out, const Inregistrare& i)
    {
        out << i.valoare << endl;
        return out;
    }
    friend istream& operator>>(istream& in, Inregistrare& inr)
    {
        cout << "Valoare atributului: ";
        in >> ws;
        getline(in, inr.valoare);
        return in;
    }
    friend ifstream& operator>>(ifstream& in, Inregistrare& inr)
    {
        cout << "Valoare atributului: ";
        in >> ws;
        getline(in, inr.valoare);
        return in;
    }
    void serializare()
    {
      
        ofstream f("inregistrare.bin", ios::out , ios::binary);
        int dimensiuneValoare = this->valoare.size();
        f.write((char*)&dimensiuneValoare, sizeof(int));
        f.write(valoare.c_str(), dimensiuneValoare+1);
        f.close();
    }
    void deserializare()
    {
        ifstream f("inregistrare.bin", ios::in ,ios::binary);
        int dim;
        f.read((char*)&dim, sizeof(int));
        char* incerc= new char[dim+1];
        f.read(incerc, dim + 1);
        this->valoare = incerc;
     
        f.close();
    }

};
class Coloana
{
    string denumireColoana;
    string tip;
    int lungime;
    int nrInregistrari = 0;
    Inregistrare** inregistrare = nullptr;
public:
    Inregistrare** getInregistrare()
    {
        return this->inregistrare;
    }
    int getNrInr()
    {
        return this->nrInregistrari;
    }
    string getDenumireColoana()
    {
        return this->denumireColoana;
    }
    Coloana()
    {

        this->denumireColoana = "";
        this->tip = "";
        this->lungime = 0;
    }
    Coloana(string denumireColoana, string tip, int lungime, int nrInregistrari, Inregistrare** inregistrare)
    {
        this->denumireColoana = denumireColoana;
        this->tip = tip;
        this->lungime = lungime;
        this->nrInregistrari = nrInregistrari;
        this->inregistrare = new Inregistrare * [this->nrInregistrari];
        for (int i = 0; i < this->nrInregistrari; i++)
        {
            this->inregistrare[i] = inregistrare[i];
        }
    }
    Coloana(const Coloana& c)
    {

        this->denumireColoana = c.denumireColoana;
        this->tip = c.tip;
        this->lungime = c.lungime;
        this->nrInregistrari = c.nrInregistrari;
        this->inregistrare = new Inregistrare * [this->nrInregistrari];
        for (int i = 0; i < this->nrInregistrari; i++)
        {
            this->inregistrare[i] = c.inregistrare[i];
        }
    }

    ~Coloana()
    {
        if (inregistrare != nullptr)
        {
            delete[]inregistrare;
        }
    }
    bool operator==(Coloana& c)
    {
        if (denumireColoana == c.denumireColoana && tip == c.tip && lungime == c.lungime)
        {
            return true;
        }
        else
            return false;
    }
    Coloana& operator=(const Coloana& c)
    {
        if (this != &c)
        {
            if (inregistrare != nullptr)
            {
                delete[]inregistrare;
            }
            this->denumireColoana = c.denumireColoana;
            this->tip = c.tip;
            this->lungime = c.lungime;
            this->nrInregistrari = c.nrInregistrari;
            this->inregistrare = new Inregistrare * [this->nrInregistrari];
            for (int i = 0; i < this->nrInregistrari; i++)
            {
                this->inregistrare[i] = c.inregistrare[i];
            }
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Coloana& c)
    {
        out << c.denumireColoana << endl;
        for (int i = 0; i < c.nrInregistrari; i++)
        {
            out << *c.inregistrare[i];
        }
 
        return out;
    }
    friend ofstream& operator<<(ofstream& out, const Coloana& c)
    {
        out << c.denumireColoana << endl;
        for (int i = 0; i < c.nrInregistrari; i++)
        {
            out << *c.inregistrare[i];
        }
        return out;
    }
    friend istream& operator>>(istream& in,  Coloana& c)
    {
        if (c.inregistrare != nullptr)
        {
            delete[]c.inregistrare;
        }
        in >> ws;
        getline(in, c.denumireColoana);
        in >> ws;
        getline(in, c.tip);
        in >> c.lungime;
        in >> c.nrInregistrari;
        c.inregistrare = new Inregistrare * [c.nrInregistrari];
        for (int i = 0; i < c.nrInregistrari; i++)
        {
            c.inregistrare[i] = new Inregistrare();
            in >> *c.inregistrare[i];
        }

    }
    friend ifstream& operator>>(ifstream& in, Coloana& c)
    {
        if (c.inregistrare != nullptr)
        {
            delete[]c.inregistrare;
        }
        in >> ws;
        getline(in, c.denumireColoana);
        in >> ws;
        getline(in, c.tip);
        in >> c.lungime;
        in >> c.nrInregistrari;
        c.inregistrare = new Inregistrare * [c.nrInregistrari];
        for (int i = 0; i < c.nrInregistrari; i++)
        {
            c.inregistrare[i] = new Inregistrare();
            in >> *c.inregistrare[i];
        }

    }
    void serializare()
    {
      
        ofstream f("coloana.bin", ios::out | ios::binary);
        int dimensiuneValoare = this->denumireColoana.size();
        f.write((char*)&dimensiuneValoare, sizeof(dimensiuneValoare));
        f.write(this->denumireColoana.c_str(), dimensiuneValoare + 1);//+1 este pentru terminator '\0')
        int dimensiuneValoare1 = this->tip.size();
        f.write((char*)&dimensiuneValoare1, sizeof(dimensiuneValoare1));
        f.write(this->tip.c_str(), dimensiuneValoare1 + 1);//+1 este pentru terminator '\0')
        f.write((char*)&this->nrInregistrari, sizeof(nrInregistrari));
        for (int i = 0; i < this->nrInregistrari; i++)
        {
            f.write((char*)&*this->inregistrare[i], sizeof(*inregistrare[i]));
        }
        f.close();
    }
    void deserializare()
    {
        ifstream f("coloana.bin", ios::in | ios::binary);
        int dimensiuneValoare = 0;
        f.read((char*)&dimensiuneValoare, sizeof(dimensiuneValoare));
        char* aux = new char[dimensiuneValoare + 1];
        f.read(aux, dimensiuneValoare + 1);//+1 este pentru terminator '\0')
        this->denumireColoana = aux;
        delete[] aux;
        int dimensiuneValoare1 = 0;
        f.read((char*)&dimensiuneValoare1, sizeof(dimensiuneValoare1));
        char* aux1 = new char[dimensiuneValoare1 + 1];
        f.read(aux1, dimensiuneValoare1 + 1);//+1 este pentru terminator '\0')
        this->tip = aux1;
        delete[] aux1;
        f.read((char*)&this->nrInregistrari, sizeof(nrInregistrari));
        delete[]this->inregistrare;
        this->inregistrare = new Inregistrare * [this->nrInregistrari];
        for (int i = 0; i < this->nrInregistrari; i++)
        {
            this->inregistrare[i] = new Inregistrare();
            f.read((char*)&*this->inregistrare[i], sizeof(*inregistrare[i]));
        }
        f.close();
    }
    
};
class Tabela
{
    string nume = "";
    int nrColoane = 0;
    Coloana** col = nullptr;
    
public:
    string getNume()
    {
        return this->nume;
    }
    void setNume(string nume)
    {
        this->nume = nume;
    }
    Coloana** getCol()
    {
        return this->col;
    }

    int getNrCol()
    {
        return this->nrColoane;
    }
 
    Tabela()
    {

    }
    Tabela(string nume, int nrColoane, Coloana** col)
    {
        this->nume = nume;
        this->nrColoane = nrColoane;
        this->col = new Coloana * [this->nrColoane];
        for (int i = 0; i < this->nrColoane; i++)
        {
            this->col[i] = col[i];
        }
        
    }
    Tabela(const Tabela& t)
    {
        this->nume = t.nume;
        this->nrColoane = t.nrColoane;
        this->col = new Coloana * [this->nrColoane];
        for (int i = 0; i < this->nrColoane; i++)
        {
            this->col[i] = t.col[i];
        }
      
    }
    ~Tabela()
    {
        if (col != nullptr)
        {
            delete[]col;
        }
       
    }
    Tabela& operator=(const Tabela& t)
    {
        if (this != &t)
        {
            if (col != nullptr)
            {
                delete[]col;
            }
          
            this->nume = t.nume;
            this->nrColoane = t.nrColoane;
            this->col = new Coloana * [this->nrColoane];
            for (int i = 0; i < this->nrColoane; i++)
            {
                this->col[i] = t.col[i];
            }
          
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Tabela& t)
    {
        out << t.nume << endl;
     
        for (int i = 0; i < t.nrColoane; i++)
        {
            out<<i<<". " << *t.col[i]<< endl<<endl;

        }
        out << endl;
     
        return out;
    }
    friend ofstream& operator<<(ofstream& out, const Tabela& t)
    {
        for (int i = 0; i < t.nrColoane; i++)
        {
            out << *t.col[i]<<endl;
        }
        out << endl;
        
        return out;
    }
    friend istream& operator>>(istream& in, Tabela& t)
    {
        in >> t.nrColoane;
        delete[]t.col;
        t.col = new Coloana * [t.nrColoane];
        for (int i = 0; i < t.nrColoane; i++)
        {
            t.col[i] = new Coloana();
            in >> *t.col[i];
        }
        return in;
    }
    friend ifstream& operator>>(ifstream& in, Tabela& t)
    {
        in >> t.nrColoane;
        delete[]t.col;
        t.col = new Coloana * [t.nrColoane];
        for (int i = 0; i < t.nrColoane; i++)
        {
            t.col[i] = new Coloana();
            in >> *t.col[i];
        }
        return in;
    }
    void serializare()
    {

        ofstream f("tabela.bin", ios::out | ios::binary);
        int dimensiuneValoare = this->nume.size();
        f.write((char*)&dimensiuneValoare, sizeof(dimensiuneValoare));
        f.write(this->nume.c_str(), dimensiuneValoare + 1);//+1 este pentru terminator '\0')

        f.write((char*)&this->nrColoane, sizeof(nrColoane));
        for (int i = 0; i < this->nrColoane; i++)
        {
            f.write((char*)&*this->col[i], sizeof(*col[i]));
        }
        f.close();
    }
    void deserializare()
    {
        ifstream f("tabela.bin", ios::in | ios::binary);
        int dimensiuneValoare = 0;
        f.read((char*)&dimensiuneValoare, sizeof(dimensiuneValoare));
        char* aux = new char[dimensiuneValoare + 1];
        f.read(aux, dimensiuneValoare + 1);//+1 este pentru terminator '\0')
        this->nume = aux;
        delete[] aux;
       
        f.read((char*)&this->nrColoane, sizeof(nrColoane));
        delete[]this->col;
        this->col = new Coloana * [this->nrColoane];
        for (int i = 0; i < this->nrColoane; i++)
        {
            this->col[i] = new Coloana();
            f.read((char*)&*this->col[i], sizeof(*col[i]));
        }
        f.close();
    }
};
class BazaDeDate
{
    string numeBaza;
    int nrTabele;
    Tabela** tab;
public:
    string getNumeBaza()
    {
        return this->numeBaza;
    }
    Tabela** getTabele()
    {
        return tab;
    }

    BazaDeDate()
    {
        this->numeBaza = "";
        this->nrTabele = 0;
        this->tab = nullptr;
    }
    BazaDeDate(string numeBaza, int nrTabele, Tabela** tab)
    {

        this->numeBaza = numeBaza;
        this->nrTabele = nrTabele;
        this->tab = new Tabela * [this->nrTabele];
        for (int i = 0; i < this->nrTabele; i++)
        {
            this->tab[i] = tab[i];
        }
    }
    BazaDeDate(const BazaDeDate& b)
    {
        this->numeBaza = b.numeBaza;
        this->nrTabele = b.nrTabele;
        this->tab = new Tabela * [this->nrTabele];
        for (int i = 0; i < this->nrTabele; i++)
        {
            this->tab[i] = b.tab[i];
        }
    }
    ~BazaDeDate()
    {
        if (this->tab != nullptr)
        {
            delete[] this->tab;
        }
    }
    BazaDeDate& operator=(const BazaDeDate& b)
    {
        if (this != &b)
        {
            if (this->tab != nullptr)
            {
                delete[] this->tab;
            }
            this->numeBaza = b.numeBaza;
            this->nrTabele = b.nrTabele;
            this->tab = new Tabela * [this->nrTabele];
            for (int i = 0; i < this->nrTabele; i++)
            {
                this->tab[i] = b.tab[i];
            }
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const BazaDeDate& b)
    {

        for (int i = 0; i < b.nrTabele; i++)
        {
            out << *b.tab[i];
        }
        out << endl;
        return out;
    }
    int getNrTabele()
    {
        return this->nrTabele;
    }
    BazaDeDate& operator+=(Tabela& l)
    {
        BazaDeDate copie = *this;
        delete[]tab;
        this->nrTabele++;
        this->tab = new Tabela * [this->nrTabele];
        for (int i = 0; i < copie.nrTabele; i++)
        {
            this->tab[i] = copie.tab[i];
        }
        this->tab[this->nrTabele - 1] = new Tabela(l);
        return *this;
    }
    void adaugaTab(Tabela& t)
    {
        (*this) += t;
    }
    BazaDeDate& operator -=(Tabela& l)
    {
        int nr = 0;
        BazaDeDate copie = *this;
        for (int i = 0; i < this->nrTabele; i++)
        {
            if (this->tab[i]->getNume() == l.getNume())
            {
                nr++;
            }
        }
        delete[]this->tab;
        this->nrTabele = this->nrTabele - nr;
        this->tab = new Tabela * [this->nrTabele];
        int poz = 0;
        for (int i = 0; i < copie.nrTabele; i++)
        {
            if (copie.tab[i]->getNume() != l.getNume())
            {
                this->tab[poz] = copie.tab[i];
                poz++;
            }
        }
        return *this;
    }
    void eliminaTab(Tabela& t)
    {
        (*this) -= t;
    }
    friend istream& operator>>(istream& in, BazaDeDate& t)
    {
        in >> t.nrTabele;
        delete[]t.tab;
        t.tab = new Tabela * [t.nrTabele];
        for (int i = 0; i < t.nrTabele; i++)
        {
            t.tab[i] = new Tabela();
            in >> *t.tab[i];
        }
        return in;
    }
    friend ifstream& operator>>(ifstream& in, BazaDeDate& t)
    {
        in >> t.nrTabele;
        delete[]t.tab;
        t.tab = new Tabela * [t.nrTabele];
        for (int i = 0; i < t.nrTabele; i++)
        {
            t.tab[i] = new Tabela();
            in >> *t.tab[i];
        }
        return in;
    }
    void serializare()
    {

        ofstream f("bazadeDate.bin", ios::out | ios::binary);
        int dimensiuneValoare = this->numeBaza.size();
        f.write((char*)&dimensiuneValoare, sizeof(dimensiuneValoare));
        f.write(this->numeBaza.c_str(), dimensiuneValoare + 1);//+1 este pentru terminator '\0')

        f.write((char*)&this->nrTabele, sizeof(nrTabele));
        for (int i = 0; i < this->nrTabele; i++)
        {
            f.write((char*)&*this->tab[i], sizeof(*tab[i]));
        }
        f.close();
    }
    void deserializare()
    {
        ifstream f("bazadeDate.bin", ios::in | ios::binary);
        int dimensiuneValoare = 0;
        f.read((char*)&dimensiuneValoare, sizeof(dimensiuneValoare));
        char* aux = new char[dimensiuneValoare + 1];
        f.read(aux, dimensiuneValoare + 1);//+1 este pentru terminator '\0')
        this->numeBaza = aux;
        delete[] aux;

        f.read((char*)&this->nrTabele, sizeof(nrTabele));
        delete[]this->tab;
        this->tab = new Tabela * [this->nrTabele];
        for (int i = 0; i < this->nrTabele; i++)
        {
            this->tab[i] = new Tabela();
            f.read((char*)&*this->tab[i], sizeof(*tab[i]));
        }
        f.close();
    }
};
class DisplayTable
{
    Tabela* tab;
public:
    DisplayTable()
    {
        this->tab = new Tabela();
    }
    DisplayTable(Tabela& t)
    {
        this->tab = new Tabela(t);

    }
    friend ostream& operator<<(ostream& out, const DisplayTable& d)
    {
        out << *d.tab << endl;
        return out;
    }
};

class LMD
{
    Tabela* tab;
public:
    LMD()
    {
        this->tab = new Tabela();
    }
    LMD(Tabela& t)
    {
        this->tab = new Tabela(t);

    }
    friend ostream& operator<<(ostream& out, const LMD& d)
    {
        out << *d.tab << endl;
        return out;
    }
    Tabela getTab()
    {
        return *this->tab;
    }
    ~LMD()
    {
        delete tab;
    }
};
class LDD
{
    BazaDeDate* bd;
public:
    LDD()
    {
        bd = new BazaDeDate();
    }
    LDD(BazaDeDate& bd)
    {
       this->bd = new BazaDeDate(bd);
    }
    void AdaugaTabela(Tabela t)
    {
        bd->adaugaTab(t);
    }
    void EliminaTabela(Tabela t)
    {
        bd->eliminaTab(t);
    }
    friend ostream& operator<<(ostream& out, const LDD& t)
    {
        for (int i = 0; i < t.bd->getNrTabele(); i++)
        {
            out <<*t.bd->getTabele()[i] << endl;

        }

        return out;
    }
    ~LDD()
    {
        delete bd;
    }
};
string get_input(const string& prompt)
{
    string temp;
    while (!getline(cin, temp) || temp.empty()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return temp;
}
class Modul
{
    string numeFisier;
    int nrFisiere;
    string* comenzi;
public:
    Modul()
    {
        this->numeFisier = "";
        this->nrFisiere = 0;
        this->comenzi = NULL;
    }
    Modul(string numeFisier, int nrFisiere, string* comenzi)
    {
        this->numeFisier = numeFisier;
        this->nrFisiere = nrFisiere;
        this->comenzi = new string[this->nrFisiere];
        for(int i=0;i<this->nrFisiere;i++)
        {
            this->comenzi[i] = comenzi[i];
        }
    }
    Modul(const Modul &m)
    {
        this->numeFisier = m.numeFisier;
        this->nrFisiere = m.nrFisiere;
        this->comenzi = new string[this->nrFisiere];
        for (int i = 0; i < this->nrFisiere; i++)
        {
            this->comenzi[i] = m.comenzi[i];
        }
    }
    ~Modul()
    {
        if (this->comenzi != NULL)
        {
            delete[]this->comenzi;
        }
    }
    Modul& operator=(const Modul& m)
    {
        if (this != &m)
        {
            if (this->comenzi != NULL)
            {
                delete[]this->comenzi;
            }
            this->numeFisier = m.numeFisier;
            this->nrFisiere = m.nrFisiere;
            this->comenzi = new string[this->nrFisiere];
            for (int i = 0; i < this->nrFisiere; i++)
            {
                this->comenzi[i] = m.comenzi[i];
            }
        }
        
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Modul& m)
    {
        out << m.numeFisier << endl;
        out << m.nrFisiere << endl;
        for (int i = 0; i < m.nrFisiere; i++)
        {
            out << m.comenzi[i] << endl;
        }
        return out;
    }
    friend ofstream& operator<<(ofstream& out, const Modul& m)
    {
        out << m.numeFisier << endl;
        out << m.nrFisiere << endl;
        for (int i = 0; i < m.nrFisiere; i++)
        {
            out << m.comenzi[i] << endl;
        }
        return out;
    }
    friend istream& operator>>(istream& in,  Modul& m)
    {
        in >> ws;
        getline(in, m.numeFisier);
        in >> m.nrFisiere;
        delete[] m.comenzi;
        m.comenzi = new string[m.nrFisiere];
        for (int i = 0; i < m.nrFisiere; i++)
        {
            in >> ws;
            getline(in, m.comenzi[i]);
        }
        return in;
    }
    friend ifstream& operator>>(ifstream& in, Modul& m)
    {
        in >> ws;
        getline(in, m.numeFisier);
        in >> m.nrFisiere;
        delete[] m.comenzi;
        m.comenzi = new string[m.nrFisiere];
        for (int i = 0; i < m.nrFisiere; i++)
        {
            in >> ws;
            getline(in, m.comenzi[i]);
        }
        return in;
    }
};
int main()
{
 /*   Inregistrare in;
    Inregistrare in1("torel");
    in1.serializare1();
    in.deserializare1();
    cout << "Inregistrarea a fost salvata!" << endl;
    cout << in << endl;*/
    Inregistrare in;
    Inregistrare in1("dorel");
    in1.serializare();
    in.deserializare();
    cout << "Inregistrarea a fost salvata!" << endl;
    cout << in << endl;
    Inregistrare in2("Ionel");
    Inregistrare in3("Tudorel");
    Inregistrare in4("22");
    Inregistrare in5("20");
    Inregistrare in6("19");
    Inregistrare in7("5000");
    Inregistrare in8("6000");
    Inregistrare in9("7000");
    Inregistrare** vect = new Inregistrare * [3];
    vect[0] = &in1;
    vect[1] = &in2;
    vect[2] = &in3;
    Inregistrare** vectI1 = new Inregistrare * [3];
    vectI1[0] = &in4;
    vectI1[1] = &in5;
    vectI1[2] = &in6;
    Inregistrare** vectI2 = new Inregistrare * [3];
    vectI2[0] = &in7;
    vectI2[1] = &in8;
    vectI2[2] = &in9;
    Coloana c1("Nume", "text", 10,3,vect);
    c1.serializare();
    Coloana c4;
    c4.deserializare();
    cout << "Coloana a fost citita!" << endl;
    cout << c4 << endl;
    Coloana c2("Varsta", "int", 10,3,vectI1);
    Coloana c3("Salariu", "float",10, 3,vectI2);
    Coloana** col = new Coloana * [3];
    col[0] = &c1;
    col[1] = &c2;
    col[2] = &c3;
  

    Tabela t1("Hotel", 3, col);
    vect[0] = &in4;
    cout << "TABELAAAAA" << endl << endl;
    cout << t1 << endl;
    Tabela t2("Receptie", 3, col);
    Tabela t3("Camera", 3, col);
    cout << "Baza de date" << endl << endl;
    t3.serializare();
    Tabela t4;
    t4.deserializare();
    cout << "Tabela a fost citita din binar!"<<endl;
    cout << t4 << endl;
    cout << "--------------------------------" << endl;
    Tabela** tab = new Tabela * [2];
    tab[0] = &t1;
    tab[1] = &t2;
    cout << "--------------------------------" << endl;  
    cout << "--------------------------------" << endl;
    BazaDeDate b1("Proces", 2, tab);
  
    b1.serializare();
    BazaDeDate b2;
    b2.deserializare();
    cout << "Baza de date a fost citita din fisierBinar!"<<endl;
    cout << b2 << endl;
    LDD cd1(b1);
    string comanda2;
    cout << "Introdu Comanda 2: ";
    comanda2 = get_input("comanda: ");
    cout << comanda2 << endl;
    char delimitator1 = ' ';
    char* comandaValabila1 = new char[comanda2.size() + 1];
    strcpy(comandaValabila1, comanda2.c_str());
    cout << comandaValabila1 << endl;
    int nrCuvinte = 1;
    for (int i = 0; i < strlen(comandaValabila1); i++)
    {
        if (comandaValabila1[i] == delimitator1 || comandaValabila1[i] == '\n')
        {
            nrCuvinte++;
        }
    }
    cout << "AICI LUCRAM" << endl;
    cout << nrCuvinte << endl;
    string* comandaF = new string[nrCuvinte];
    int nr = 0;
    for (int i = 0; i < strlen(comandaValabila1); i++)
    {
        if (comandaValabila1[i] != delimitator1)
        {
            if (comandaValabila1[i] != ',')
                comandaF[nr] = comandaF[nr] + comandaValabila1[i];
        }
        else
        {
            nr++;
        }
    }

    for (int i = 0; i < nrCuvinte; i++)
    {
        string comanda[100];
        int numarator = 0;
        cout << comandaF[i] << endl;
        ifstream verifCom(comandaF[i]);
        if (verifCom.is_open())
        {
            while (!verifCom.eof()) {


                cout << "Am gasit fisierul " << comandaF[i] << endl;


                getline(verifCom, comanda[numarator]);
                numarator++;

            }

            string* comenziFinale = new string[numarator];
            for (int j = 0; j < numarator; j++)
            {
                comenziFinale[j] = comanda[j];
            }

            for (int j = 0; j < numarator; j++)
            {
                cout << comenziFinale[j] << endl;
            }
            cout << "numarul de comenzi citite este!:" << numarator << endl;

            cout << "Comenzi Finale" << endl;
            for (int j = 0; j < numarator; j++)
            {
                cout << comenziFinale[j] << endl;
            }

            for (int j = 0; j < numarator; j++)
            {
                char delimitator2 = ' ';
                char* comandaValabila2 = new char[comenziFinale[j].size() + 1];
                strcpy(comandaValabila2, comenziFinale[j].c_str());
                cout << comandaValabila2 << endl;
                int nrCuvinte2 = 1;
                for (int it = 0; it < strlen(comandaValabila2); it++)
                {
                    if (comandaValabila2[it] == delimitator2 || comandaValabila2[it] == '\n')
                    {
                        nrCuvinte2++;
                    }
                }
                cout << "AICI LUCRAM" << endl;
                cout << nrCuvinte2;
                string* comandaF2 = new string[nrCuvinte2];
                int nr2 = 0;
                for (int it = 0; it < strlen(comandaValabila2); it++)
                {
                    if (comandaValabila2[it] != delimitator2)
                    {
                        if (comandaValabila2[it] != ',')
                            comandaF2[nr2] = comandaF2[nr2] + comandaValabila2[it];
                    }
                    else
                    {
                        nr2++;
                    }
                }
                for (int it = 0; it < nrCuvinte2; it++)
                {
                    cout << comandaF2[it] << endl;
                }
                string indetificareComanda2 = comandaF2[0] + " " + comandaF2[1];
                cout << indetificareComanda2 << endl;

                if (indetificareComanda2 == "CREATE TABLE" || indetificareComanda2 == "create table")
                {
                    cout << "cream tabela" << endl;
                    string numeTabela2 = comandaF2[2];
                    ifstream g(numeTabela2 + ".txt");
                    if (g.is_open())
                    {
                        cout << "Numele fisierului deja exista!" << endl;
                    }
                    else
                    {
                        ofstream f(numeTabela2 + ".txt");
                        int nrColoane2 = nrCuvinte2 - 3;
                        string* dateVariabila2 = new string[nrColoane2];
                        for (int it = 3; it < nrCuvinte2; it++)
                        {
                            dateVariabila2[it - 3] = comandaF2[it];
                        }
                        for (int it = 0; it < nrColoane2; it++)
                        {
                            if ((it % 3 == 0) && (it == 0 || it >= 3))
                            {
                                f << dateVariabila2[it] << " \t ";
                            }

                        }
                        f.close();
                        cout << "NR COLOANE!!!! : " << nrColoane2 << endl;
                    }


                }
            }
        }
        else
        {
            cout << "N-am gasit fisierul " << comandaF[i] << endl;

        }
    }

    cout << "Introduceti comanda: ";
    string comanda = "";
    do
    {
        comanda = get_input("comanda: ");
        cout << comanda << endl;
        char delimitator = ' ';
        char* comandaValabila = new char[comanda.size() + 1];
        strcpy(comandaValabila, comanda.c_str());
        cout << comandaValabila << endl;
        int nrCuvinte = 1;
        for (int i = 0; i < strlen(comandaValabila); i++)
        {
            if (comandaValabila[i] == delimitator || comandaValabila[i] == '\n')
            {
                nrCuvinte++;
            }
        }
        cout << "AICI LUCRAM" << endl;
        cout << nrCuvinte;
        string* comandaF = new string[nrCuvinte];
        int nr = 0;
        for (int i = 0; i < strlen(comandaValabila); i++)
        {
            if (comandaValabila[i] != delimitator)
            {
                if (comandaValabila[i] != ',')
                    comandaF[nr] = comandaF[nr] + comandaValabila[i];
            }
            else
            {
                nr++;
            }
        }
        for (int i = 0; i < nrCuvinte; i++)
        {
            cout << comandaF[i] << endl;
        }
        if (nrCuvinte % 3 != 0)
        {
            cout << "Ai gresit comanda" << endl;
        }
        else
        {
            string indetificareComanda = comandaF[0] + " " + comandaF[1];
            cout << indetificareComanda << endl;

            if (indetificareComanda == "CREATE TABLE" || indetificareComanda == "create table")
            {
                cout << "cream tabela" << endl;
                string numeTabela = comandaF[2];
                ifstream g(numeTabela + ".txt");
                if (g.is_open())
                {
                    cout << "Numele fisierului deja exista!" << endl;
                }
                else
                {
                    ofstream f(numeTabela + ".txt");
                    int nrColoane = nrCuvinte - 3;
                    string* dateVariabila = new string[nrColoane];
                    for (int i = 3; i < nrCuvinte; i++)
                    {
                        dateVariabila[i - 3] = comandaF[i];
                    }
                    for (int i = 0; i < nrColoane; i++)
                    {
                        if ((i % 3 == 0) && (i == 0 || i >= 3))
                        {
                            f << dateVariabila[i] << " \t ";
                        }

                    }
                    f.close();
                    cout << "NR COLOANE!!!! : " << nrColoane << endl;
                }


            }
            
            else if (indetificareComanda == "DROP TABLE" || indetificareComanda == "drop table")
            {
                string numeTabela = comandaF[2];
                string fis = numeTabela + ".txt";
                char* aux = new char[fis.size() + 1];
                strcpy(aux, fis.c_str());
                if (remove(aux) == 0)
                    cout << ("Tabela a fost stearsa!\n");
                else
                    cout << ("Tabela invalida! Operatiunea nu a fost efectuata!\n");
            }
            else if (comandaF[0] == "SELECT" || comandaF[0] == "select")
            {
                string numeTabela = comandaF[3];
                string coloana = comandaF[1];
                Tabela tselect;
                Coloana cselect;
                string numeCol = "";
                string numeTab = "";
                int nrT = 0;
                int nrC = 0;
                for (int i = 0; i < b1.getNrTabele(); i++)
                {

                    if (numeTabela == b1.getTabele()[i]->getNume())
                    {
                        tselect = *b1.getTabele()[i];
                        nrT++;
                    }

                }
                if (nrT == 0)
                {
                    cout << "Nu exista tabela cautata!" << endl;
                }
                else
                {
                    LMD s1(tselect);
                    if (coloana == "*")
                    {
                        cout << s1 << endl << endl;
                    }
                    else
                    {
                        for (int i = 0; i < s1.getTab().getNrCol(); i++)
                        {

                            if (coloana == s1.getTab().getCol()[i]->getDenumireColoana())
                            {
                                cout << endl << endl << *s1.getTab().getCol()[i] << endl << endl;
                                nrC++;

                            }
                        }
                        if (nrC == 0)
                        {
                            cout << "Nu exista coloana cautata!" << endl;
                        }
                    }
                }
               
              
            }
        }

    } while (comanda != "-1");
    cout << "Numarul de fisiere totale: " << endl;
    cout << cd1<< endl;
   
}
