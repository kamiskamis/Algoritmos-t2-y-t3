#ifndef FUERZA_BRUTA_H
#define FUERZA_BRUTA_H

#include <vector>
#include <string>

// Declaración de la función calcular_fuerza_bruta
int calcular_fuerza_bruta(const std::string& s1, const std::string& s2,
                           int n, int m,
                           const std::vector<std::vector<int>>& cost_insert,
                           const std::vector<std::vector<int>>& cost_delete,
                           const std::vector<std::vector<int>>& cost_replace,
                           const std::vector<std::vector<int>>& cost_transpose);

#endif // FUERZA_BRUTA_H
