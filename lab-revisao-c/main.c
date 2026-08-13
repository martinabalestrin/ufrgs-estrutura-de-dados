#include <stdio.h>

#define MAX 50
#define NUM_NOTAS 3

typedef struct {
    char nome[50];
    int matricula;
    float media;
} Aluno;

void lerAluno(Aluno *aluno);
void lerNotas(float notas[], int n);
float calcularMedia(float notas[], int n);
void atualizarMedia(Aluno *aluno, float media);
void imprimirAluno(Aluno aluno);
int contarAprovados(Aluno turma[], int n);
void salvarBinario(Aluno turma[], int n, char *nomeArquivo);
void gerarRelatorioTexto(Aluno turma[], int n, char *nomeArquivo);

void lerAluno(Aluno *aluno) {
    printf("Nome do aluno: ");
    scanf("%s", aluno->nome);

    printf("Matrícula do aluno: ");
    scanf("%d", &aluno->matricula);
}

void lerNotas(float notas[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Nota: ");
        scanf("%f", &notas[i]);
    }
}

float calcularMedia(float notas[], int n) {
    float soma = 0;

    for (int i = 0; i < n; i++) {
        soma += notas[i];
    }

    return soma / n;
}

void atualizarMedia(Aluno *aluno, float media) {
    aluno->media = media;
}

void imprimirAluno(Aluno aluno) {
    printf("\n================");
    printf("\nNome: %s", aluno.nome);
    printf("\nMatrícula: %d", aluno.matricula);
    printf("\nMédia: %.2f", aluno.media);
    printf("\n================\n");
}

int contarAprovados(Aluno turma[], int n) {

    if (n == 0) return 0;

    int aprovado = 0;
    if (turma[n-1].media >= 6) aprovado = 1;

    return aprovado + contarAprovados(turma, n-1);
}

void salvarBinario(Aluno turma[], int n, char *nomeArquivo) {

    FILE *ftpr = fopen(nomeArquivo, "wb");

    if (ftpr == NULL) {
        printf("Erro ao abrir o arquivo!");
        return;
    }
    else {
        fwrite(turma, sizeof(Aluno), n, ftpr);
        fclose(ftpr);
    }
}

void gerarRelatorioTexto(Aluno turma[], int n, char *nomeArquivo) {

    FILE *ftpr = fopen(nomeArquivo, "w");

    if (ftpr == NULL) {
        printf("Erro ao abrir o arquivo!");
        return;
    }
    else {
        for (int i = 0; i < n; i++) {
            fprintf(ftpr, "%s %d %.2f \n", turma[i].nome, turma[i].matricula, turma[i].media);
        }
        fclose(ftpr);
    }
}

int main() {
    Aluno turma[MAX];
    float notas[NUM_NOTAS];
    float media;
    int n, i;

    printf("Quantos alunos serão cadastrados? ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        // Item (a): leitura do aluno (nome e matrícula) por referência
        lerAluno(&turma[i]);

        // Item (b): leitura das notas em um vetor
        lerNotas(notas, NUM_NOTAS);

        // Item (c): cálculo da média do vetor de notas
        media = calcularMedia(notas, NUM_NOTAS);

        // Item (d): atualização da média do aluno via ponteiro (->)
        atualizarMedia(&turma[i], media);
    }

    printf("\n--- Dados da turma ---\n");
    for (i = 0; i < n; i++) {
        // Item (e): impressão do aluno (passagem por valor)
        imprimirAluno(turma[i]);
    }

    // Item (f): contagem recursiva de aprovados
    printf("\nTotal de aprovados: %d\n", contarAprovados(turma, n));

    // Item (g): gravação da turma em arquivo binário
    salvarBinario(turma, n, "turma.dat");

    // Item (h): geração do relatório em arquivo texto
    gerarRelatorioTexto(turma, n, "relatorio.txt");

    return 0;
}