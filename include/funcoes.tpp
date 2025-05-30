#include "funcoes.hpp"
#include "estatisticas.hpp"

template<typename T>
T median(T a, T b, T c){
    if ((a <= b) && (b <= c)) return b;  // a b c
    if ((a <= c) && (c <= b)) return c;  // a c b
    if ((b <= a) && (a <= c)) return a;  // b a c
    if ((b <= c) && (c <= a)) return c;  // b c a
    if ((c <= a) && (a <= b)) return a;  // c a b
    if ((c <= b) && (b <= a)) return b;  // c b a

    std::cerr << "Erro: entrada inválida em median()\n";
    return a;
};

template<typename T>
void swap(T*& v, int i, int j, Estatisticas& est) {
    T temp = v[i];
    v[i] = v[j];
    v[j] = temp;

    est.incmoves(); // Pode considerar como 3 movimentos (1 leitura, 2 gravações)
    est.incmoves();
    est.incmoves();
};


template<typename T>
int menorElemento(T* v, int tam){
    T menor = v[0];
    int idmenor = 0;
    for (int i = 0; i < tam; i++) {
        if (v[i] < menor) {
            menor = v[i];
            idmenor = i;
        }
    }
    return idmenor;
};