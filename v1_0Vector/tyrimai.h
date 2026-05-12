#ifndef TYRIMAI_H
#define TYRIMAI_H

#include <iostream>
#include <string>
using namespace std;

/**
 * @file tyrimai.h
 * @brief Funkcijos greičio tyrimams atlikti
 * @author jusu vardas
 * @version 1.5
 */

/**
 * @brief Pagrindinis tyrimų meniu
 * Leidžia pasirinkti kurį tyrimą atlikti
 */
void tyrimai();

/**
 * @brief Pirmasis tyrimas - failų generavimas
 * Generuoja testinuos failus su 1000, 10000, 100000,
 * 1000000 ir 10000000 studentų ir matuoja laiką
 */
void pirmasTyrimas();

/**
 * @brief Antrasis tyrimas - rūšiavimo greičio palyginimas
 * Matuoja trijų skirtingų rūšiavimo metodų greitį
 * pasirinktam studentų kiekiui
 */
void antrasTyrimas();

#endif