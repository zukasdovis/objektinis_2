#ifndef IVEDIMAS_H
#define IVEDIMAS_H

#include "studentai.h"
#include <vector>

/**
 * @file ivedimas.h
 * @brief Funkcijos studentų duomenų įvedimui
 * @author jusu vardas
 * @version 1.5
 */

/**
 * @brief Įveda studentus rankiniu būdu iš klaviatūros
 *
 * Vartotojas įveda vardą, pavardę, pažymius ir egzaminą.
 * Įvedimas baigiamas įvedus "0 0".
 *
 * @param grupe vektorius į kurį pridedami studentai
 * @throws std::runtime_error jei įvestis neteisinga
 *
 * Pavyzdys:
 * @code
 * std::vector<Studentas> grupe;
 * ranka(grupe);
 * @endcode
 */
void ranka(std::vector<Studentas> &grupe);

/**
 * @brief Įveda studentus su atsitiktinai generuojamais pažymiais
 *
 * Vartotojas įveda vardą ir pavardę, pažymiai generuojami automatiškai.
 * Įvedimas baigiamas įvedus "0 0".
 *
 * @param grupe vektorius į kurį pridedami studentai
 * @throws std::runtime_error jei įvestis neteisinga
 */
void pazymiu_gen(std::vector<Studentas> &grupe);

/**
 * @brief Generuoja studentus su atsitiktiniais duomenimis
 *
 * Vardai, pavardės ir pažymiai generuojami automatiškai.
 *
 * @param grupe vektorius į kurį pridedami studentai
 */
void visk_gen(std::vector<Studentas> &grupe);

#endif