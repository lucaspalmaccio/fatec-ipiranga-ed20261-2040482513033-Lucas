/*
 * ============================================================================
 * Fatec Ipiranga - Disciplina: Estrutura de Dados - Prof. Verissimo
 * Atividade N2-1: Explorando Arvore Binaria
 * Aluno: Lucas Bastos Palmaccio
 * RA: 2040482513033
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Criacao e insercao (recursiva) na BST                                      
No* criarNo(int valor) {
    No *novo = (No*) malloc(sizeof(No));
    novo->valor    = valor;
    novo->esquerda = NULL;
    novo->direita  = NULL;
    return novo;
}

No* inserir(No *raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->valor)
        raiz->esquerda = inserir(raiz->esquerda, valor);
    else if (valor > raiz->valor)
        raiz->direita = inserir(raiz->direita, valor);
    return raiz;
}

// Busca recursiva por um valor
No* buscar(No *raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) return raiz;
    if (valor < raiz->valor) return buscar(raiz->esquerda, valor);
    return buscar(raiz->direita, valor);
}

// 1) RAIZ                                                                    
void imprimirRaiz(No *raiz) {
    printf("Raiz:\n%d\n\n", raiz->valor);
}

// 2) NOS INTERNOS (pre-ordem, recursivo)                                     
void coletarInternos(No *raiz, int *vet, int *n) {
    if (raiz == NULL) return;
    if (raiz->esquerda != NULL || raiz->direita != NULL)
        vet[(*n)++] = raiz->valor;
    coletarInternos(raiz->esquerda, vet, n);
    coletarInternos(raiz->direita,  vet, n);
}

void imprimirInternos(No *raiz) {
    int vet[100], n = 0;
    coletarInternos(raiz, vet, &n);
    printf("Nos Internos:\n");
    for (int i = 0; i < n; i++) {
        printf("%d", vet[i]);
        if (i < n - 1) printf(", ");
    }
    printf("\n\n");
}

// 3) NOS EXTERNOS (FOLHAS) - grau 0                                          
void coletarFolhas(No *raiz, int *vet, int *n) {
    if (raiz == NULL) return;
    if (raiz->esquerda == NULL && raiz->direita == NULL)
        vet[(*n)++] = raiz->valor;
    coletarFolhas(raiz->esquerda, vet, n);
    coletarFolhas(raiz->direita,  vet, n);
}

void imprimirFolhas(No *raiz) {
    int vet[100], n = 0;
    coletarFolhas(raiz, vet, &n);
    printf("Nos Externos (Folhas):\n");
    for (int i = 0; i < n; i++) {
        printf("%d", vet[i]);
        if (i < n - 1) printf(", ");
    }
    printf("\n\n");
}


// 4) NIVEIS  (Nivel 1 = raiz)                                                
void coletarNivel(No *raiz, int nivelAtual, int nivelDesejado,
                  int *vet, int *n) {
    if (raiz == NULL) return;
    if (nivelAtual == nivelDesejado) {
        vet[(*n)++] = raiz->valor;
        return;
    }
    coletarNivel(raiz->esquerda, nivelAtual + 1, nivelDesejado, vet, n);
    coletarNivel(raiz->direita,  nivelAtual + 1, nivelDesejado, vet, n);
}

void imprimirNiveis(No *raiz, int totalNiveis) {
    printf("Niveis:\n");
    for (int i = 1; i <= totalNiveis; i++) {
        int vet[100], n = 0;
        coletarNivel(raiz, 1, i, vet, &n);
        printf("Nivel %d: ", i);
        if (n == 0) {
            printf("(vazio)");
        } else {
            for (int k = 0; k < n; k++) {
                printf("%d", vet[k]);
                if (k < n - 1) printf(", ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// 5) GRAU de cada no                                                         
int grau(No *no) {
    if (no == NULL) return -1;
    int g = 0;
    if (no->esquerda != NULL) g++;
    if (no->direita  != NULL) g++;
    return g;
}

void imprimirGrausRec(No *raiz) {
    if (raiz == NULL) return;
    printf("  %d -> grau %d\n", raiz->valor, grau(raiz));
    imprimirGrausRec(raiz->esquerda);
    imprimirGrausRec(raiz->direita);
}

void imprimirGraus(No *raiz) {
    printf("Grau dos Nos:\n");
    imprimirGrausRec(raiz);
    printf("\n");
}

// 6) ANCESTRAIS (recursivo - sobe na pilha de chamadas)                      
int coletarAncestrais(No *raiz, int valor, int *vet, int *n) {
    if (raiz == NULL) return 0;
    if (raiz->valor == valor) return 1;
    if (coletarAncestrais(raiz->esquerda, valor, vet, n) ||
        coletarAncestrais(raiz->direita,  valor, vet, n)) {
        vet[(*n)++] = raiz->valor;
        return 1;
    }
    return 0;
}

void imprimirAncestrais(No *raiz, int valor) {
    int vet[100], n = 0;
    coletarAncestrais(raiz, valor, vet, &n);
    printf("Ancestrais: ");
    if (n == 0) {
        printf("(nenhum - eh a raiz)");
    } else {
        for (int i = 0; i < n; i++) {
            printf("%d", vet[i]);
            if (i < n - 1) printf(", ");
        }
    }
    printf("\n");
}

// 7) DESCENDENTES (todos os nos abaixo)                                      
void coletarDescendentes(No *no, int *vet, int *n) {
    if (no == NULL) return;
    vet[(*n)++] = no->valor;
    coletarDescendentes(no->esquerda, vet, n);
    coletarDescendentes(no->direita,  vet, n);
}

void imprimirDescendentes(No *no) {
    int vet[100], n = 0;
    // O proprio no nao conta como descendente -> comeca pelos filhos 
    coletarDescendentes(no->esquerda, vet, &n);
    coletarDescendentes(no->direita,  vet, &n);
    printf("Descendentes: ");
    if (n == 0) {
        printf("(nenhum - eh folha)");
    } else {
        for (int i = 0; i < n; i++) {
            printf("%d", vet[i]);
            if (i < n - 1) printf(", ");
        }
    }
    printf("\n");
}

// 8) ALTURA (distancia do no ate a folha mais profunda abaixo)               
int altura(No *no) {
    if (no == NULL) return -1;     /* no nulo: -1 */
    int hE = altura(no->esquerda);
    int hD = altura(no->direita);
    return 1 + (hE > hD ? hE : hD);
}

// 9) PROFUNDIDADE (distancia do no ate a raiz)                               
int profundidade(No *raiz, int valor, int nivel) {
    if (raiz == NULL) return -1;
    if (raiz->valor == valor) return nivel;
    int e = profundidade(raiz->esquerda, valor, nivel + 1);
    if (e != -1) return e;
    return profundidade(raiz->direita, valor, nivel + 1);
}

// 10) SUB-ARVORE  - desenho recursivo em formato visual                      
void desenharSubarvore(No *raiz, const char *prefixo,
                       int ehUltimo, int eRaiz) {
    if (raiz == NULL) return;

    if (eRaiz) {
        printf("%d\n", raiz->valor);
    } else {
        printf("%s%s%d\n", prefixo, ehUltimo ? "`-- " : "|-- ", raiz->valor);
    }

    char novoPref[512];
    if (eRaiz)
        snprintf(novoPref, sizeof(novoPref), "%s", "");
    else
        snprintf(novoPref, sizeof(novoPref), "%s%s",
                 prefixo, ehUltimo ? "    " : "|   ");

    int temE = (raiz->esquerda != NULL);
    int temD = (raiz->direita  != NULL);

    if (temE) desenharSubarvore(raiz->esquerda, novoPref, !temD, 0);
    if (temD) desenharSubarvore(raiz->direita,  novoPref, 1,    0);
}

void imprimirSubarvore(No *raiz, int valor) {
    No *no = buscar(raiz, valor);
    printf("Subarvore (raiz %d):\n", valor);
    if (no == NULL) {
        printf("  (no nao encontrado)\n");
        return;
    }
    desenharSubarvore(no, "", 1, 1);
    printf("\n");
}
