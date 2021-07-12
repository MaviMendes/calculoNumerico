#include <stdio.h>
#include <stdlib.h>

void gaussSeidel(int n, float eps, int NMAX, int count,float *xPrevious);
float evaluateError(float *xNext, float *xPrevious, int n);
float maxElement(float *Array, int n);
float *subtract(float *Xnext, float *xPrevious, int n);
void showResult(float *lastX, int n);

int main()
{
    
    /*
    Input:
    tamanho da matriz
    eps
    NMAX
    */
   
    int n;
    float eps;
    int NMAX;

    printf("\t\t\tMETODO DE GAUSS-SEIDEL PARA MATRIX TRIDIAGONAL\nInsira o tamanho da matriz, o erro e o numero maximo de tentativas.\n");

    scanf("%d%*c",&n);
    scanf("%f%*c",&eps);
    scanf("%d%*c",&NMAX);
    
    float *xPrevious = (float*)malloc((n+1)*sizeof(float));

    xPrevious[1] = 1;
    xPrevious[n] = 1;
    int i;
    for(i=2;i<=n-1;i++)
        xPrevious[i] = 0;

    
    gaussSeidel(n,eps,NMAX,0,xPrevious);

    return 0;
}

void gaussSeidel(int n, float eps, int NMAX, int count,float *xPrevious)
{
    int i = 1;
    float *xNext = (float*)malloc((n+1)*sizeof(float)); 
    float erro;
    
    
    xNext[i] = (1 - xPrevious[i+1])/-2;

    for(i = 2; i<=n-1;i++)
        xNext[i] = (-1*xNext[i-1] -1*xPrevious[i+1])/-2;
    
    xNext[n] = (1 - xNext[n-1])/-2;
    
    erro = evaluateError(xNext, xPrevious, n);
    
    
    if(erro>eps && (count + 1) <= NMAX)
        gaussSeidel(n,eps,NMAX,count+1,xNext);
    else
        showResult(xNext,n);
    
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

void showResult(float *lastX, int n)
{
    int i;
    printf("\nResultado final: \n");
    for(i=1;i<=n;i++)
    {
        printf(" %f ", lastX[i]);
    }
    printf("\n");
}