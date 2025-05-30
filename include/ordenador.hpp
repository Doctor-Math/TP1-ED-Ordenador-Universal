#ifndef ORDENADOR_HPP
#define ORDENADOR_HPP
#include <iostream>

class Estatisticas;

template<typename T>
class OrdenadorUniversal{
    public:

    void ordenadorUniversal(T* vetor, int tam, int minTamParticao, int limiarQuebras, Estatisticas& estQs, Estatisticas& estIn);
    int determinaLimiarParticao(T* vetor, int tam, int limiarCusto,double a, double b, double c);
    int determinaLimiarQuebra(T* vetor, int tam, int limiarCusto,double a, double b, double c, int limiarParticao);
    void calculaNovaFaixa(int limParticao, int& minMPS, int& maxMPS,int& passoMPS, int& idMin, int& idMax, int numMPS);

    void setNumeroQuebras(int);
    void setSeed(int);

    // Função para embaralhar um vetor para um número específico de quebras

    void embaralhar(T* vetor, int numShuffle, int tam, long int seed);

    // Algoritmos de ordenação:

    void quickSort(T* vetor, int inicio, int fim, Estatisticas&, int minTamParticao);

    void partition3(T* vetor, int inicio, int fim, Estatisticas&, int* i, int* j);

    void insertionSort(T* vetor, int inicio, int fim, Estatisticas&);

    private:
    int minMPS;
    int maxMPS;
    int numeroQuebras;
    int seed;
    friend class Estatisticas;

};

#include "ordenador.tpp"

#endif