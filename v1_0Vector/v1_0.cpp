#include <iostream>
#include <vector>
#include "vector.h"
#include <string>
#include <algorithm>
#include <stdexcept>

#include "studentai.h"
#include "ivedimas.h"
#include "failai.h"
#include "rusiavimas.h"
#include "output.h"
#include "generatorius.h"
#include "tyrimai.h"

using std::cin;
using std::cout;
using std::endl;
using std::exception;
using std::runtime_error;
using std::string;
using std::vector;

int main()
{
    srand(time(0));
    Vector<Studentas> grupe;

    while (true)
    {
        cout << "1-ranka 2-generuoti pazymius 3-viska generuoti 4-skaityti faila\n";
        cout << "6-rusiuoti varda 7-pavarde 8-galutinis\n";
        cout << "9-i faila 10-i ekrana 11-atlikti tyrimus 5-baigti\n";

        int x;
        try
        {
            cin >> x;
            if (!cin)
                throw runtime_error("Neteisinga ivestis");
        }
        catch (exception &e)
        {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        try
        {
            if (x == 1)
                ranka(grupe);
            else if (x == 2)
                pazymiu_gen(grupe);
            else if (x == 3)
                visk_gen(grupe);
            else if (x == 4)
            {
                string failas;
                cout << "Iveskite failo pavadinima: ";
                cin >> failas;
                failu_nusk(grupe, failas);
            }
            else if (x == 6)
                sort(grupe.begin(), grupe.end(), compare);
            else if (x == 7)
                sort(grupe.begin(), grupe.end(), comparePagalPavarde);
            else if (x == 8)
                sort(grupe.begin(), grupe.end(), comparePagalEgza);
            else if (x == 9)
                outputas_fr(grupe);
            else if (x == 10)
                outputas(grupe);
            else if (x == 11)
                tyrimai();
            else
                break;
        }
        catch (exception &e)
        {
            cout << "Klaida: " << e.what() << endl;
        }
    }

    cout << "Programa baige darba" << endl;
    return 0;
}