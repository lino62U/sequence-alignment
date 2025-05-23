#include "Menu.hpp"
#include "AlignmentUtils.hpp"
#include <iostream>

using namespace std;

void ejecutarMenu() {
    int opcion;
    string c1, c2;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Verificar si una cadena es substring de otra\n";
        cout << "2. Calcular el score de dos cadenas alineadas\n";
        cout << "3. Realizar alineamiento global (Needleman-Wunsch)\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (opcion >= 1 && opcion <= 3) {
            cout << "Ingrese la primera cadena: ";
            cin >> c1;
            cout << "Ingrese la segunda cadena: ";
            cin >> c2;
        }

        switch (opcion) {
            case 1:
                cout << verificarSubstring(c1, c2) << "\n";
                break;
            case 2: {
                int sc = calcularScoreAlineado(c1, c2);
                if (sc == -99999)
                    cout << "Error: las cadenas deben tener el mismo tamaño.\n";
                else
                    cout << "Score total entre las cadenas alineadas: " << sc << "\n";
                break;
            }
            case 3:
                alineamientoGlobal(c1, c2);
                break;
            case 0:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }

    } while (opcion != 0);
}
