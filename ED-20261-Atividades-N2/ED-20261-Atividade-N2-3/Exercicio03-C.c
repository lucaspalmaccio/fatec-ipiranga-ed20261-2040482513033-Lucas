// RA: 2040482513033 - Nome do Aluno: Lucas Bastos Palmaccio
/* ===========================================================================
 * Exercicio 03 - Parte C : Torres de Hanoi com rastreamento da PROFUNDIDADE
 *                          da recursao (parametro 'nivel').
 *                          A saida e indentada com (nivel * 2) espacos.
 * Compilar: gcc -Wall -Wextra -o prog Exercicio03-C.c
 * =========================================================================== */

#include <stdio.h>

static long contador = 0;

/* Imprime 'qtd' espacos sem laco explicito no chamador. */
static void indentar(int qtd) {
    int i;
    for (i = 0; i < qtd; i++) putchar(' ');
}

/* ---------------------------------------------------------------------------
 * Funcao recursiva com parametro 'nivel' que representa a profundidade
 * atual da pilha de chamadas. A cada movimento, a profundidade e impressa
 * antes da acao, e a indentacao reflete visualmente a arvore de recursao.
 * --------------------------------------------------------------------------- */
void hanoi(int n, char origem, char destino, char auxiliar, int nivel) {
    if (n == 1) {
        contador++;
        indentar(nivel * 2);
        printf("[nivel %d] Mover disco 1 de %c -> %c\n", nivel, origem, destino);
        return;
    }
    hanoi(n - 1, origem, auxiliar, destino, nivel + 1);
    contador++;
    indentar(nivel * 2);
    printf("[nivel %d] Mover disco %d de %c -> %c\n", nivel, n, origem, destino);
    hanoi(n - 1, auxiliar, destino, origem, nivel + 1);
}

int main(void) {
    printf("=== Torres de Hanoi com profundidade (n = 1) ===\n");
    contador = 0;
    hanoi(1, 'A', 'C', 'B', 0);
    printf("Total: %ld movimento(s)\n\n", contador);

    printf("=== Torres de Hanoi com profundidade (n = 3) ===\n");
    contador = 0;
    hanoi(3, 'A', 'C', 'B', 0);
    printf("Total: %ld movimentos\n\n", contador);

    printf("=== Torres de Hanoi com profundidade (n = 4) ===\n");
    contador = 0;
    hanoi(4, 'A', 'C', 'B', 0);
    printf("Total: %ld movimentos\n", contador);

    printf("\nObservacao: a profundidade maxima da pilha e igual a n.\n");
    printf("Cada chamada recursiva empilha um novo stack frame com suas\n");
    printf("proprias variaveis locais. Ao retornar, o frame e desempilhado.\n");
    return 0;
}
