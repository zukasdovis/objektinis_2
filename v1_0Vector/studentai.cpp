#include "studentai.h"
#include <iomanip>
#include <sstream>

using std::istream;
using std::ostream;
using std::string;
using std::vector;

// 2. copy konstruktorius
Studentas::Studentas(const Studentas &kitas)
    : Zmogus(kitas), // iškviečiame bazinės klasės copy konstruktorių
      egzaminas_(kitas.egzaminas_),
      nd_(kitas.nd_),
      galutinis_med_(kitas.galutinis_med_),
      galutinis_vid_(kitas.galutinis_vid_)
{
}

// 3. move konstruktorius
Studentas::Studentas(Studentas &&kitas) noexcept
    : Zmogus(std::move(kitas)), // iškviečiame bazinės klasės move konstruktorių
      egzaminas_(kitas.egzaminas_),
      nd_(std::move(kitas.nd_)),
      galutinis_med_(kitas.galutinis_med_),
      galutinis_vid_(kitas.galutinis_vid_)
{
    kitas.egzaminas_ = 0;
    kitas.galutinis_med_ = 0;
    kitas.galutinis_vid_ = 0;
}

// 4. copy assignment
Studentas &Studentas::operator=(const Studentas &kitas)
{
    if (this == &kitas)
        return *this;
    Zmogus::operator=(kitas); // bazinės klasės copy assignment
    egzaminas_ = kitas.egzaminas_;
    nd_ = kitas.nd_;
    galutinis_med_ = kitas.galutinis_med_;
    galutinis_vid_ = kitas.galutinis_vid_;
    return *this;
}

// 5. move assignment
Studentas &Studentas::operator=(Studentas &&kitas) noexcept
{
    if (this == &kitas)
        return *this;
    Zmogus::operator=(std::move(kitas)); // bazinės klasės move assignment
    egzaminas_ = kitas.egzaminas_;
    nd_ = std::move(kitas.nd_);
    galutinis_med_ = kitas.galutinis_med_;
    galutinis_vid_ = kitas.galutinis_vid_;
    kitas.egzaminas_ = 0;
    kitas.galutinis_med_ = 0;
    kitas.galutinis_vid_ = 0;
    return *this;
}

// papildomi konstruktoriai
Studentas::Studentas(istream &is) : Zmogus()
{
    readStudent(is);
}

Studentas::Studentas(istream &is, int n) : Zmogus()
{
    readStudent(is, n);
}

// galBalas
double Studentas::galBalas(double (*f)(vector<int>)) const
{
    if (f == mediana)
        return galutinis_med_;
    return galutinis_vid_;
}

// readStudent be n
istream &Studentas::readStudent(istream &is)
{
    is >> vardas_ >> pavarde_;
    nd_.clear();
    int x;
    while (is.peek() != '\n' && is >> x)
        nd_.push_back(x);
    if (!nd_.empty())
    {
        egzaminas_ = nd_.back();
        nd_.pop_back();
    }
    galutinis_med_ = 0.4 * mediana(nd_) + 0.6 * egzaminas_;
    galutinis_vid_ = 0.4 * vidurkis(nd_) + 0.6 * egzaminas_;
    return is;
}

// readStudent su n
istream &Studentas::readStudent(istream &is, int n)
{
    is >> vardas_ >> pavarde_;
    nd_.clear();
    nd_.reserve(n);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        int x;
        is >> x;
        nd_.push_back(x);
        sum += x;
    }
    is >> egzaminas_;
    galutinis_med_ = 0.4 * mediana(nd_) + 0.6 * egzaminas_;
    galutinis_vid_ = (n != 0) ? 0.4 * ((double)sum / n) + 0.6 * egzaminas_
                              : 0.6 * egzaminas_;
    return is;
}

// print - virtualios funkcijos realizacija
void Studentas::print(ostream &os) const
{
    os << std::fixed << std::setprecision(2);
    os << std::left << std::setw(16) << vardas_
       << std::setw(16) << pavarde_
       << std::setw(16) << galutinis_med_
       << std::setw(16) << galutinis_vid_;
}

// >> operatorius
istream &operator>>(istream &is, Studentas &s)
{
    return s.readStudent(is);
}

// << operatorius
ostream &operator<<(ostream &os, const Studentas &s)
{
    s.print(os);
    return os;
}

// compare funkcijos
bool compare(const Studentas &A, const Studentas &B)
{
    return A.vardas() < B.vardas();
}

bool comparePagalPavarde(const Studentas &A, const Studentas &B)
{
    return A.pavarde() < B.pavarde();
}

bool comparePagalEgza(const Studentas &A, const Studentas &B)
{
    return A.galBalas() < B.galBalas();
}