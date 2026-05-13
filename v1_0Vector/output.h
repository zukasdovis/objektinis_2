#ifndef OUTPUT_H
#define OUTPUT_H

#include "studentai.h"
#include <vector>
#include "vector.h"

/**
 * @file output.h
 * @brief Funkcijos studentų duomenų išvedimui
 * @author jusu vardas
 * @version 1.5
 */

/**
 * @brief Išveda studentų duomenis į ekraną
 *
 * Išvesties formatas:
 * @code
 * Vardas          Pavarde         GalutinisMed    GalutinisVid
 * Jonas           Jonaitis        7.88            7.90
 * @endcode
 *
 * @param grupe studentų vektorius
 */
void outputas(Vector<Studentas> &grupe);

/**
 * @brief Išveda studentų duomenis į failą "rezultatai.txt"
 *
 * Išvesties formatas toks pat kaip outputas().
 *
 * @param grupe studentų vektorius
 * @see outputas()
 */
void outputas_fr(Vector<Studentas> &grupe);

#endif