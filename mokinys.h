#ifndef MOKINYS_H
#define MOKINYS_H

#include <vector>
#include <string>

using namespace std;

struct Mokinys
{
    string vardas, pavarde;
    vector<int> ndRez;
    int egzRez;
    double galutinisAVG = 0;
    double galutinisMed = 0;
};

bool tikrinti_zodi(const string &zodis);
void skaiciuoti(vector<Mokinys> &A, int nd);
void rezultatai(const vector<Mokinys> &A);
void generuoti_random(Mokinys &A, int nd);
void nuskaityti(vector<Mokinys> &A, int &nd, const string &failas);
void rikiuoti_1(vector<Mokinys> &A);
void rikiuoti_2(vector<Mokinys> &A);
void generuoti_faila(const string &failo_pav, int kiekis, int nd);
void skaidyti_studentus(const vector<Mokinys> &A);

#endif