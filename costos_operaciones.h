#ifndef COSTO_OPERACIONES_H
#define COSTO_OPERACIONES_H

#include <vector>
#include <string>

// Tablas globales para los costos
extern std::vector<std::vector<int>> cost_insert;    // Para la inserción
extern std::vector<std::vector<int>> cost_delete;    // Para la eliminación
extern std::vector<std::vector<int>> cost_replace;   // Para la sustitución
extern std::vector<std::vector<int>> cost_transpose; // Para la transposición

void leertablascostos();
void leertablacostos(const std::string& archivo, std::vector<std::vector<int>>& tabla_costos);

int costo_sub(char a, char b);
int costo_ins(char b);
int costo_del(char a);
int costo_trans(char a, char b);

#endif 