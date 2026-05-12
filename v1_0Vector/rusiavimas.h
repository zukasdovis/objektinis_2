#ifndef RUSIAVIMAS_H
#define RUSIAVIMAS_H

#include "studentai.h"
#include "failai.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

/**
 * @file rusiavimas.h
 * @brief Funkcijos studentų rūšiavimui ir skirstymui
 * @author jusu vardas
 * @version 1.5
 */

/**
 * @brief Perskirsto studentus į du konteinerius pagal galutinį balą
 *
 * Studentai su balas >= 5.0 lieka grupe,
 * studentai su balas < 5.0 perkeliami į silpniakai.
 *
 * @tparam Container konteinerio tipas (pvz. vector<Studentas>)
 * @param grupe pradinis konteineris - po funkcijos lieka tik >= 5.0
 * @param silpniakai konteineris į kurį perkeliami < 5.0
 *
 * Pavyzdys:
 * @code
 * std::vector<Studentas> grupe, silpniakai;
 * splitContainer(grupe, silpniakai);
 * @endcode
 */
template <typename Container>
void splitContainer(Container &grupe, Container &silpniakai);

/**
 * @brief Rūšiavimo metodas 1 - du atskiri vektoriai
 *
 * Nuskaito failą, sukuria du atskirus vektorius (kietiakai/silpniakai),
 * rūšiuoja ir išsaugo į failus.
 *
 * @param kiekis studentų kiekis faile
 */
void failoRusiavimas1(int kiekis);

/**
 * @brief Rūšiavimo metodas 2 - rūšiavimas ir pop_back
 *
 * Nuskaito failą, surūšiuoja pagal balą, tada pop_back'u
 * atskiria silpnus studentus.
 *
 * @param kiekis studentų kiekis faile
 */
void failoRusiavimas2(int kiekis);

/**
 * @brief Rūšiavimo metodas 3 - std::partition
 *
 * Nuskaito failą, naudoja std::partition per splitContainer
 * studentams atskirti.
 *
 * @param kiekis studentų kiekis faile
 */
void failoRusiavimas3(int kiekis);

#endif