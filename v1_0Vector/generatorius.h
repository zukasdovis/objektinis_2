#ifndef GENERATORIUS_H
#define GENERATORIUS_H

/**
 * @file generatorius.h
 * @brief Funkcijos testinių failų generavimui
 * @author jusu vardas
 * @version 1.5
 */

/**
 * @brief Generuoja visus testiniuos failus
 * Sukuria failus: 1000, 10000, 100000, 1000000, 10000000 studentų
 */
void generuotiVisus();

/**
 * @brief Generuoja vieną testinį failą
 * @param kiekis studentų kiekis faile
 *
 * Sukuria failą pavadinimu "studentai_[kiekis].txt"
 *
 * Pavyzdys:
 * @code
 * generuotiFaila(1000); // sukuria "studentai_1000.txt"
 * @endcode
 */
void generuotiFaila(int kiekis);

#endif