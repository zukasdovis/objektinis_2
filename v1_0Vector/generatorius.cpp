#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>

void generuotiFaila(int kiekis)
{
    clock_t start = clock();
    std::string failas = "studentai_" + std::to_string(kiekis) + ".txt";
    std::ofstream out(failas);

    out << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 ND6 ND7 ND8 ND9 ND10 Egz\n";

    for (int i = 1; i <= kiekis; i++)
    {

        out << "Vardas" << i << " " << "Pavarde" << i << " ";

        for (int i = 0; i < 10; i++)
        {
            int paz = rand() % 10 + 1;
            out << paz << " ";
        }
        int egzaminas = rand() % 10 + 1;
        out << egzaminas << "\n";
    }

    out.close();
    clock_t end = clock();
    double laikas = double(end - start) / CLOCKS_PER_SEC;

    std::cout << "Failas " << kiekis << " dydzio sukurtas per " << laikas << " s\n";
}

void generuotiVisus()
{

    generuotiFaila(1000);
    generuotiFaila(10000);
    generuotiFaila(100000);
    generuotiFaila(1000000);
    generuotiFaila(10000000);
}
