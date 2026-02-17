#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
using namespace std;
struct Mokinys
{
    string vardas, pavarde;
    int ndRez[100], egzRez;
    double galutinisAVG = 0;
    double galutinisMed = 0;
};
bool tikrinti_zodi(const string &zodis);
void ivestis(Mokinys A[], int n, int nd);
void skaiciuoti(Mokinys A[], int n, int nd);
void rezultatai(Mokinys A[], int n);
int main()
{
    int n = 1, nd = 5;
    Mokinys A[n];
    ivestis(A, n, nd);
    skaiciuoti(A, n, nd);
    rezultatai(A, n);
    return 0;
}

void ivestis(Mokinys A[], int n, int nd)
{
    for (int i = 0; i < n; i++)
    {

        do
        {
            cout << "Vardas - ";
            cin >> A[i].vardas;
            if (!tikrinti_zodi(A[i].vardas))
                cout << "Klaida! Galima naudoti tik raides." << endl;

        } while (!tikrinti_zodi(A[i].vardas));

        do
        {
            cout << "Pavarde - ";
            cin >> A[i].pavarde;
            if (!tikrinti_zodi(A[i].pavarde))
                cout << "Klaida! Galima naudoti tik raides." << endl;

        } while (!tikrinti_zodi(A[i].pavarde));

        cout << endl
             << "Namu darbu tarpiniai pazymiai:" << endl;

        for (int j = 0; j < nd; j++)
        {
            while (true)
            {
                cin >> A[i].ndRez[j];

                if (cin.fail())
                {
                    cout << "Klaida! Galima naudoti tik skaicius. Bandykite dar karta." << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }

                if (A[i].ndRez[j] < 1 && A[i].ndRez[j] > 10)
                {
                    cout << "Klaida! Skaicius per didelis/per mazas. Bandykite dar karta." << endl;
                    continue;
                }
                else
                    break;
            }
        }
        cout << "Egzamino rezultatas - ";
        while (true)
        {
            cin >> A[i].egzRez;

            if (cin.fail())
            {
                cout << "Klaida! Galima naudoti tik skaicius. Bandykite dar karta." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            if (A[i].egzRez < 1 && A[i].egzRez > 10)
            {
                cout << "Klaida! Skaicius per didelis/per mazas. Bandykite dar karta." << endl;
                continue;
            }
            else
                break;
        }
    }
}

bool tikrinti_zodi(const string &zodis)
{
    for (char c : zodis)
    {
        if (!isalpha(c))
        {
            return false;
        }
    }
    return true;
}

void skaiciuoti(Mokinys A[], int n, int nd)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < nd; j++)
            A[i].galutinisAVG += A[i].ndRez[j];
        A[i].galutinisAVG = A[i].galutinisAVG / nd * 0.4;
        A[i].galutinisAVG = A[i].galutinisAVG + A[i].egzRez * 0.6;

        sort(A[i].ndRez, A[i].ndRez + nd);
        if (nd % 2 != 0)
            A[i].galutinisMed = A[i].ndRez[nd / 2] * 0.4 + A[i].egzRez * 0.6;
        else
            A[i].galutinisMed = (A[i].ndRez[(nd - 1) / 2] + A[i].ndRez[nd / 2]) / 2.0 * 0.4 + A[i].egzRez * 0.6;
    }
}

void rezultatai(Mokinys A[], int n)
{
    cout << left
         << setw(15) << "Pavardė"
         << setw(15) << "Vardas"
         << setw(20) << "Galutinis (Vid.)"
         << setw(20) << "Galutinis (Med.)"
         << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < n; i++)
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