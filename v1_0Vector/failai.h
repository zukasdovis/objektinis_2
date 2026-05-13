#ifndef FAILAI_H
#define FAILAI_H

#include "studentai.h"
#include "vector.h"
#include <vector>
#include <string>

/**
 * @file failai.h
 * @brief Funkcijos darbui su failais
 * @author jusu vardas
 * @version 1.5
 */

/**
 * @brief Nuskaito studentų duomenis iš failo
 *
 * Failo formatas:
 * @code
 * Vardas Pavarde ND1 ND2 ... NDn Egzaminas
 * Jonas  Jonaitis 8   7   9   6  10
 * @endcode
 *
 * @param grupe vektorius į kurį įrašomi studentai
 * @param failas failo pavadinimas
 * @throws std::runtime_error jei failas neegzistuoja
 */
void failu_nusk(Vector<Studentas> &grupe, std::string failas);

#endif