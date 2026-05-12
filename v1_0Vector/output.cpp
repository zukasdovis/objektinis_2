#include "output.h"
#include "mediana.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using std::cout;
using std::endl;
using std::fixed;
using std::left;
using std::ofstream;
using std::setprecision;
using std::setw;
using std::vector;

void outputas(vector<Studentas> &grupe)
{
    cout << fixed << setprecision(2);
    cout << left << setw(16) << "Vardas"
         << setw(16) << "Pavarde"
         << setw(16) << "Galutinis(med)"
         << setw(16) << "Galutinis(vid)" << endl;
    for (const auto &A : grupe)
    {
        cout << left << setw(16) << A.vardas()
             << setw(16) << A.pavarde()
             << setw(16) << A.galBalas(mediana)
             << setw(16) << A.galBalas(vidurkis) << endl;
    }
}

void outputas_fr(vector<Studentas> &grupe)
{
    ofstream fr("rezultatai.txt");
    fr << fixed << setprecision(2);
    fr << left << setw(16) << "Vardas"
       << setw(16) << "Pavarde"
       << setw(16) << "Galutinis(med)"
       << setw(16) << "Galutinis(vid)" << "\n";
    for (const auto &A : grupe)
    {
        fr << left << setw(16) << A.vardas()
           << setw(16) << A.pavarde()
           << setw(16) << A.galBalas(mediana)
           << setw(16) << A.galBalas(vidurkis) << "\n";
    }
}