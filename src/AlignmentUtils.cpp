#include "AlignmentUtils.hpp"
#include "IOUtils.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int calcularScoreCaracter(char a, char b) {
    return (a == b) ? 1 : -1;
}

std::string verificarSubstring(const std::string& s1, const std::string& s2) {
    if (s1.find(s2) != string::npos)
        return "\"" + s2 + "\" es substring de \"" + s1 + "\".";
    if (s2.find(s1) != string::npos)
        return "\"" + s1 + "\" es substring de \"" + s2 + "\".";
    return "Ninguna cadena es substring de la otra.";
}

int calcularScoreAlineado(const std::string& s1, const std::string& s2) {
    
    std::string clean1, clean2;

    // Eliminar espacios directamente
    for (char c : s1) {
        if (c != ' ') clean1 += c;
    }
    for (char c : s2) {
        if (c != ' ') clean2 += c;
    }

    if (clean1.size() != clean2.size()) {
        throw std::invalid_argument("Las secuencias alineadas deben tener el mismo tamaño tras eliminar espacios.");
        // Alternativamente: return -99999;
    }

    int total = 0;
    for (size_t i = 0; i < s1.size(); ++i) {
        total += (s1[i] == '-' || s2[i] == '-') ? -2 : calcularScoreCaracter(s1[i], s2[i]);
    }
    return total;
}

void reconstruirAlineamientos(const string& s1, const string& s2,
                               const vector<vector<int>>& scores,
                               vector<string>& alineamientos1,
                               vector<string>& alineamientos2) {
    struct Nodo { int i, j; string a1, a2; };
    vector<Nodo> stack = { { (int)s1.size(), (int)s2.size(), "", "" } };
    int gap = -2;

    while (!stack.empty()) {
        Nodo nodo = stack.back();
        stack.pop_back();

        int i = nodo.i, j = nodo.j;
        string a1 = nodo.a1, a2 = nodo.a2;

        if (i == 0 && j == 0) {
            reverse(a1.begin(), a1.end());
            reverse(a2.begin(), a2.end());
            alineamientos1.push_back(a1);
            alineamientos2.push_back(a2);
            continue;
        }

        if (i > 0 && j > 0 &&
            scores[i][j] == scores[i - 1][j - 1] + calcularScoreCaracter(s1[i - 1], s2[j - 1]))
            stack.push_back({ i - 1, j - 1, a1 + s1[i - 1], a2 + s2[j - 1] });

        if (i > 0 && scores[i][j] == scores[i - 1][j] + gap)
            stack.push_back({ i - 1, j, a1 + s1[i - 1], a2 + '-' });

        if (j > 0 && scores[i][j] == scores[i][j - 1] + gap)
            stack.push_back({ i, j - 1, a1 + '-', a2 + s2[j - 1] });
    }
}

int alineamientoGlobal(const string& s1, const string& s2) {
    int gap = -2;
    size_t n = s1.size(), m = s2.size();
    vector<vector<int>> matriz(n + 1, vector<int>(m + 1));

    for (size_t i = 0; i <= n; ++i) matriz[i][0] = i * gap;
    for (size_t j = 0; j <= m; ++j) matriz[0][j] = j * gap;

    for (size_t i = 1; i <= n; ++i)
        for (size_t j = 1; j <= m; ++j)
            matriz[i][j] = max({
                matriz[i - 1][j - 1] + calcularScoreCaracter(s1[i - 1], s2[j - 1]),
                matriz[i - 1][j] + gap,
                matriz[i][j - 1] + gap
            });

    mostrarMatriz(matriz, s1, s2);

    vector<string> a1, a2;
    reconstruirAlineamientos(s1, s2, matriz, a1, a2);

    cout << "\nScore final: " << matriz[n][m] << "\n";
    cout << "Cantidad de alineamientos óptimos: " << a1.size() << "\n";

    for (size_t i = 0; i < a1.size(); ++i)
        cout << "\nAlineamiento " << i + 1 << ":\n" << a1[i] << "\n" << a2[i] << "\n";

    guardarResultado("data/resultado.txt", matriz, a1, a2, matriz[n][m]);
    return matriz[n][m]; 
}

#include <fstream>
#include <set>

// Función para obtener subsecuencia común sin gaps
std::string subsecuenciaComun(const std::string& a1, const std::string& a2) {
    std::string res;
    for (size_t i = 0; i < a1.size(); ++i) {
        if (a1[i] == a2[i] && a1[i] != '-' && a2[i] != '-')
            res += a1[i];
    }
    return res;
}

// Función para guardar resultados en txt según los requisitos
void guardarResultadoLocal(const std::string& filename,
                           const std::vector<std::vector<int>>& matriz,
                           int maxScore,
                           const std::vector<std::string>& a1,
                           const std::vector<std::string>& a2,
                           const std::vector<std::pair<int,int>>& posiciones1,
                           const std::vector<std::pair<int,int>>& posiciones2) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "No se pudo abrir el archivo para guardar resultados.\n";
        return;
    }

    out << "Score máximo local: " << maxScore << "\n\n";

    std::set<std::string> subsecuencias_unicas;

    for (size_t i = 0; i < a1.size(); ++i) {
        std::string subseq = subsecuenciaComun(a1[i], a2[i]);
        subsecuencias_unicas.insert(subseq);

        out << "Alineamiento local " << i+1 << ":\n";
        out << "Subsecuencia común: " << subseq << "\n";
        out << "Posición en s1: desde " << posiciones1[i].first << " hasta " << posiciones1[i].second << "\n";
        out << "Posición en s2: desde " << posiciones2[i].first << " hasta " << posiciones2[i].second << "\n";
        out << a1[i] << "\n" << a2[i] << "\n\n";
    }

    out << "¿Existe subsecuencia común en otra subsecuencia? ";
    out << (subsecuencias_unicas.size() < a1.size() ? "Sí" : "No") << "\n\n";

    out << "Matriz de scores:\n";
    for (const auto& fila : matriz) {
        for (int val : fila) out << val << "\t";
        out << "\n";
    }
    out.close();
}

int alineamientoLocal(const std::string& s1, const std::string& s2) {
    int gap = -2;
    size_t n = s1.size(), m = s2.size();
    std::vector<std::vector<int>> matriz(n + 1, std::vector<int>(m + 1, 0));

    int maxScore = 0;
    std::vector<std::pair<int,int>> maxPositions; // posiciones (i,j) con score máximo

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m; ++j) {
            int scoreDiagonal = matriz[i - 1][j - 1] + calcularScoreCaracter(s1[i - 1], s2[j - 1]);
            int scoreArriba = matriz[i - 1][j] + gap;
            int scoreIzquierda = matriz[i][j - 1] + gap;

            matriz[i][j] = std::max({0, scoreDiagonal, scoreArriba, scoreIzquierda});

            if (matriz[i][j] > maxScore) {
                maxScore = matriz[i][j];
                maxPositions.clear();
                maxPositions.emplace_back(i, j);
            } else if (matriz[i][j] == maxScore) {
                maxPositions.emplace_back(i, j);
            }
        }
    }

    // <-- AÑADE ESTO AQUÍ:
    mostrarMatriz(matriz, s1, s2);

    // Reconstrucción de alineamientos locales para todos los máximos encontrados
    struct Nodo { int i, j; std::string a1, a2; };
    std::vector<std::string> alineamientos1, alineamientos2;
    std::vector<std::pair<int,int>> posiciones1, posiciones2; // para guardar start-end en s1 y s2

    int gap_penalty = gap;

    for (auto& pos : maxPositions) {
        int start_i = pos.first;
        int start_j = pos.second;
        std::vector<Nodo> stack = { { start_i, start_j, "", "" } };

        while (!stack.empty()) {
            Nodo nodo = stack.back();
            stack.pop_back();

            int i = nodo.i, j = nodo.j;
            std::string a1 = nodo.a1, a2 = nodo.a2;

            if (matriz[i][j] == 0) {
                // Recordar posiciones originales en s1 y s2
                int end_i = start_i - 1;
                int end_j = start_j - 1;
                int begin_i = i;
                int begin_j = j;

                // Como retrocedemos, la longitud del alineamiento es a1.size()
                // La posición inicial real en s1 es end_i - (a1.size() - 1)
                int posIniS1 = end_i - ((int)a1.size() - 1);
                int posIniS2 = end_j - ((int)a2.size() - 1);

                // Guardamos alineamientos y posiciones
                std::reverse(a1.begin(), a1.end());
                std::reverse(a2.begin(), a2.end());
                alineamientos1.push_back(a1);
                alineamientos2.push_back(a2);
                posiciones1.emplace_back(posIniS1, end_i);
                posiciones2.emplace_back(posIniS2, end_j);
                continue;
            }

            // Movimientos permitidos:
            if (i > 0 && j > 0 &&
                matriz[i][j] == matriz[i - 1][j - 1] + calcularScoreCaracter(s1[i - 1], s2[j - 1]))
                stack.push_back({ i - 1, j - 1, a1 + s1[i - 1], a2 + s2[j - 1] });

            if (i > 0 && matriz[i][j] == matriz[i - 1][j] + gap_penalty)
                stack.push_back({ i - 1, j, a1 + s1[i - 1], a2 + '-' });

            if (j > 0 && matriz[i][j] == matriz[i][j - 1] + gap_penalty)
                stack.push_back({ i, j - 1, a1 + '-', a2 + s2[j - 1] });
        }
    }

    // Guardar resultado en archivo
    guardarResultadoLocal("data/resultado_local.txt", matriz, maxScore, alineamientos1, alineamientos2, posiciones1, posiciones2);

    // Mostrar por consola (opcional)
    std::cout << "\nScore máximo local: " << maxScore << "\n";
    std::cout << "Cantidad de alineamientos óptimos: " << alineamientos1.size() << "\n";
    for (size_t i = 0; i < alineamientos1.size(); ++i) {
        std::cout << "\nAlineamiento local " << i + 1 << ":\n";
        std::cout << alineamientos1[i] << "\n" << alineamientos2[i] << "\n";
        std::cout << "Posición en s1: " << posiciones1[i].first << "-" << posiciones1[i].second << "\n";
        std::cout << "Posición en s2: " << posiciones2[i].first << "-" << posiciones2[i].second << "\n";
    }

    return maxScore;
}
