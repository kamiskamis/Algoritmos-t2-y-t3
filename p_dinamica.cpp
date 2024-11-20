#include "p_dinamica.h"
#include "costos_operaciones.h"
#include <algorithm>

int pdinamicamemo(const std::string& s1, const std::string& s2, int m, int n, std::vector<std::vector<int>>& memo){
    if(memo[m][n] != -1){
        return memo[m][n];    
    }

    if(m == 0){
        return n* costo_ins(s2[n-1]);
    }
    if(n == 0){
        return n* costo_del(s1[m-1]);
    }

    int costo = (s1[m-1] == s2[n-1]) ? 0 : costo_sub(s1[m-1], s2[n-2]);

    int insertar = pdinamicamemo(s1, s2, m, n-1, memo)+costo_ins(s2[n-1]);
    int eliminar = pdinamicamemo(s1, s2, m-1, n, memo)+costo_del(s1[m-1]);
    int sustituir = pdinamicamemo(s1, s2, m-1, n-1, memo)+costo;

    int resultado = std::min({insertar, eliminar, sustituir});

    if (m>1 && n>1 && (s1[m-1] == s2[n-2]) && (s1[m-2] == s2[n-1])){
        int transponer = pdinamicamemo(s1, s2, m-2, n-2, memo)+ costo_trans(s1[m-1],s2[n-2]);
        resultado = std::min(resultado, transponer);
    }
    memo[m][n]= resultado;
    return resultado;
}

