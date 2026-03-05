#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "mokinys.h"
using namespace std;
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