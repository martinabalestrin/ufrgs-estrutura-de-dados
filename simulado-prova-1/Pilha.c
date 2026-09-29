#include "Pilha.h"
#include <stddef.h>

void inicializa(PilhaEnc *p) {
    p->topo = NULL;
}

int estaVazia(const PilhaEnc *p) {
    return p->topo == NULL;
}

void push(PilhaEnc *p, Produto valor) {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL)
        return;

    novo->dado = valor;
    novo->prox = p->topo; 
    p->topo = novo;
}

Produto pop(PilhaEnc *p) {
    Nodo *removido;
    Produto valorRemovido;

    removido = p->topo;
    valorRemovido = removido->dado;
    p->topo = removido->prox;
    free(removido);
    return valorRemovido;
}

// Implemente maiorPrecoPilha, que retorna o produto de maior preco 
// da pilha sem alterar a ordem dos elementos. Use apenas operações do TAD.
Produto maiorPrecoPilha(PilhaEnc *pilha) {
    Produto maiorPreco = {0, "", 0.0f};
    PilhaEnc aux;
    inicializaPilha(&aux);

    while (!estaVazia(pilha)) {
        Produto atual = pop(pilha);
        if (atual.preco > maiorPreco.preco) maiorPreco = atual;
        push(&aux, atual);
    }

    while (!estaVazia(&aux)) push(pilha, pop(&aux));

    return maiorPreco;
}

// Implemente removerDaPilhaPorCod, que remove da pilha o primeiro produto 
// (do topo para a base) cujo cod seja igual ao parâmetro, preservando a 
// ordem dos demais. Use apenas operações do TAD.
void removerDaPilhaPorCod(PilhaEnc *pilha, int cod) {
    PilhaEnc aux;
    inicializaPilha(&aux);
    int removido = 0;

    while (!estaVaziaPilha(pilha)) {
        Produto atual = pop(pilha);
        if (atual.cod == cod && !removido) removido = 1;
        else push(&aux, atual);
    }

    while (!estaVaziaPilha(&aux)) push(pilha, pop(&aux));
}

// Implemente mesmasElementos, que retorna 1 se a pilha e a fila possuem a 
// mesma quantidade de elementos e os mesmos cod na mesma ordem (topo da 
// pilha corresponde à frente da fila), e 0 caso contrário. Ambas devem ser 
// preservadas. Use apenas operações do TAD.
int mesmasElementos(PilhaEnc *pilha, FilaEnc *fila) {
    PilhaEnc auxPilha;
    inicializaPilha(&auxPilha);
    FilaEnc auxFila;
    inicializaFila(&auxFila);

    int iguais = 1;

    while (!estaVaziaPilha(pilha) && !estaVaziaFila(fila)) {
        Produto prodPilha = pop(pilha);
        Produto prodFila = dequeue(fila);

        if (prodPilha.cod != prodFila.cod) iguais = 0;

        push(&auxPilha, prodPilha);
        enqueue(&auxFila, prodFila);
    }

    // Se uma das duas não estiver esvaziado
    if (!estaVaziaPilha(pilha) || !estaVaziaFila(fila)) {
        iguais = 0;

        while(!estaVaziaPilha(pilha)) push(&auxPilha, pop(pilha));
        while(!estaVaziaFila(fila)) enqueue(&auxFila, dequeue(fila));
    }

    while (!estaVaziaPilha(&auxPilha)) push(pilha, pop(&auxPilha));
    while (!estaVaziaFila(&auxFila)) enqueue(fila, dequeue(&auxFila));

    return iguais;
}