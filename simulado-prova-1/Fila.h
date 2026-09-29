#include "ListaEnc.h"

typedef struct str_NodoFila NodoFila;

struct str_NodoFila {
    NodoFila *prox;
    Produto dado;
};

typedef struct {
    NodoFila *ini;
    NodoFila *fim;
} FilaEnc;

void inicializaFila(FilaEnc *f);
int estaVaziaFila(FilaEnc *f);
void enqueue(FilaEnc *f, Produto d);
Produto dequeue(FilaEnc *f);
Produto maiorPrecoFila(FilaEnc *fila);
void removerDaFilaPorCod(FilaEnc *fila, int cod);
void separarParImpar(FilaEnc *fila, FilaEnc *pares, FilaEnc *impares);
float somarPrecosImparesPreservando(FilaEnc *fila);
int temConsecutivosIguais(FilaEnc *fila);