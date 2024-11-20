#include "p_dinamica.h"
#include "costos_operaciones.h"
#include <algorithm>

int pdinamicamemo(const std::string& s1, const std::string& s2, int m, int n, std::vector<std::vector<int>>& memo) {
    // Si ya tenemos la solución para esta subcadena, la devolvemos
    if (memo[m][n] != -1) { 
        return memo[m][n];  
    }

    // Caso base: si uno de los strings está vacío
    if (m == 0) {
        // Si s1 está vacío, debemos insertar los caracteres de s2
        return n * costo_ins(s2[n-1]);
    }

    if (n == 0) {
        // Si s2 está vacío, debemos eliminar los caracteres de s1
        return m * costo_del(s1[m-1]);
    }

    // Caso general: calcular el costo de sustitución
    int costo = (s1[m - 1] == s2[n - 1]) ? 0 : costo_sub(s1[m - 1], s2[n - 1]);

    // Recursión para insertar, eliminar o sustituir
    int insertar = pdinamicamemo(s1, s2, m, n-1, memo) + costo_ins(s2[n-1]);
    int eliminar = pdinamicamemo(s1, s2, m-1, n, memo) + costo_del(s1[m-1]);
    int sustituir = pdinamicamemo(s1, s2, m-1, n-1, memo) + costo;

    // Elegimos el mínimo entre las tres opciones
    int resultado = std::min({insertar, eliminar, sustituir});

    // Caso de transposición: solo si m > 1 y n > 1
    if (m > 1 && n > 1) {
        if (s1[m-1] == s2[n-2] && s1[m-2] == s2[n-1]) {
            // Si los caracteres se pueden transponer, actualizamos el resultado
            int transponer = pdinamicamemo(s1, s2, m-2, n-2, memo) + costo_trans(s1[m-1], s2[n-2]);
            resultado = std::min(resultado, transponer);
        }
    }

    // Guardamos el resultado en la tabla de memoria
    memo[m][n] = resultado;

    return resultado;
}


