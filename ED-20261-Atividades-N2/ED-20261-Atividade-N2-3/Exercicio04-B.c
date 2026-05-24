// RA: 2040482513033 - Nome do Aluno: Lucas Bastos Palmaccio
// /* ===========================================================================
 * Exercicio 04 - Parte B : Potenciacao Rapida (Fast Exponentiation).
 *   - Recursiva, com complexidade O(log n).
 *   - Comparada com a potenciacao ingenua O(n).
 *   - Proibido o uso de pow / math.h.
 * Compilar: gcc -Wall -Wextra -o prog Exercicio04-B.c
 * =========================================================================== */

#include <stdio.h>

static int chamadasRapida = 0;
static int chamadasIngenua = 0;

/* ---------------------------------------------------------------------------
 * Potenciacao rapida.
 *   Caso base    : exp == 0 -> retorna 1.
 *   Caso recursivo:
 *     - exp par   : b^exp = (b^(exp/2))^2  -> UMA chamada recursiva.
 *     - exp impar : b^exp = b * b^(exp-1)  -> reduz para o caso par.
 * Complexidade: O(log exp).
 * --------------------------------------------------------------------------- */
long long potenciaRapida(long long base, int exp) {
    long long meio;
    chamadasRapida++;

    if (exp == 0) return 1;                 /* CASO BASE */

    if (exp % 2 == 0) {
        meio = potenciaRapida(base, exp / 2);
        return meio * meio;
    } else {
        return base * potenciaRapida(base, exp - 1);
    }
}

/* ---------------------------------------------------------------------------
 * Potenciacao ingenua (recursiva linear) - para comparacao.
 * Complexidade: O(exp).
 * --------------------------------------------------------------------------- */
long long potenciaIngenua(long long base, int exp) {
    chamadasIngenua++;
    if (exp == 0) return 1;                 /* CASO BASE */
    return base * potenciaIngenua(base, exp - 1);
}

static void testar(long long base, int exp) {
    long long r1, r2;

    chamadasRapida = 0;
    chamadasIngenua = 0;

    r1 = potenciaRapida(base, exp);
    r2 = potenciaIngenua(base, exp);

    printf("%lld^%-2d = %-15lld | rapida: %2d chamadas | ingenua: %2d chamadas\n",
           base, exp, r1, chamadasRapida, chamadasIngenua);

    /* sanity check em tempo de execucao */
    if (r1 != r2)
        printf("  !! divergencia entre as duas implementacoes !!\n");
}

int main(void) {
    printf("=== Potenciacao Rapida vs Ingenua ===\n");
    printf("Casos pedidos: 2^10, 3^7, 5^0, 7^12\n\n");

    testar(2, 10);
    testar(3,  7);
    testar(5,  0);
    testar(7, 12);

    /* ------------------------------------------------------------------------
     * Comentario de analise:
     *   Para 7^12 a rapida usa cerca de log2(12) ~ 4 niveis pares + os impares
     *   reduzidos, totalizando muito menos chamadas que as 13 da ingenua.
     *   Conforme exp cresce, a diferenca explode: 2^1000 usa ~10 niveis na
     *   rapida e 1001 chamadas na ingenua.
     * ----------------------------------------------------------------------- */
    printf("\nConclusao:\n");
    printf("  - Rapida: O(log exp) chamadas recursivas.\n");
    printf("  - Ingenua: O(exp) chamadas recursivas.\n");
    printf("  - Para exp = 1.000.000, a ingenua estouraria a pilha; a rapida\n");
    printf("    faria apenas ~20 chamadas.\n");
    return 0;
}
