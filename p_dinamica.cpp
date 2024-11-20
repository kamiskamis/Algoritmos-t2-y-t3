#include "p_dinamica.h"
#include <vector>
#include <algorithm>

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
    for (int i = 1; i <= m; ++i) dp[i][0] = i * cost_delete[s1[i - 1] - 'a'][0]; // Eliminar de s1
    for (int j = 1; j <= n; ++j) dp[0][j] = j * cost_insert[s2[j - 1] - 'a'][0]; // Insertar en s2

    // Llenar la tabla dp con los costos mínimos
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            // Calcular el costo de sustitución
            int costo_sub = (s1[i - 1] == s2[j - 1]) ? 0 : cost_replace[s1[i - 1] - 'a'][s2[j - 1] - 'a'];

            // Calcular el costo mínimo de las tres operaciones (eliminar, insertar, sustituir)
            dp[i][j] = std::min({dp[i - 1][j] + cost_delete[s1[i - 1] - 'a'][0],   // Eliminar
                                 dp[i][j - 1] + cost_insert[s2[j - 1] - 'a'][0],   // Insertar
                                 dp[i - 1][j - 1] + costo_sub});                    // Sustituir

            // Verificar si se puede realizar una transposición
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                dp[i][j] = std::min(dp[i][j], dp[i - 2][j - 2] + cost_transpose[s1[i - 1] - 'a'][s2[j - 2] - 'a']);
            }
        }
    }

    // El resultado final es el valor en dp[m][n]
    return dp[m][n];
}
