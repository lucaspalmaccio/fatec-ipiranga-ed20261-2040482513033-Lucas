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
/* Estrutura do No                                                            */
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
/* inserir - Insercao recursiva em arvore binaria de busca (BST)              */
/*   Constroi a arvore dinamicamente a partir dos valores informados.         */
/*   Obs.: se os valores forem inseridos em ordem decrescente (ex: 20,10,5,2) */
/*   resulta na "escada linear" do enunciado.                                 */
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
/* calcularAltura - Recursiva                                                 */
/*   Imprime cada passo do calculo (em ordem bottom-up, conforme a            */
/*   recursao retorna).                                                       */
/*                                                                            */
/*   Caso base: no NULL retorna -1                                            */
/*   Passo:     1 + max(altura(esq), altura(dir))                             */
/*============================================================================*/
int calcularAltura(struct No* n) {
    /* Caso base: subarvore vazia tem altura -1 */
    if (n == NULL) return -1;

    /* Pergunta a altura para os filhos (recursao) */
    int h_filho_esq = calcularAltura(n->esq);
    int h_filho_dir = calcularAltura(n->dir);

    /* Calcula a propria altura */
    int h = 1 + ((h_filho_esq > h_filho_dir) ? h_filho_esq : h_filho_dir);

    /* PRINT do passo - mostra na tela como o no resolveu seu calculo */
    printf("  No %3d  ->  1 + max(%3d, %3d) = %d\n",
           n->valor, h_filho_esq, h_filho_dir, h);

    return h;
}

/*============================================================================*/
/* obterFB - Fator de Balanceamento                                           */
/*   FB = Altura_Esq - Altura_Dir                                             */
/*============================================================================*/
int obterFB(struct No* n) {
    if (n == NULL) return 0;
    int he = calcularAltura(n->esq);
    int hd = calcularAltura(n->dir);
    return he - hd;
}

/*============================================================================*/
/* desenharArvore - Desenho recursivo da arvore em formato visual             */
/*============================================================================*/
void desenharArvore(struct No* raiz, const char* prefixo,
                    int eh_ultimo, int eh_raiz) {
    if (raiz == NULL) return;
    if (eh_raiz)
        printf("  %d\n", raiz->valor);
    else
        printf("  %s%s%d\n", prefixo,
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
/* analisarFBPorNo - Recursiva: imprime FB de cada no com diagnostico         */
/*============================================================================*/
void analisarFBPorNo(struct No* n) {
    if (n == NULL) return;
    int fb = calcularAltura(n->esq) - calcularAltura(n->dir);
    printf("  FB(%3d) = %3d  %s\n",
           n->valor, fb,
           (fb > 1 || fb < -1) ? "[DESBALANCEADO]" : "[balanceado]");
    analisarFBPorNo(n->esq);
    analisarFBPorNo(n->dir);
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
    printf("==============================================================\n");
    printf("  Atividade N2-2 - Altura e Fator de Balanceamento (DINAMICO)\n");
    printf("  Estrutura de Dados - FATEC Ipiranga\n");
    printf("==============================================================\n\n");

    /*------------------------------------------------------------------*/
    /* 1) Leitura dinamica dos valores                                  */
    /*------------------------------------------------------------------*/
    int n;
    printf("Quantos valores deseja inserir na arvore? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Entrada invalida.\n");
        return 1;
    }

    struct No *raiz = NULL;
    printf("Digite os %d valores (separados por espaco ou enter):\n", n);
    for (int i = 0; i < n; i++) {
        int v;
        if (scanf("%d", &v) != 1) {
            printf("Erro ao ler o valor %d.\n", i + 1);
            liberarArvore(raiz);
            return 1;
        }
        raiz = inserir(raiz, v);
    }

    /*------------------------------------------------------------------*/
    /* 2) Visualizacao da arvore construida                             */
    /*------------------------------------------------------------------*/
    printf("\n--------------------------------------------------------------\n");
    printf("  Arvore construida (BST):\n");
    printf("--------------------------------------------------------------\n");
    desenharArvore(raiz, "", 1, 1);

    /*------------------------------------------------------------------*/
    /* 3) Calculo recursivo da altura (passo a passo, bottom-up)        */
    /*------------------------------------------------------------------*/
    printf("\n--------------------------------------------------------------\n");
    printf("  Calculo recursivo da Altura (bottom-up)\n");
    printf("  Formato:  No X  ->  1 + max(h_esq, h_dir) = h\n");
    printf("--------------------------------------------------------------\n");
    int h_raiz = calcularAltura(raiz);
    printf("\n  >> Altura final da raiz = %d\n", h_raiz);

    /*------------------------------------------------------------------*/
    /* 4) FB de cada no                                                 */
    /*------------------------------------------------------------------*/
    printf("\n--------------------------------------------------------------\n");
    printf("  Fator de Balanceamento por no (FB = h_esq - h_dir)\n");
    printf("--------------------------------------------------------------\n");
    /* Cabecalho silencioso: a chamada de calcularAltura dentro do FB    */
    /* tambem imprime, entao avisamos o leitor.                          */
    printf("  (cada FB recalcula as alturas - prints abaixo, depois o FB)\n\n");
    analisarFBPorNo(raiz);

    /*------------------------------------------------------------------*/
    /* 5) Diagnostico geral                                             */
    /*------------------------------------------------------------------*/
    int fb_raiz = obterFB(raiz);
    printf("\n==============================================================\n");
    printf("  FB da raiz (%d) = %d   %s\n",
           raiz->valor, fb_raiz,
           (fb_raiz > 1 || fb_raiz < -1)
             ? "-> DESBALANCEADA (precisa rotacao)"
             : "-> BALANCEADA");
    printf("==============================================================\n");

    /*------------------------------------------------------------------*/
    /* 6) Libera memoria                                                */
    /*------------------------------------------------------------------*/
    liberarArvore(raiz);
    return 0;
}
