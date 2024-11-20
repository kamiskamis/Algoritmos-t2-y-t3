#include "fuerza_bruta.h"
#include "costos_operaciones.h"
#include <algorithm>

int fuerzabrutarecursiva(const std::string& s1, const std::string& s2, int m, int n){
    if (m==0){
        return n* costo_ins(s2[n-1]);
    } 
    if (n==0){
        return m* costo_ins(s2[m-1]);
    }
    int costo = (s1[m-1] == s2[n-1]) ? 0 : costo_sub(s1[m-1],s2[n-1]);

    int insertar = fuerzabrutarecursiva(s1, s2, m, n-1)+costo_ins(s2[n-1]);
    int eliminar = fuerzabrutarecursiva(s1, s2, m-1, n)+costo_del(s1[m-1]);
    int sustituir = fuerzabrutarecursiva(s1, s2, m-1, n-1)+costo;

    int resultado = std::min({insertar, eliminar, sustituir});

    if (m>1 && n>1 && s1[m-1] == s2[n-2]&&s1[m-2 == s2[n-1]]){
        int transponer = fuerzabrutarecursiva(s1, s2, m-2,n-2)+ costo_trans(s1[m-1], s2[n-2]);
        resultado = std::min(resultado, transponer);
    }
    return resultado;
}