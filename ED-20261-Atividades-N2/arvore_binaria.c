/*
 * ============================================================================
 *  Fatec Ipiranga - Estrutura de Dados - Prof. Verissimo
 *  Atividade N2-1: Explorando Arvore Binaria
 *  Aluno: Lucas Bastos Palmaccio
 *  RA: 2040482513033
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "arvore_binaria.h"
                          
/* Busca recursiva por um valor */
static No* buscar(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) return raiz;
    if (valor < raiz->valor) return buscar(raiz->esq, valor);
    return buscar(raiz->dir, valor);
}

/* Grau de um no (0, 1 ou 2) */
static int grau(No* no) {
    if (no == NULL) return 0;
    int g = 0;
    if (no->esq != NULL) g++;
    if (no->dir != NULL) g++;
    return g;
}

/* Imprime os nos de UM nivel especifico (em ordem da esquerda
   para a direita) - ajudante recursivo da imprimir_niveis. */
static void imprimir_no_do_nivel(No* raiz, int nivel_corrente,
                                 int nivel_alvo) {
    if (raiz == NULL) return;
    if (nivel_corrente == nivel_alvo) {
        printf("%d ", raiz->valor);
        return;
    }
    imprimir_no_do_nivel(raiz->esq, nivel_corrente + 1, nivel_alvo);
    imprimir_no_do_nivel(raiz->dir, nivel_corrente + 1, nivel_alvo);
}

/* Imprime grau de cada no (pre-ordem recursiva) */
static void imprimir_graus(No* raiz) {
    if (raiz == NULL) return;
    printf("  %d -> grau %d\n", raiz->valor, grau(raiz));
    imprimir_graus(raiz->esq);
    imprimir_graus(raiz->dir);
}

/* Desenho recursivo de sub-arvore com prefixos visuais */
static void desenhar_subarvore(No* raiz, const char* prefixo,
                               int eh_ultimo, int eh_raiz) {
    if (raiz == NULL) return;

    if (eh_raiz)
        printf("%d\n", raiz->valor);
    else
        printf("%s%s%d\n", prefixo,
               eh_ultimo ? "`-- " : "|-- ", raiz->valor);

    char novo_pref[512];
    if (eh_raiz)
        novo_pref[0] = '\0';
    else
        snprintf(novo_pref, sizeof(novo_pref), "%s%s",
                 prefixo, eh_ultimo ? "    " : "|   ");

    int tem_e = (raiz->esq != NULL);
    int tem_d = (raiz->dir != NULL);
    if (tem_e) desenhar_subarvore(raiz->esq, novo_pref, !tem_d, 0);
    if (tem_d) desenhar_subarvore(raiz->dir, novo_pref, 1, 0);
}

/* ============================================================ */
/*  Construcao da arvore (extras)                               */
/* ============================================================ */
No* criar_no(int valor) {
    No* novo = (No*) malloc(sizeof(No));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

No* inserir(No* raiz, int valor) {
    if (raiz == NULL) return criar_no(valor);
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

/* ============================================================ */
/*  Nos internos: nos com pelo menos 1 filho                    */
/* ============================================================ */
void imprimir_nos_internos(No* raiz) {
    if (raiz == NULL) return;
    if (raiz->esq != NULL || raiz->dir != NULL)
        printf("%d ", raiz->valor);
    imprimir_nos_internos(raiz->esq);
    imprimir_nos_internos(raiz->dir);
}

/* ============================================================ */
/*  Folhas: nos de grau 0                                       */
/* ============================================================ */
void imprimir_folhas(No* raiz) {
    if (raiz == NULL) return;
    if (raiz->esq == NULL && raiz->dir == NULL)
        printf("%d ", raiz->valor);
    imprimir_folhas(raiz->esq);
    imprimir_folhas(raiz->dir);
}

/* ============================================================ */
/*  Niveis: imprime cada nivel a partir de nivel_atual          */
/* ============================================================ */
void imprimir_niveis(No* raiz, int nivel_atual) {
    if (raiz == NULL) return;
    int total_niveis = calcular_altura(raiz) + 1;
    for (int i = nivel_atual; i <= total_niveis; i++) {
        printf("  Nivel %d: ", i);
        imprimir_no_do_nivel(raiz, 1, i);
        printf("\n");
    }
}

/* ============================================================ */
/*  Altura: distancia ate a folha mais profunda abaixo do no    */
/*  (folha = 0, no nulo = -1)                                   */
/* ============================================================ */
int calcular_altura(No* no) {
    if (no == NULL) return -1;
    int hE = calcular_altura(no->esq);
    int hD = calcular_altura(no->dir);
    return 1 + (hE > hD ? hE : hD);
}

/* ============================================================ */
/*  Profundidade: distancia do no ate a raiz                    */
/*  (raiz = 0, retorna -1 se nao encontrar)                     */
/* ============================================================ */
int calcular_profundidade(No* raiz, int valor, int profundidade_atual) {
    if (raiz == NULL) return -1;
    if (raiz->valor == valor) return profundidade_atual;
    int p = calcular_profundidade(raiz->esq, valor,
                                  profundidade_atual + 1);
    if (p != -1) return p;
    return calcular_profundidade(raiz->dir, valor,
                                 profundidade_atual + 1);
}

/* ============================================================ */
/*  Ancestrais: imprime do mais proximo ate a raiz              */
/* ============================================================ */
/* Helper recursivo: ao subir na pilha, imprime os pais         */
static int ancestrais_aux(No* raiz, int valor) {
    if (raiz == NULL) return 0;
    if (raiz->valor == valor) return 1;
    if (ancestrais_aux(raiz->esq, valor) ||
        ancestrais_aux(raiz->dir, valor)) {
        printf("%d ", raiz->valor);
        return 1;
    }
    return 0;
}

void imprimir_ancestrais(No* raiz, int valor) {
    printf("Ancestrais de %d: ", valor);
    if (!ancestrais_aux(raiz, valor)) printf("(nenhum)");
    printf("\n");
}

/* ============================================================ */
/*  Descendentes: todos os nos abaixo (sem o proprio no)        */
/* ============================================================ */
/* Helper: percorre a sub-arvore em pre-ordem */
static void descendentes_aux(No* no) {
    if (no == NULL) return;
    printf("%d ", no->valor);
    descendentes_aux(no->esq);
    descendentes_aux(no->dir);
}

void imprimir_descendentes(No* no) {
    if (no == NULL) return;
    printf("Descendentes de %d: ", no->valor);
    if (no->esq == NULL && no->dir == NULL) {
        printf("(nenhum - eh folha)");
    } else {
        descendentes_aux(no->esq);
        descendentes_aux(no->dir);
    }
    printf("\n");
}

/* ============================================================ */
/*  FUNCAO PRINCIPAL                                            */
/* ============================================================ */
void analisar_arvore(No* raiz, int valorBusca) {
    if (raiz == NULL) {
        printf("Arvore vazia.\n");
        return;
    }

    printf("=========================================================\n");
    printf("   MAPA DA ARVORE BINARIA DE BUSCA\n");
    printf("   Atividade N2-1 - Estrutura de Dados - Fatec Ipiranga\n");
    printf("=========================================================\n\n");

    /* 1) Raiz */
    printf("Raiz: %d\n\n", raiz->valor);

    /* 2) Nos internos */
    printf("Nos Internos: ");
    imprimir_nos_internos(raiz);
    printf("\n\n");

    /* 3) Nos externos (folhas) */
    printf("Nos Externos (Folhas): ");
    imprimir_folhas(raiz);
    printf("\n\n");

    /* 4) Niveis */
    printf("Niveis:\n");
    imprimir_niveis(raiz, 1);
    printf("\n");

    /* 5) Grau dos nos */
    printf("Grau dos Nos:\n");
    imprimir_graus(raiz);
    printf("\n");

    /* 6) Analise focada do valorBusca */
    No* alvo = buscar(raiz, valorBusca);
    printf("---------------------------------------------------------\n");
    printf("  Analise focada do No %d\n", valorBusca);
    printf("---------------------------------------------------------\n");
    if (alvo == NULL) {
        printf("Valor %d nao encontrado na arvore.\n\n", valorBusca);
        return;
    }
    imprimir_ancestrais(raiz, valorBusca);
    imprimir_descendentes(alvo);
    printf("Altura do no %d:        %d\n",
           valorBusca, calcular_altura(alvo));
    printf("Profundidade do no %d:  %d\n\n",
           valorBusca, calcular_profundidade(raiz, valorBusca, 0));

    /* 7) Sub-arvore a partir do valorBusca */
    printf("Subarvore (raiz %d):\n", valorBusca);
    desenhar_subarvore(alvo, "", 1, 1);
}
