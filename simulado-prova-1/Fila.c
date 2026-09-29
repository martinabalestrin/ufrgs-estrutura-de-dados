#include "Fila.h"
#include <stddef.h>

void inicializa(FilaEnc *f) {
    f->ini = NULL;
    f->fim = NULL;
}

int estaVazia(const FilaEnc *f) {
    return f->ini == NULL;
}

void enqueue(FilaEnc *f, Produto valor) {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL)
        return;

    novo->dado = valor;
    novo->prox = NULL;

    if (f->fim != NULL)
        f->fim->prox = novo;
    else
        f->ini = novo;

    f->fim = novo;
    return;
}

Produto dequeue(FilaEnc *f) {
    Produto valorRemovido = {0, "", 0.0f};

    if (estaVazia(f)) return valorRemovido;

    NodoFila *removido = f->ini;
    valorRemovido = removido->dado;
    f->ini = removido->prox;

    if (f->ini == NULL)
        f->fim = NULL;

    free(removido);
    return valorRemovido;
}

// Implemente maiorPrecoFila, que retorna o produto de maior preco 
// da fila sem alterar a ordem dos elementos. Use apenas operações do TAD.
Produto maiorPrecoFila(FilaEnc *fila) {
    Produto maiorPreco = {0, "", 0.0f};
    FilaEnc aux;
    inicializaFila(&aux);

    while (!estaVaziaFila(fila)) {
        Produto atual = dequeue(fila);
        if (atual.preco > maiorPreco.preco) maiorPreco = atual;
        enqueue(&aux, atual);
    }

    while (!estaVaziaFila(&aux)) {
        enqueue(fila, dequeue(&aux));
    }

    return maiorPreco;
}

// Implemente removerDaFilaPorCod, que remove da fila o primeiro 
// produto cujo cod seja igual ao parâmetro, preservando a ordem 
// dos demais. Use apenas operações do TAD.
void removerDaFilaPorCod(FilaEnc *fila, int cod) {
    FilaEnc aux;
    inicializaFila(&aux);
    int removido = 0;

    while (!estaVaziaFila(fila)) {
        Produto atual = dequeue(fila);
        if (atual.cod == cod && !removido) removido = 1;
        else enqueue(&aux, atual);
    }

    while (!estaVaziaFila(&aux)) enqueue(fila, dequeue(&aux));
}

// Implemente separarParImpar, que separa os elementos de fila em duas 
// novas filas: pares (cod par) e impares (cod ímpar), preservando a ordem 
// original em cada fila. A fila original é consumida.
void separarParImpar(FilaEnc *fila, FilaEnc *pares, FilaEnc *impares) {
    inicializaFila(pares);
    inicializaFila(impares);

    while(!estaVaziaFila) {
        Produto atual = dequeue(fila);
        if (atual.cod % 2 == 0) enqueue(pares, atual);
        else enqueue(impares, atual);
    }
}

// Implemente somarPrecosImparesPreservando, que retorna a soma dos preco 
// dos produtos com cod ímpar, preservando o conteúdo e a ordem da fila. 
// Use apenas operações do TAD.
float somarPrecosImparesPreservando(FilaEnc *fila) {
    float somaPrecosImpares = 0.0;
    FilaEnc aux;
    inicializaFila(&aux);

    while (!estaVaziaFila(fila)) {
        Produto atual = dequeue(fila);
        if (atual.cod % 2 != 0) somaPrecosImpares += atual.preco;
        enqueue(&aux, atual);
    }

    while (!estaVaziaFila(&aux)) enqueue(fila, dequeue(&aux));

    return somaPrecosImpares;
}

// Implemente temConsecutivosIguais, que retorna 1 se existem dois produtos 
// consecutivos com o mesmo cod na fila, e 0 caso contrário. A fila deve ser 
// preservada. Use apenas operações do TAD.
int temConsecutivosIguais(FilaEnc *fila) {
    if (estaVaziaFila) return 0;
 
    FilaEnc aux;
    inicializaFila(&aux);
    int consecutivos = 0;
    
    // lida com o primeiro elemento
    Produto ant = dequeue(fila);
    enqueue(&aux, ant);

    while (!estaVaziaFila(fila)) {
        Produto atual = dequeue(fila);
        if (ant.cod == atual.cod) consecutivos = 1;
        
        enqueue(&aux, atual);
        ant = atual;
    }

    while (!estaVaziaFila(&aux)) enqueue(fila, dequeue(&aux));

    return consecutivos;
}