#ifndef FUNCOES_HPP
#define FUNCOES_HPP

#include <iostream>

class Estatisticas;

// Função mediana genérica
template<typename T>
T median(T a, T b, T c);

// Função swap genérica
template<typename T>
void swap(T*& v, int i, int j, Estatisticas& est);

// Função que encontra o índice do menor elemento
template<typename T>
int menorElemento(T* v, int tam);

#include "funcoes.tpp"

#endif
