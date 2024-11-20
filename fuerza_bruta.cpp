#include "fuerza_bruta.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits.h>
#include <vector>
#include <string>
#include <stdexcept>

int calcular_fuerza_bruta(const std::string& s1, const std::string& s2,
                          const std::vector<std::vector<int>>& cost_insert,
                          const std::vector<std::vector<int>>& cost_delete,
                          const std::vector<std::vector<int>>& cost_replace,
                          const std::vector<std::vector<int>>& cost_transpose) {
    size_t m = s1.size();
    size_t n = s2.size();

    if (m == 0) return n * cost_insert[s2[0] - 'a'][0];
    if (n == 0) return m * cost_delete[s1[0] - 'a'][0];

    int costo = 0;

    // Verificación de índices válidos
    auto obtener_indice = [](char c) -> int {
        if (c < 'a' || c > 'z') {
            throw std::out_of_range("Caracter fuera de rango permitido (a-z)");
        }
        return c - 'a';
    };

    // Comparación de los caracteres de las cadenas
    for (size_t idx_s1 = 0; idx_s1 < m; ++idx_s1) {
        for (size_t idx_s2 = 0; idx_s2 < n; ++idx_s2) {
            if (s1[idx_s1] != s2[idx_s2]) {
                int idx_s1_rep = obtener_indice(s1[idx_s1]);
                int idx_s2_rep = obtener_indice(s2[idx_s2]);
                costo += cost_replace[idx_s1_rep][idx_s2_rep];
            }
        }
    }

    // Eliminar
    for (size_t idx_s1 = 0; idx_s1 < m; ++idx_s1) {
        int idx_s1_rep = obtener_indice(s1[idx_s1]);
        costo += cost_delete[idx_s1_rep][0];  // Costo por eliminar
    }

    // Insertar
    for (size_t idx_s2 = 0; idx_s2 < n; ++idx_s2) {
        int idx_s2_rep = obtener_indice(s2[idx_s2]);
        costo += cost_insert[idx_s2_rep][0];  // Costo por insertar
    }

    // Verificar si hay transposición
    for (size_t idx_s1_rep = 0; idx_s1_rep < m - 1; ++idx_s1_rep) {
        for (size_t idx_s2_rep = 0; idx_s2_rep < n - 1; ++idx_s2_rep) {
            if (s1[idx_s1_rep] == s2[idx_s2_rep + 1] && s1[idx_s1_rep + 1] == s2[idx_s2_rep]) {
                costo += cost_transpose[obtener_indice(s1[idx_s1_rep])][obtener_indice(s2[idx_s2_rep])];
            }
        }
    }

    return costo;
}

