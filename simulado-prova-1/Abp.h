#include "ListaEnc.h"

typedef struct str_NodoArv NodoArv;

struct str_NodoArv {
    Produto dado;
    NodoArv *esq;
    NodoArv *dir;
};

int abpTodosPares(const NodoArv *raiz);
int abpContarComUmFilho(const NodoArv *raiz);
int abpContarMenoresQue(const NodoArv *raiz, int x);
int abpMaiorCod(const NodoArv *raiz);
void abpImprimirIntervalo(const NodoArv *raiz, int minCod, int maxCod);
int abpContarMaioresQue(const NodoArv *raiz, int x);
int abpExisteNoIntervalo(const NodoArv *raiz, int minCod, int maxCod);
int abpSomaCods(const NodoArv *raiz);
