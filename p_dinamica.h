#ifndef P_DINAMICA_H
#define P_DINAMICA_H

#include <vector>
#include <string>

// Función para obtener el índice del caracter
// Asegura que el caracter esté entre 'a' y 'z'
int obtener_indice(const char c);

// Función para calcular la distancia mínima de Damerau-Levenshtein entre dos cadenas
int calcular_dinamica(const std::string& s1, const std::string& s2,
                      const std::vector<std::vector<int>>& cost_insert,
                      const std::vector<std::vector<int>>& cost_delete,
                      const std::vector<std::vector<int>>& cost_replace,
                      const std::vector<std::vector<int>>& cost_transpose);

#endif // P_DINAMICA_H
