#include "estatisticas.hpp"

Estatisticas::Estatisticas(){
    cmps=0;
    moves=0;
    calls=0;
    cost=0;
};

void Estatisticas::inccalls(){
    calls++;
};

void Estatisticas::inccmps(){
    cmps++;
};

void Estatisticas::incmoves(){
    moves++;
};

// Sobrecarga das funções de contagem
void Estatisticas::inccalls(int n){
    calls+=n;
};

void Estatisticas::inccmps(int n){
    cmps+=n;
};

void Estatisticas::incmoves(int n){
    moves+=n;
};

// Mostrar as estatísticas:
int Estatisticas::getCmps(){
    return cmps;
};

int Estatisticas::getCalls(){
    return calls;
};

int Estatisticas::getMoves(){
    return moves;
};

double Estatisticas::getCost(){
    return cost;
}

double Estatisticas::calculaCusto(double a, double b, double c){
    cost=a*cmps+b*moves+c*calls;
    return cost;
};

Estatisticas operator+(const Estatisticas& e1, const Estatisticas& e2) {
    Estatisticas result;

    result.calls = e1.calls + e2.calls;
    result.moves = e1.moves + e2.moves;
    result.cmps = e1.cmps + e2.cmps;
    result.cost = e1.cost + e2.cost;

    result.breaks = e1.breaks + e2.breaks;

    return result;
};
