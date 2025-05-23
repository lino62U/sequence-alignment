#pragma once
#include <string>
#include <vector>

/**
 * @brief Calcula la puntuación entre dos caracteres.
 * @param a Primer carácter.
 * @param b Segundo carácter.
 * @return 1 si los caracteres son iguales, -1 si son distintos.
 */
int calcularScoreCaracter(char a, char b);

/**
 * @brief Verifica si una cadena es substring de otra.
 * @param s1 Primera cadena.
 * @param s2 Segunda cadena.
 * @return Mensaje indicando la relación de substring.
 */
std::string verificarSubstring(const std::string& s1, const std::string& s2);

/**
 * @brief Calcula el score de dos cadenas alineadas (pueden incluir gaps '-').
 * @param s1 Primera cadena alineada.
 * @param s2 Segunda cadena alineada.
 * @return Score total del alineamiento.
 */
int calcularScoreAlineado(const std::string& s1, const std::string& s2);

/**
 * @brief Realiza el alineamiento global entre dos cadenas con Needleman-Wunsch.
 * @param s1 Primera cadena.
 * @param s2 Segunda cadena.
 */
int alineamientoGlobal(const std::string& s1, const std::string& s2);

