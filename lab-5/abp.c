#include "abp.h"

NodoArv* abpBuscar(NodoArv *raiz, int cod) {
    if (raiz == NULL)              return NULL;    // não encontrado
    if (cod == raiz->dado.cod)     return raiz;    // encontrado
    if (cod < raiz->dado.cod)
        return abpBuscar(raiz->esq, cod);           // só olha a esquerda
    return abpBuscar(raiz->dir, cod);               // só olha a direita
}

NodoArv* abpInserir(NodoArv *raiz, Produto valor) {
    if (raiz == NULL) {
        NodoArv *novo = (NodoArv*) malloc(sizeof(NodoArv));
        novo->dado = valor;
        novo->esq  = NULL;
        novo->dir  = NULL;
        return novo;                         // pai vai "pendurar" este nó
    }
    if (valor.cod < raiz->dado.cod)
        raiz->esq = abpInserir(raiz->esq, valor);
    else if (valor.cod > raiz->dado.cod)
        raiz->dir = abpInserir(raiz->dir, valor);
    // se igual: código já existe, não insere duplicado
    return raiz;                             // devolve raiz (inalterada) ao pai
}

// encontra o nó de menor valor (mais à esquerda) de uma subárvore
NodoArv* abpMinimo(NodoArv *raiz) {
    while (raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz;
}

NodoArv* abpRemover(NodoArv *raiz, int cod) {
    if (raiz == NULL) return NULL;               // não encontrado

    if (cod < raiz->dado.cod)
        raiz->esq = abpRemover(raiz->esq, cod);   // procura/remove na esquerda
    else if (cod > raiz->dado.cod)
        raiz->dir = abpRemover(raiz->dir, cod);   // procura/remove na direita
    else {
        // achou o nó a remover
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);   // caso 1: folha
            return NULL;
        }
        if (raiz->esq == NULL) {
            NodoArv *filho = raiz->dir;   // caso 2: só filho direito
            free(raiz);
            return filho;
        }
        if (raiz->dir == NULL) {
            NodoArv *filho = raiz->esq;   // caso 2: só filho esquerdo
            free(raiz);
            return filho;
        }
        // caso 3: dois filhos
        NodoArv *sucessor = abpMinimo(raiz->dir);
        raiz->dado = sucessor->dado;                              // copia valor do sucessor
        raiz->dir  = abpRemover(raiz->dir, sucessor->dado.cod);  // remove o sucessor
    }
    return raiz;
}

void abpDestruir(NodoArv *raiz) {
    if (raiz == NULL) return;
    abpDestruir(raiz->esq);
    abpDestruir(raiz->dir);
    free(raiz);
}

void abpEmOrdem(const NodoArv *raiz) {
    if (raiz == NULL) return;
    abpEmOrdem(raiz->esq);
    Produto prod = raiz->dado;
    printf("[%d] -- %s -- %.2f\n", prod.cod, prod.nome, prod.preco);
    abpEmOrdem(raiz->dir);
}

// Funções a implementar

void abpContarParesImpares(const NodoArv *raiz, int *pares, int *impares) {
    if (raiz == NULL) return; 

    if (raiz->dado.cod % 2 == 0) (*pares)++; else (*impares)++;

    if (raiz->esq != NULL) abpContarParesImpares(raiz->esq, pares, impares);
    if (raiz->dir != NULL) abpContarParesImpares(raiz->dir, pares, impares);

    return;
}

void abpPodar(NodoArv *raiz, int altura) {
    if (raiz == NULL) return;
    if (altura < 0) return;

    // logica se chegar no limite de altura
    if (altura == 0) {
        abpDestruir(raiz->esq);
        abpDestruir(raiz->dir);
        raiz->esq = NULL;
        raiz->dir = NULL;
        return;
    }

    else {
        // recursivamente, mandando altura -1
        if (raiz->esq != NULL) abpPodar(raiz->esq, altura - 1);
        if (raiz->dir != NULL) abpPodar(raiz->dir, altura - 1);
    }
}

// Questão bônus
NodoArv* abpExtrairFolhas(const NodoArv *raiz) {
    if (raiz == NULL) return raiz;
    NodoArv *folhas;

    // caso trivial: chegamos em uma folha
    if (raiz->esq == NULL && raiz->dir == NULL) {
        return abpInserir(folhas, raiz->dado);
    }

    // caso recursivo: existe esq e ou existe null
    folhas = abpExtrairFolhas(raiz->esq);
    folhas = abpExtrairFolhas(raiz->dir);
    abpEmOrdem(folhas);

    return folhas;
}