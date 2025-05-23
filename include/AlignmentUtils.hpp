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

/**
 * @brief Realiza el alineamiento local entre dos cadenas con Smith-Waterman.
 * 
 * El alineamiento local permite encontrar la subsecuencia más similar dentro de ambas cadenas.
 * Utiliza una matriz de puntuaciones que permite reinicios en cero para detectar regiones con alta similitud.
 * 
 * @param s1 Primera cadena.
 * @param s2 Segunda cadena.
 * @return El score máximo del alineamiento local.
 */
int alineamientoLocal(const std::string& s1, const std::string& s2);

/**
 * @brief Reconstruye los alineamientos locales óptimos a partir de la matriz de scores.
 * 
 * La reconstrucción comienza en la posición del score máximo y retrocede hasta encontrar una celda con valor cero.
 * Permite obtener todos los alineamientos locales óptimos posibles.
 * 
 * @param s1 Primera cadena original.
 * @param s2 Segunda cadena original.
 * @param scores Matriz de puntuaciones calculada por Smith-Waterman.
 * @param start_i Fila donde inicia la reconstrucción (pos. del score máximo).
 * @param start_j Columna donde inicia la reconstrucción.
 * @param alineamientos1 Vector donde se almacenan los alineamientos reconstruidos para s1.
 * @param alineamientos2 Vector donde se almacenan los alineamientos reconstruidos para s2.
 */
void reconstruirAlineamientosLocal(const std::string& s1, const std::string& s2,
                                   const std::vector<std::vector<int>>& scores,
                                   int start_i, int start_j,
                                   std::vector<std::string>& alineamientos1,
                                   std::vector<std::string>& alineamientos2);
