#include <stdio.h>
#include <stdlib.h>
#include "filaEnc.c"
#include "pilhaEnc.c"

void imprimePilhaInverso(PilhaEnc *p) {
    PilhaEnc aux;
    Produto prod;

    inicializaPilha(&aux);

    // transferir todos elementos para a pilha auxiliar, assim o topo será o último elemento
    while (!estaVaziaPilha(p)) {
        topo(p, &prod);
        empilha(&aux, prod);
        desempilha(p, &prod);
    }

    // imprimir o elemento e transferi-lo de volta para a pilha p, mantendo a ordem anterior
    while (!estaVaziaPilha(&aux)) {
        topo(&aux, &prod);
        printf("%d -- %s -- %.2f\n", prod.cod, prod.nome, prod.preco);
        empilha(p, prod);
        desempilha(&aux, &prod);
    }
}

void transfereOrdenado(FilaEnc *f, PilhaEnc *p) {

    Produto prod;
    Produto prodTopo;

    if (!estaVaziaFila(f)) {
        frente(f, &prod);
        empilha(p, prod); 
        desenfileira(f, &prod);

        while (!estaVaziaFila(f)) {

            frente(f, &prod);
            topo(p, &prodTopo);

            // enquanto o código do prod (fila) for maior do que o topo da pilha
            while (prod.cod > prodTopo.cod) {
                // remover da pilha e inserir na fila de novo
                enfileira(f, prodTopo);
                desempilha(p, &prodTopo);

                if(estaVaziaPilha(p)) break;
                else topo(p, &prodTopo);
            }

            // insere o primeiro elemento da fila na pilha e remove da fila
            empilha(p, prod);
            desenfileira(f, &prod);
        }
    }
}

void enchePilha(PilhaEnc *p) {
    Produto p1 = {12, "a", 0.0};
    Produto p2 = {3, "b", 0.0};
    Produto p3 = {7, "c", 0.0};
    Produto p4 = {19, "d", 0.0};
    Produto p5 = {5, "e", 0.0};

    empilha(p, p1);
    empilha(p, p2);
    empilha(p, p3);
    empilha(p, p4);
    empilha(p, p5);
}

void encheFila(FilaEnc *f) {
    Produto p1 = {15, "g", 0.0};
    Produto p2 = {4, "i", 0.0};
    Produto p3 = {20, "f", 0.0};
    Produto p4 = {1, "j", 0.0};
    Produto p5 = {10, "h", 0.0};    

    enfileira(f, p1);
    enfileira(f, p2);
    enfileira(f, p3);
    enfileira(f, p4);
    enfileira(f, p5);
}

int main() {
    PilhaEnc p, dest;
    FilaEnc f;

    inicializaPilha(&p);
    inicializaPilha(&dest);
    inicializaFila(&f);

    // Testes com estruturas vazias
    imprimePilhaInverso(&p);
    transfereOrdenado(&f, &p);

    // Preenche as estruturas
    enchePilha(&p);
    encheFila(&f);

    // Testa as funções
    imprimePilhaInverso(&p);

    printf("-----------------\n");

    transfereOrdenado(&f, &dest);
    imprimePilhaInverso(&dest);

}