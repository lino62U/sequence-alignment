#include "Menu.hpp"
#include "AlignmentUtils.hpp"
#include <iostream>

using namespace std;

void ejecutarMenu() {
    int opcion;
    string c1, c2;

    do {
        cout << "\n=====================================\n";
        cout << "           🧬 MENU PRINCIPAL          \n";
        cout << "=====================================\n";
        cout << "1️⃣  Verificar si una cadena es substring de otra\n";
        cout << "2️⃣  Calcular el score de dos cadenas alineadas\n";
        cout << "3️⃣  Realizar alineamiento global (Needleman-Wunsch)\n";
        cout << "4️⃣  Realizar alineamiento local (Smith-Waterman)\n";
        cout << "0️⃣  Salir\n";
        cout << "-------------------------------------\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cout << "-------------------------------------\n";

        if (opcion >= 1 && opcion <= 4) {
            cout << "🔹 Ingrese la primera cadena: ";
            cin >> c1;
            cout << "🔹 Ingrese la segunda cadena: ";
            cin >> c2;
            cout << "-------------------------------------\n";
        }

        switch (opcion) {
            case 1:
                cout << "\n🔍 RESULTADO - Verificación de Substring\n";
                cout << "-------------------------------------\n";
                cout << verificarSubstring(c1, c2) << "\n";
                cout << "-------------------------------------\n";
                break;

            case 2: {
                cout << "\n🧮 RESULTADO - Score de Alineamiento\n";
                cout << "-------------------------------------\n";
                int sc = calcularScoreAlineado(c1, c2);
                if (sc == -99999)
                    cout << "❌ Error: las cadenas deben tener el mismo tamaño.\n";
                else
                    cout << "✅ Score total entre las cadenas alineadas: " << sc << "\n";
                cout << "-------------------------------------\n";
                break;
            }

            case 3:
                cout << "\n🌐 RESULTADO - Alineamiento Global (Needleman-Wunsch)\n";
                cout << "-------------------------------------\n";
                alineamientoGlobal(c1, c2);
                cout << "-------------------------------------\n";
                break;

            case 4:
                cout << "\n📍 RESULTADO - Alineamiento Local (Smith-Waterman)\n";
                cout << "-------------------------------------\n";
                alineamientoLocal(c1, c2);
                cout << "📁 Resultado guardado en 'data/resultado_local.txt'.\n";
                cout << "-------------------------------------\n";
                break;

            case 0:
                cout << "\n👋 Saliendo del programa...\n";
                break;

            default:
                cout << "\n⚠️  Opción inválida. Intente nuevamente.\n";
        }

    } while (opcion != 0);
}
