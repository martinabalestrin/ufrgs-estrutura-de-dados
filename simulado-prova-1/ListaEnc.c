#include "ListaEnc.h"
#include <stddef.h>

// Implemente maiorPreco, que percorre a lista e retorna o produto de 
// maior preco. Assuma lista não vazia.
Produto maiorPreco(const ListaEnc *lista) {
    Nodo *atual = lista->ini;
    Produto maior = atual->dado;

    atual = atual->prox;

    while (atual != NULL) {
        if (atual->dado.preco > maior.preco) maior = atual->dado;
        atual = atual->prox;
    }

    return maior;
}

// Implemente somarPrecosImpares, que percorre a lista e retorna a soma dos 
// preco dos produtos cujo cod seja ímpar. Retorne 0.0 para lista vazia.
float somarPrecosImpares(const ListaEnc *lista) {
    Nodo *atual = lista->ini;
    float soma = 0.0;

    while (atual != NULL) {
        if (atual->dado.cod % 2 != 0) 
            soma += atual->dado.preco;
        atual = atual->prox;
    }

    return soma;
}

// Implemente removerMenoresQuePreco, que remove da lista todos os produtos 
// com preco estritamente menor que p. Libere cada nodo com free. Trate 
// múltiplos consecutivos no início.
void removerMenoresQuePreco(ListaEnc *lista, float p) {
    while (lista->ini != NULL && lista->ini->dado.preco < p) {
        Nodo *tmp = lista->ini;
        lista->ini = lista->ini->prox;
        free(tmp);
    }

    if (lista->ini == NULL) return;

    Nodo *ant = lista->ini;

    while (ant->prox != NULL) {
        if (ant->prox->dado.preco < p) {
            Nodo *tmp = ant->prox;
            ant->prox = tmp->prox;
            free(tmp);
            // não avançar ant
        } else {
            ant = ant->prox;
        }
    }
}

// Implemente concatenarListas, que concatena b ao final de a sem criar novos 
// nodos (apenas redirecione ponteiros). Trate os casos em que a ou b estejam vazias.
void concatenarListas(ListaEnc *a, const ListaEnc *b) {
    if (b == NULL) return;
    if (a == NULL) a->ini = b->ini; return;

    Nodo *atual = a->ini;

    while (atual->prox != NULL) {
        atual = atual->prox;
    }

    atual->prox = b->ini;
}

// Implemente inverterLista, que inverte a ordem dos nodos in-place, sem criar 
// novos nodos. Use três ponteiros auxiliares para redirecionar os campos prox.
void inverterLista(ListaEnc *lista) {
    Nodo *ant = NULL;
    Nodo *atual = lista->ini;

    while (atual != NULL) {
        Nodo *prox = atual->prox; // guarda o ponteiro do prox
        atual->prox = ant;
        ant = atual;
        atual = prox;
    }
    lista->ini = ant;
}

// Implemente moverPrimeiroParaFim, que move o primeiro nodo da lista para o 
// final sem criar ou destruir nodos. Não faça nada se a lista for vazia ou unitária.
void moverPrimeiroParaFim(ListaEnc *lista) {
    if (lista == NULL) return;
    if (lista->ini->prox == NULL) return;

    Nodo *primeiro = lista->ini;
    lista->ini = primeiro->prox;
    primeiro->prox == NULL;

    Nodo *atual = lista->ini;

    while (atual->prox != NULL) atual = atual->prox;

    atual->prox = primeiro;
}

// Implemente inserirAntesDeCod, que insere um novo produto imediatamente antes 
// do primeiro nodo cujo cod seja igual ao parâmetro. Se o código não existir, 
// insira o novo produto no final da lista.
void inserirAntesDeCod(ListaEnc *lista, Produto p, int cod) {
    Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
    novo->dado = p;

    // se o código estiver no primeiro nodo ou a lista for vazia
    if (lista->ini->dado.cod == cod || lista->ini == NULL) {
        novo->prox = lista->ini;
        lista->ini = novo;
        return;
    }
    
    Nodo *ant = NULL;
    while (ant->prox != NULL && ant->prox->dado.cod != cod) ant = ant->prox;

    // se não encontrar o código ou se ant->prox tiver o código procurado
    novo->prox = ant->prox;
    ant->prox = novo;
    return;
}

// Implemente segundoMaiorPreco, que percorre a lista e retorna o segundo 
// maior preço distinto. Assuma preços não-negativos; retorne -1.0 se não 
// houver segundo preço distinto.
float segundoMaiorPreco(const ListaEnc *lista) {
    float maior = -1.0;
    float segundoMaior = -1.0;
    Nodo *atual = lista->ini;

    while (atual != NULL) {
        if (atual->dado.preco > maior) {
            segundoMaior = maior;
            maior = atual->dado.preco;
        }
        
        else if (atual->dado.preco < maior && atual->dado.preco > segundoMaior) {
            segundoMaior = atual->dado.preco;
        }

        atual = atual->prox;
    }

    return segundoMaior;
}