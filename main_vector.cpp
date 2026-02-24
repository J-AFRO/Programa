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

int main()
{
    cin.tie(nullptr);

    srand(time(nullptr));

    vector<Mokinys> A;
    int nd = 0;

    char failas;
    cout << "Ar norite nuskaityti duomenis is failo? (t/n): ";
    cin >> failas;

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
                cout << "Klaida! Galima naudoti skaicius > 2. Bandykite dar karta.\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            else
                break;
        }

        char pasirinkimas;
        cout << "Ar norite sugeneruoti rezultatus atsitiktinai? (t/n): ";
        cin >> pasirinkimas;

        while (true)
        {
            Mokinys m;

            if (tolower(pasirinkimas) != 't')
            {
                cout << "Vardas: ";
                cin >> m.vardas;
                if (m.vardas.empty())
                    break;

                cout << "Pavarde: ";
                cin >> m.pavarde;

                m.ndRez.resize(nd);
                cout << "Namu darbu rezultatai:\n";
                for (int i = 0; i < nd; i++)
                    cin >> m.ndRez[i];

                cout << "Egzamino rezultatas: ";
                cin >> m.egzRez;
            }
            else
            {
                generuoti_random(m, nd);
            }

            A.push_back(m);

            cout << "Ar prideti dar viena mokini? (t/n): ";
            char dar;
            cin >> dar;
            if (tolower(dar) != 't')
                break;
        }
    }

    skaiciuoti(A, nd);
    rezultatai(A);

    return 0;
}

void nuskaityti(vector<Mokinys> &A, int &nd)
{
    ifstream fd("studentai1000000.txt");
    if (!fd)
    {
        cout << "Nepavyko atidaryti failo!\n";
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

    A.reserve(1000000);

    while (true)
    {
        Mokinys m;
        if (!(fd >> m.vardas >> m.pavarde))
            break;

        m.ndRez.resize(nd);
        for (int i = 0; i < nd; i++)
            fd >> m.ndRez[i];

        fd >> m.egzRez;

        A.push_back(std::move(m));
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

void rezultatai(const vector<Mokinys> &A)
{
    ofstream fr("rezultatai.txt");
    if (!fr)
    {
        cout << "Nepavyko sukurti rezultatai.txt failo!\n";
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
