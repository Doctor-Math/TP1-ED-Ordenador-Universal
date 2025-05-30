#include <iostream>
#include <fstream>
#include <string>
#include "ordenador.hpp"
#include "estatisticas.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile.is_open()) {
        return 1;
    }

    int seed, tam, breaks;
    double limiarCusto, a, b, c;
    int chave;

    if (!(infile >> seed >> limiarCusto >> a >> b >> c >> tam)) {
        return 1;
    }

    int* v = new int[tam];

    int i = 0;
    while (infile >> chave) {
        if (i >= tam) break;
        v[i]=chave;
        i++;
    }

    Estatisticas EstVetor;
    breaks = EstVetor.countBreaks(v, tam);

    OrdenadorUniversal<int> OrdVetor;
    OrdVetor.setNumeroQuebras(breaks);
    OrdVetor.setSeed(seed);

    std::cout << "size " << tam << " seed " << seed << " breaks " << breaks << std::endl;

    std::cout<<std::endl;

    int limiarParticao = OrdVetor.determinaLimiarParticao(v, tam, limiarCusto, a, b, c);
    OrdVetor.determinaLimiarQuebra(v, tam, limiarCusto, a, b, c, limiarParticao);

    delete v;
    return 0;
}