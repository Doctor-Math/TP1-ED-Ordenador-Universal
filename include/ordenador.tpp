#include "ordenador.hpp"
#include "funcoes.hpp"
#include "estatisticas.hpp"

#include <cstdlib>
#include <cmath>
#include <iomanip>

#define INTERVALOS 6



template <typename T>
void OrdenadorUniversal<T>::ordenadorUniversal(T* v, int tamanho, int minTamParticao, int limiarQuebras, Estatisticas& estQs, Estatisticas& estIn) { 
    if (numeroQuebras < limiarQuebras) {
        insertionSort(v, 0, tamanho - 1, estIn);
    } else {
        if (tamanho > minTamParticao) {
            quickSort(v, 0, tamanho - 1, estQs, minTamParticao);
        } else {
            insertionSort(v, 0, tamanho - 1, estIn);
        }
    }
};


template <typename T>
void OrdenadorUniversal<T>::embaralhar(T* vetor, int numShuffle, int tam, long int seed) {
    srand48(seed);
    int p1 = 0, p2 = 0;
    T temp;

    for (int t = 0; t < numShuffle; t++) {
        while (p1 == p2) {
            p1 = static_cast<int>(drand48() * tam);
            p2 = static_cast<int>(drand48() * tam);
        }

        temp = vetor[p1];
        vetor[p1] = vetor[p2];
        vetor[p2] = temp;

        p1 = p2 = 0;
    }
};


template<typename T>
int OrdenadorUniversal<T>::determinaLimiarParticao(T* vetor, int tam, int limiarCusto, double a, double b, double c) {
    int minMPS = 2;
    int maxMPS = tam;
    int idMin = 0, idMax = INTERVALOS - 1;

    // numMPS>=5 para garantir o início da iteração
    int numMPS = INTERVALOS;

    // Vetor que armazenará o custo total para um limiar de partição
    double custos[10];

    // diffCusto>limiarCusto para garantir o início da iteração
    double diffCusto = limiarCusto + 1;
    int limParticao = 0;
    int iteracao = 0;

    int passoMPS = (maxMPS - minMPS) / 5;

    while (diffCusto > limiarCusto && numMPS >= 5) {
        numMPS = 0;
        std::cout << "iter " << iteracao << std::endl;

        for (int t = minMPS; t <= maxMPS; t += passoMPS) {

            // Cria uma cópia do vetor para uso no ordenador
            T* vteste = new T[tam];
            for (int i = 0; i < tam; i++) {
                vteste[i] = vetor[i];
            }

            Estatisticas estQs, estIn, estTotal;

            ordenadorUniversal(vteste, tam, t, this->numeroQuebras, estQs, estIn);

            estTotal = estQs + estIn;
            double custo = estTotal.calculaCusto(a, b, c);
            custos[numMPS] = custo;

            // Imprime estatísticas referentes à ordenação com o limiar de partição testado
            std::cout << "mps " << t << " cost " << std::fixed << std::setprecision(9)
            << estTotal.getCost() << " cmp " << estTotal.getCmps()
            << " move " << estTotal.getMoves()
            << " calls " << estTotal.getCalls() << std::endl;

            numMPS++;
            delete[] vteste;
        }

        // Encontrar índice do menor custo
        int idmenor = menorElemento(custos, numMPS);

        // Calcular o limiar baseado no índice do menor custo
        limParticao = minMPS + idmenor * passoMPS;

        // Ajustar faixa para a próxima iteração
        calculaNovaFaixa(idmenor, minMPS, maxMPS, passoMPS, idMin, idMax, numMPS);

        // Calcular diferença de custo entre extremos da nova faixa
        diffCusto = fabs(custos[idMin] - custos[idMax]);

        // Imprime resultados finais da iteração
        std::cout << "numMPS " << numMPS << " limParticao " << limParticao
                  << " mpsdiff " << std::setprecision(6) << static_cast<float>(diffCusto) << std::endl
                  << std::endl;

        iteracao++;
    }

    return limParticao;
};

template<typename T>
int OrdenadorUniversal<T>::determinaLimiarQuebra(T* vetor, int tam, int limiarCusto, double a, double b, double c, int limiarParticao){
    int minLq = 1;
    int maxLq = tam / 2;
    int idMin = 0, idMax = 0;
    // numLq>=5 para garantir o início da iteração
    int numLq = INTERVALOS;

    // Vetores que armazenarão os custos totais e de cada algoritmo para um número de quebras
    double custos[20];
    double custos_in[20]; 
    double custos_qs[20];

    // diffCusto>limiarCusto para garantir o início da iteração
    double diffCusto = limiarCusto + 1;
    int limQuebras = 0;
    int iteracao = 0;

    int passoLq = (maxLq - minLq) / 5;

    while (diffCusto > limiarCusto && numLq >= 5) {
        numLq = 0;

        std::cout << "iter " << iteracao << std::endl;

        for (int t = minLq; t <= maxLq; t += passoLq) {

            // Cria uma cópia do vetor para uso no ordenador
            T* vteste = new T[tam];
            for (int i = 0; i < tam; i++) {
                vteste[i] = vetor[i];
            }

            Estatisticas estQs, estIn, estTotal, estAux;

            // Ordena, embaralha e aplica o quickSort

            insertionSort(vteste, 0, tam - 1, estAux);

            embaralhar(vteste, t, tam, seed);

            quickSort(vteste, 0, tam - 1, estQs, limiarParticao);

            custos_qs[numLq] = estQs.calculaCusto(a, b, c);

            // Imprime estatísticas referentes à ordenação por quickSort com o número de quebras testado

            std::cout << "qs lq " << t << " cost " << std::fixed << std::setprecision(9) << estQs.getCost()
            << " cmp " << estQs.getCmps() << " move " << estQs.getMoves() << " calls " << estQs.getCalls() << std::endl;

            // Ordena, embaralha e aplica o insertionSort

            embaralhar(vteste, t, tam, seed);

            insertionSort(vteste, 0, tam - 1, estIn);

            custos_in[numLq] = estIn.calculaCusto(a, b, c);

            // Insere, num vetor, a diferença de custos entre os algoritmos de ordenação para o mesmo número de quebras
            double custo = fabs(custos_in[numLq] - custos_qs[numLq]);
            custos[numLq] = custo;

            // Imprime estatísticas referentes à ordenação por insertion com o número de quebras testado
            std::cout << "in lq " << t << " cost " << std::fixed << std::setprecision(9) << estIn.getCost()
            << " cmp " << estIn.getCmps() << " move " << estIn.getMoves() << " calls " << estIn.getCalls() << std::endl;

            numLq++;

            delete[] vteste;
        }

        // Encontrar índice com a menor diferença de custo
        int idmenor = menorElemento(custos, numLq);

        // Calcular o limiar baseado no índice da menor diferença
        limQuebras = minLq + idmenor * passoLq;

        // Ajustar faixa para a próxima iteração
        calculaNovaFaixa(idmenor, minLq, maxLq, passoLq, idMin, idMax, numLq);

        // Calcular diferença de custo entre extremos da nova faixa
        diffCusto = fabs(custos_in[idMin] - custos_in[idMax]);

        // Imprime resultados finais da iteração
        std::cout << "numlq " << numLq << " limQuebras " << limQuebras
        << " lqdiff " << std::setprecision(6) << static_cast<float>(diffCusto) << std::endl << std::endl;

        iteracao++;
    }

    return limQuebras;
};

template<typename T>
void OrdenadorUniversal<T>::calculaNovaFaixa(int limParticao, int& minMPS, int& maxMPS, int& passoMPS, int& idMin, int& idMax, int numMPS) {
    int newMin, newMax;

    if (limParticao == 0) {
        newMin = 0;
        newMax = 2;
    } else if (limParticao == numMPS - 1) {
        newMin = numMPS - 3;
        newMax = numMPS - 1;
    } else {
        newMin = limParticao - 1;
        newMax = limParticao + 1;
    }

    // Atualiza os limites de tamanho da partição baseado no passoMPS
    int novoMinMPS = minMPS + newMin * passoMPS;
    int novoMaxMPS = minMPS + newMax * passoMPS;

    idMin = newMin;
    idMax = newMax;

    minMPS = novoMinMPS;
    maxMPS = novoMaxMPS;

    passoMPS = (maxMPS - minMPS) / 5;
    if (passoMPS == 0) passoMPS++;
};

template<typename T>
void OrdenadorUniversal<T>::setNumeroQuebras(int numeroQuebras){
    this->numeroQuebras=numeroQuebras;
};

template<typename T>
void OrdenadorUniversal<T>::setSeed(int seed){
    this->seed=seed;
};


template<typename T>
void OrdenadorUniversal<T>::insertionSort(T* v, int inicio, int fim, Estatisticas& est) {
    T chave;
    int i, j;

    est.inccalls();
    for (i = inicio + 1; i <= fim; i++) {
        chave = v[i];
        est.incmoves();  // Pegando a chave para inserção (leitura+armazenamento)

        j = i - 1;

        while (j >= 0 && chave < v[j]) {
            est.inccmps();  // Comparação v[j] > chave

            T valor = v[j];
            v[j + 1] = valor;
            est.incmoves();  // Movimento da chave v[j] para frente

            j--;
        }
        est.inccmps();  // Comparação que causou a saída do while

        v[j + 1] = chave;
        est.incmoves();  // Inserindo a chave na posição correta
    }
};


template<typename T>
void OrdenadorUniversal<T>::partition3(T* v, int inicio, int fim, Estatisticas& est, int* i, int* j) {
    int meio = (inicio + fim) / 2;
    T pivo = median(v[inicio], v[meio], v[fim]);
    *i = inicio;
    *j = fim;

    est.inccalls();  // Conta a chamada recursiva que vai usar esse partition

    do {
        while (pivo > v[*i]) {
            est.inccmps();  // Comparação para avançar i
            (*i)++;
        }
        est.inccmps();  // Para a última comparação que falhou

        while (pivo < v[*j]) {
            est.inccmps();  // Comparação para retroceder j
            (*j)--;
        }
        est.inccmps();  // Para a última comparação que falhou

        if ((*i) <= (*j)) {
            swap(v, *i, *j, est);
            (*i)++;
            (*j)--;
        }
    } while ((*i) <= (*j));
};

template<typename T>
void OrdenadorUniversal<T>::quickSort(T* v, int inicio, int fim, Estatisticas& est, int minTamParticao) {
    int i, j;
    est.inccalls();  // Contar a chamada do quickSort
        partition3(v, inicio, fim, est, &i, &j);

    // Lado esquerdo: [inicio .. j]
    if ((j > inicio) && (abs(j - inicio) < minTamParticao)) {
        insertionSort(v, inicio, j, est);
    } else if (j > inicio) {
        quickSort(v, inicio, j, est, minTamParticao);
    }

    // Lado direito: [i .. fim]
    if ((i < fim) && (abs(fim - i) < minTamParticao)) {
        insertionSort(v, i, fim, est);
    } else if (i < fim) {
        quickSort(v, i, fim, est, minTamParticao);
    }
};



