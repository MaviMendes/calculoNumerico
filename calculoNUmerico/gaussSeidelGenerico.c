#include <stdio.h>
#include <stdlib.h>

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
    printf("\nTamanho n da matriz:\n");
    scanf("%d%*c",&n);

   float **M = (float**)malloc((n+1)*sizeof(float*));
   int aux;
   for(aux = 0; aux <=n; aux++) M[aux] = (float*)malloc((n+1)* sizeof(float));

    printf("\nInsira os elementos de M\n");
    printf("2 elementos da linha 1: \n");
    scanf("%f%*c",&M[1][1]);
    scanf("%f%*c",&M[1][2]);
    int i;
    printf("3 elementos de cada linha (2 ate %d), na ordem em que aparecem, ex: 1 -2 1: \n",n-1);
    /*float a,b,c;
    scanf("%f%*c",&a);
    scanf("%f%*c",&b);
    scanf("%f%*c",&c);*/
    for(i = 2;i<=n-1;i++)
    {
       scanf("%f%*c",&M[i][i-1]);
       scanf("%f%*c",&M[i][i]);
       scanf("%f%*c",&M[i][i+1]);
    }
    printf("2 elementos da linha %d: \n",n);
    scanf("%f%*c",&M[n][n-1]);
    scanf("%f%*c",&M[n][n]);

    showMatrix(M,n);
    
    printf("\nInsira os elementos do vetor b de Ax = b\n");
    float *b = (float*)malloc((n+1)*sizeof(float));
    for(i=1;i<=n;i++)
        scanf("%f",&b[i]);
    printf("\nOs elementos inseridos foram:\n");
    showArray(b,n);

    printf("\nInsira os elementos do vetor incial X0\n");
    float *X0 = (float*)malloc((n+1)*sizeof(float));
    for(i=1;i<=n;i++)
        scanf("%f",&X0[i]);
    printf("\nOs elementos inseridos foram:\n");
    showArray(X0,n);
    
    float eps;
    int NMAX;
    printf("\nInsira o erro(eps) e o numero maximo de iteracoes:\n");
    scanf("%f%*c",&eps);
    scanf("%d%*c",&NMAX);
    

    // gaussSeidel: n,eps,nmax,X0,M
    gaussSeidel(n,eps,NMAX,1,X0,b,M);
    // funcao para desalocar o espaco de M
    // freeMatrix(M);
    free(b);
    free(X0);
    return 0;
}

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

void showArray(float *Array, int n)
{
    int i;
    printf("\nVetor:\n");
    for(i=1;i<=n;i++)
        printf(" %f ",Array[i]);
}

float *gaussSeidel(int n,float eps,int NMAX,int count,float *XPrevious,float *b,float **M)
{
    float *XNext = (float*)malloc((n+1)*sizeof(float));

    int i = 1;

    XNext[i] = (b[i] - M[i][i+1]*XPrevious[i+1])/M[i][i];

    for(i=2;i<=n-1;i++)
        XNext[i] = (b[i] - XNext[i-1]*M[i][i-1] - XPrevious[i+1]*M[i][i+1])/M[i][i];
    
    XNext[n] = (b[n] - XNext[n-1]*M[n][n-1])/M[n][n];

    float erro = evaluateError(XNext, XPrevious, n);

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

float evaluateError(float *xNext, float *xPrevious, int n)
{
    
    float d = maxElement(xNext,n);

    float *differenceArray = (float*)malloc((n+1)*sizeof(float));
    
    differenceArray = subtract(xNext,xPrevious,n);

    float num = maxElement(differenceArray,n);

    return (d/n);
}

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

float *subtract(float *Xnext, float *xPrevious, int n)
{
    float *resultArray = (float*)malloc((n+1)*sizeof(float));

    int i;
    for(i=1;i<=n;i++)
        resultArray[i] = abs(Xnext[i] - xPrevious[i]);

    return resultArray;
}
