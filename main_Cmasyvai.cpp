#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Mokinys
{
    string vardas, pavarde;
    int *ndRez = nullptr;
    int egzRez;
    double galutinisAVG = 0;
    double galutinisMed = 0;
};

bool tikrinti_zodi(const string &zodis);
void skaiciuoti(Mokinys *A, int kiekis, int nd);
void rezultatai(Mokinys *A, int kiekis);
void generuoti_random(Mokinys &A, int nd);

int main()
{
    srand(time(nullptr));

    int nd;
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

    Mokinys *A = nullptr;
    int kiekis = 0;

    while (true)
    {
        Mokinys m;
        m.ndRez = new int[nd];

        if (tolower(pasirinkimas) != 't')
        {
            cout << "Vardas: ";
            cin >> m.vardas;
            if (m.vardas.empty())
                break;

            cout << "Pavarde: ";
            cin >> m.pavarde;

            cout << "Namu darbu rezultatai:" << endl;
            for (int i = 0; i < nd; i++)
            {
                cin >> m.ndRez[i];
            }

            cout << "Egzamino rezultatas: ";
            cin >> m.egzRez;
        }
        else
        {
            generuoti_random(m, nd);
        }

        Mokinys *temp = new Mokinys[kiekis + 1];
        for (int i = 0; i < kiekis; i++)
            temp[i] = A[i];

        temp[kiekis] = m;

        delete[] A;
        A = temp;
        kiekis++;

        cout << "Ar ivesti dar viena mokini? (t/n): ";
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

    skaiciuoti(A, kiekis, nd);
    rezultatai(A, kiekis);

    for (int i = 0; i < kiekis; i++)
        delete[] A[i].ndRez;
    delete[] A;

    return 0;
}

void generuoti_random(Mokinys &A, int nd)
{
    string vardai[] = {"Justas", "Arnas", "Vytas", "Ignas", "Kernius",
                       "Martynas", "Dovydas", "Rolandas", "Matas", "Linas"};

    string pavardes[] = {"Viskevicius", "Lekavicius", "Bartuska",
                         "Malinauskas", "Jankus", "Bijauskas",
                         "Andraikenas", "Rinkevicius",
                         "Bujauskas", "Kundzis"};

    A.vardas = vardai[rand() % 10];
    A.pavarde = pavardes[rand() % 10];

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

void skaiciuoti(Mokinys *A, int kiekis, int nd)
{
    for (int i = 0; i < kiekis; i++)
    {
        double suma = 0;
        for (int j = 0; j < nd; j++)
            suma += A[i].ndRez[j];

        A[i].galutinisAVG = suma / nd * 0.4 + A[i].egzRez * 0.6;

        sort(A[i].ndRez, A[i].ndRez + nd);

        if (nd % 2 != 0)
            A[i].galutinisMed = A[i].ndRez[nd / 2] * 0.4 + A[i].egzRez * 0.6;
        else
            A[i].galutinisMed =
                ((A[i].ndRez[nd / 2] + A[i].ndRez[nd / 2 - 1]) / 2.0) * 0.4 +
                A[i].egzRez * 0.6;
    }
}

void rezultatai(Mokinys *A, int kiekis)
{
    cout << left
         << setw(15) << "Vardas"
         << setw(15) << "Pavarde"
         << setw(20) << "Galutinis (Vid.)"
         << setw(20) << "Galutinis (Med.)"
         << endl;

    cout << string(70, '-') << endl;

    for (int i = 0; i < kiekis; i++)
    {
        cout << left
             << setw(15) << A[i].vardas
             << setw(15) << A[i].pavarde
             << setw(20) << fixed << setprecision(2) << A[i].galutinisAVG
             << setw(20) << fixed << setprecision(2) << A[i].galutinisMed
             << endl;
    }

    cout << string(70, '-') << endl;
}