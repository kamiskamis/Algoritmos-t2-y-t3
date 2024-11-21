#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <stdexcept>
#include "p_dinamica.h"

// Función para obtener el índice del carácter
// Asegura que el carácter esté entre 'a' y 'z'
int obtener_indice(const char c) {
    if (c < 'a' || c > 'z') {
        throw std::out_of_range("Caracter fuera de rango permitido (a-z)");
    }
    return c - 'a';
}

int calcular_dinamica(const std::string& s1, const std::string& s2,
                      const std::vector<std::vector<int>>& cost_insert,
                      const std::vector<std::vector<int>>& cost_delete,
                      const std::vector<std::vector<int>>& cost_replace,
                      const std::vector<std::vector<int>>& cost_transpose) {
    int m = s1.size();
    int n = s2.size();

    // Validación de cadenas vacías
    if (s1.empty() || s2.empty()) {
        std::cerr << "Las cadenas no deben estar vacías." << std::endl;
        return -1;
    }

    // Crear una tabla dp de (m+1) x (n+1) para almacenar los costos
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    // Casos base: si una de las cadenas está vacía
    for (int i = 1; i <= m; ++i) {
        dp[i][0] = i * cost_delete[obtener_indice(s1[i - 1])][0]; // Eliminar caracteres de s1
    }

    for (int j = 1; j <= n; ++j) {
        dp[0][j] = j * cost_insert[0][obtener_indice(s2[j - 1])]; // Insertar caracteres en s2
    }

    // Llenar la tabla dp con los costos mínimos
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int idx1 = obtener_indice(s1[i - 1]);
            int idx2 = obtener_indice(s2[j - 1]);

            // Costo de reemplazo, si los caracteres son diferentes
            int costo_sub = (s1[i - 1] == s2[j - 1]) ? 0 : cost_replace[idx1][idx2];

            // Calcular el costo mínimo de las operaciones: eliminar, sustituir e insertar
            dp[i][j] = std::min({dp[i - 1][j] + cost_delete[idx1][0],       // Eliminar
                                 dp[i][j - 1] + cost_insert[0][idx2],       // Insertar
                                 dp[i - 1][j - 1] + costo_sub});            // Reemplazar

            // Verificar si se puede realizar una transposición
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                dp[i][j] = std::min(dp[i][j], dp[i - 2][j - 2] + cost_transpose[idx1][obtener_indice(s2[j - 2])]);
            }
        }
    }

    // El resultado final es el valor en dp[m][n]
    return dp[m][n];
}
