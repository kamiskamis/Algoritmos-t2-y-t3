#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <stdexcept>
#include "p_dinamica.h"

// Función para obtener el índice del caracter
// Asegura que el caracter esté entre 'a' y 'z'
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

    // Crear una tabla dp de m+1 x n+1 para almacenar los costos
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    // Inicializar el primer renglón y la primera columna
    for (int i = 1; i <= m; ++i) {
        dp[i][0] = i * cost_delete[obtener_indice(s1[i - 1])][0]; // Eliminar de s1
    }
    for (int j = 1; j <= n; ++j) {
        dp[0][j] = j * cost_insert[obtener_indice(s2[j - 1])][0]; // Insertar en s2
    }

    // Llenar la tabla dp con los costos mínimos
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            // Si los caracteres son iguales, no hay costo por sustitución
            int costo_sub = (s1[i - 1] == s2[j - 1]) ? 0 : cost_replace[obtener_indice(s1[i - 1])][obtener_indice(s2[j - 1])];

            // Calcular el costo mínimo de las tres operaciones: eliminar, insertar, sustituir
            dp[i][j] = std::min({dp[i - 1][j] + cost_delete[obtener_indice(s1[i - 1])][0],  // Eliminar
                                 dp[i][j - 1] + cost_insert[obtener_indice(s2[j - 1])][0],  // Insertar
                                 dp[i - 1][j - 1] + costo_sub});  // Sustituir

            // Verificar si se puede realizar una transposición (i > 1 y j > 1)
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                dp[i][j] = std::min(dp[i][j], dp[i - 2][j - 2] + cost_transpose[obtener_indice(s1[i - 1])][obtener_indice(s2[j - 2])]);
            }
        }
    }

    // El resultado final es el valor en dp[m][n]
    return dp[m][n];
}
