#include <iostream>
#include <sstream>
#include <cassert>
#include "studentai.h"

void testDefaultKonstruktorius()
{
    Studentas s;
    assert(s.vardas() == "");
    assert(s.pavarde() == "");
    assert(s.galutinis_med() == 0);
    assert(s.galutinis_vid() == 0);
    std::cout << "Default konstruktorius\n";
}

void testStreamKonstruktorius()
{
    std::stringstream ss("Jonas Jonaitis 8 7 9 6 10");
    Studentas s(ss);
    assert(s.vardas() == "Jonas");
    assert(s.pavarde() == "Jonaitis");
    assert(s.galutinis_med() > 0);
    assert(s.galutinis_vid() > 0);
    std::cout << "Stream konstruktorius\n";
}

void testStreamKonstruktoriusSuN()
{
    std::stringstream ss("Jonas Jonaitis 8 7 9 6 10");
    Studentas s(ss, 4); // 4 nd, 10 = egzaminas
    assert(s.vardas() == "Jonas");
    assert(s.galutinis_med() > 0);
    std::cout << "Stream konstruktorius su n\n";
}

void testCopyKonstruktorius()
{
    std::stringstream ss("Petras Petraitis 9 8 7 6");
    Studentas s1(ss);
    Studentas s2(s1); // copy
    assert(s2.vardas() == s1.vardas());
    assert(s2.pavarde() == s1.pavarde());
    assert(s2.galutinis_med() == s1.galutinis_med());
    assert(s2.galutinis_vid() == s1.galutinis_vid());
    std::cout << "Copy konstruktorius\n";
}

void testMoveKonstruktorius()
{
    std::stringstream ss("Antanas Antanaitis 5 6 7 8");
    Studentas s1(ss);
    std::string vardas = s1.vardas();
    Studentas s2(std::move(s1)); // move
    assert(s2.vardas() == vardas);
    assert(s1.vardas() == ""); // s1 tuščias po move
    std::cout << "Move konstruktorius\n";
}

void testCopyAssignment()
{
    std::stringstream ss1("Kazys Kazlauskas 7 8 9 10");
    std::stringstream ss2("Stasys Stasiulis 5 6 7 8");
    Studentas s1(ss1);
    Studentas s2(ss2);
    s2 = s1; // copy assignment
    assert(s2.vardas() == s1.vardas());
    assert(s2.galutinis_med() == s1.galutinis_med());
    std::cout << "Copy assignment\n";
}

void testMoveAssignment()
{
    std::stringstream ss1("Mantas Mantys 6 7 8 9");
    std::stringstream ss2("Rytis Rytas 4 5 6 7");
    Studentas s1(ss1);
    Studentas s2(ss2);
    std::string vardas = s1.vardas();
    s2 = std::move(s1); // move assignment
    assert(s2.vardas() == vardas);
    assert(s1.vardas() == ""); // s1 tuščias po move
    std::cout << "Move assignment\n";
}

void testSelfAssignment()
{
    std::stringstream ss("Darius Dariuskas 8 9 10 7");
    Studentas s(ss);
    s = s; // self-assignment neturi sugadinti
    assert(s.vardas() == "Darius");
    std::cout << "Self-assignment apsauga\n";
}

void testIvestiesOperatorius()
{
    std::stringstream ss("Romas Romaitis 7 8 9 6");
    Studentas s;
    ss >> s; // >> operatorius
    assert(s.vardas() == "Romas");
    assert(s.pavarde() == "Romaitis");
    std::cout << ">> operatorius\n";
}

void testIsvestiesOperatorius()
{
    std::stringstream ss("Linas Linaitis 8 7 6 9");
    Studentas s(ss);
    std::ostringstream os;
    os << s;                   // << operatorius
    assert(!os.str().empty()); // kažkas išvesta
    std::cout << "<< operatorius\n";
    std::cout << "  Išvestis: " << s << "\n";
}

void testDestruktorius()
{
    {
        std::stringstream ss("Jonas Jonaitis 8 7 9 6 10");
        Studentas s(ss);
    } // destruktorius iškviestas čia
    std::cout << "Destruktorius\n";
}
void testAbstrakti()
{
    // Zmogus z; // KLAIDA - abstrakti klasė, nekompiliuojasi
    //  Tai įrodo kad Zmogus yra abstrakti

    Studentas s;         // Studentas - galima
    Zmogus *z = &s;      // rodyklė į bazinę klasę - galima
    z->print(std::cout); // virtualios funkcijos iškvietimas
    std::cout << "\n✓ Abstrakti klase Zmogus - objekto sukurti negalima\n";
}

int main()
{
    std::cout << "=== Studentas klasės testai ===\n\n";
    testDefaultKonstruktorius();
    testStreamKonstruktorius();
    testStreamKonstruktoriusSuN();
    testCopyKonstruktorius();
    testMoveKonstruktorius();
    testCopyAssignment();
    testMoveAssignment();
    testSelfAssignment();
    testIvestiesOperatorius();
    testIsvestiesOperatorius();
    testDestruktorius();
    testAbstrakti();
    std::cout << "\n=== Visi testai praėjo ===\n";
    return 0;
}