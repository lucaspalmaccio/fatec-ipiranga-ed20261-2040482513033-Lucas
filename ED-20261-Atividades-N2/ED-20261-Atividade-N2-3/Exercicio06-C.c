// RA: 2040482513033 - Nome do Aluno: Lucas Bastos Palmaccio
/* ===========================================================================
 * Exercicio 06 - Parte C : Teste sistematico do relatorioNo para os valores
 *                          50 (raiz), 30 (intermediario), 10 (folha) e
 *                          70 (intermediario).
 *
 * Compilar: gcc -Wall -Wextra -o prog Exercicio06-C.c
 * =========================================================================== */

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
} No;

static No *novoNo(int v) {
    No *n = (No *) malloc(sizeof(No));
    if (!n) { fprintf(stderr, "malloc falhou\n"); exit(1); }
    n->dado = v; n->esq = NULL; n->dir = NULL;
    return n;
}

No *inserir(No *raiz, int valor) {
    if (raiz == NULL) return novoNo(valor);
    if (valor < raiz->dado)      raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->dado) raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

No *buscar(No *raiz, int valor) {
    if (raiz == NULL || raiz->dado == valor) return raiz;
    if (valor < raiz->dado) return buscar(raiz->esq, valor);
    else                    return buscar(raiz->dir, valor);
}

int alturaNo(No *no) {
    int hE, hD;
    if (no == NULL) return -1;
    hE = alturaNo(no->esq);
    hD = alturaNo(no->dir);
    return 1 + (hE > hD ? hE : hD);
}

int profundidadeNo(No *raiz, int valor, int prof) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return prof;
    if (valor < raiz->dado) return profundidadeNo(raiz->esq, valor, prof + 1);
    else                    return profundidadeNo(raiz->dir, valor, prof + 1);
}

int grauNo(No *no) {
    int g = 0;
    if (no == NULL) return 0;
    if (no->esq) g++;
    if (no->dir) g++;
    return g;
}

static int imprimirAncestralAux(No *raiz, int valor) {
    int achou;
    if (raiz == NULL) return 0;
    if (raiz->dado == valor) return 1;
    if (valor < raiz->dado) achou = imprimirAncestralAux(raiz->esq, valor);
    else                    achou = imprimirAncestralAux(raiz->dir, valor);
    if (achou) printf("%d ", raiz->dado);
    return achou;
}

void imprimirAncestral(No *raiz, int valor) {
    if (buscar(raiz, valor) == NULL) { printf("(nao existe) "); return; }
    if (!imprimirAncestralAux(raiz, valor)) printf("(nenhum) ");
}

static void emOrdem(No *raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esq);
    printf("%d ", raiz->dado);
    emOrdem(raiz->dir);
}

void imprimirDescendentes(No *raiz, int valor) {
    No *no = buscar(raiz, valor);
    if (no == NULL) { printf("(nao existe) "); return; }
    if (no->esq == NULL && no->dir == NULL) { printf("(nenhum - folha) "); return; }
    emOrdem(no->esq);
    emOrdem(no->dir);
}

static int contarNos(No *no) {
    if (no == NULL) return 0;
    return 1 + contarNos(no->esq) + contarNos(no->dir);
}

int contarDescendentes(No *no) {
    if (no == NULL) return 0;
    return contarNos(no->esq) + contarNos(no->dir);
}

void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

void relatorioNo(No *raiz, int valor) {
    No *no = buscar(raiz, valor);
    if (no == NULL) {
        printf("+----------------------------------+\n");
        printf("| ERRO: no %-4d nao encontrado     |\n", valor);
        printf("+----------------------------------+\n\n");
        return;
    }
    printf("+----------------------------------+\n");
    printf("| RELATORIO DO NO: %-15d |\n", valor);
    printf("+----------------------------------+\n");
    printf("| Profundidade : %-17d |\n", profundidadeNo(raiz, valor, 0));
    printf("| Altura       : %-17d |\n", alturaNo(no));
    printf("| Grau         : %-17d |\n", grauNo(no));
    printf("| Ancestrais   : ");  imprimirAncestral(raiz, valor);     printf("\n");
    printf("| Descendentes : ");  imprimirDescendentes(raiz, valor);  printf("\n");
    printf("| Qtd Descend. : %-17d |\n", contarDescendentes(no));
    printf("+----------------------------------+\n\n");
}

/* ===========================================================================
 * Teste sistematico - 4 nos representando 4 categorias estruturais.
 * =========================================================================== */
int main(void) {
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65};
    int n = sizeof(valores) / sizeof(valores[0]);
    int i;
    No *raiz = NULL;

    for (i = 0; i < n; i++) raiz = inserir(raiz, valores[i]);

    printf(">>> Teste 1: no RAIZ (50)\n");
    relatorioNo(raiz, 50);

    printf(">>> Teste 2: no INTERMEDIARIO esquerdo (30)\n");
    relatorioNo(raiz, 30);

    printf(">>> Teste 3: no FOLHA (10)\n");
    relatorioNo(raiz, 10);

    printf(">>> Teste 4: no INTERMEDIARIO direito (70)\n");
    relatorioNo(raiz, 70);

    liberarArvore(raiz);
    return 0;
}
