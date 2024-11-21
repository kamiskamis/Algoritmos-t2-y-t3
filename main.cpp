#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>  // Para medir el tiempo de ejecución
#include "fuerza_bruta.h"  // Para la fuerza bruta
#include "p_dinamica.h"    // Para la programación dinámica

// Función para leer las matrices desde un archivo
std::vector<std::vector<int>> leer_matriz(const std::string& nombre_archivo) {
    std::vector<std::vector<int>> matriz;
    std::ifstream archivo(nombre_archivo);
    if (archivo.is_open()) {
        int valor;
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::vector<int> fila;
            std::istringstream stream(linea);
            while (stream >> valor) {
                fila.push_back(valor);
            }
            matriz.push_back(fila);
        }
    } else {
        std::cerr << "No se pudo abrir el archivo: " << nombre_archivo << std::endl;
    }
    return matriz;
}

// Función para leer las cadenas de prueba
std::pair<std::string, std::string> leer_caso() {
    std::ifstream archivo("caso_prueba.txt");
    std::string s1, s2;
    if (archivo.is_open()) {
        std::getline(archivo, s1);
        std::getline(archivo, s2);
    } else {
        std::cerr << "No se pudo abrir el archivo de casos de prueba." << std::endl;
    }
    return {s1, s2};
}

int main() {
    // Leer las matrices de costos desde los archivos
    auto cost_insert = leer_matriz("matrices_costos/cost_insert.txt");
    auto cost_delete = leer_matriz("matrices_costos/cost_delete.txt");
    auto cost_replace = leer_matriz("matrices_costos/cost_replace.txt");
    auto cost_transpose = leer_matriz("matrices_costos/cost_transpose.txt");

    // Verificar que las matrices hayan sido cargadas correctamente
    if (cost_insert.empty() || cost_delete.empty() || cost_replace.empty() || cost_transpose.empty()) {
        std::cerr << "Error al leer las matrices de costos." << std::endl;
        return 1;  // Salir si hubo un error en la lectura de matrices
    }

    // Leer las cadenas de prueba
    auto [s1, s2] = leer_caso();

    // Verificar que las cadenas hayan sido leídas correctamente
    if (s1.empty() || s2.empty()) {
        std::cerr << "Error al leer las cadenas de prueba." << std::endl;
        return 1;  // Salir si hubo un error en la lectura de cadenas
    }

    // Mostrar las cadenas
    std::cout << "Cadena 1: " << s1 << std::endl;
    std::cout << "Cadena 2: " << s2 << std::endl;

    // Calcular la distancia con fuerza bruta y medir el tiempo
    auto start_fb = std::chrono::high_resolution_clock::now();  // Tomamos el tiempo inicial
    int m = s1.size();
    int n = s2.size();
    std::cout << "\nFuerza Bruta:" << std::endl;
    int distancia_fb = calcular_fuerza_bruta(s1, s2, m, n, cost_insert, cost_delete, cost_replace, cost_transpose);
    auto end_fb = std::chrono::high_resolution_clock::now();  // Tomamos el tiempo final
    auto duration_fb = std::chrono::duration_cast<std::chrono::nanoseconds>(end_fb - start_fb);  // Calculamos la duración
    std::cout << "Distancia de Damerau-Levenshtein (Fuerza Bruta): " << distancia_fb << std::endl;
    std::cout << "Tiempo de ejecución (Fuerza Bruta): " << duration_fb.count() << " ns" << std::endl;  // Imprimimos el tiempo

    // Calcular la distancia con programación dinámica y medir el tiempo
    auto start_pd = std::chrono::high_resolution_clock::now();  // Tomamos el tiempo inicial
    std::cout << "\nProgramación Dinámica:" << std::endl;
    int distancia_pd = calcular_dinamica(s1, s2, cost_insert, cost_delete, cost_replace, cost_transpose);
    auto end_pd = std::chrono::high_resolution_clock::now();  // Tomamos el tiempo final
    auto duration_pd = std::chrono::duration_cast<std::chrono::nanoseconds>(end_pd - start_pd);  // Calculamos la duración
    std::cout << "Distancia de Damerau-Levenshtein (Programación Dinámica): " << distancia_pd << std::endl;
    std::cout << "Tiempo de ejecución (Programación Dinámica): " << duration_pd.count() << " ns" << std::endl;  // Imprimimos el tiempo

    return 0;
}
