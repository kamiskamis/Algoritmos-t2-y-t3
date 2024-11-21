#include "fuerza_bruta.h"
#include <algorithm>
#include <climits>

// Función recursiva para calcular la distancia de Damerau-Levenshtein (fuerza bruta)
int calcular_fuerza_bruta(const std::string& s1, const std::string& s2,
                           int n, int m,
                           const std::vector<std::vector<int>>& cost_insert,
                           const std::vector<std::vector<int>>& cost_delete,
                           const std::vector<std::vector<int>>& cost_replace,
                           const std::vector<std::vector<int>>& cost_transpose) {

    // Caso base: si una de las cadenas es vacía
    if (n == 0) {
        int costo = 0;
        for (int i = 0; i < m; ++i) {
            costo += cost_insert[0][s2[i] - 'a'];  // Insertar los caracteres de s2
        }
        return costo;
    }

    if (m == 0) {
        int costo = 0;
        for (int i = 0; i < n; ++i) {
            costo += cost_delete[0][s1[i] - 'a'];  // Eliminar los caracteres de s1
        }
        return costo;
    }


    // Si los caracteres son iguales, no hay costo, procedemos con las cadenas más pequeñas
    if (s1[n - 1] == s2[m - 1]) {
        return calcular_fuerza_bruta(s1, s2, n - 1, m - 1, cost_insert, cost_delete, cost_replace, cost_transpose);
    }

    // Cálculo de los costos para las operaciones: insertar, borrar o reemplazar
    int insertar = calcular_fuerza_bruta(s1, s2, n, m - 1, cost_insert, cost_delete, cost_replace, cost_transpose) + cost_insert[m - 1][0];
    int borrar = calcular_fuerza_bruta(s1, s2, n - 1, m, cost_insert, cost_delete, cost_replace, cost_transpose) + cost_delete[n - 1][0];
    int reemplazar = calcular_fuerza_bruta(s1, s2, n - 1, m - 1, cost_insert, cost_delete, cost_replace, cost_transpose) + cost_replace[n - 1][m - 1];

    // Devolver el costo mínimo entre las operaciones
    return std::min({insertar, borrar, reemplazar});
}
