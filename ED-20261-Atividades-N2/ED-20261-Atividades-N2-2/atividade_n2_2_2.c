/*----------------------------------------------------------------------------*/
/* FATEC Ipiranga - Disciplina: Estrutura de Dados                            */
/* Prof. Verissimo                                                            */
/*                                                                            */
/* Atividade N2-2: Calculando Fator de Balanceamento (AVL)                    */
/* Data de Entrega: 12/05/2026                                                */
/* Aluno: Lucas Bastos Palmaccio                                              */
/* RA: 2040482513033                                                          */
/*----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*============================================================================*/
/*                                                                            */
/*   >>>>>>>>>>>>>>>>>>>>  CONFIGURACAO DA ARVORE  <<<<<<<<<<<<<<<<<<<<       */
/*                                                                            */
/*   Altere o array `VALORES` abaixo para testar a arvore com outros          */
/*   numeros. Recompile e execute - o passo-a-passo do calculo aparecera      */
/*   automaticamente no terminal.                                             */
/*                                                                            */
/*   Exemplos:                                                                */
/*     {20, 10, 5, 2}              -> escada linear a esquerda (desbalanc.)   */
/*     {50, 30, 70, 20, 40, 60, 80} -> arvore balanceada (FB = 0)             */
/*     {10, 20, 30, 40}             -> escada linear a direita                */
/*                                                                            */
/*============================================================================*/

int VALORES[] = {20, 10, 5, 2};

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
/* criarNo - aloca um no na heap                                              */
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
/* inserir - Insercao recursiva em BST                                        */
/*   Constroi a arvore a partir dos valores do array VALORES.                 */
/*============================================================================*/
struct No* inserir(struct No* raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

/*============================================================================*/
/* calcularAltura - Recursiva, com PRINT do passo de cada no                  */
/*                                                                            */
/*   Caso base: no NULL retorna -1                                            */
/*   Passo:     1 + max(altura(esq), altura(dir))                             */
/*                                                                            */
/*   Como a recursao retorna BOTTOM-UP (filhos antes do pai), o printf        */
/*   aparece na ordem natural: folhas primeiro, raiz por ultimo.              */
/*   Isto reproduz exatamente os Passos A, B, C, D do enunciado.              */
/*============================================================================*/
int calcularAltura(struct No* n) {
    /* Caso base: subarvore vazia tem altura -1 */
    if (n == NULL) return -1;

    /* O no "pergunta" a altura para seus filhos (chamada recursiva) */
    int h_filho_esq = calcularAltura(n->esq);
    int h_filho_dir = calcularAltura(n->dir);

    /* Calcula sua propria altura */
    int h = 1 + ((h_filho_esq > h_filho_dir) ? h_filho_esq : h_filho_dir);

    /* Imprime o calculo deste no */
    printf("   No %3d  ->  1 + max(%3d, %3d) = %d\n",
           n->valor, h_filho_esq, h_filho_dir, h);

    return h;
}

/*============================================================================*/
/* obterFB - Fator de Balanceamento                                           */
/*   FB = Altura_Esq - Altura_Dir                                             */
/*   Utiliza calcularAltura (conforme exigido na especificacao).              */
/*============================================================================*/
int obterFB(struct No* n) {
    if (n == NULL) return 0;
    return calcularAltura(n->esq) - calcularAltura(n->dir);
}

/*============================================================================*/
/* desenharArvore - Desenho recursivo em formato visual (apenas ilustrativo)  */
/*============================================================================*/
void desenharArvore(struct No* raiz, const char* prefixo,
                    int eh_ultimo, int eh_raiz) {
    if (raiz == NULL) return;
    if (eh_raiz)
        printf("   %d\n", raiz->valor);
    else
        printf("   %s%s%d\n", prefixo,
               eh_ultimo ? "`-- " : "|-- ", raiz->valor);

    char novo[512];
    if (eh_raiz)
        novo[0] = '\0';
    else
        snprintf(novo, sizeof(novo), "%s%s",
                 prefixo, eh_ultimo ? "    " : "|   ");

    int tem_e = (raiz->esq != NULL);
    int tem_d = (raiz->dir != NULL);
    if (tem_e) desenharArvore(raiz->esq, novo, !tem_d, 0);
    if (tem_d) desenharArvore(raiz->dir, novo, 1, 0);
}

/*============================================================================*/
/* liberarArvore - Libera memoria em pos-ordem                                */
/*============================================================================*/
void liberarArvore(struct No* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

/*============================================================================*/
/* MAIN                                                                       */
/*============================================================================*/
int main(void) {
    int qtd = sizeof(VALORES) / sizeof(VALORES[0]);

    printf("==============================================================\n");
    printf("  Atividade N2-2 - Altura e Fator de Balanceamento\n");
    printf("  Estrutura de Dados - FATEC Ipiranga\n");
    printf("==============================================================\n\n");

    /*------------------------------------------------------------------*/
    /* 1) Construcao da arvore a partir do array VALORES                */
    /*------------------------------------------------------------------*/
    printf("Valores inseridos (na ordem): ");
    for (int i = 0; i < qtd; i++) {
        printf("%d", VALORES[i]);
        if (i < qtd - 1) printf(", ");
    }
    printf("\n\n");

    struct No *raiz = NULL;
    for (int i = 0; i < qtd; i++)
        raiz = inserir(raiz, VALORES[i]);

    /*------------------------------------------------------------------*/
    /* 2) Visualizacao da arvore construida                             */
    /*------------------------------------------------------------------*/
    printf("--------------------------------------------------------------\n");
    printf(" Arvore construida (BST):\n");
    printf("--------------------------------------------------------------\n");
    desenharArvore(raiz, "", 1, 1);

    /*------------------------------------------------------------------*/
    /* 3) Calculo recursivo da Altura - passo a passo de cada no        */
    /*------------------------------------------------------------------*/
    printf("\n--------------------------------------------------------------\n");
    printf(" Calculo recursivo da Altura (bottom-up)\n");
    printf(" Formato:  No X  ->  1 + max(h_esq, h_dir) = h\n");
    printf("--------------------------------------------------------------\n");
    int h_raiz = calcularAltura(raiz);
    printf("\n   >> Altura final da raiz (%d) = %d\n", raiz->valor, h_raiz);

    /*------------------------------------------------------------------*/
    /* 4) Calculo do Fator de Balanceamento da raiz                     */
    /*------------------------------------------------------------------*/
    printf("\n--------------------------------------------------------------\n");
    printf(" Calculo do FB da raiz (FB = h_esq - h_dir)\n");
    printf("--------------------------------------------------------------\n");
    printf(" Recalculando alturas para obter o FB...\n");
    int fb_raiz = obterFB(raiz);
    int h_esq_raiz = (raiz->esq != NULL) ? calcularAltura(raiz->esq) : -1;
    int h_dir_raiz = (raiz->dir != NULL) ? calcularAltura(raiz->dir) : -1;
    printf("\n   >> FB(%d) = %d - (%d) = %d\n",
           raiz->valor, h_esq_raiz, h_dir_raiz, fb_raiz);

    /*------------------------------------------------------------------*/
    /* 5) Diagnostico                                                   */
    /*------------------------------------------------------------------*/
    printf("\n==============================================================\n");
    if (fb_raiz > 1 || fb_raiz < -1) {
        printf("  Diagnostico: DESBALANCEADA  (|FB| > 1)\n");
        printf("               Necessita rotacoes para virar uma AVL.\n");
    } else {
        printf("  Diagnostico: BALANCEADA  (|FB| <= 1)\n");
    }
    printf("==============================================================\n");

    /*------------------------------------------------------------------*/
    /* 6) Liberacao de memoria                                          */
    /*------------------------------------------------------------------*/
    liberarArvore(raiz);
    return 0;
}
