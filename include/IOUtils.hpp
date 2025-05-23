#pragma once
#include <vector>
#include <string>

/**
 * @brief Muestra la matriz de puntuación en formato tabular.
 * @param matriz Matriz de scores.
 * @param s1 Cadena base horizontal.
 * @param s2 Cadena base vertical.
 */
void mostrarMatriz(const std::vector<std::vector<int>>& matriz,
                   const std::string& s1, const std::string& s2);

/**
 * @brief Guarda el resultado del alineamiento en un archivo.
 * @param filename Nombre del archivo de salida.
 * @param matriz Matriz de puntuación.
 * @param alineamientos1 Lista de cadenas alineadas (s1).
 * @param alineamientos2 Lista de cadenas alineadas (s2).
 * @param scoreFinal Score final del mejor alineamiento.
 */
void guardarResultado(const std::string& filename,
                      const std::vector<std::vector<int>>& matriz,
                      const std::vector<std::string>& alineamientos1,
                      const std::vector<std::string>& alineamientos2,
                      int scoreFinal);



// Función para guardar resultados en txt según los requisitos
void guardarResultadoLocal(const std::string& filename,
                           const std::vector<std::vector<int>>& matriz,
                           int maxScore,
                           const std::vector<std::string>& a1,
                           const std::vector<std::string>& a2,
                           const std::vector<std::pair<int,int>>& posiciones1,
                           const std::vector<std::pair<int,int>>& posiciones2);