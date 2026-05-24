// RA: 2040482513033 - Nome do Aluno: Lucas Bastos Palmaccio
/* ===========================================================================
 * Exercicio 03 - Parte A : Torres de Hanoi recursivas com contador global.
 *
 * O programa:
 *   1) Imprime cada movimento para n = 1, 3 e 4 (testes pedidos).
 *   2) Conta silenciosamente os movimentos para n = 1..6 e gera a tabela
 *      comparativa contado x 2^n - 1.
 *
 * Compilar: gcc -Wall -Wextra -o prog Exercicio03-A.c
 * =========================================================================== */

#include <stdio.h>

/* contador global - incrementado a cada movimento */
static long contador = 0;
/* flag para silenciar a impressao quando estamos apenas contando */
static int silencioso = 0;

/* ---------------------------------------------------------------------------
 * Funcao recursiva canonica das Torres de Hanoi.
 *   Caso base    : n == 1  -> mover 1 disco direto de origem para destino.
 *   Caso recursivo: mover n-1 para auxiliar, mover o maior, mover n-1 de volta.
 * --------------------------------------------------------------------------- */
void hanoi(int n, char origem, char destino, char auxiliar) {
    if (n == 1) {                                       /* CASO BASE */
        contador++;
        if (!silencioso)
            printf("Mover disco 1 de %c -> %c\n", origem, destino);
        return;
    }
    hanoi(n - 1, origem, auxiliar, destino);            /* recursao 1 */
    contador++;
    if (!silencioso)
        printf("Mover disco %d de %c -> %c\n", n, origem, destino);
    hanoi(n - 1, auxiliar, destino, origem);            /* recursao 2 */
}

/* Calcula 2^n - 1 sem usar math.h. */
static long doisElevadoMenos1(int n) {
    long r = 1;
    int i;
    for (i = 0; i < n; i++) r *= 2;
    return r - 1;
}

int main(void) {
    int n;

    /* ----- Testes obrigatorios com impressao -------------------------------- */
    silencioso = 0;

    printf("=== n = 1 ===\n");
    contador = 0;
    hanoi(1, 'A', 'C', 'B');
    printf("Total: %ld movimento(s)\n\n", contador);

    printf("=== n = 3 ===\n");
    contador = 0;
    hanoi(3, 'A', 'C', 'B');
    printf("Total: %ld movimentos\n\n", contador);

    printf("=== n = 4 ===\n");
    contador = 0;
    hanoi(4, 'A', 'C', 'B');
    printf("Total: %ld movimentos\n\n", contador);

    /* ----- Tabela comparativa para n = 1..6 (impressao silenciada) ---------- */
    silencioso = 1;
    printf("=== Tabela comparativa: movimentos x 2^n - 1 ===\n");
    printf(" n | Contado | 2^n - 1\n");
    printf("---+---------+---------\n");
    for (n = 1; n <= 6; n++) {
        contador = 0;
        hanoi(n, 'A', 'C', 'B');
        printf(" %d | %7ld | %7ld\n", n, contador, doisElevadoMenos1(n));
    }
    printf("\nA igualdade contado == 2^n - 1 confirma a complexidade O(2^n).\n");

    return 0;
}
