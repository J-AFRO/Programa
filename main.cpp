#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include "mokinys.h"

using namespace std;
using namespace std::chrono;
int main()
{
    ofstream laikas("programos_spartumas.txt");
    
    srand(time(nullptr));
    vector<Mokinys> A;
    int nd = 0;

    cout << "Pasirinkite veiksma:\n";
    cout << "1 - Generuoti faila\n";
    cout << "2 - Skaityti is failo\n";
    cout << "3 - Vesti ranka / random\n";

    int pasirinkimas;
    cin >> pasirinkimas;

    string failo_vardas;

    if (pasirinkimas == 1)
    {
        int dydis;
        cout << "Pasirinkite failo dydi:\n";
        cout << "1 - 1 000\n";
        cout << "2 - 10 000\n";
        cout << "3 - 100 000\n";
        cout << "4 - 1 000 000\n";
        cout << "5 - 10 000 000\n";

        cin >> dydis;

        int kiekis;
        switch (dydis)
        {
        case 1:
            kiekis = 1000;
            break;
        case 2:
            kiekis = 10000;
            break;
        case 3:
            kiekis = 100000;
            break;
        case 4:
            kiekis = 1000000;
            break;
        case 5:
            kiekis = 10000000;
            break;
        default:
            return 0;
        }

        nd = 15;
        failo_vardas = "studentai_" + to_string(kiekis) + ".txt";
        
        auto generavimas_start = high_resolution_clock::now();
        generuoti_faila(failo_vardas, kiekis, nd);
        auto generavimas_end = high_resolution_clock::now();
        
        laikas << "Failo generavimas:"
        << duration<double>(generavimas_end - generavimas_start).count()
        << " s\n";

        auto nuskaitymas_start = high_resolution_clock::now();        
        nuskaityti(A, nd, failo_vardas);
        auto nuskaitymas_end = high_resolution_clock::now();

        laikas << "Failo nuskaitymas:"
        << duration<double>(nuskaitymas_end - nuskaitymas_start).count()
        << " s\n";
    }
    else if (pasirinkimas == 2)
    {
        cout << "Iveskite failo pavadinima: ";
        cin >> failo_vardas;

        auto nuskaitymas_start = high_resolution_clock::now();  
        nuskaityti(A, nd, failo_vardas);
        auto nuskaitymas_end = high_resolution_clock::now();

        laikas << "Failo nuskaitymas:"
        << duration<double>(nuskaitymas_end - nuskaitymas_start).count()
        << " s\n";

    }
    else if (pasirinkimas == 3)
    {
        cout << "ND kiekis: ";
        cin >> nd;
        if (nd < 3)
        {
            cerr << "Klaida. Netinkami skaiciai\n";
            return -1;
        }
        int random;
        cout << "Atsitiktinai?\n";
        cout << "1 - Taip\n";
        cout << "2 - Ne\n";
        cin >> random;

        while (true)
        {
            Mokinys m;

            if (random == 2)
            {
                cout << "Vardas: ";
                cin >> m.vardas;
                if (tikrinti_zodi(m.vardas) == false)
                {
                    cerr << "Klaida. Naudokite tik raides\n";
                    return -1;
                }
                cout << "Pavarde: ";
                cin >> m.pavarde;
                if (tikrinti_zodi(m.pavarde) == false)
                {
                    cerr << "Klaida. Naudokite tik raides\n";
                    return -1;
                }
                m.ndRez.resize(nd);
                cout << "Iveskite pazymius:\n";
                for (int i = 0; i < nd; i++)
                {
                    cin >> m.ndRez[i];
                    if (m.ndRez[i] < 1 || m.ndRez[i] > 10)
                    {
                        cerr << "Klaida. Netinkami skaiciai\n";
                        return -1;
                    }
                }
                cin >> m.egzRez;
                if (m.egzRez < 1 || m.egzRez > 10)
                {
                    cerr << "Klaida. Netinkami skaiciai\n";
                    return -1;
                }
            }
            else if (random == 1)
            {
                generuoti_random(m, nd);
            }
            else
            {
                cerr << "Klaida. Nera tokio pasirinkimo\n";
                return -1;
            }

            A.push_back(m);

            int t;
            cout << "Prideti dar viena mokini?\n";
            cout << "1 - Taip\n";
            cout << "2 - Ne\n";
            cin >> t;
            if (t == 2)
                break;
            else if (t != 1)
            {
                cerr << "Klaida. Nera tokio pasirinkimo\n";
                return -1;
            }
        }
    }

    else
    {
        cerr << "Klaida. Nera tokio pasirinkimo\n";
        return -1;
    }

    skaiciuoti(A, nd);

    int r;
    cout << "Rikiavimas:\n";
    cout << "1 - pagal vid. didėjancia tvarka\n";
    cout << "2 - pagal med. mazejancia tvarka\n";
    cin >> r;

    if (r == 1)
        rikiuoti_1(A);
    else if (r == 2)
        rikiuoti_2(A);
    else
    {
        cerr << "Klaida. Nera tokio pasirinkimo\n";
        return -1;
    }

    int skaidyti;
    cout << "Ar skaidyti i geruliai/blogiukai?\n";
    cout << "1 - Taip\n";
    cout << "2 - Ne\n";
    cin >> skaidyti;

    if (skaidyti == 1)
    {
    
        auto skaidyti_start = high_resolution_clock::now();
        skaidyti_studentus(A);
        auto skaidyti_end = high_resolution_clock::now();
        
        laikas << "Mokiniu skaidymas ir isvedimas:"
            << duration<double>(skaidyti_end - skaidyti_start).count()
            << " s\n";
    }
    else if (skaidyti == 2)
        rezultatai(A);
    else
    {
        cerr << "Klaida. Nera tokio pasirinkimo\n";
        return -1;
    }

    laikas.close();

    return 0;
}