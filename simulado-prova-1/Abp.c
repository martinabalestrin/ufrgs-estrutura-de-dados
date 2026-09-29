#include "Abp.h"
#include <stddef.h>

// Implemente recursivamente abpTodosPares, que retorna 1 se 
// todos os produtos possuem cod par, e 0 se algum é ímpar. 
// Retorne 1 para árvore vazia.
int abpTodosPares(const NodoArv *raiz) {
    if (raiz == NULL) return 1;
    if (raiz->dado.cod % 2 != 0) return 0;
    if (abpTodosPares(raiz->esq) == 0) return 0;
    return abpTodosPares(raiz->dir);
}

// Implemente recursivamente abpContarComUmFilho, que retorna 
// a quantidade de nodos com exatamente um filho (esquerdo ou 
// direito, mas não ambos).
int abpContarComUmFilho(const NodoArv *raiz) {
    if (raiz == NULL) return 0;
    int apenasUmFilho = 0;

    if ((raiz->esq != NULL && raiz->dir == NULL) || 
        (raiz->esq == NULL && raiz->dir != NULL)) apenasUmFilho = 1;

    return  apenasUmFilho +
            abpContarComUmFilho(raiz->esq) +
            abpContarComUmFilho(raiz->dir);
}

// Implemente recursivamente abpContarMenoresQue, que retorna a 
// quantidade de produtos cujo cod é estritamente menor que x. 
// Dica: use a propriedade da ABP para podar subárvores.
int abpContarMenoresQue(const NodoArv *raiz, int x) {
    if (raiz == NULL) return 0;

    if (raiz->dado.cod >= x) 
        return  1 + 
                abpContarMenoresQue(raiz->esq, x) 
                + abpContarMenoresQue(raiz->dir, x);

    else return abpContarMenoresQue(raiz->esq, x);
}

// Implemente recursivamente abpMaiorCod, que retorna o maior cod 
// aproveitando a propriedade da ABP (sem percorrer toda a árvore). 
// Assuma árvore não vazia.
int abpMaiorCod(const NodoArv *raiz) {
    if (raiz->dir != NULL) return abpMaiorCod(raiz->dir);
    else return raiz->dado.cod;
}

// Implemente recursivamente abpImprimirIntervalo, que imprime em 
// ordem crescente todos os produtos com cod ∈ [minCod, maxCod]. 
// Dica: use a propriedade da ABP para evitar subárvores fora do intervalo.
void abpImprimirIntervalo(const NodoArv *raiz, int minCod, int maxCod) {
    if (raiz == NULL) return;

    if (raiz->dado.cod > minCod) 
        abpImprimirIntervalo(raiz->esq, minCod, maxCod);
    if (raiz->dado.cod >= minCod && raiz->dado.cod <= maxCod)
        printf("%d - %s\n", raiz->dado.cod, raiz->dado.nome);
    if (raiz->dado.cod < maxCod)
        abpImprimirIntervalo(raiz->dir, minCod, maxCod);
}

// Implemente recursivamente abpContarMaioresQue, que retorna a quantidade 
// de produtos cujo cod é estritamente maior que x. Dica: use a propriedade 
// da ABP para podar subárvores.
int abpContarMaioresQue(const NodoArv *raiz, int x) {
    if (raiz == NULL) return 0;

    if (raiz->dado.cod <= x) 
        return abpContarMaioresQue (raiz->dir, x);
         
    return  1 +
            abpContarMaioresQue(raiz->esq, x) +
            abpContarMaioresQue(raiz->dir, x);
}

// Implemente recursivamente abpExisteNoIntervalo, que retorna 1 se existir 
// pelo menos um produto com cod ∈ [minCod, maxCod], e 0 caso contrário. 
// Dica: use a propriedade da ABP para retornar antecipadamente.
int abpExisteNoIntervalo(const NodoArv *raiz, int minCod, int maxCod) {
    if (raiz == NULL) return 0;
    if (raiz->dado.cod >= minCod || raiz->dado.cod <= maxCod) return 1;
    if (raiz->dado.cod < minCod) return abpExisteNoIntervalo(raiz->dir, minCod, maxCod);
    else return abpExisteNoIntervalo(raiz->esq, minCod, maxCod);
}

// Implemente recursivamente abpSomaCods, que retorna a soma de todos 
// os cod armazenados na árvore. Retorne 0 para árvore vazia.
int abpSomaCods(const NodoArv *raiz) {
    if (raiz == NULL) return 0;
    else    raiz->dado.cod +
            abpSomaCods(raiz->esq) +
            abpSomaCods(raiz->dir);
}