/*
* Projeto 2
* Calculo Numerico - 2021/1
* Gabriel Carvalho, Maria Vitoria, Paulo
* Ajuste por funcoes linearizaveis
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void solucao(float *x, float *fx, int n, int flag);
int main()
{
    
    // abrir arquivo
    char filename[] = "tabela_trabalho2.txt";
    char *input[2];

    int k = 0;
    FILE *file = fopen(filename,"r");
    if(!file)
        printf("Erro ao abrir arquivo!");

    char linha[100];
    while(fgets(linha,sizeof(linha),file))
    {
        input[k] = linha;
        // checar se ta ok
        printf("lido: input[%d] = %s",k,input[k]);
        k++;
    }
    
    // transformar os dados em valores numericos
    int n,flag,i,j;
    int size = strlen(input[0]);
    char strX[size];
    strcpy(strX,input[0]);
    char strFx[size];
    strcpy(strFx,input[1]);

    printf("Valor de n (quantos valores de x, quantos pontos): \n");
    scanf("%d%*c",&n);
    printf("Polinomio 1 ou 2: \n");
    scanf("%d%*c",&flag);
    float *x, *fx,*lnfx;
    x = (float*)malloc(n*sizeof(float));
    fx = (float*)malloc(n*sizeof(float));
    lnfx = (float*)malloc(n*sizeof(float));
    // preenchimento manual do vetor a fim de testar a funcao

    x[0] = 0.35; x[1] = 0.40; x[2]=0.45;x[3]=0.50;x[4]=0.55;x[5]=0.60;x[6]=0.65;
    fx[0] = 1.52; x[1] = 1.51; x[2]=1.59;x[3]=1.47;x[4]=1.44;x[5]=1.42;x[6]=1.39;
    /*
    Na verdade, o que deve ser feito eh isso aqui:

    TRANSFORMAR A STRING EM ARRAY DE FLOATS. Nao deu certo utilizar atof porque o argumento deve ser do tipo string e nao um char
    Talvez seja melhor mudar a leitura do arquivo
    Pensar nessa parte

    for(i=0;i< size;i++)
    {
        if(strX[i] != ' ')
            x[j++] = atof(strX[i]);
    }
    j=0;
    for(i=0;i< size;i++)
    {
        if(strFx[i] != ' ')
            x[j++] = atof(strFx[i]);
    }
     for(i=0;i< size;i++)
    {
        printf("\nx[%d]=%f",i,x[i]);
    }*/

    // gerar dados para o teste de alinhamento
    for(i=0;i<n;i++)
        lnfx[i] = logf(fx[i]);

    solucao(x,fx,n,flag);
    
    printf("\nDados para o teste de alinhamento: ");
    for(i=0;i<n;i++)
        printf(" %f ",lnfx[i]); // DEU ERRADO 

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
