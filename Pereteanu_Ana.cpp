#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

int countWord(string str)
{
    int nr = 0;
    
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ' ' || str[i] == ', ')
        {
            nr++;
        }
    }
    return nr;
}

string* wordsNumber(string& str)
{
    
    int nr = countWord(str);
    str = str + " !";
    string* eachWord = new string[nr]; 

    int poz = 0;
    string word = "";
 
    for (int i=0;i<str.size();i++)
    {
        if (str[i] != ' ' && str[i] != ', ' )
        {
            eachWord[poz] == word;
            poz++;
            word = "";
        }
        else {
            if(str[i] != ',')
            word = word + str[i];
        }
    }
    return eachWord;
}
string commandType(string com)
{
    string firstWord= com.substr(0, 6);
    if (com == "CREATE TABLE" || com == "create table")
    {
        return "Comanda tastata este:  create table";
    }
    else if (firstWord== "update" || firstWord== "UPDATE")
    {
         return "Comanda tastata este:  update" ;

    }
    else if (firstWord== "select" || firstWord== "SELECT")
    {
        return "Comanda tastata este:  select" ;

    }
    else if (com == "DROP TABLE" || com == "drop table")
    {

       return "Comanda tastata este:  drop table" ;
    }
    else if (com == "DISPLAY TABLE" || com == "display table")
    {
       return "Comanda tastata este:  display table" ;
    }

    else if (com == "insert into" || com == "INSERT INTO")
    {
         return "Comanda tastata este:  insert";
    }
    else if (com == "delete from" || com == "DELETE FROM")
    {
        return "Comanda tastata este:  delete" ;

    }
    else
    {
        return "Comanda introdusa este gresita";
    }
}
class Value
{
    char* val;
    const int id;
    static int contor;
public:
    Value() :id(contor++)
    {
        this->val = new char[strlen("NULL") + 1];
        strcpy(this->val, "NULL");
    }
    Value(const char* val) :id(contor++)
    {
        this->val = new char[strlen(val) + 1];
        strcpy(this->val, val);
    }
    Value(const Value& in) :id(in.contor)
    {
        this->val = new char[strlen(in.val) + 1];
        strcpy(this->val, in.val);
    }
    ~Value()
    {
        if (this->val != NULL)
        {
            delete[]this->val;
        }
    }
    Value& operator=(const Value& in)
    {
        if (this != &in)
        {
            this->val = new char[strlen(in.val) + 1];
            strcpy(this->val, in.val);
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Value& v)
    {
        out << v.val << "\t\t";
        return out;
    }
    friend ofstream& operator<<(ofstream& out, const Value& v)
    {
        out << v.val << "\t\t";
        return out;
    }
    friend istream& operator>>(istream& in, Value& i)
    {
        char aux[250];
        in >> aux;
        i.val = new char[strlen(aux) + 1];
        strcpy(i.val, aux);
        return in;
    }
};
int Value::contor = 1;


class Column
{
    const int id;
    static int contor;
    string val[3];
public:
    Column() :id(contor++)
    {
        this->val[0] = "NULL";
        this->val[1] = "TEXT";
        this->val[2] = "0";
    }
    Column(string val[3]) :id(contor++)
    {
        for (int i = 0; i < 3; i++)
        {
            this->val[i] = val[i];
        }
    }
    Column(const Column& c) :id(contor++)
    {
        for (int i = 0; i < 3; i++)
        {
            this->val[i] = c.val[i];
        }
    }
    string* getval()
    {
        return this->val;
    }
    void setval(string val[3])
    {
        for (int i = 0; i < 3; i++)
        {
            this->val[i] = val[i];
        }
    }
    Column& operator=(const Column& c)
    {
        for (int i = 0; i < 3; i++)
        {
            this->val[i] = c.val[i];
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Column& c)
    {
        out << c.val[0] << "\t\t";
        /* for (int i = 0; i < 3; i++)
         {
             out << c.val[i] << "\t\t";
         }*/

        return out;
    }
    friend istream& operator>>(istream& in, Column& c)
    {
        for (int i = 0; i < 3; i++)
        {
            in >> c.val[i];
        }

        return in;
    }
    string& operator[](int index)
    {
        if (index >= 0 && index < 3)
        {
            return this->val[index];
        }
    }
};
int Column::contor = 1;
class Row
{
    const int id;
    static int contor;
    int noValues;
    Value** values;
public:
    Value** getValues()
    {
        return values;
    }
    const int getId()
    {
        return this->id;
    }
    Row() :id(contor++)
    {
        this->noValues = 0;
        this->values = nullptr;
    }
    Row(int noValues, Value** values) :id(contor++)
    {
        this->noValues = noValues;
        this->values = new Value * [this->noValues];
        for (int i = 0; i < this->noValues; i++)
        {
            this->values[i] = values[i];
        }
    }
    Row(const Row& r) :id(r.id)
    {
        this->noValues = r.noValues;
        this->values = new Value * [this->noValues];
        for (int i = 0; i < this->noValues; i++)
        {
            this->values[i] = r.values[i];
        }
    }
    ~Row()
    {
        if (this->values != nullptr)
        {
            delete[] this->values;
        }
    }
    Row& operator=(const Row& r)
    {
        if (this != &r)
        {
            if (this->values != nullptr)
            {
                delete[] this->values;
            }
            this->noValues = r.noValues;
            this->values = new Value * [this->noValues];
            for (int i = 0; i < this->noValues; i++)
            {
                this->values[i] = r.values[i];
            }
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Row& r)
    {
        out << r.id << "\t\t";
        for (int i = 0; i < r.noValues; i++)
        {
            out << *r.values[i];
        }
        out << endl;
        return out;
    }
    friend ofstream& operator<<(ofstream& out, const Row& r)
    {
        out << r.id << "\t\t";
        for (int i = 0; i < r.noValues; i++)
        {
            out << *r.values[i];
        }
        out << endl;
        return out;
    }
};
int Row::contor = 1;
class Tabel
{
    string name = "";
    int columnsNo = 0;
    Column** col = nullptr;
    int NoRows = 0;
    Row** row = nullptr;
public:
    string getname()
    {
        return this->name;
    }
    Column** getCol()
    {
        return this->col;
    }
    Row** getRow()
    {
        return this->row;
    }
    Tabel()
    {

    }
    Tabel(string name, int columnsNo, Column** col, int NoRows, Row** row)
    {
        this->name = name;
        this->columnsNo = columnsNo;
        this->col = new Column * [this->columnsNo];
        for (int i = 0; i < this->columnsNo; i++)
        {
            this->col[i] = col[i];
        }
        this->NoRows = NoRows;
        this->row = new Row * [this->NoRows];
        for (int i = 0; i < this->NoRows; i++)
        {
            this->row[i] = row[i];
        }
    }
    Tabel(const Tabel& t)
    {
        this->name = t.name;
        this->columnsNo = t.columnsNo;
        this->col = new Column * [this->columnsNo];
        for (int i = 0; i < this->columnsNo; i++)
        {
            this->col[i] = t.col[i];
        }
        this->NoRows = t.NoRows;
        this->row = new Row * [this->NoRows];
        for (int i = 0; i < this->NoRows; i++)
        {
            this->row[i] = t.row[i];
        }
    }
    ~Tabel()
    {
        if (col != nullptr)
        {
            delete[]col;
        }
        if (row != nullptr)
        {
            delete[]row;
        }
    }
    Tabel& operator=(const Tabel& t)
    {
        if (this != &t)
        {
            if (col != nullptr)
            {
                delete[]col;
            }
            if (row != nullptr)
            {
                delete[]row;
            }
            this->name = t.name;
            this->columnsNo = t.columnsNo;
            this->col = new Column * [this->columnsNo];
            for (int i = 0; i < this->columnsNo; i++)
            {
                this->col[i] = t.col[i];
            }
            this->NoRows = t.NoRows;
            this->row = new Row * [this->NoRows];
            for (int i = 0; i < this->NoRows; i++)
            {
                this->row[i] = t.row[i];
            }
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Tabel& t)
    {
        out << t.name << endl << endl;
        for (int i = 0; i < t.columnsNo; i++)
        {
            out << *t.col[i];
        }
        out << endl;
        for (int i = 0; i < t.NoRows; i++)
        {
            out << *t.row[i];
        }
        out << endl << endl;
        return out;
    }
    friend ofstream& operator<<(ofstream& out, const Tabel& t)
    {
        for (int i = 0; i < t.columnsNo; i++)
        {
            out << *t.col[i];
        }
        out << " ";
        for (int i = 0; i < t.NoRows; i++)
        {
            out << *t.row[i];
        }
        return out;
    }
};
class Database
{
    string databaseName;
    int tablesNo;
    Tabel** tab;
public:
    string getdatabaseName()
    {
        return this->databaseName;
    }
    Tabel** getTabel()
    {
        return tab;
    }

    Database()
    {
        this->databaseName = "";
        this->tablesNo = 0;
        this->tab = nullptr;
    }
    Database(string databaseName, int tablesNo, Tabel** tab)
    {

        this->databaseName = databaseName;
        this->tablesNo = tablesNo;
        this->tab = new Tabel * [this->tablesNo];
        for (int i = 0; i < this->tablesNo; i++)
        {
            this->tab[i] = tab[i];
        }
    }
    Database(const Database& b)
    {
        this->databaseName = b.databaseName;
        this->tablesNo = b.tablesNo;
        this->tab = new Tabel * [this->tablesNo];
        for (int i = 0; i < this->tablesNo; i++)
        {
            this->tab[i] = b.tab[i];
        }
    }
    ~Database()
    {
        if (this->tab != nullptr)
        {
            delete[] this->tab;
        }
    }
    Database& operator=(const Database& b)
    {
        if (this != &b)
        {
            if (this->tab != nullptr)
            {
                delete[] this->tab;
            }
            this->databaseName = b.databaseName;
            this->tablesNo = b.tablesNo;
            this->tab = new Tabel * [this->tablesNo];
            for (int i = 0; i < this->tablesNo; i++)
            {
                this->tab[i] = b.tab[i];
            }
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Database& b)
    {

        for (int i = 0; i < b.tablesNo; i++)
        {
            out << *b.tab[i];
        }
        out << endl;
        return out;
    }


};

//clasa template pentru a gestiona mai usor tabele/Rowurile/coloane
template<class T>
class Gestiune
{
    int nrElemente;
    T* vector;
};
void main()
{
	string comand;
	cout << "Introduceti com: ";
	getline(cin, comand);
    comand = comand + " ";
    int nr = 0;
    nr = countWord(comand);
    char* identifyCommand = new char[comand.size() + 1];
    strcpy(identifyCommand, comand.c_str());
    vector<string> vectCom;
    string word = "";
    for (int i = 0; i < strlen(identifyCommand); i++)
    {
        
        if (identifyCommand[i] != ' ' && identifyCommand[i] != ', ')
        {
            if (identifyCommand[i] != ',')
            {
                word= word+ identifyCommand[i];

            }
        }
        else
        {
            vectCom.push_back(word);
            word = "";
        }
        
    }
    vector<string>::iterator it;

    string com = vectCom[0];
    com += " ";
    com += vectCom[1];
    string message = commandType(com);
    cout << message << endl;
}