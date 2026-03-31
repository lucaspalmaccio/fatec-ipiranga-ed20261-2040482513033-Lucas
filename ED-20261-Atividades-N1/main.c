/*----------------------------------------------------------------------------------*/
/*                                FATEC-Ipiranga                                    */        
/*                            ADS - Estrutura de Dados                              */
/*                             Id da Atividade: ATIVIDADE N1-3                      */
/*                                                                                  */
/*                                                                                  */
/*                                  Autor: Lucas Bastos Palmaccio                   */
/*                                                                   Data:31/03/2026*/
/*----------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------PILHA------------------------------------
#define tamanhoPilha 4
typedef struct{
    double digito[tamanhoPilha];
    int topo;
} Pilha;

void listarPilha(Pilha* p){
    printf("\n\n/////////LISTA PILHA////////////");
    for(int i=0; i<=p->topo; i++){
        printf("\n %iº posição da pilha têm: %.2f", tamanhoPilha-i, p->digito[i]);
    }
    printf("\n///////////////////////////////");
}
void iniciar(Pilha* p) {
    p->topo = -1; // -1 significa pilha vazia
}

void push(Pilha* p, double valor) {
    p->topo++;
    p->digito[p->topo] = valor;
    listarPilha(p);
}

double pop(Pilha* p) {
    double valor = p->digito[p->topo];
    p->topo--;
    listarPilha(p);
    return valor;
}

int vazia(Pilha* p) {
    return p->topo == -1;
}
//----------------------------------------------PILHA---------------------------------------------


//---------------------------------------------FUNÇÕES--------------------------------------------

char** separar(char* operacaoDigi){//separar os digitos em um vetor de strings
    int i = 0;
    char **listaSepara;
    listaSepara = malloc(100 * sizeof(char*));//aloca 100 ponteiros de caracteres
    
    char* token = strtok(operacaoDigi, " ");//vai quebrar os espaços da str original com \0
    while(token != NULL)
    {
        listaSepara[i] = token;
        i++;
        token = strtok(NULL, " ");//continua o processo de quebra da str
    }
    
    return listaSepara; 
}

double resolverOperacao(char** listaSepara, Pilha* pilha){
    int i=0;
    double op1=0, op2=0;
    double temp;
    while(listaSepara[i] != NULL){//Enquanto tiver elementos na lista
        if(*listaSepara[i]=='-'){ //Sequencia de Ifs para verificar a operação
            op2 = pop(pilha);
            op1 = pop(pilha);
            push(pilha, op1 - op2);
            i++;
        }else if(*listaSepara[i]=='+'){
            op2 = pop(pilha);
            op1 = pop(pilha);
            push(pilha, op1 + op2);
            i++;
        }else if(*listaSepara[i]=='*'){
            op2 = pop(pilha);
            op1 = pop(pilha);
            push(pilha, op1 * op2);
            i++;
        }else if(*listaSepara[i]=='/'){
            op2 = pop(pilha);
            op1 = pop(pilha);
            push(pilha, op1 / op2);
            i++;
        }else{ //em nenhum dos casos, deve ser um número
            temp = atof(listaSepara[i]); //converte a string em um double
            push(pilha, temp);
            i++;
        }
    }
    
    return pilha->digito[pilha->topo];
}
//---------------------------------------------FUNÇÕES--------------------------------------------


//---------------------------------------------MAIN-----------------------------------------------
int main()
{
    char operacaoDigi[100];
    Pilha* pilha;
    pilha = malloc(sizeof(Pilha));
    iniciar(pilha);
    char** listaSepara;
    printf("Olá, digite sua operação no formato RPN: ");
    fgets(operacaoDigi, 100, stdin);
    listaSepara = separar(operacaoDigi);//vai separar em um vetor de strings
    printf("\n\nO resultado da operação é: %0.2f", resolverOperacao(listaSepara, pilha));
    

    return 0;
}