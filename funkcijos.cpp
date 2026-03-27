#include "mokinys.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;
void nuskaityti(vector<Mokinys> &A, int &nd)
{
    ifstream fd("studentai10000.txt");
    if (!fd)
    {
        cout << "Nepavyko atidaryti failo!" << endl;
        exit(1);
    }

    string header;
    getline(fd, header);

    {
        string tmp;
        stringstream ss(header);
        int count = 0;
        while (ss >> tmp)
            count++;
        nd = count - 3;
    }

    while (true)
    {
        Mokinys m;
        if (!(fd >> m.vardas >> m.pavarde))
            break;

        m.ndRez.resize(nd);
        for (int i = 0; i < nd; i++)
            fd >> m.ndRez[i];

        fd >> m.egzRez;

        A.push_back(move(m));
    }

    fd.close();
}

void generuoti_random(Mokinys &A, int nd)
{
    vector<string> vardai = {"Justas", "Arnas", "Vytas", "Ignas", "Kernius",
                             "Martynas", "Dovydas", "Rolandas", "Matas", "Linas"};
    vector<string> pavardes = {"Viskevicius", "Lekavicius", "Bartuska", "Malinauskas",
                               "Jankus", "Bijauskas", "Andraikenas", "Rinkevicius",
                               "Bujauskas", "Kundzis"};

    A.vardas = vardai[rand() % vardai.size()];
    A.pavarde = pavardes[rand() % pavardes.size()];

    A.ndRez.resize(nd);
    for (int i = 0; i < nd; i++)
        A.ndRez[i] = rand() % 10 + 1;

    A.egzRez = rand() % 10 + 1;
}

bool tikrinti_zodi(const string &zodis)
{
    for (char c : zodis)
        if (!isalpha(c))
            return false;
    return true;
}

void skaiciuoti(vector<Mokinys> &A, int nd)
{
    for (auto &m : A)
    {
        double suma = 0;
        for (int val : m.ndRez)
            suma += val;

        m.galutinisAVG = suma / nd * 0.4 + m.egzRez * 0.6;

        sort(m.ndRez.begin(), m.ndRez.end());

        if (nd % 2 != 0)
            m.galutinisMed = m.ndRez[nd / 2] * 0.4 + m.egzRez * 0.6;
        else
            m.galutinisMed =
                ((m.ndRez[nd / 2] + m.ndRez[nd / 2 - 1]) / 2.0) * 0.4 + m.egzRez * 0.6;
    }
}

void rikiuoti_1(vector<Mokinys> &A)
{
    sort(A.begin(), A.end(), [](const Mokinys &a, const Mokinys &b)
         { return a.galutinisAVG < b.galutinisAVG; });
}

void rikiuoti_2(vector<Mokinys> &A)
{
    sort(A.begin(), A.end(), [](const Mokinys &a, const Mokinys &b)
         { return a.galutinisMed > b.galutinisMed; });
}

void rezultatai(const vector<Mokinys> &A)
{
    ofstream fr("rezultatai.txt");
    if (!fr)
    {
        cout << "Nepavyko sukurti rezultatai.txt failo!" << endl;
        return;
    }
    fr << left
       << setw(15) << "Vardas"
       << setw(15) << "Pavarde"
       << setw(20) << "Galutinis (Vid.)"
       << setw(20) << "Galutinis (Med.)\n";

    fr << string(70, '-') << "\n";

    for (const auto &m : A)
    {
        fr << left
           << setw(15) << m.vardas
           << setw(15) << m.pavarde
           << setw(20) << fixed << setprecision(2) << m.galutinisAVG
           << setw(20) << fixed << setprecision(2) << m.galutinisMed
           << "\n";
    }

    fr << string(70, '-') << "\n";

    fr.close();
}