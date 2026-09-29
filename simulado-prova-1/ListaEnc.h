typedef struct str_Nodo Nodo;

typedef struct {
    int cod; 
    char nome[50]; 
    float preco;
} Produto;

struct str_Nodo { 
    Nodo *prox; 
    Produto dado; 
};

typedef struct { 
    Nodo *ini; 
} ListaEnc;

Produto maiorPreco(const ListaEnc *lista);
float somarPrecosImpares(const ListaEnc *lista);
void removerMenoresQuePreco(ListaEnc *lista, float p);
void concatenarListas(ListaEnc *a, const ListaEnc *b);
void inverterLista(ListaEnc *lista);
void moverPrimeiroParaFim(ListaEnc *lista);
void inserirAntesDeCod(ListaEnc *lista, Produto p, int cod);
float segundoMaiorPreco(const ListaEnc *lista);