/*
    Atividade: ED02 - Questao 5
    
    Pergunta: Escreva uma funcao chamada troca que troca os valores dos 
    parametros recebidos, sua assinatura deve ser: void troca(float *a, float *b);  
    
    EXPLICAÇÃO:
    Para trocar os valores de duas variaveis na memoria usando ponteiros, 
    precisamos de uma variavel auxiliar (temporaria)
    1. A variavel 'temp' guarda o valor que esta no endereco 'a'
    2. O endereco 'a' recebe o valor que esta no endereco 'b'
    3. O endereco 'b' recebe o valor que guardamos em 'temp'
    Como passamos os enderecos de memoria (por referencia), a mudanca 
    afeta diretamente as variaveis originais na funcao main
 */

#include <stdio.h>

// Funcao que troca os valores de dois floats usando ponteiros
void troca(float *a, float *b) {
    float temp; // Variavel temporaria (nao eh ponteiro)
    
    temp = *a;  // Salva o valor apontado por 'a'
    *a = *b;    // O espaco apontado por 'a' recebe o valor de 'b'
    *b = temp;  // O espaco apontado por 'b' recebe o valor salvo em 'temp'
}

int main() {
    // Declarando duas variaveis float para o teste
    float valor1 = 10.5;
    float valor2 = 99.9;
    
    printf("===== TESTE DA FUNCAO DE TROCA (FLOAT) =====\n\n");
    
    // Imprimindo os valores antes da chamada da funcao
    printf("ANTES da troca:\n");
    printf("valor1 = %.2f\n", valor1);
    printf("valor2 = %.2f\n\n", valor2);
    
    // Chamando a funcao e passando os enderecos de memoria com o '&'
    troca(&valor1, &valor2);
    
    // Imprimindo os valores depois da chamada da funcao
    printf("DEPOIS da troca:\n");
    printf("valor1 = %.2f\n", valor1);
    printf("valor2 = %.2f\n", valor2);
    
    return 0;
}
