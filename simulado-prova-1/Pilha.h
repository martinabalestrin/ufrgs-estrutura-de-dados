#include "ListaEnc.h"
#include "Fila.h"

typedef struct str_NodoPilha NodoPilha;

struct str_NodoPilha { 
    NodoPilha *prox; 
    Produto dado; 
};

typedef struct { 
    NodoPilha *topo; 
} PilhaEnc;

void inicializaPilha(PilhaEnc *p);
int estaVaziaPilha(PilhaEnc *p);
void push(PilhaEnc *p, Produto d);
Produto pop(PilhaEnc *p);
Produto maiorPrecoPilha(PilhaEnc *pilha);
void removerDaPilhaPorCod(PilhaEnc *pilha, int cod);
int mesmasElementos(PilhaEnc *pilha, FilaEnc *fila);