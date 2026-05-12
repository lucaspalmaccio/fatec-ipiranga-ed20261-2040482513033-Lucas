/*----------------------------------------------------------------------------*/
/* FATEC Ipiranga - Disciplina: Estrutura de Dados                            */
/* Prof. Verissimo                                                               */
/*                                                                            */
/* Atividade N2-2: Calculando Fator de Balanceamento (AVL)                    */
/* Data de Entrega: 12/05/2026                                                */
/* Aluno: Lucas Bastos Palmaccio
/* RA: 2040482513033                                                                            */                                          */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*============================================================================*/
/* Estrutura do No (modelo dado na especificacao)                             */
/*============================================================================*/
struct No {
    int valor;
    int altura;
    struct No *esq;
    struct No *dir;
};

/*============================================================================*/
/* criarNo - aloca um no na heap com filhos NULL                              */
/*============================================================================*/
struct No* criarNo(int valor) {
    struct No *novo = (struct No*) malloc(sizeof(struct No));
    if (novo == NULL) {
        printf("Erro: falha na alocacao de memoria.\n");
        exit(1);
    }
    novo->valor  = valor;
    novo->altura = 0;
    novo->esq    = NULL;
    novo->dir    = NULL;
    return novo;
}

/*============================================================================*/
/* calcularAltura                                                             */
/*   Aplica recursivamente: 1 + max(altura(esq), altura(dir))                 */
/*   Caso base: no NULL retorna -1                                            */
/*                                                                            */
/*   Folha: 1 + max(-1, -1) = 0                                               */
/*============================================================================*/
int calcularAltura(struct No* n) {
    /* Caso base: subarvore vazia tem altura -1 */
    if (n == NULL) return -1;

    /* Passo recursivo: o no "pergunta" a altura para seus filhos */
    int h_filho_esq = calcularAltura(n->esq);
    int h_filho_dir = calcularAltura(n->dir);

    /* Altura do no = 1 + maior das alturas dos filhos */
    return 1 + ((h_filho_esq > h_filho_dir) ? h_filho_esq : h_filho_dir);
}

/*============================================================================*/
/* obterFB - Fator de Balanceamento                                           */
/*   FB = Altura_Esquerda - Altura_Direita                                    */
/*   |FB| <= 1  -> arvore balanceada naquele no                               */
/*   |FB|  > 1  -> arvore desbalanceada naquele no                            */
/*============================================================================*/
int obterFB(struct No* n) {
    if (n == NULL) return 0;
    return calcularAltura(n->esq) - calcularAltura(n->dir);
}

/*============================================================================*/
/* MAIN                                                                       */
/*============================================================================*/
int main(void) {
    /*------------------------------------------------------------------*/
    /* 1) Montagem MANUAL da estrutura 20 -> 10 -> 5 -> 2 -> NULL       */
    /*------------------------------------------------------------------*/
    struct No *no20 = criarNo(20);
    struct No *no10 = criarNo(10);
    struct No *no5  = criarNo(5);
    struct No *no2  = criarNo(2);

    /* Conectando: cada no fica a esquerda do anterior (escada linear) */
    no20->esq = no10;
    no10->esq = no5;
    no5->esq  = no2;
    /* esq dos demais ja eh NULL; todos os dir's tambem ja sao NULL    */

    /*------------------------------------------------------------------*/
    /* 2) Cabecalho                                                     */
    /*------------------------------------------------------------------*/
    printf("==============================================================\n");
    printf("  Atividade N2-2 - Calculo de Altura e Fator de Balanceamento\n");
    printf("  Estrutura de Dados - FATEC Ipiranga\n");
    printf("==============================================================\n\n");

    printf("Estrutura montada manualmente:\n");
    printf("   (20) -> (10) -> (5) -> (2) -> NULL\n");
    printf("   (escada linear a esquerda)\n\n");

    /*------------------------------------------------------------------*/
    /* 3) Calculo recursivo das alturas (bottom-up)                     */
    /*------------------------------------------------------------------*/
    printf("--------------------------------------------------------------\n");
    printf("  Alturas calculadas recursivamente (bottom-up)\n");
    printf("--------------------------------------------------------------\n");

    int h2  = calcularAltura(no2);
    int h5  = calcularAltura(no5);
    int h10 = calcularAltura(no10);
    int h20 = calcularAltura(no20);

    printf("  Passo A | No 2  (folha) : 1 + max(-1, -1) = %d\n", h2);
    printf("  Passo B | No 5         : 1 + max( %d, -1) = %d\n", h2, h5);
    printf("  Passo C | No 10        : 1 + max( %d, -1) = %d\n", h5, h10);
    printf("  Passo D | No 20 (raiz) : 1 + max( %d, -1) = %d\n\n", h10, h20);

    /*------------------------------------------------------------------*/
    /* 4) Fator de Balanceamento da raiz                                */
    /*------------------------------------------------------------------*/
    int fb_raiz = obterFB(no20);

    printf("--------------------------------------------------------------\n");
    printf("  Fator de Balanceamento (FB = Altura_Esq - Altura_Dir)\n");
    printf("--------------------------------------------------------------\n");
    printf("  FB da raiz (20) = %d - (-1) = %d\n\n", h10, fb_raiz);

    /*------------------------------------------------------------------*/
    /* 5) Diagnostico                                                   */
    /*------------------------------------------------------------------*/
    printf("  Diagnostico: ");
    if (fb_raiz > 1 || fb_raiz < -1) {
        printf("DESBALANCEADA (|FB| > 1)\n");
        printf("  -> Esta arvore necessita rotacoes para virar uma AVL.\n");
    } else {
        printf("BALANCEADA (|FB| <= 1)\n");
    }
    printf("\n");

    /*------------------------------------------------------------------*/
    /* 6) FB de cada no (analise extra)                                 */
    /*------------------------------------------------------------------*/
    printf("--------------------------------------------------------------\n");
    printf("  FB de cada no individualmente\n");
    printf("--------------------------------------------------------------\n");
    printf("  FB(2)  = %d\n", obterFB(no2));
    printf("  FB(5)  = %d\n", obterFB(no5));
    printf("  FB(10) = %d\n", obterFB(no10));
    printf("  FB(20) = %d\n", obterFB(no20));
    printf("==============================================================\n");

    /*------------------------------------------------------------------*/
    /* 7) Liberacao da memoria (folhas primeiro)                        */
    /*------------------------------------------------------------------*/
    free(no2);
    free(no5);
    free(no10);
    free(no20);

    return 0;
}
