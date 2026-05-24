// RA: 2040482513033 - Nome do Aluno: Lucas Bastos Palmaccio
/* ===========================================================================
 * Exercicio 04 - Parte A : Busca Binaria Recursiva.
 *   - Vetor ordenado crescente.
 *   - Retorna o indice do alvo ou -1 se ausente.
 *   - Contabiliza o numero de chamadas recursivas por busca.
 * Compilar: gcc -Wall -Wextra -o prog Exercicio04-A.c
 * =========================================================================== */

#include <stdio.h>

/* Contador global de chamadas recursivas - zerado antes de cada busca. */
static int chamadas = 0;

/* ---------------------------------------------------------------------------
 * Busca binaria recursiva.
 *   Caso base 1 : inicio > fim          -> nao encontrou, retorna -1.
 *   Caso base 2 : vet[meio] == alvo     -> encontrou, retorna 'meio'.
 *   Caso recursivo:
 *     - se alvo < vet[meio] -> buscar na metade esquerda.
 *     - se alvo > vet[meio] -> buscar na metade direita.
 * Complexidade: O(log n) - cada chamada reduz o espaco de busca pela metade.
 * --------------------------------------------------------------------------- */
int buscaBinaria(int *vet, int inicio, int fim, int alvo) {
    int meio;
    chamadas++;

    if (inicio > fim) return -1;           /* CASO BASE - nao encontrou */

    meio = inicio + (fim - inicio) / 2;    /* evita overflow vs (i+f)/2 */

    if (vet[meio] == alvo) return meio;    /* CASO BASE - encontrou     */
    if (alvo < vet[meio])
        return buscaBinaria(vet, inicio, meio - 1, alvo);   /* esquerda */
    else
        return buscaBinaria(vet, meio + 1, fim, alvo);      /* direita  */
}

/* Funcao auxiliar de teste que zera o contador, executa a busca e imprime. */
static void testarBusca(int *vet, int n, int alvo) {
    int idx;
    chamadas = 0;
    idx = buscaBinaria(vet, 0, n - 1, alvo);
    if (idx >= 0)
        printf("alvo = %2d  -> encontrado no indice %d (%d chamadas)\n",
               alvo, idx, chamadas);
    else
        printf("alvo = %2d  -> NAO encontrado          (%d chamadas)\n",
               alvo, chamadas);
}

int main(void) {
    int dados[] = {2, 5, 8, 12, 16, 23, 38, 45, 72, 91};
    int n = sizeof(dados) / sizeof(dados[0]);

    printf("=== Busca Binaria Recursiva ===\n");
    printf("Vetor: 2 5 8 12 16 23 38 45 72 91  (n = %d)\n\n", n);

    /* 1) Valor presente no meio do vetor                                    */
    testarBusca(dados, n,  23);
    /* 2) Valor ausente                                                      */
    testarBusca(dados, n,  17);
    /* 3) Primeiro elemento (pior caso do lado esquerdo)                     */
    testarBusca(dados, n,   2);
    /* Extras para evidenciar O(log n)                                       */
    testarBusca(dados, n,  91);     /* ultimo elemento  */
    testarBusca(dados, n, 100);     /* alem do final    */

    return 0;
}
