// RA: 2040482513033 - Nome do Aluno: Lucas Bastos Palmaccio
/* ===========================================================================
 * Exercicio 01 - Parte B : Aritmetica de ponteiros aplicada a um vetor.
 * Proibido usar o operador [] - somente *(p+i), p++ e p-- sao permitidos.
 * Compilar: gcc -Wall -Wextra -o prog Exercicio01-B.c
 * =========================================================================== */

#include <stdio.h>

int main(void) {
    int v[] = {10, 20, 30, 40, 50};
    int n = sizeof(v) / sizeof(v[0]);  /* tamanho calculado em tempo de compilacao */

    int *p;     /* ponteiro generico para percorrer o vetor                    */
    int soma;   /* acumulador da soma                                           */
    int *ini;   /* ponteiro para o inicio do vetor (usado na inversao)         */
    int *fim;   /* ponteiro para o final do vetor (usado na inversao)          */
    int tmp;    /* auxiliar usado APENAS na troca da inversao (nao e proibido) */

    /* ------------------------------------------------------------------------
     * (a) Imprime cada elemento e seu endereco.
     *     Lembrete: o nome 'v' decai em &v[0], entao v == &v[0].
     *     A expressao *(v + i) acessa o i-esimo elemento sem usar [].
     * ----------------------------------------------------------------------- */
    printf("=== (a) Elementos e enderecos ===\n");
    for (p = v; p < v + n; p++) {
        /* *p = valor apontado por p ; p = endereco em si (sem desreferenciar) */
        printf("Endereco %p -> valor %d\n", (void *)p, *p);
    }

    /* ------------------------------------------------------------------------
     * (b) Soma de todos os elementos usando aritmetica de ponteiros.
     * ----------------------------------------------------------------------- */
    soma = 0;
    for (p = v; p < v + n; p++) {
        soma += *p;     /* *p = desreferencia o ponteiro = pega o valor */
    }
    printf("\n=== (b) Soma dos elementos = %d ===\n", soma);

    /* ------------------------------------------------------------------------
     * (c) Inversao in-place do vetor usando DOIS ponteiros:
     *     'ini' inicia no comeco, 'fim' inicia no final - convergem ao centro.
     * ----------------------------------------------------------------------- */
    ini = v;            /* aponta para o primeiro elemento (equivale a &v[0]) */
    fim = v + n - 1;    /* aponta para o ultimo elemento (equivale a &v[n-1]) */

    while (ini < fim) {
        tmp  = *ini;    /* salva o valor apontado por ini                    */
        *ini = *fim;    /* sobrescreve o valor no inicio com o do fim         */
        *fim = tmp;     /* coloca o valor antigo do inicio no fim             */
        ini++;          /* aritmetica de ponteiros: avanca 1 * sizeof(int)    */
        fim--;          /* aritmetica de ponteiros: recua 1 * sizeof(int)     */
    }

    printf("\n=== (c) Vetor invertido ===\n");
    for (p = v; p < v + n; p++) {
        printf("%d ", *p);
    }
    printf("\n");

    return 0;
}
