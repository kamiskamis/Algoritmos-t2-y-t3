#include "costos_operaciones.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// Definición de las tablas globales de costos
std::vector<std::vector<int>> cost_insert(26, std::vector<int>(1));  
std::vector<std::vector<int>> cost_delete(26, std::vector<int>(1));  
std::vector<std::vector<int>> cost_replace(26, std::vector<int>(26)); 
std::vector<std::vector<int>> cost_transpose(26, std::vector<int>(26));


void leertablascostos(){
    leertablacostos("matrices_costos/cost_insert.txt", cost_insert);
    leertablacostos("matrices_costos/cost_delete.txt", cost_delete);
    leertablacostos("matrices_costos/cost_replace.txt", cost_replace);
    leertablacostos("matrices_costos/cost_transpose.txt", cost_transpose);
}

void leertablacostos(const std::string& archivo, std::vector<std::vector<int>>& tabla_costos){
    std::ifstream file(archivo);
    std::string linea;
    int i = 0;
    while(std::getline(file, linea)){
        std::istringstream ss(linea);
        int j = 0;
        int costo;
        while (ss>>costo){
            tabla_costos[i][j]= costo;
            j++;
        }
        i++;
    }
}

int charaindex(char b) {
    if (b >= 'a' && b <= 'z') {
        return (b - 'a');  
    }
    std::cerr << "Carácter no válido: " << b << std::endl;
    return -1;  
}



int costo_sub(char a, char b) {
    int i = charaindex(a);  
    int j = charaindex(b);  

    if (i == -1 || j == -1) {
        std::cerr << "Error: índices no válidos para los caracteres: " << a << "y " << b << std::endl;
        return -1;  
    }

    return cost_replace[i][j];
}


int costo_ins(char b) {
    std::cout<<b<<std::endl;
    int i = charaindex(b);  

    if (i == -1) {
        std::cerr << "Error: índice no válido para el carácter de inserción: " << b << std::endl;
        return -1;  // Retorna un valor de error o puedes elegir otro valor adecuado
    }
    return cost_insert[i][0];
}

int costo_del(char b) {
    int i = charaindex(b);

    if (i == -1) {
        std::cerr << "Error: índice no válido para el carácter de eliminación: " << b << std::endl;
        return -1;  // Retorna un valor de error o puedes elegir otro valor adecuado
    }
    return cost_delete[i][0];
}


int costo_trans(char a, char b) {
    int i = charaindex(a);  
    int j = charaindex(b);  

    if (i == -1 || j == -1) {
        std::cerr << "Error: índices no válidos para los caracteres de transposición: " << a << "y " << b << std::endl;
        return -1;  // Retorna un valor de error o puedes elegir otro valor adecuado
    }
    return cost_transpose[i][j];
}


