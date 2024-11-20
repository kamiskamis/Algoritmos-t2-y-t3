#include <utility> 
#include <vector>
#include <algorithm>
#include "fuerza_bruta.h"
#include "p_dinamica.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>







// Definición de las tablas globales de costos
std::vector<std::vector<int>> cost_insert(26, std::vector<int>(1));  
std::vector<std::vector<int>> cost_delete(26, std::vector<int>(1));  
std::vector<std::vector<int>> cost_replace(26, std::vector<int>(26)); 
std::vector<std::vector<int>> cost_transpose(26, std::vector<int>(26));

// Función para leer las tablas de costos desde los archivos
void leertablacostos(const std::string& archivo, std::vector<std::vector<int>>& tabla_costos) {
    std::ifstream file(archivo);
    if (!file) {
        std::cerr << "Error al abrir el archivo: " << archivo << std::endl;
        return;
    }

    std::string linea;
    size_t i = 0;
    while (std::getline(file, linea) && i < tabla_costos.size()) {
        std::istringstream ss(linea);
        size_t j = 0;
        int costo;
        while (ss >> costo && j < tabla_costos[i].size()) {
            tabla_costos[i][j] = costo;
            j++;
        }
        i++;
    }
    file.close();
}

// Función para obtener el índice de un carácter
int charaindex(char b) {
    b = std::tolower(b);  // Convertir el carácter a minúscula
    int ascii_value = static_cast<int>(b) - static_cast<int>('a');
    if (b >= 'a' && b <= 'z') {
        return ascii_value;
    }
    std::cerr << "Carácter no válido: " << b << std::endl;
    return -1;  // Índice no válido
}

// Funciones de costos
int costo_sub(char a, char b) {
    int index_a = charaindex(a);  
    int index_b = charaindex(b);  

    if (index_a >= 0 && index_a < 26 && index_b >= 0 && index_b < 26) {
        return cost_replace[index_a][index_b];  
    } 
    else {
        std::cerr << "Índices fuera de rango: a = " << index_a << ", b = " << index_b << std::endl;
        return -1;  
    }
}

int costo_ins(char b) {
    int i = charaindex(b);  
    if (i == -1) {
        std::cerr << "Error: índice no válido para el carácter de inserción: " << b << std::endl;
        return -1;
    }
    return cost_insert[i][0];
}

int costo_del(char b) {
    int i = charaindex(b);
    if (i == -1) {
        std::cerr << "Error: índice no válido para el carácter de eliminación: " << b << std::endl;
        return -1;
    }
    return cost_delete[i][0];
}

int costo_trans(char a, char b) {
    int i = charaindex(a);  
    int j = charaindex(b);  

    if (i == -1 || j == -1) {
        std::cerr << "Error: índices no válidos para los caracteres de transposición: " << a << " y " << b << std::endl;
        return -1;  
    }
    return cost_transpose[i][j];
}

// Función de Fuerza Bruta Recursiva
int fuerza_bruta_recursiva(const std::string& s1, const std::string& s2, int m, int n) {
    if (m == 0) return n * costo_ins(s2[n - 1]);
    if (n == 0) return m * costo_del(s1[m - 1]);

    int cost_subs = fuerza_bruta_recursiva(s1, s2, m - 1, n - 1) + costo_sub(s1[m - 1], s2[n - 1]);
    int cost_del = fuerza_bruta_recursiva(s1, s2, m - 1, n) + costo_del(s1[m - 1]);
    int cost_ins = fuerza_bruta_recursiva(s1, s2, m, n - 1) + costo_ins(s2[n - 1]);

    return std::min({cost_subs, cost_del, cost_ins});
}

// Función de Programación Dinámica Top-Down
int p_dinamica_top_down(const std::string& s1, const std::string& s2, int m, int n, std::vector<std::vector<int>>& memo) {
    if (m == 0) return n * costo_ins(s2[n - 1]);
    if (n == 0) return m * costo_del(s1[m - 1]);

    if (memo[m][n] != -1) return memo[m][n];

    int cost_subs = p_dinamica_top_down(s1, s2, m - 1, n - 1, memo) + costo_sub(s1[m - 1], s2[n - 1]);
    int cost_del = p_dinamica_top_down(s1, s2, m - 1, n, memo) + costo_del(s1[m - 1]);
    int cost_ins = p_dinamica_top_down(s1, s2, m, n - 1, memo) + costo_ins(s2[n - 1]);

    memo[m][n] = std::min({cost_subs, cost_del, cost_ins});
    return memo[m][n];
}

// Lógica principal
int main() {
    // Leer las tablas de costos desde los archivos
    leertablacostos("matrices_costos/cost_insert.txt", cost_insert);
    leertablacostos("matrices_costos/cost_delete.txt", cost_delete);
    leertablacostos("matrices_costos/cost_replace.txt", cost_replace);
    leertablacostos("matrices_costos/cost_transpose.txt", cost_transpose);

    // Ejemplo de cadenas
    std::string s1 = "hola";
    std::string s2 = "holla";

    // Fuerza Bruta Recursiva
    std::cout << "Costo por Fuerza Bruta (Recursiva): " << fuerza_bruta_recursiva(s1, s2, s1.size(), s2.size()) << std::endl;

    // Programación Dinámica Top-Down
    std::vector<std::vector<int>> memo(s1.size() + 1, std::vector<int>(s2.size() + 1, -1));
    std::cout << "Costo por Programación Dinámica Top-Down: " << p_dinamica_top_down(s1, s2, s1.size(), s2.size(), memo) << std::endl;

    return 0;
}
