#include "fuerza_bruta.h"
#include <algorithm>
#include <climits>
#include <stdexcept>

// Cambiar el nombre de la función para evitar conflictos con p_dinamica.cpp
int obtener_indice_fb(const char c) {
    if (c < 'a' || c > 'z') {
        throw std::out_of_range("Caracter fuera de rango permitido (a-z)");
    }
    return c - 'a';
}

// Función recursiva para calcular la distancia de Damerau-Levenshtein (fuerza bruta)
int calcular_fuerza_bruta(const std::string& s1, const std::string& s2,
                           int n, int m,
                           const std::vector<std::vector<int>>& cost_insert,
                           const std::vector<std::vector<int>>& cost_delete,
                           const std::vector<std::vector<int>>& cost_replace,
                           const std::vector<std::vector<int>>& cost_transpose) {
    // Caso base: si una de las cadenas está vacía
    if (n == 0) {
        return m * cost_insert[0][s2[m - 1] - 'a'];  // Costo de insertar los caracteres de s2
    }

    if (m == 0) {
        int costo = 0;
        for (int i = 0; i < n; ++i) {
            costo += cost_delete[0][s1[i] - 'a'];  // Eliminar los caracteres de s1
        }
        return costo;
    }

    // Si los últimos caracteres son iguales, no necesitamos hacer nada
    if (s1[n - 1] == s2[m - 1]) {
        return calcular_fuerza_bruta(s1, s2, n - 1, m - 1, cost_insert, cost_delete, cost_replace, cost_transpose);
    }

    // Operación de eliminación (borrar carácter de s1)
    int borrar = calcular_fuerza_bruta(s1, s2, n - 1, m, cost_insert, cost_delete, cost_replace, cost_transpose) + cost_delete[n - 1][0];

    // Operación de reemplazo (reemplazar carácter de s1 por el de s2)
    int reemplazar = calcular_fuerza_bruta(s1, s2, n - 1, m - 1, cost_insert, cost_delete, cost_replace, cost_transpose) + cost_replace[n - 1][m - 1];

    // Operación de inserción (insertar carácter en s1)
    int insertar = calcular_fuerza_bruta(s1, s2, n, m - 1, cost_insert, cost_delete, cost_replace, cost_transpose) + cost_insert[0][s2[m - 1] - 'a'];

    // Operación de transposición (intercambiar caracteres adyacentes)
    int transponer = INT_MAX;
    if (n > 1 && m > 1 && s1[n - 1] == s2[m - 2] && s1[n - 2] == s2[m - 1]) {
        transponer = calcular_fuerza_bruta(s1, s2, n - 2, m - 2, cost_insert, cost_delete, cost_replace, cost_transpose) + cost_transpose[n - 1][m - 1];
    }

    // Retornamos el valor mínimo de las operaciones
    return std::min({borrar, reemplazar, insertar, transponer});
}
