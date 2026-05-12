#ifndef MEDIANA_H
#define MEDIANA_H

#include <vector>

/**
 * @file mediana.h
 * @brief Statistinių funkcijų deklaracijos
 * @author jusu vardas
 * @version 1.5
 */

/**
 * @brief Skaičiuoja skaičių vektoriaus medianą
 * @param nd skaičių vektorius
 * @return mediana arba 0.0 jei vektorius tuščias
 *
 * Pavyzdys:
 * @code
 * std::vector<int> v = {6, 8, 10};
 * double m = mediana(v); // 8.0
 * @endcode
 */
double mediana(std::vector<int> nd);

/**
 * @brief Skaičiuoja skaičių vektoriaus vidurkį
 * @param nd skaičių vektorius
 * @return vidurkis arba 0.0 jei vektorius tuščias
 *
 * Pavyzdys:
 * @code
 * std::vector<int> v = {6, 8, 10};
 * double v = vidurkis(v); // 8.0
 * @endcode
 */
double vidurkis(std::vector<int> nd);

#endif