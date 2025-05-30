#ifndef ESTATISTICAS_HPP
#define ESTATISTICAS_HPP

#include <iostream>

class Estatisticas {
public:
    Estatisticas();

    void inccalls();
    void incmoves();
    void inccmps();

    void inccalls(int n);
    void incmoves(int n);
    void inccmps(int n);

    template <typename T>
    int countBreaks(T* &v, int tam) {
        int count = 0;
        for (int i = 1; i < tam; ++i) {
            if (v[i] < v[i - 1]) {
                count++;
            }
        }
        return count;
    }

    double calculaCusto(double a, double b, double c);

    double getCost();
    int getCalls();
    int getMoves();
    int getCmps();

private:
    int calls;
    int moves;
    int cmps;
    double cost;
    int breaks;
    float* custos;

    template<typename T>
    friend class OrdenadorUniversal;

    friend Estatisticas operator+(const Estatisticas& e1, const Estatisticas& e2);
};

#endif