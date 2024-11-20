#include <iostream>
#include <fstream>
#include <string>
#include <utility> 
#include <vector>
#include <algorithm>
#include "costos_operaciones.h"
#include "fuerza_bruta.h"
#include "p_dinamica.h"


void limpiarCadena(std::string& str) {
    std::cout << "Antes de limpiar: '" << str << "'" << std::endl;
    str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());

    // Elimina caracteres no imprimibles
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isprint(ch);  // Elimina cualquier carácter no imprimible
    }), str.end());

    // Elimina los espacios en blanco al principio y al final
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());

    std::cout << "Después de limpiar: '" << str << "'" << std::endl;

    // Asegúrate de que la cadena no esté vacía después de limpiar
    if (str.empty()) {
        std::cerr << "Advertencia: La cadena está vacía después de limpiar." << std::endl;
    }
}



std::pair<std::string, std::string> leerArchivo() {
    std::ifstream archivo("caso_prueba.txt");  // Abrir el archivo de texto

    if (!archivo) {  
        std::cerr << "Error al abrir el archivo." << std::endl;
        return {"", ""};  
    }
    std::string s1, s2;
    std::getline(archivo, s1);  
    std::getline(archivo, s2);  
    archivo.close();  
    limpiarCadena(s1);
    limpiarCadena(s2);
    return {s1, s2};  
}


int main() {
    auto [s1, s2] = leerArchivo();

    if (s1.empty() || s2.empty()) {
        std::cerr << "Error: Las cadenas leídas están vacías." << std::endl;
        return 1;  // Termina el programa si las cadenas son vacías
    }

    std::cout << "Contenido de s1: " << s1 << std::endl;
    std::cout << "Contenido de s2: " << s2 << std::endl;

    //int d_fuerzabruta = fuerzabrutarecursiva(s1, s2, s1.size(), s2.size());
    //std::cout<<"Distancia con fuerza bruta recursiva:"<<d_fuerzabruta<<std::endl;

    //std::vector<std::vector<int>> memo(s1.size() + 1, std::vector<int>(s2.size() +1, -1));
    //int d_pdinamicatopdown = pdinamicamemo(s1, s2, s1.size(), s2.size(), memo);
    //std::cout<< "Distancia con prog dinamica top-down:"<<d_pdinamicatopdown<<std::endl;

    return 0;
}
