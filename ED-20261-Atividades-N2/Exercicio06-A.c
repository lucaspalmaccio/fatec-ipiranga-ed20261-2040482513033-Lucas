// RA: 2040482513033 - Nome do Aluno: Lucas Bastos Palmaccio
/* ===========================================================================
 * Exercicio 06 - Parte A : Funcoes de parentesco em ABB.
 *   imprimirAncestral(raiz, valor)   - recursiva
 *   imprimirDescendentes(raiz, valor) - percurso em-ordem
 *   contarDescendentes(no)
 *
 * Compilar: gcc -Wall -Wextra -o prog Exercicio06-A.c
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

/* ---------------------------------------------------------------------------
 * Imprime ancestrais do no com 'valor' do PAI ate a RAIZ.
 * Estrategia recursiva:
 *   - desce pela ABB ate encontrar o valor;
 *   - na volta da pilha (apos a chamada recursiva), imprime o no atual.
 *     Como a recursao desempilha de baixo para cima, os ancestrais saem
 *     na ordem pai -> avo -> raiz (ordem crescente de proximidade ao no).
 * Retorna 1 se encontrou o valor na subarvore, 0 caso contrario.
 * --------------------------------------------------------------------------- */
static int imprimirAncestralAux(No *raiz, int valor) {
    int achou;
    if (raiz == NULL) return 0;
    if (raiz->dado == valor) return 1;          /* nao imprime o proprio no */

    if (valor < raiz->dado) achou = imprimirAncestralAux(raiz->esq, valor);
    else                    achou = imprimirAncestralAux(raiz->dir, valor);

    if (achou) printf("%d ", raiz->dado);       /* imprime na volta */
    return achou;
}

void imprimirAncestral(No *raiz, int valor) {
    if (buscar(raiz, valor) == NULL) {
        printf("(no %d nao existe na arvore)", valor);
        return;
    }
    if (!imprimirAncestralAux(raiz, valor))
        printf("(sem ancestrais - este e o no raiz)");
}

/* Auxiliar: percorre em-ordem imprimindo TODOS os nos da subarvore. */
static void emOrdem(No *raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esq);
    printf("%d ", raiz->dado);
    emOrdem(raiz->dir);
}

/* ---------------------------------------------------------------------------
 * Imprime todos os descendentes do no com 'valor' em percurso em-ordem,
 * exceto o proprio no.
 * --------------------------------------------------------------------------- */
void imprimirDescendentes(No *raiz, int valor) {
    No *no = buscar(raiz, valor);
    if (no == NULL) {
        printf("(no %d nao existe na arvore)", valor);
        return;
    }
    if (no->esq == NULL && no->dir == NULL) {
        printf("(folha - sem descendentes)");
        return;
    }
    emOrdem(no->esq);
    emOrdem(no->dir);
}

/* ---------------------------------------------------------------------------
 * contarNos - auxiliar que retorna o numero total de nos da subarvore
 * (incluindo o proprio 'no'). Soma 1 + esquerda + direita.
 * --------------------------------------------------------------------------- */
static int contarNos(No *no) {
    if (no == NULL) return 0;
    return 1 + contarNos(no->esq) + contarNos(no->dir);
}

/* ---------------------------------------------------------------------------
 * Conta quantos descendentes o no possui (toda a subarvore exceto o proprio).
 *   descendentes = nos da subarvore esquerda + nos da subarvore direita.
 * --------------------------------------------------------------------------- */
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

/* ===========================================================================
 * main de teste da Parte A.
 * =========================================================================== */
int main(void) {
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65};
    int n = sizeof(valores) / sizeof(valores[0]);
    int i;
    No *raiz = NULL;

    for (i = 0; i < n; i++)
        raiz = inserir(raiz, valores[i]);

    printf("Ancestrais de 10  : ");
    imprimirAncestral(raiz, 10);   printf("\n");

    printf("Ancestrais de 45  : ");
    imprimirAncestral(raiz, 45);   printf("\n");

    printf("Ancestrais de 50  : ");
    imprimirAncestral(raiz, 50);   printf("\n");

    printf("\nDescendentes de 30 (em-ordem): ");
    imprimirDescendentes(raiz, 30); printf("\n");

    printf("Descendentes de 70 (em-ordem): ");
    imprimirDescendentes(raiz, 70); printf("\n");

    printf("Descendentes de 10 (folha)   : ");
    imprimirDescendentes(raiz, 10); printf("\n");

    printf("\nQtd descendentes do no 30 : %d  (esperado: 5)\n",
           contarDescendentes(buscar(raiz, 30)));
    printf("Qtd descendentes do no 50 : %d  (esperado: 10)\n",
           contarDescendentes(buscar(raiz, 50)));
    printf("Qtd descendentes do no 10 : %d  (esperado: 0)\n",
           contarDescendentes(buscar(raiz, 10)));

    liberarArvore(raiz);
    return 0;
}
