#ifndef FUERZA_BRUTA_H
#define FUERZA_BRUTA_H

#include <vector>
#include <string>


// Declaración de la función para calcular la distancia de Damerau-Levenshtein usando fuerza bruta
int calcular_fuerza_bruta(const std::string& s1, const std::string& s2,
                          const std::vector<std::vector<int>>& cost_insert,
                          const std::vector<std::vector<int>>& cost_delete,
                          const std::vector<std::vector<int>>& cost_replace,
                          const std::vector<std::vector<int>>& cost_transpose);

#endif // FUERZA_BRUTA_H
