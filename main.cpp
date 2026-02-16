#include <iostream>
#include <iomanip>
using namespace std;
struct Mokinys
{
    string vardas, pavarde;
    int ndRez[5], egzRez;
    double galutinis = 0;
};
void ivestis(Mokinys A[], int n);
void skaiciuoti(Mokinys A[], int n);
void rezultatai(Mokinys A[], int n);
int main()
{
    int n = 1;
    Mokinys A[n];
    ivestis(A, n);
    skaiciuoti(A, n);
    rezultatai(A, n);
    return 0;
}

void ivestis(Mokinys A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Vardas - ";
        cin >> A[i].vardas;
        cout << "Pavarde - ";
        cin >> A[i].pavarde;
        cout << endl
             << "Namu darbu tarpiniai pazymiai:" << endl;
        for (int j = 0; j < 5; j++)
            cin >> A[i].ndRez[j];
        cout << "Egzamino rezultatas - ";
        cin >> A[i].egzRez;
    }
}

void skaiciuoti(Mokinys A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 5; j++)
            A[i].galutinis += A[i].ndRez[j];
        A[i].galutinis = A[i].galutinis / 5 * 0.4;
        A[i].galutinis = A[i].galutinis + A[i].egzRez * 0.6;
    }
}

void rezultatai(Mokinys A[], int n)
{
    cout << left
         << setw(15) << "Pavardė"
         << setw(15) << "Vardas"
         << setw(20) << "Galutinis (Vid.)"
         << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < n; i++)
    {
        cout << left
             << setw(15) << A[i].vardas
             << setw(15) << A[i].pavarde
             << setw(20) << fixed << setprecision(2) << A[i].galutinis
             << endl;
    }
    cout << string(70, '-') << endl;   
}