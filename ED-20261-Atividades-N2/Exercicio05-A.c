// RA: 2040482513033 - Nome do Aluno: Lucas Bastos Palmaccio
// /* ===========================================================================
 * Exercicio 05 - Parte A : Definicao da Arvore Binaria de Busca (ABB) e
 *                          funcoes basicas: inserir, alturaNo, profundidadeNo,
 *                          grauNo e liberarArvore.
 *
 * Compilar: gcc -Wall -Wextra -o prog Exercicio05-A.c
 * =========================================================================== */

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
} No;

/* Cria um no isolado (auxiliar). */
static No *novoNo(int valor) {
    No *n = (No *) malloc(sizeof(No));
    if (n == NULL) {
        fprintf(stderr, "Erro: malloc falhou.\n");
        exit(1);
    }
    n->dado = valor;
    n->esq  = NULL;
    n->dir  = NULL;
    return n;
}

/* ---------------------------------------------------------------------------
 * Insercao recursiva em ABB.
 *   - Se a (sub)arvore esta vazia, cria o no aqui.
 *   - Se valor < raiz->dado, desce a esquerda.
 *   - Se valor > raiz->dado, desce a direita.
 *   - Valores duplicados sao ignorados (poderiam ir a direita).
 * --------------------------------------------------------------------------- */
No *inserir(No *raiz, int valor) {
    if (raiz == NULL) return novoNo(valor);
    if (valor < raiz->dado)      raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->dado) raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

/* ---------------------------------------------------------------------------
 * Altura de um no: maior caminho (em arestas) ate uma folha descendente.
 *   - Para ponteiro nulo retorna -1 (convencao - assim folhas tem altura 0).
 *   - Folha tem altura 0.
 * --------------------------------------------------------------------------- */
int alturaNo(No *no) {
    int hE, hD;
    if (no == NULL) return -1;
    hE = alturaNo(no->esq);
    hD = alturaNo(no->dir);
    return 1 + (hE > hD ? hE : hD);
}

/* ---------------------------------------------------------------------------
 * Profundidade de um no a partir da raiz.
 *   Retorna a distancia em arestas entre a raiz e o no com 'valor'.
 *   Se o valor nao existir, retorna -1.
 *   Como a ABB e ordenada, descemos sempre por um unico lado.
 * --------------------------------------------------------------------------- */
int profundidadeNo(No *raiz, int valor, int prof) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return prof;
    if (valor < raiz->dado)
        return profundidadeNo(raiz->esq, valor, prof + 1);
    else
        return profundidadeNo(raiz->dir, valor, prof + 1);
}

/* ---------------------------------------------------------------------------
 * Grau do no: numero de filhos diretos (0, 1 ou 2 em arvore binaria).
 * --------------------------------------------------------------------------- */
int grauNo(No *no) {
    int g = 0;
    if (no == NULL) return 0;
    if (no->esq != NULL) g++;
    if (no->dir != NULL) g++;
    return g;
}

/* Libera toda a arvore em pos-ordem (filhos antes do pai). */
void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

/* ===========================================================================
 * main de teste minimo da Parte A: insere os valores pedidos e verifica que
 * as 4 funcoes funcionam para um par de nos.
 * =========================================================================== */
int main(void) {
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65};
    int n = sizeof(valores) / sizeof(valores[0]);
    int i;
    No *raiz = NULL;

    for (i = 0; i < n; i++)
        raiz = inserir(raiz, valores[i]);

    printf("ABB construida com %d valores.\n\n", n);

    printf("alturaNo(raiz=50)         = %d   (esperado: 3)\n", alturaNo(raiz));
    printf("alturaNo(no  =30)         = %d   (esperado: 2)\n", alturaNo(raiz->esq));
    printf("profundidadeNo(20)        = %d   (esperado: 2)\n",
           profundidadeNo(raiz, 20, 0));
    printf("profundidadeNo(999) inex. = %d   (esperado: -1)\n",
           profundidadeNo(raiz, 999, 0));
    printf("grauNo(40)                = %d   (esperado: 1)\n", grauNo(raiz->esq->dir));
    printf("grauNo(10)  folha         = %d   (esperado: 0)\n",
           grauNo(raiz->esq->esq->esq));

    liberarArvore(raiz);
    return 0;
}
