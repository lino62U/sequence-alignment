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

    guardarResultado("resultado.txt", matriz, a1, a2, matriz[n][m]);
    return matriz[n][m]; 
}
