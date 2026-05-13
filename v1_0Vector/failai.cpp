#include "failai.h"
#include "vector.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

using std::ifstream;
using std::runtime_error;
using std::string;
using std::stringstream;
using std::vector;

void failu_nusk(Vector<Studentas> &grupe, string failas)
{
    ifstream fd(failas);
    if (!fd)
        throw runtime_error("Failas neegzistuoja arba negali buti atidarytas.");

    string line, niekas;
    getline(fd, line);
    stringstream ss(line);
    int n = 0;
    ss >> niekas >> niekas;
    while (ss >> niekas)
        n++;
    n--; // paskutinis yra egzaminas
    int perskirstymu_sk = 0;
    while (getline(fd, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        Studentas A(ss, n); // perduodame n
        if (grupe.size() == grupe.capacity())
            perskirstymu_sk++;
        grupe.push_back(A);
    }
    std::cout << "Perskirstymu skaicius: " << perskirstymu_sk << std::endl;
}