/*
* Projeto 2
* Calculo Numerico - 2021/1
* Gabriel Carvalho, Maria Vitoria, Paulo Domingues
* Ajuste por funcoes linearizaveis
* Dado um arquivo de 2 linhas e n colunas, contendo na linha 1 os valores de x e,na linha 2, os valores de f(x)
* O programa calcula os coeficientes da funcao linear que aproxima f(x) nos pontos dados utilizando uma funcao exponencial g(x)
* e uma funcao geometrica h(x)
* 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
* NUM_FIELDS refere-se ao numero de campos no arquivo. Nesse caso, as duas linhas, x e f(x)
* NUM_FIELD_INPUTS refere-se a quantos valores ha em cada campo. Nesse caso, 7 pontos x, associados aos respectivos f(x)
*/
#define NUM_FIELDS 2
#define NUM_FIELD_INPUTS 7
#define FILE_NAME "tabela_trabalho2.txt"

/*
* Prototipo da funcao que soluciona o problema 
*/
void solucao(float * x, float * fx, float *Fx,int n, int flag);
void gx(float ag,float bg, float *x,float *gxi);
void hx(float ah, float bh, float *x,float *hxi);
float erroTotal(float *fx, float *aproximacao);

int main()
{
    
    char* input[NUM_FIELDS];
    /*
    * Abertura do arquivo
    */
    FILE * file = fopen(FILE_NAME, "r");

    if(!file)
        printf("Erro ao abrir arquivo!");

    
    float * x, * fx,* lnfx;
    x = (float *) malloc(NUM_FIELD_INPUTS * sizeof(float));
    fx = (float *) malloc(NUM_FIELD_INPUTS * sizeof(float));
    lnfx = (float *) malloc(NUM_FIELD_INPUTS * sizeof(float));


    /*
    * Leitura dos valores de x
    */
    int k = 0;
    while(k < NUM_FIELD_INPUTS && fscanf(file, "%f", &x[k]))
    {
        printf("%d / %d valores de x lidos\n", k + 1, NUM_FIELD_INPUTS);
        printf("\t Valor lido: %f \n", x[k]);
        k++;

    }

    /*
    * Leitura dos valores de f(x)
    */
    k = 0;
    while(k < NUM_FIELD_INPUTS && fscanf(file, "%f", &fx[k]))
    {
        printf("%d / %d valores de f(x) lidos\n", k + 1, NUM_FIELD_INPUTS);
        printf("\t Valor lido: %f \n", fx[k]);
        k++;

    }

    /*
    * Gerar dados para o teste de alinhamento: nesse caso, eh necessario calcular lnf(x)
    */
    for(int i = 0; i < NUM_FIELD_INPUTS; i++)
        lnfx[i] = logf(fx[i]);

    printf("\nDados para o teste de alinhamento: ");
    for(int i = 0; i < NUM_FIELD_INPUTS; i++)
        printf(" %f ", lnfx[i]); 

    /*
    * Usuario escolher qual polinomio quer usar para a aproximacao
    */

    int flag;
    printf("\nPolinomio 1 ou 2: \n");
    scanf("%d%*c",&flag);

    solucao(x,fx,lnfx,NUM_FIELD_INPUTS,flag);
    

    free(x);
    free(fx);
    free(lnfx);

    return 0;
}

void solucao(float *x, float *fx,float *Fx, int n, int flag)
{
    /*
    * Variaveis que representam os elementos do sistema normal
    * Algumas variaveis sao redundantes, pois tem o mesmo valor, tal como g1g2 e g2g1. Entretanto, serao
    * mantidas a fim de manter o codigo autodocumentado e semelhante ah expressao matematica.
    */
    float g1g1=0,g1g2=0,g2g1=0,g2g2=0,g1F1=0,g2F1=0;  
    int i;

    /*
    * Loop equivalente ah operacao de somatorio
    */
    for(i=0;i<n;i++)
    {
        g1g1 +=1;
        g1g2 += x[i];
        g2g2 += (pow(x[i],2));
        g1F1 += Fx[i];
        g2F1 += (x[i]*Fx[i]);

    }
    g2g1 = g1g2;
    printf("\nSistema normal:\n<g1,g1> = %f\t\t\t<g1,g2> = %f\t\ta1\t\t<g1,F1> = %f\n<g2,g1> = %f\t\t\t<g2,g2>= %f\t\ta2\t\t<g2,F1> = %f",g1g1,g1g2,g1F1,g2g1,g2g2,g2F1);
    
    
    /*
    * O sistema sera resolvido por meio da solucao apresentada na Aula 10, pagina 6, que utiliza o Metodo de Cramer
    * A vantagem eh achar os valores que solucionam o sistema com uma complexidade 0(1). Isso diminui o tempo de execucao e 
    * simplifica o entendimento da solucao.
    */

    float numeradorA,numumeradorB,denominador;
    numeradorA = (g1F1*g2g2) - (g1g2*g2F1);
    numumeradorB = (g1g1*g2F1) - (g1F1*g1g2);
    denominador = (g1g1*g2g2) - (g1g2*g1g2);
    
    float a = numeradorA/denominador;
    float b = numumeradorB/denominador;
    
    /*
    * Valores de g(x)
    */
    float ag = exp(a); // exp(x) = e^x , double exp(double x) returns the value of e raised to the xth power.
    float bg = b;
    float *gxi = (float*)malloc(NUM_FIELD_INPUTS*sizeof(float));
    gx(ag,bg,x,gxi);
    float erroGx = erroTotal(fx,gxi);
    
   /*
   * Valores de h(x)
   */
    float ah = exp(a);
    float bh = exp(b); 
    float *hxi = (float*)malloc(NUM_FIELD_INPUTS*sizeof(float));
    hx(ah,bh,x,hxi);
    float erroHx = erroTotal(fx,gxi);

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

    if(erroGx>erroHx)
        printf("\nh(x) eh uma melhor aproximacao.\nErro de h(x) = %f\nErro de g(x) = %f\n",erroHx,erroGx);
    else if(erroHx>erroGx)
        printf("\ng(x) eh uma melhor aproximacao.\nErro de g(x) = %f\nErro de h(x) = %f\n",erroGx,erroHx);
    else 
        printf("\nErro igual: %f\n", erroGx);

    free(gxi);
    free(hxi);
}

void gx(float ag,float bg, float *x,float *gxi)
{
    int i;

    for(i=0;i<NUM_FIELD_INPUTS;i++)
        gxi[i] = ag*exp(bg*x[i]);
}

void hx(float ah, float bh, float *x,float *hxi)
{
    int i;
    for(i=0;i<NUM_FIELD_INPUTS;i++)
        hxi[i] = ah*pow(bh,x[i]);
}

float erroTotal(float *fx, float *aproximacao)
{
    int i;
    float somaDosResiduosAoQuadrado = 0;

    for(i=0;i<NUM_FIELD_INPUTS;i++)
        somaDosResiduosAoQuadrado += (fx[i]-aproximacao[i])*(fx[i]-aproximacao[i]);
    
    return somaDosResiduosAoQuadrado;
}
