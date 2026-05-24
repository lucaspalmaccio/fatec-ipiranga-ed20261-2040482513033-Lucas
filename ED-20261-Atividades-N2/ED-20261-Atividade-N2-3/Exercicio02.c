// RA: 2040482513033 - Nome do Aluno: Lucas Bastos Palmaccio
/* ===========================================================================
 * Exercicio 02 : Mini-sistema de estatisticas sobre um vetor de floats.
 *                Toda iteracao usa incremento de ponteiro (ptr++) - sem [].
 * Compilar: gcc -Wall -Wextra -o prog Exercicio02.c
 * =========================================================================== */

#include <stdio.h>

/* ---------------------------------------------------------------------------
 * Calcula e RETORNA a media aritmetica do vetor.
 * Recebe o ponteiro para o primeiro elemento e o tamanho.
 * --------------------------------------------------------------------------- */
float calcularMedia(float *vet, int n) {
    float soma = 0.0f;
    float *fim = vet + n;       /* ponteiro logo apos o ultimo elemento */
    while (vet < fim) {
        soma += *vet;           /* *vet = valor atual */
        vet++;                  /* aritmetica de ponteiros: avanca sizeof(float) */
    }
    return soma / (float)n;
}

/* ---------------------------------------------------------------------------
 * Encontra maior e menor valor. NAO retorna - escreve diretamente nos
 * enderecos recebidos (passagem por ponteiro = simula retorno multiplo).
 * --------------------------------------------------------------------------- */
void encontrarExtremos(float *vet, int n, float *maior, float *menor) {
    float *fim = vet + n;
    *maior = *vet;              /* inicializa com o primeiro elemento */
    *menor = *vet;
    vet++;                      /* ja consumimos o primeiro, avancamos */
    while (vet < fim) {
        if (*vet > *maior) *maior = *vet;
        if (*vet < *menor) *menor = *vet;
        vet++;
    }
}

/* ---------------------------------------------------------------------------
 * Normaliza o vetor: divide cada elemento pelo valor maximo.
 * Apos a operacao, todos os valores ficam no intervalo [0, 1].
 *
 * IMPORTANTE: alteracoes feitas aqui MODIFICAM o vetor original do main.
 * Isso ocorre porque, ao passar 'notas' para a funcao, o que chega aqui
 * e um PONTEIRO para o mesmo espaco de memoria - nao uma copia do vetor.
 * Em C, arrays sempre decaem em ponteiros quando passados a funcoes.
 * --------------------------------------------------------------------------- */
void normalizar(float *vet, int n) {
    float maior, menor;
    float *p;
    float *fim = vet + n;

    encontrarExtremos(vet, n, &maior, &menor);
    if (maior == 0.0f) return;  /* evita divisao por zero */

    p = vet;
    while (p < fim) {
        *p = *p / maior;
        p++;
    }
}

/* ---------------------------------------------------------------------------
 * Imprime o vetor formatado, com um titulo opcional.
 * --------------------------------------------------------------------------- */
void imprimirVetor(float *vet, int n, const char *titulo) {
    float *fim = vet + n;
    printf("%s: [ ", titulo);
    while (vet < fim) {
        printf("%.3f ", *vet);
        vet++;
    }
    printf("]\n");
}

int main(void) {
    float notas[] = {7.5f, 3.2f, 9.8f, 6.0f, 5.5f, 8.1f};
    int n = sizeof(notas) / sizeof(notas[0]);

    float media;
    float maior, menor;

    /* --- Estado original ----------------------------------------------------- */
    imprimirVetor(notas, n, "Vetor original     ");

    /* --- Estatisticas sobre o vetor original --------------------------------- */
    media = calcularMedia(notas, n);
    encontrarExtremos(notas, n, &maior, &menor);
    printf("Media aritmetica   : %.3f\n", media);
    printf("Maior valor        : %.3f\n", maior);
    printf("Menor valor        : %.3f\n", menor);

    /* --- Normalizacao -------------------------------------------------------- *
     * Apos esta chamada, o array notas no main estara modificado.
     * Isso prova a passagem por ponteiro: nao houve copia, o que a funcao
     * alterou foi o conteudo no mesmo endereco de memoria.                      */
    normalizar(notas, n);
    imprimirVetor(notas, n, "Vetor normalizado  ");

    printf("\nObservacao: o vetor 'notas' foi MODIFICADO pela funcao normalizar\n");
    printf("porque, em C, ao passar o nome de um array para uma funcao, o que\n");
    printf("chega na funcao e um ponteiro para o MESMO espaco de memoria - nao\n");
    printf("uma copia. Assim, *p = x altera diretamente o vetor do chamador.\n");
    return 0;
}
