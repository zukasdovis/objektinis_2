#include "rusiavimas.h"
#include "vector.h"
using namespace std;

template <typename Container>
void splitContainer(Container &grupe, Container &silpniakai)
{
    auto it = std::partition(grupe.begin(), grupe.end(), [](const Studentas &s)
                             { return s.galBalas() >= 5.0; });

    silpniakai.insert(silpniakai.end(), it, grupe.end());
    grupe.erase(it, grupe.end());
}

void failoRusiavimas1(int kiekis)
{
    string failas = "studentai_" + to_string(kiekis) + ".txt";
    Vector<Studentas> grupe;

    clock_t start = clock();
    failu_nusk(grupe, failas);
    clock_t end = clock();
    double laikas1 = double(end - start) / CLOCKS_PER_SEC;
    cout << "Faila nuskaite per " << laikas1 << " s\n";

    Vector<Studentas> silpniakai, kietiakai;
    int perskirstymu_sk = 0;
    clock_t start1 = clock();
    for (const auto &student : grupe)
    {
        if (student.galBalas() > 5.0)
        {
            kietiakai.push_back(student);
        }

        else
        {
            silpniakai.push_back(student);
        }
    }
    clock_t end1 = clock();
    double laikas2 = double(end1 - start1) / CLOCKS_PER_SEC;
    cout << "Faila rusiuoti uztruko " << laikas2 << " s\n";

    cout << "Pagal ka rusiuoti? 1-varda 2-pavarde 3-galutinis\n";
    int x;
    cin >> x;
    switch (x)
    {
    case 1:
        sort(kietiakai.begin(), kietiakai.end(), compare);
        sort(silpniakai.begin(), silpniakai.end(), compare);
        break;
    case 2:
        sort(kietiakai.begin(), kietiakai.end(), comparePagalPavarde);
        sort(silpniakai.begin(), silpniakai.end(), comparePagalPavarde);
        break;
    case 3:
        sort(kietiakai.begin(), kietiakai.end(), comparePagalEgza);
        sort(silpniakai.begin(), silpniakai.end(), comparePagalEgza);
        break;
    default:
        cout << "Neteisinga ivestis\n";
        return;
    }

    clock_t start2 = clock();

    string kietiakaiFailas = "kietiakai_" + to_string(kiekis) + ".txt";
    string silpniakaiFailas = "silpniakai_" + to_string(kiekis) + ".txt";
    ofstream kietiakaiF(kietiakaiFailas);
    ofstream silpniakaiF(silpniakaiFailas);

    kietiakaiF << fixed << setprecision(2);
    kietiakaiF << "Vardas          Pavarde         GalutinisBalas\n";
    for (const auto &s : kietiakai)
        kietiakaiF << left << setw(16) << s.vardas()
                   << setw(16) << s.pavarde()
                   << s.galBalas() << "\n";

    silpniakaiF << fixed << setprecision(2);
    silpniakaiF << "Vardas          Pavarde         GalutinisBalas\n";
    for (const auto &s : silpniakai)
        silpniakaiF << left << setw(16) << s.vardas()
                    << setw(16) << s.pavarde()
                    << s.galBalas() << "\n";

    clock_t end2 = clock();
    double laikas3 = double(end2 - start2) / CLOCKS_PER_SEC;
    cout << "Faila irasyti uztruko " << laikas3 << " s\n";
    cout << "Programa uztruko " << laikas1 + laikas2 + laikas3 << " s\n";
}

void failoRusiavimas2(int kiekis)
{
    string failas = "studentai_" + to_string(kiekis) + ".txt";
    Vector<Studentas> grupe;

    clock_t start = clock();
    failu_nusk(grupe, failas);
    clock_t end = clock();
    double laikas1 = double(end - start) / CLOCKS_PER_SEC;
    cout << "Faila nuskaite per " << laikas1 << " s\n";

    Vector<Studentas> silpniakai;

    clock_t start1 = clock();
    sort(grupe.begin(), grupe.end(), comparePagalEgza);
    for (int i = grupe.size() - 1; i >= 0; i--)
    {
        if (grupe[i].galBalas() > 5.0)
            break;
        silpniakai.push_back(grupe[i]);
        grupe.pop_back();
    }
    clock_t end1 = clock();
    double laikas2 = double(end1 - start1) / CLOCKS_PER_SEC;
    cout << "Faila rusiuoti uztruko " << laikas2 << " s\n";

    cout << "Pagal ka rusiuoti? 1-varda 2-pavarde 3-galutinis\n";
    int x;
    cin >> x;
    switch (x)
    {
    case 1:
        sort(grupe.begin(), grupe.end(), compare);
        sort(silpniakai.begin(), silpniakai.end(), compare);
        break;
    case 2:
        sort(grupe.begin(), grupe.end(), comparePagalPavarde);
        sort(silpniakai.begin(), silpniakai.end(), comparePagalPavarde);
        break;
    case 3:
        sort(grupe.begin(), grupe.end(), comparePagalEgza);
        sort(silpniakai.begin(), silpniakai.end(), comparePagalEgza);
        break;
    default:
        cout << "Neteisinga ivestis\n";
        return;
    }

    clock_t start2 = clock();

    string kietiakaiFailas = "kietiakai_" + to_string(kiekis) + ".txt";
    string silpniakaiFailas = "silpniakai_" + to_string(kiekis) + ".txt";
    ofstream kietiakaiF(kietiakaiFailas);
    ofstream silpniakaiF(silpniakaiFailas);

    kietiakaiF << fixed << setprecision(2);
    kietiakaiF << "Vardas          Pavarde         GalutinisBalas\n";
    for (const auto &s : grupe)
        kietiakaiF << left << setw(16) << s.vardas()
                   << setw(16) << s.pavarde()
                   << s.galBalas() << "\n";

    silpniakaiF << fixed << setprecision(2);
    silpniakaiF << "Vardas          Pavarde         GalutinisBalas\n";
    for (const auto &s : silpniakai)
        silpniakaiF << left << setw(16) << s.vardas()
                    << setw(16) << s.pavarde()
                    << s.galBalas() << "\n";

    clock_t end2 = clock();
    double laikas3 = double(end2 - start2) / CLOCKS_PER_SEC;
    cout << "Faila irasyti uztruko " << laikas3 << " s\n";
    cout << "Programa uztruko " << laikas1 + laikas2 + laikas3 << " s\n";
}

void failoRusiavimas3(int kiekis)
{
    string failas = "studentai_" + to_string(kiekis) + ".txt";
    Vector<Studentas> grupe;

    clock_t start = clock();
    failu_nusk(grupe, failas);
    clock_t end = clock();
    double laikas1 = double(end - start) / CLOCKS_PER_SEC;
    cout << "Faila nuskaite per " << laikas1 << " s\n";

    Vector<Studentas> silpniakai;

    clock_t start1 = clock();
    splitContainer(grupe, silpniakai);
    clock_t end1 = clock();
    double laikas2 = double(end1 - start1) / CLOCKS_PER_SEC;
    cout << "Faila rusiuoti uztruko " << laikas2 << " s\n";

    cout << "Pagal ka rusiuoti? 1-varda 2-pavarde 3-galutinis\n";
    int x;
    cin >> x;
    switch (x)
    {
    case 1:
        sort(grupe.begin(), grupe.end(), compare);
        sort(silpniakai.begin(), silpniakai.end(), compare);
        break;
    case 2:
        sort(grupe.begin(), grupe.end(), comparePagalPavarde);
        sort(silpniakai.begin(), silpniakai.end(), comparePagalPavarde);
        break;
    case 3:
        sort(grupe.begin(), grupe.end(), comparePagalEgza);
        sort(silpniakai.begin(), silpniakai.end(), comparePagalEgza);
        break;
    default:
        cout << "Neteisinga ivestis\n";
        return;
    }

    clock_t start2 = clock();

    string kietiakaiFailas = "kietiakai_" + to_string(kiekis) + ".txt";
    string silpniakaiFailas = "silpniakai_" + to_string(kiekis) + ".txt";
    ofstream kietiakaiF(kietiakaiFailas);
    ofstream silpniakaiF(silpniakaiFailas);

    kietiakaiF << fixed << setprecision(2);
    kietiakaiF << "Vardas          Pavarde         GalutinisBalas\n";
    for (const auto &s : grupe)
        kietiakaiF << left << setw(16) << s.vardas()
                   << setw(16) << s.pavarde()
                   << s.galBalas() << "\n";

    silpniakaiF << fixed << setprecision(2);
    silpniakaiF << "Vardas          Pavarde         GalutinisBalas\n";
    for (const auto &s : silpniakai)
        silpniakaiF << left << setw(16) << s.vardas()
                    << setw(16) << s.pavarde()
                    << s.galBalas() << "\n";

    clock_t end2 = clock();
    double laikas3 = double(end2 - start2) / CLOCKS_PER_SEC;
    cout << "Faila irasyti uztruko " << laikas3 << " s\n";
    cout << "Programa uztruko " << laikas1 + laikas2 + laikas3 << " s\n";
}