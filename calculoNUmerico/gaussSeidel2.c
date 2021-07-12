/*
Projeto 1 - Calculo Numerico
Maria Vitoria
Paulo Santos
Gabriel Carvalho
*/

#include <stdio.h>
#include <stdlib.h>

// prototipo das funcoes

void showMatrix(float **M, int n);
void showArray(float *Array, int n);
float *gaussSeidel(int n,float eps,int NMAX,int count,float *XPrevious,float *b,float **M);
float evaluateError(float *xNext, float *xPrevious, int n);
float maxElement(float *Array, int n);
float *subtract(float *Xnext, float *xPrevious, int n);

int main()
{
    /*
    Input e procedimentos:
    tamanho n
    cria matriz de tamamnho nxn
    receber elementos da matriz
    imprimir a matriz formada
    receber elementos de b
    exibir o vetor b
    receber o vetor xInicial
    receber o erro
    receber nmax
    calculo de guass-seidel
    exibir resultado

    */
    
    int n;
    int i;
    
    // Pedir informacoes ao usuario: tamanho da matriz, os elementos que irao preencher a matriz

    printf("\nTamanho n da matriz:\n");
    scanf("%d%*c",&n);

   float **M = (float**)malloc((n+1)*sizeof(float*));
   int aux;
   for(aux = 0; aux <=n; aux++) M[aux] = (float*)malloc((n+1)* sizeof(float));

    // Supondo uma matriz como a do enunciado, 3 elementos que se repetem ao longo da diagonal
    printf("\nInsira os 3 elementos de M\n");
    float r,s,t;
    scanf("%f%*c",&r);
    scanf("%f%*c",&s);
    scanf("%f%*c",&t);
    
    // Preenchimento da matriz com os valores lidos

    M[1][1] = s;
    M[1][2] = t;
    
    for(i = 2;i<=n-1;i++)
    {
       M[i][i-1] = r;
       M[i][i] = s;
       M[i][i+1] = t;
    }

    M[n][n-1] = r;
    M[n][n] = s;

    //showMatrix(M,n);
    
    // Vetor b de Ax = b. Supondo um vetor como o do problema do enunciado: valor 1 para a primeira posicao
    // e valor 1 para a ultima posicao. O restante das posicoes tem valor zero

    float *b = (float*)malloc((n+1)*sizeof(float));
    b[1] = 1;
    b[n] = 1;
    for(i=2;i<n;i++)
        b[i] = 0;
    
    printf("\nO vetor b:\n");
    showArray(b,n);
    
    // Vetor X0 inicial recebe zeros
    float *X0 = (float*)malloc((n+1)*sizeof(float));
    for(i=1;i<=n;i++)
        X0[i] = 0;
    printf("\nVetor X0:\n");
    showArray(X0,n);
    
    float eps;
    int NMAX;
    printf("\nInsira o erro(eps) e o numero maximo de iteracoes:\n");
    scanf("%f%*c",&eps);
    scanf("%d%*c",&NMAX);
    

    // gaussSeidel: n,eps,nmax,X0,M
    // Chama a funcao

    gaussSeidel(n,eps,NMAX,1,X0,b,M);
    
    free(b);
    free(X0);
    return 0;
}

// Funcoes auxiliares do programa

// mostrar a matriz

void showMatrix(float **M, int n)
{
    int i,j;
    printf("\nMatriz:\n");
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            printf(" %f ",M[i][j]);
        }

        printf("\n");
    }
}

// mostrar um array/vetor

void showArray(float *Array, int n)
{
    int i;
    printf("\nVetor:\n");
    for(i=1;i<=n;i++)
        printf("%f\n",Array[i]);
}

// Funcao que implementa o algoritimo do metodo de gauss-seidel

float *gaussSeidel(int n,float eps,int NMAX,int count,float *XPrevious,float *b,float **M)
{
    float *XNext = (float*)malloc((n+1)*sizeof(float)); // X(k+1) da formula

    int i = 1;

    XNext[i] = (b[i] - M[i][i+1]*XPrevious[i+1])/M[i][i]; // Calculo do X1 de X(k+1)
    
    // Da segunda ate a penultima linha: X(k+1) = (bi - X(k+1)*elemento da diagonal antes da principal - X(k)*elemento da diagonal apos a principal)/ elemento da diagonal principal

    for(i=2;i<=n-1;i++)
        XNext[i] = (b[i] - XNext[i-1]*M[i][i-1] - XPrevious[i+1]*M[i][i+1])/M[i][i];
    
    // X(k+1) do elemento da ultima linha: (bn - X(k)* elemento da coluna antes da diagonal) / elemento da diagonal principal
    XNext[n] = (b[n] - XNext[n-1]*M[n][n-1])/M[n][n];
    
    // Calculo do erro
    float erro = evaluateError(XNext, XPrevious, n);

    // Teste de parada

    if(erro>eps && (count + 1) <= NMAX)
        gaussSeidel(n,eps,NMAX,count+1,XNext,b,M);
    else
    {
        if(count == NMAX)
            printf("\nFim da iteracao. Numero maximo de iteracoes atingido.\nVetor x:\n");
        else 
            printf("Fim da iteracao. Erro < eps.\nVetor x:\n");

        showArray(XNext,n);
    }
    free(XNext);
}

// Funcao que avalia o erro

float evaluateError(float *xNext, float *xPrevious, int n)
{
    
    float d = maxElement(xNext,n); // Elemento maximo, em modulo, do vetor X(k) mais atual

    float *differenceArray = (float*)malloc((n+1)*sizeof(float));
    
    differenceArray = subtract(xNext,xPrevious,n); // Realiza a subtracao de dois arrays

    float num = maxElement(differenceArray,n); // Elemento maximo, em modulo, do array resultante da subtracao

    return (d/n);
}

// Funcao que retorna o elemento maximo, em modulo, de um vetor

float maxElement(float *Array, int n)
{
    float max = abs(Array[1]);
    int i;

    for(i=2;i<=n;i++)
    {
        if(abs(Array[i])>max)
            max = abs(Array[i]);
    }
    
    return max;
}

// Funcao que realiza a subtracao de dois vetores

float *subtract(float *Xnext, float *xPrevious, int n)
{
    float *resultArray = (float*)malloc((n+1)*sizeof(float));

    int i;
    // abs: valor absoluto da subtracao
    for(i=1;i<=n;i++)
        resultArray[i] = abs(Xnext[i] - xPrevious[i]);

    return resultArray;
}