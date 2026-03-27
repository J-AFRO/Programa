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

void generuoti_faila(const string &failo_pav, int kiekis, int nd)
{
    ofstream fr(failo_pav);

    fr << left << setw(20) << "Vardas"
       << setw(20) << "Pavarde";

    for (int i = 1; i <= nd; i++)
        fr << setw(8) << ("ND" + to_string(i));

    fr << setw(8) << "Egz." << endl;

    for (int i = 1; i <= kiekis; i++)
    {
        fr << left << setw(20) << ("Vardas" + to_string(i))
           << setw(20) << ("Pavarde" + to_string(i));

        for (int j = 0; j < nd; j++)
            fr << setw(8) << (rand() % 10 + 1);

        fr << setw(8) << (rand() % 10 + 1) << endl;
    }

    fr.close();
}

void nuskaityti(vector<Mokinys> &A, int &nd, const string &failas)
{
    ifstream fd(failas);
    if (!fd)
    {
        cout << "Nepavyko atidaryti failo!" << endl;
        exit(1);
    }

    string header;
    getline(fd, header);

    string tmp;
    stringstream ss(header);
    int count = 0;
    while (ss >> tmp)
        count++;
    nd = count - 3;

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
    A.vardas = "Vardas";
    A.pavarde = "Pavarde";

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

    fr.close();

    cout << "Rezultatai - rezultatai.txt";
}

void skaidyti_studentus(const vector<Mokinys> &A)
{
    ofstream geruliai("geruliai.txt");
    ofstream blogiukai("blogiukai.txt");

    geruliai << left << setw(15) << "Vardas"
             << setw(15) << "Pavarde"
             << setw(20) << "Galutinis (Vid.)"
             << setw(20) << "Galutinis (Med.)\n";

    geruliai << string(70, '-') << "\n";

    blogiukai << left << setw(15) << "Vardas"
              << setw(15) << "Pavarde"
              << setw(20) << "Galutinis (Vid.)"
              << setw(20) << "Galutinis (Med.)\n";

    blogiukai << string(70, '-') << "\n";

    for (const auto &m : A)
    {
        if (m.galutinisAVG >= 5.0)
        {
            geruliai << left
                     << setw(15) << m.vardas
                     << setw(15) << m.pavarde
                     << setw(20) << fixed << setprecision(2) << m.galutinisAVG
                     << setw(20) << fixed << setprecision(2) << m.galutinisMed
                     << "\n";
        }
        else
        {
            blogiukai << left
                      << setw(15) << m.vardas
                      << setw(15) << m.pavarde
                      << setw(20) << fixed << setprecision(2) << m.galutinisAVG
                      << setw(20) << fixed << setprecision(2) << m.galutinisMed
                      << "\n";
        }
    }

    geruliai.close();
    blogiukai.close();

    cout << "Rezultai: geruliai.txt / blogiukai.txt\n";
}