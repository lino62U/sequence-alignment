#include "IOUtils.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void mostrarMatriz(const vector<vector<int>>& matriz, const string& s1, const string& s2) {
    cout << "\nMatriz de puntuaciones:\n    ";
    for (char c : s2) cout << setw(3) << c;
    cout << "\n";

    for (size_t i = 0; i <= s1.size(); ++i) {
        if (i == 0) cout << "  ";    // Espacio para alinear la primera fila
        else cout << s1[i - 1] << " ";
        for (int val : matriz[i]) cout << setw(3) << val;
        cout << "\n";
    }
}

void guardarResultado(const string& filename, const vector<vector<int>>& matriz,
                      const vector<string>& a1, const vector<string>& a2, int scoreFinal) {
    ofstream out(filename);
    out << "Score final: " << scoreFinal << "\n\nMatriz de scores:\n";
    for (const auto& row : matriz) {
        for (int val : row) out << val << "\t";
        out << "\n";
    }
    out << "\nCantidad de alineamientos óptimos: " << a1.size() << "\n";
    for (size_t i = 0; i < a1.size(); ++i) {
        out << "Alineamiento " << i + 1 << ":\n" << a1[i] << "\n" << a2[i] << "\n\n";
    }
    out.close();
}
