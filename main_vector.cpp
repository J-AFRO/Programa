#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
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

int main()
{
    srand(time(nullptr));

    int nd;
    vector<Mokinys> A;

    cout << "Iveskite namu darbu skaiciu - ";
    while (true)
    {
        cin >> nd;
        if (cin.fail() || nd < 3)
        {
            cout << "Klaida! Galima naudoti skaicius > 2. Bandykite dar karta." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else
            break;
    }

    char pasirinkimas;
    cout << "Ar norite sugeneruoti rezultatus atsitiktinai? (t/n): ";
    while (true)
    {
        cin >> pasirinkimas;
        if (tolower(pasirinkimas) != 't' && tolower(pasirinkimas) != 'n')
        {
            cout << "Klaida. Pasirinkite t arba n. Bandykite dar karta." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else
            break;
    }

    while (true)
    {
        Mokinys m;
        if (tolower(pasirinkimas) != 't')
        {
            do
            {
                cout << "Vardas: ";
                cin >> m.vardas;
                if (m.vardas.empty())
                    break;
            } while (!tikrinti_zodi(m.vardas));

            if (m.vardas.empty())
                break;

            do
            {
                cout << "Pavarde: ";
                cin >> m.pavarde;
            } while (!tikrinti_zodi(m.pavarde));

            m.ndRez.resize(nd);
            cout << "Namu darbu rezultatai:" << endl;
            for (int i = 0; i < nd; i++)
            {
                while (true)
                {
                    cin >> m.ndRez[i];
                    if (cin.fail() || m.ndRez[i] < 1 || m.ndRez[i] > 10)
                    {
                        cout << "Klaida! Skaicius nuo 1 iki 10. Bandykite dar karta." << endl;
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    else
                        break;
                }
            }
            cout << "Egzamino rezultatas: ";
            while (true)
            {
                cin >> m.egzRez;
                if (cin.fail() || m.egzRez < 1 || m.egzRez > 10)
                {
                    cout << "Klaida! Skaicius nuo 1 iki 10. Bandykite dar karta." << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else
                    break;
            }
        }
        else
        {
            generuoti_random(m, nd);
        }

        A.push_back(m);

        if (tolower(pasirinkimas) != 't')
        {
            cout << "Ar norite ivesti dar viena mokini? (t/n): ";
            char dar;
            while (true)
            {
                cin >> dar;
                if (tolower(dar) != 't' && tolower(dar) != 'n')
                {
                    cout << "Klaida. Pasirinkite t arba n. Bandykite dar karta." << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else
                    break;
            }
            if (tolower(dar) != 't')
                break;
        }
        else
        {
            cout << "Ar generuoti dar viena mokini? (t/n): ";
            char dar;
            while (true)
            {
                cin >> dar;
                if (tolower(dar) != 't' && tolower(dar) != 'n')
                {
                    cout << "Klaida. Pasirinkite t arba n. Bandykite dar karta." << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else
                    break;
            }
            if (tolower(dar) != 't')
                break;
        }
    }

    skaiciuoti(A, nd);
    rezultatai(A);
    return 0;
}

void generuoti_random(Mokinys &A, int nd)
{
    vector<string> vardai = {"Justas", "Arnas", "Vytas", "Ignas", "Kernius", "Martynas", "Dovydas", "Rolandas", "Matas", "Linas"};
    vector<string> pavardes = {"Viskevicius", "Lekavicius", "Bartuska", "Malinauskas", "Jankus", "Bijauskas", "Andraikenas", "Rinkevicius", "Bujauskas", "Kundzis"};
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
            m.galutinisMed = ((m.ndRez[nd / 2] + m.ndRez[nd / 2 - 1]) / 2.0) * 0.4 + m.egzRez * 0.6;
    }
}

void rezultatai(const vector<Mokinys> &A)
{
    cout << left
         << setw(15) << "Vardas"
         << setw(15) << "Pavarde"
         << setw(20) << "Galutinis (Vid.)"
         << setw(20) << "Galutinis (Med.)"
         << endl;
    cout << string(70, '-') << endl;
    for (const auto &m : A)
        cout << left
             << setw(15) << m.vardas
             << setw(15) << m.pavarde
             << setw(20) << fixed << setprecision(2) << m.galutinisAVG
             << setw(20) << fixed << setprecision(2) << m.galutinisMed << endl;
    cout << string(70, '-') << endl;
}
