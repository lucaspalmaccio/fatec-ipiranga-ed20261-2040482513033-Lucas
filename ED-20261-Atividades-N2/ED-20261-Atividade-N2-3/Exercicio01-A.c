// RA: 2040482513033 - Nome do Aluno: Lucas Bastos Palmaccio
/* ===========================================================================
 * Exercicio 01 - Parte A : Troca de valores com ponteiros (sem variavel temp).
 * Tecnica utilizada: aritmetica de inteiros (soma e subtracao).
 * Compilar: gcc -Wall -Wextra -o prog Exercicio01-A.c
 * =========================================================================== */

#include <stdio.h>

void trocar(int *a, int *b) {
    *a = *a + *b;   /* *a recebe a soma dos dois valores (desreferencia a e b) */
    *b = *a - *b;   /* *b recebe (soma - b_original) = a_original             */
    *a = *a - *b;   /* *a recebe (soma - novo_b) = b_original                  */
}

int main(void) {
    int x = 25;
    int y = 70;

    printf("=== Antes da troca ===\n");
    printf("x = %d   endereco de x = %p\n", x, (void *)&x); /* &x = endereco de x */
    printf("y = %d   endereco de y = %p\n", y, (void *)&y); /* &y = endereco de y */

    /* Passa os enderecos para a funcao trabalhar com os valores originais.
     * Como passamos &x e &y, a funcao consegue alterar x e y do main. */
    trocar(&x, &y);

    printf("\n=== Depois da troca ===\n");
    printf("x = %d   endereco de x = %p\n", x, (void *)&x);
    printf("y = %d   endereco de y = %p\n", y, (void *)&y);

    printf("\nObservacao: os enderecos NAO mudaram - apenas o conteudo das\n");
    printf("posicoes de memoria foi reorganizado pela funcao trocar.\n");
    return 0;
}
