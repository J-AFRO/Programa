#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

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

int main()
{
    cin.tie(nullptr);
    srand(time(nullptr));

    vector<Mokinys> A;
    int nd = 0;

    char failas;
    cout << "Ar norite nuskaityti duomenis is failo? (t/n): ";
    while (true)
    {
        cin >> failas;
        if (tolower(failas) != 't' && tolower(failas) != 'n')
        {
            cout << "Klaida. Pasirinkite t arba n. Bandykite dar karta." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else
            break;
    }

    if (tolower(failas) == 't')
    {
        nuskaityti(A, nd);
    }
    else
    {
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

            cout << "Ar prideti dar viena mokini? (t/n): ";
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

    cout << "Pasirinkite rikiavimo buda:" << endl;
    cout << "1 - Pagal galutini rezultata (vidurkis), nuo maziausio iki didziausio" << endl;
    cout << "2 - Pagal galutini rezultata (mediana), nuo didziausio iki maziausio" << endl;
    int rikiuote;
    cin >> rikiuote;

    if (rikiuote == 1)
    {
        rikiuoti_1(A);
    }
    else if (rikiuote == 2)
    {
        rikiuoti_2(A);
    }
    else
    {
        cout << "Pasirinkote neegzistuojama rikiavima. Bus nerikiuota." << endl;
    }

    rezultatai(A);

    return 0;
}

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

    cout << left
         << setw(15) << "Vardas"
         << setw(15) << "Pavarde"
         << setw(20) << "Galutinis (Vid.)"
         << setw(20) << "Galutinis (Med.)\n";

    cout << string(70, '-') << "\n";

    fr << left
       << setw(15) << "Vardas"
       << setw(15) << "Pavarde"
       << setw(20) << "Galutinis (Vid.)"
       << setw(20) << "Galutinis (Med.)\n";

    fr << string(70, '-') << "\n";

    for (const auto &m : A)
    {
        cout << left
             << setw(15) << m.vardas
             << setw(15) << m.pavarde
             << setw(20) << fixed << setprecision(2) << m.galutinisAVG
             << setw(20) << fixed << setprecision(2) << m.galutinisMed
             << "\n";

        fr << left
           << setw(15) << m.vardas
           << setw(15) << m.pavarde
           << setw(20) << fixed << setprecision(2) << m.galutinisAVG
           << setw(20) << fixed << setprecision(2) << m.galutinisMed
           << "\n";
    }

    cout << string(70, '-') << "\n";
    fr << string(70, '-') << "\n";

    fr.close();
}