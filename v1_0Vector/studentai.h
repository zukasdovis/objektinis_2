#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "Zmogus.h"
#include "mediana.h"
#include <vector>

/**
 * @file studentai.h
 * @brief Studentas klasė išvesta iš Zmogus
 * @author jusu vardas
 * @version 1.5
 */

/**
 * @class Studentas
 * @brief Išvestinė klasė iš Zmogus studento duomenims saugoti
 *
 * Saugo namų darbų pažymius, egzamino pažymį ir
 * skaičiuoja galutinius balus pagal medianą arba vidurkį.
 *
 * @note Galutinio balo formulė:
 * @code
 * galutinis = 0.4 * nd_rezultatas + 0.6 * egzaminas
 * @endcode
 *
 * Naudojimo pavyzdys:
 * @code
 * // Sukurti iš srauto
 * std::stringstream ss("Jonas Jonaitis 8 7 9 6 10");
 * Studentas s(ss);
 *
 * // Išvesti
 * std::cout << s;
 *
 * // Gauti balą
 * double med = s.galBalas(mediana);
 * double vid = s.galBalas(vidurkis);
 * @endcode
 */
class Studentas : public Zmogus
{
private:
    double egzaminas_;     ///< Egzamino pažymys
    std::vector<int> nd_;  ///< Namų darbų pažymiai
    double galutinis_med_; ///< Galutinis balas pagal medianą (cache)
    double galutinis_vid_; ///< Galutinis balas pagal vidurkį (cache)

public:
    /**
     * @brief Default konstruktorius
     * Sukuria tuščią studento objektą
     */
    Studentas() : Zmogus(), egzaminas_(0), galutinis_med_(0), galutinis_vid_(0) {}

    /**
     * @brief Copy konstruktorius
     * @param kitas kopijuojamas studentas
     */
    Studentas(const Studentas &kitas);

    /**
     * @brief Move konstruktorius
     * @param kitas perkeliamas studentas - po perkėlimo tampa tuščias
     */
    Studentas(Studentas &&kitas) noexcept;

    /**
     * @brief Copy priskyrimo operatorius
     * @param kitas kopijuojamas studentas
     * @return nuoroda į šį objektą
     */
    Studentas &operator=(const Studentas &kitas);

    /**
     * @brief Move priskyrimo operatorius
     * @param kitas perkeliamas studentas - po perkėlimo tampa tuščias
     * @return nuoroda į šį objektą
     */
    Studentas &operator=(Studentas &&kitas) noexcept;

    /**
     * @brief Destruktorius
     */
    ~Studentas() override {}

    /**
     * @brief Konstruktorius iš įvesties srauto (be n)
     * Naudojamas rankiniam įvedimui per cin arba stringstream.
     * Skaito kol randa '\\n'.
     * @param is įvesties srautas
     */
    Studentas(std::istream &is);

    /**
     * @brief Konstruktorius iš įvesties srauto (su n)
     * Naudojamas failo skaitymui kai žinomas pažymių kiekis.
     * Greitesnis už versiją be n.
     * @param is įvesties srautas
     * @param n namų darbų pažymių kiekis
     */
    Studentas(std::istream &is, int n);

    /**
     * @brief Grąžina galutinį balą pagal medianą (cache)
     * @return galutinis balas pagal medianą
     */
    inline double galutinis_med() const { return galutinis_med_; }

    /**
     * @brief Grąžina galutinį balą pagal vidurkį (cache)
     * @return galutinis balas pagal vidurkį
     */
    inline double galutinis_vid() const { return galutinis_vid_; }

    /**
     * @brief Skaičiuoja galutinį balą pagal pasirinktą funkciją
     * @param f funkcija skaičiavimui - mediana arba vidurkis (default: mediana)
     * @return galutinis balas
     *
     * Pavyzdys:
     * @code
     * s.galBalas()          // naudoja medianą
     * s.galBalas(mediana)   // naudoja medianą
     * s.galBalas(vidurkis)  // naudoja vidurkį
     * @endcode
     */
    double galBalas(double (*f)(std::vector<int>) = mediana) const;

    /**
     * @brief Nuskaito studento duomenis iš srauto (be n)
     * Realizuoja Zmogus grynąją virtualią funkciją.
     * @param is įvesties srautas
     * @return srautas po nuskaitymo
     */
    std::istream &readStudent(std::istream &is) override;

    /**
     * @brief Nuskaito studento duomenis iš srauto (su n)
     * Greitesnė versija kai žinomas pažymių kiekis.
     * @param is įvesties srautas
     * @param n namų darbų pažymių kiekis
     * @return srautas po nuskaitymo
     */
    std::istream &readStudent(std::istream &is, int n);

    /**
     * @brief Išveda studento duomenis į srautą
     * Realizuoja Zmogus grynąją virtualią funkciją.
     * @param os išvesties srautas
     */
    void print(std::ostream &os) const override;

    /**
     * @brief Įvesties operatorius
     * @param is įvesties srautas
     * @param s studentas į kurį skaitoma
     * @return srautas po nuskaitymo
     *
     * Pavyzdys:
     * @code
     * Studentas s;
     * std::cin >> s;
     * std::ifstream f("studentai.txt");
     * f >> s;
     * @endcode
     */
    friend std::istream &operator>>(std::istream &is, Studentas &s);

    /**
     * @brief Išvesties operatorius
     * @param os išvesties srautas
     * @param s išvedamas studentas
     * @return srautas su studento duomenimis
     *
     * Pavyzdys:
     * @code
     * Studentas s;
     * std::cout << s;
     * std::ofstream f("rezultatai.txt");
     * f << s;
     * @endcode
     */
    friend std::ostream &operator<<(std::ostream &os, const Studentas &s);
};

/**
 * @brief Lygina du studentus pagal vardą
 * @param A pirmasis studentas
 * @param B antrasis studentas
 * @return true jei A.vardas < B.vardas
 */
bool compare(const Studentas &, const Studentas &);

/**
 * @brief Lygina du studentus pagal pavardę
 * @param A pirmasis studentas
 * @param B antrasis studentas
 * @return true jei A.pavarde < B.pavarde
 */
bool comparePagalPavarde(const Studentas &, const Studentas &);

/**
 * @brief Lygina du studentus pagal galutinį balą
 * @param A pirmasis studentas
 * @param B antrasis studentas
 * @return true jei A.galBalas < B.galBalas
 */
bool comparePagalEgza(const Studentas &, const Studentas &);

#endif