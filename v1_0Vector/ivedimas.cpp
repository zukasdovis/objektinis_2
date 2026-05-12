#include "ivedimas.h"
#include "mediana.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

using std::cin;
using std::cout;
using std::runtime_error;
using std::string;
using std::stringstream;
using std::vector;

void ranka(vector<Studentas> &grupe)
{
    while (true)
    {
        string vardas, pavarde;
        cout << "Iveskite varda ir pavarde (0 0 - baigti): ";
        if (!(cin >> vardas >> pavarde))
            throw runtime_error("Klaida ivestyje");
        if (vardas == "0" && pavarde == "0")
            break;

        string line = vardas + " " + pavarde;

        cout << "Iveskite pazymius (>10 baigti): ";
        int x;
        while (cin >> x && x <= 10)
            line += " " + std::to_string(x);

        int egz;
        cout << "Iveskite egzamino pazymi: ";
        cin >> egz;
        line += " " + std::to_string(egz);

        stringstream ss(line);
        Studentas A(ss);
        grupe.push_back(A);
    }
}

void pazymiu_gen(vector<Studentas> &grupe)
{
    while (true)
    {
        string vardas, pavarde;
        cout << "Iveskite varda pavarde (0 0 - baigti): ";
        if (!(cin >> vardas >> pavarde))
            throw runtime_error("Klaida ivestyje");
        if (vardas == "0" && pavarde == "0")
            break;

        cout << "Kiek pazymiu generuoti: ";
        int kiek;
        cin >> kiek;

        string line = vardas + " " + pavarde;
        for (int i = 0; i < kiek; i++)
            line += " " + std::to_string(rand() % 10 + 1);
        line += " " + std::to_string(rand() % 10 + 1); // egzaminas

        stringstream ss(line);
        Studentas A(ss);
        grupe.push_back(A);
    }
}

void visk_gen(vector<Studentas> &grupe)
{
    const string vardai[10] = {"Jonas", "Petras", "Antanas", "Kazys", "Stasys",
                               "Mantas", "Rytis", "Darius", "Romas", "Linas"};
    const string pavardes[10] = {"Jonaitis", "Petraitis", "Antanaitis", "Kazlauskas",
                                 "Stasytis", "Mantys", "Rytys", "Dariuskas", "Romaitis", "Linaitis"};

    int stud;
    cout << "Kiek studentu generuoti: ";
    cin >> stud;

    int kiek;
    cout << "Kiek pazymiu generuoti: ";
    cin >> kiek;

    while (stud--)
    {
        string vardas = vardai[rand() % 10];
        string pavarde = pavardes[rand() % 10];
        string line = vardas + " " + pavarde;
        for (int i = 0; i < kiek; i++)
            line += " " + std::to_string(rand() % 10 + 1);
        line += " " + std::to_string(rand() % 10 + 1); // egzaminas

        stringstream ss(line);
        Studentas A(ss);
        grupe.push_back(A);
    }
}