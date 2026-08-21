#include <stdio.h>
#include <stdlib.h>
#include "listaEnc.h"

void inicializar(ListaEnc *lista) {
    lista->ini = NULL;
}

int tamanho(const ListaEnc *lista) {
    Nodo *aux = lista->ini;
    int contador = 0;

    while (aux != NULL) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

void imprimir(const ListaEnc *lista) {
    Nodo *aux;
    aux = lista->ini;

    while (aux != NULL) {
        printf("Codigo: %d\n", aux->dado.cod);
        printf("Nome: %s\n", aux->dado.nome);
        printf("Preco: %.2f\n", aux->dado.preco);
        printf("-------\n");
        aux = aux->prox;
    }
}

Produto buscar(const ListaEnc *lista, int cod) {
    Nodo *aux;
    Produto prod = {0, "", 0.0f};
    aux = lista->ini;

    while (aux != NULL) {
        if (aux->dado.cod == cod)
            return aux->dado;
        aux = aux->prox;
    }

    return prod; // não encontrado: produto "vazio"
}

int inserirInicio(ListaEnc *lista, Produto prod) {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL)
        return 0; // falha na alocação

    novo->dado = prod;
    novo->prox = lista->ini; // o novo nodo aponta para o antigo início
    lista->ini = novo;        // o novo nodo passa a ser o início

    return 1;
}

int inserirFim(ListaEnc *lista, Produto prod) {
    Nodo *novo;
    Nodo *aux;

    novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL)
        return 0;

    novo->dado = prod;
    novo->prox = NULL;

    if (lista->ini == NULL) { // lista vazia: o novo nodo é o único (e o início)
        lista->ini = novo;
    } else {
        aux = lista->ini;
        while (aux->prox != NULL) // percorre até o último nodo
            aux = aux->prox;
        aux->prox = novo;
    }

    return 1;
}

int removerPorCod(ListaEnc *lista, int cod) {
    Nodo *ant;
    Nodo *aux;

    ant = NULL;
    aux = lista->ini;

    while (aux != NULL && aux->dado.cod != cod) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) // não encontrado
        return 0;

    if (ant == NULL) // removendo o primeiro nodo
        lista->ini = aux->prox;
    else             // removendo do meio ou do final
        ant->prox = aux->prox;

    free(aux);
    return 1;
}

void destruir(ListaEnc *lista) {
    Nodo *ant;
    Nodo *aux;
    aux = lista->ini;

    while (aux != NULL) {
        ant = aux;
        aux = aux->prox;
        free(ant);
    }

    lista->ini = NULL;
}

// Funções a implementar
int removerFim(ListaEnc *l, Produto *prodRemovido) {
    Nodo *ant = NULL;
    Nodo *aux = l->ini;
    int cont = 0;

    if (aux == NULL) return 0; // se a lista for vazia

    while (aux->prox != NULL) {
        ant = aux;
        aux = aux->prox;
        cont++;
    }

    *prodRemovido = aux->dado;
    
    if (ant == NULL) l->ini = NULL;
    else ant->prox = NULL;
    
    free(aux);
    return 1;
}

int trocarComProximo(ListaEnc *l, int pos) {
    Nodo *aux = l->ini;

    if (pos > tamanho(l) - 1) return 0;

    for (int i = 0; i < pos; i++) {
        aux = aux->prox;
    }

    // DESAFIO: trocar o último com o primeiro
    if (aux->prox == NULL) {
        Produto temp = aux->dado;
        aux->dado = l->ini->dado;
        l->ini->dado = temp;
    }

    // caso geral: trocar com o próximo nodo
    else {
        Nodo *prox = aux->prox;
        Produto temp = aux->dado;
        aux->dado = prox->dado;
        prox->dado = temp;
    }

    return 1;
}