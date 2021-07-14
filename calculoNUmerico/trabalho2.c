/*
* Projeto 2
* Calculo Numerico - 2021/1
* Gabriel Carvalho, Maria Vitoria, Paulo Domingues
* Ajuste por funcoes linearizaveis
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//* Nesse caso é fixo mesmo, não sei se tem muito pq deixar dinamico pro trabalho
//*  mas se quiser, depois faço uma função q descobre esses valores automaticamente
#define NUM_FIELDS 2
#define NUM_FIELD_INPUTS 7


void solucao(float * x, float * fx, int n, int flag);
int main()
{
    
    // abrir arquivo
    char filename[] = "tabela_trabalho2.txt"; //? acho que tem q como colocar num define, se sim, seria top
    char* input[2];

    
    FILE * file = fopen(filename, "r");
    if(!file)
        printf("Erro ao abrir arquivo!");


    float * x, * fx,* lnfx;
    x = (float *) malloc(NUM_FIELD_INPUTS * sizeof(float));
    fx = (float *) malloc(NUM_FIELD_INPUTS * sizeof(float));
    lnfx = (float *) malloc(NUM_FIELD_INPUTS * sizeof(float));


    // ler x
    int k = 0;
    while(k < NUM_FIELD_INPUTS && fscanf(file, "%f", &x[k]))
    {
        printf("%d / %d valores de x lidos\n", k + 1, NUM_FIELD_INPUTS);
        printf("\t Valor lido: %f \n", x[k]);
        k++;

    }

    // ler f(x)
    k = 0;
    while(k < NUM_FIELD_INPUTS && fscanf(file, "%f", &fx[k]))
    {
        printf("%d / %d valores de f(x) lidos\n", k + 1, NUM_FIELD_INPUTS);
        printf("\t Valor lido: %f \n", fx[k]);
        k++;

    }

    // gerar dados para o teste de alinhamento
    for(int i = 0; i < NUM_FIELD_INPUTS; i++)
        lnfx[i] = logf(fx[i]);

    
    int flag;
    printf("Polinomio 1 ou 2: \n");
    scanf("%d%*c",&flag);

    solucao(x,fx,NUM_FIELD_INPUTS,flag);
    
    printf("\nDados para o teste de alinhamento: ");
    for(int i = 0; i < NUM_FIELD_INPUTS; i++)
        printf(" %f ", lnfx[i]); // ! DEU ERRADO 

    free(x);
    free(fx);
    free(lnfx);

    return 0;
}

void solucao(float *x, float *fx, int n, int flag)
{
    float g1g1=0,g1g2=0,g2g1=0,g2g2=0,g1F1=0,g2F1=0;
    int i;
    for(i=0;i<n;i++)
    {
        g1g1 +=1;
        g1g2 += x[i];
        // g1g2 = g2g1
        g2g2 += x[i]*x[i];
        g1F1 += fx[i];
        g2F1 += x[i]*fx[i];
    }
    g2g1 = g1g2;
    printf("\nSistema normal:\n<g1,g1> = %f\t\t\t<g1,g2> = %f\t\ta1\t\t<g1,F1> = %f\n<g2,g1> = %f\t\t\t<g2,g2>= %f\t\ta2\t\t<g2,F1> = %f",g1g1,g1g2,g1F1,g2g1,g2g2,g2F1);
    
    // achar a e b por meio da resolucao do sistema pelo metodo de cramer (pdf aula 10 pg 6)
    float numeradorA,numumeradorB,denominador;
    numeradorA = (g1F1*g2g2) - (g1g2*g2F1);
    numumeradorB = (g1g1*g2F1) - (g1F1*g1g2);
    denominador = (n*g2g2) - (g1g1*g1g2);
    
    float a = numeradorA/denominador;
    float b = numumeradorB/denominador;
    
    // valores da g(x)
    float ag = exp(a); // exp(x) = e^x
    float bg = b;
    
    // valores da h(x)
    float ah = exp(a);
    float bh = exp(b); 

    if(flag ==1 )
    {
        printf("\nO polinomio g(x), escolhido: g(x) = ae^bx = %f*e^%f*x",ag,bg);
        printf("\nEm contraste, o polinomio h(x) = ab^x = %f*%f^x",ah,bh);
    }
    else 
    {
        printf("\nO polinomio h(x), escolhido: h(x) = ab^x = %f*%f^x",ah,bh);
        printf("\nEm contraste, o polinomio g(x) = ae^bx = %f*e^%f*x",ag,bg);
    }
}
