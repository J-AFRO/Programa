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
void ivestis(vector<Mokinys> &A, int nd);
void skaiciuoti(vector<Mokinys> &A, int nd);
void rezultatai(const vector<Mokinys> &A);
void generuoti_random(Mokinys &A, int nd);
void nuskaityti(vector<Mokinys> &A, int &nd);
void rikiuoti_1(vector<Mokinys> &A);
void rikiuoti_2(vector<Mokinys> &A);

#endif