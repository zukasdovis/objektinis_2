#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>
#include <iostream>

/**
 * @file Zmogus.h
 * @brief Abstrakti bazinė klasė žmogui aprašyti
 * @author jusu vardas
 * @version 1.5
 */

/**
 * @class Zmogus
 * @brief Abstrakti bazinė klasė. Tiesiogiai objektų kurti negalima.
 *
 * Aprašo bendrą žmogų su vardu ir pavarde.
 * Išvestinės klasės privalo realizuoti readStudent() ir print().
 *
 * @note Objektų kurti negalima:
 * @code
 * Zmogus z;        // KLAIDA - abstrakti klasė
 * Studentas s;     // GERAI - išvestinė klasė
 * Zmogus* z = &s;  // GERAI - rodyklė į bazinę klasę
 * @endcode
 */
class Zmogus
{
protected:
    std::string vardas_;  ///< Žmogaus vardas
    std::string pavarde_; ///< Žmogaus pavardė

public:
    /**
     * @brief Default konstruktorius
     * Sukuria tuščią žmogaus objektą
     */
    Zmogus() : vardas_(""), pavarde_("") {}

    /**
     * @brief Konstruktorius su parametrais
     * @param vardas žmogaus vardas
     * @param pavarde žmogaus pavardė
     */
    Zmogus(const std::string &vardas, const std::string &pavarde)
        : vardas_(vardas), pavarde_(pavarde) {}

    /**
     * @brief Copy konstruktorius
     * @param kitas kopijuojamas objektas
     */
    Zmogus(const Zmogus &kitas)
        : vardas_(kitas.vardas_), pavarde_(kitas.pavarde_) {}

    /**
     * @brief Move konstruktorius
     * @param kitas perkeliamas objektas - po perkėlimo tampa tuščias
     */
    Zmogus(Zmogus &&kitas) noexcept
        : vardas_(std::move(kitas.vardas_)),
          pavarde_(std::move(kitas.pavarde_)) {}

    /**
     * @brief Copy priskyrimo operatorius
     * @param kitas kopijuojamas objektas
     * @return nuoroda į šį objektą
     */
    Zmogus &operator=(const Zmogus &kitas)
    {
        if (this == &kitas)
            return *this;
        vardas_ = kitas.vardas_;
        pavarde_ = kitas.pavarde_;
        return *this;
    }

    /**
     * @brief Move priskyrimo operatorius
     * @param kitas perkeliamas objektas - po perkėlimo tampa tuščias
     * @return nuoroda į šį objektą
     */
    Zmogus &operator=(Zmogus &&kitas) noexcept
    {
        if (this == &kitas)
            return *this;
        vardas_ = std::move(kitas.vardas_);
        pavarde_ = std::move(kitas.pavarde_);
        return *this;
    }

    /**
     * @brief Virtualus destruktorius
     * Būtinas abstrakčiai klasei su virtualiais metodais
     */
    virtual ~Zmogus() {}

    /**
     * @brief Grąžina vardą
     * @return vardas kaip string
     */
    inline std::string vardas() const { return vardas_; }

    /**
     * @brief Grąžina pavardę
     * @return pavardė kaip string
     */
    inline std::string pavarde() const { return pavarde_; }

    /**
     * @brief Grynoji virtuali funkcija duomenų nuskaitymui
     * Privalo būti realizuota išvestinėje klasėje.
     * @param is įvesties srautas
     * @return įvesties srautas po nuskaitymo
     */
    virtual std::istream &readStudent(std::istream &) = 0;

    /**
     * @brief Grynoji virtuali funkcija duomenų išvedimui
     * Privalo būti realizuota išvestinėje klasėje.
     * @param os išvesties srautas
     */
    virtual void print(std::ostream &) const = 0;
};

#endif