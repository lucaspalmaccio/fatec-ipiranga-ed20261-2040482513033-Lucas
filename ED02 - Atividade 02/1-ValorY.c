/*
    Atividade: ED02 - Questao 1

    Pergunta: Qual o valor de y no final do programa?
 
    RESPOSTA: A resposta exata depende da interpretacao da linha "x–;". 

    Seguem as duas analises possiveis:


-- CENARIO 1: Interpretando de forma literal (sem assumir erro) ---

    RESULTADO: O programa NAO COMPILA.
 
    EXPLICACAO: Se o codigo contiver literalmente "x-;" (apenas um sinal de menos) 
     ou "x–;" (com um travessao de texto copiado de um PDF), o compilador C acusara 
     um erro de sintaxe ou "stray character". Uma operacao de subtracao exige dois 
     operandos (ex: x - 1;), e caracteres de formatacao de texto nao sao lidos pela 
     linguagem. Logo, a execucao e abortada e 'y' nao tem valor final.

-- CENARIO 2: Assumindo que "x–;" era um erro de digitacao para "x--;" ---
 
    RESULTADO: O valor final de y sera 4.
    EXPLICACAO PASSO A PASSO:
        1. y = 0;      -> y inicia com valor 0
        2. p = &y;     -> O ponteiro 'p' guarda o endereco de 'y'
        3. x = *p;     -> 'x' recebe o valor apontado por 'p' (x = 0)
        4. x = 4;      -> 'x' passa a valer 4 (isso nao altera y)
        5. ++(*p);     -> Incrementa o valor apontado por 'p'. 'y' passa a ser 1
        6. x--;        -> Decrementa 'x'. 'x' passa a ser 3
        7. (*p) += x++;-> Soma o valor atual de 'x' (3) ao valor de 'y' (1). 'y' vira 4 
        O 'x' e incrementado para 4 logo depois, mas nao afeta 'y'
 */

#include <stdio.h>

int main() {
    int y, *p, x;
    
    y = 0;
    p = &y;
    x = *p;
    x = 4;
    ++(*p);
    
    // Utilizando x-- para permitir que o codigo compile e demonstre o Cenario 2
    x--;          
    
    (*p) += x++;
    
    printf("y = %d\n", y); 
    
    return 0;
}
