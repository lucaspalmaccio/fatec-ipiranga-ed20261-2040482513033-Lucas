// RA: 2040482513033 - Nome do Aluno: Lucas Bastos Palmaccio
/* ===========================================================================
 * Exercicio 05 - Partes B e C : Consultas estruturais na ABB + desenho ASCII.
 *   (a) altura dos nos: 50, 30, 70, 20 e 10
 *   (b) profundidade dos nos: 50, 30, 70, 45 e 10
 *   (c) grau de cada no (percurso em-ordem)
 *   (d) altura total da arvore
 *
 * Compilar: gcc -Wall -Wextra -o prog Exercicio05-B.c
 *
 * ---------------------------------------------------------------------------
 * Parte C - ASCII art da ABB resultante das insercoes
 *   50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65
 * ---------------------------------------------------------------------------
 *
 *                       50
 *                     /    \
 *                   30      70
 *                  /  \    /  \
 *                 20  40  60  80
 *                /  \   \   \
 *               10  25  45  65
 *
 *   Verificacao manual (3 nos):
 *   - No 50 (raiz):  prof = 0, alt = 3, grau = 2  (caminho 50->30->20->10)
 *   - No 30 (interm): prof = 1, alt = 2, grau = 2
 *   - No 10 (folha):  prof = 3, alt = 0, grau = 0
 *   Todos os valores conferem com a saida das funcoes implementadas.
 * --------------------------------------------------------------------------- */

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

/* Busca recursiva por um no com determinado valor (auxiliar). */
No *buscar(No *raiz, int valor) {
    if (raiz == NULL || raiz->dado == valor) return raiz;
    if (valor < raiz->dado) return buscar(raiz->esq, valor);
    else                    return buscar(raiz->dir, valor);
}

/* Percurso em-ordem imprimindo o grau de cada no. */
void imprimirGrausEmOrdem(No *raiz) {
    if (raiz == NULL) return;
    imprimirGrausEmOrdem(raiz->esq);
    printf("  no %2d -> grau %d\n", raiz->dado, grauNo(raiz));
    imprimirGrausEmOrdem(raiz->dir);
}

void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

/* Auxiliar: imprime altura/profundidade procurando o no. */
static void mostrarAltura(No *raiz, int valor) {
    No *n = buscar(raiz, valor);
    if (n) printf("  altura(%2d) = %d\n", valor, alturaNo(n));
    else   printf("  altura(%2d) = (no nao encontrado)\n", valor);
}

static void mostrarProfundidade(No *raiz, int valor) {
    int p = profundidadeNo(raiz, valor, 0);
    if (p >= 0) printf("  profundidade(%2d) = %d\n", valor, p);
    else        printf("  profundidade(%2d) = (no nao encontrado)\n", valor);
}

int main(void) {
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65};
    int n = sizeof(valores) / sizeof(valores[0]);
    int i;
    No *raiz = NULL;

    /* --- Construcao da arvore ----------------------------------------------- */
    for (i = 0; i < n; i++)
        raiz = inserir(raiz, valores[i]);

    /* --- (a) Altura dos nos pedidos ----------------------------------------- */
    printf("=== (a) Altura dos nos ===\n");
    mostrarAltura(raiz, 50);
    mostrarAltura(raiz, 30);
    mostrarAltura(raiz, 70);
    mostrarAltura(raiz, 20);
    mostrarAltura(raiz, 10);

    /* --- (b) Profundidade dos nos pedidos ----------------------------------- */
    printf("\n=== (b) Profundidade dos nos ===\n");
    mostrarProfundidade(raiz, 50);
    mostrarProfundidade(raiz, 30);
    mostrarProfundidade(raiz, 70);
    mostrarProfundidade(raiz, 45);
    mostrarProfundidade(raiz, 10);

    /* --- (c) Grau de cada no (percurso em-ordem) ---------------------------- */
    printf("\n=== (c) Grau de cada no (em-ordem) ===\n");
    imprimirGrausEmOrdem(raiz);

    /* --- (d) Altura total --------------------------------------------------- */
    printf("\n=== (d) Altura total da arvore ===\n");
    printf("  altura(raiz) = %d\n", alturaNo(raiz));

    liberarArvore(raiz);
    return 0;
}
