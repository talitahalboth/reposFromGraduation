#include <stdio.h>
#define N 3
int troca (double a[N][N], int j, int k) {
    double aux;
    for (int i = 0; i < N; ++i) {
        aux = a[j][i];
        a[j][i] = a[k][i];
        a[k][i]=aux;
    }
}
//TODO: pivotamento parcial
void elimina (double a[N][N], double l[N][N], double u[N][N] ) {
    double m;
    for (int k = 0; k < N-1; ++k) {
        int i;
        for (i = k; i < N, a[i][k] == 0; ++i);
            if ( k != i) troca (a,i,k);
            
            for (i = k+1; i < N; ++i) {
                m = (a[i][k]*1.0)/a[k][k];
                for (int j = k; j < N; ++j)
                        a[i][j] -= m*a[k][j];
                a[i][k] = m;
            }
    }
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (i<j)
            {
                u[i][j]=a[i][j];
                l[i][j]=0;
            }
            else if (i == j)
            {
                l[i][j]=1;
                u[i][j]=a[i][j];
            }
            else
            {
                l[i][j]=a[i][j];
                u[i][j]=0;
            }
        }
    }
}

/*TODOs: 
    resolver superior e inferior na mesma função
    resolver usando só uma matriz (LU)
    resolver sem precisar passar o vetor b
*/
int resolveSup (double a[N][N], double x[N], double b[N]) {
    double soma = 0;
    x[N-1] = b[N-1]/a[N-1][N-1];
    for (int k = N-2; k >= 0; --k) {
        soma = b[k];

        for (int j = k; j < N; ++j)
        {
            soma-= a[k][j]*(x[j]);
        }

        
        x[k]=(soma*1.0)/a[k][k];
    }

    
    return 0;
}
/*
TODO:
    refinamento
        R = I - A * inv(A)
        ||r|| = sqrt( sum( R[i,j] ² ) ), [i,j] = {1,2,...,n}
    mensagem de erro se A não for inversível
    opções para execução do programa
    alocar matrizes dinâmicamente
    calcular tempo
    gerar matriz aleatoria
*/

int resolveInf (double a[N][N], double x[N], double b[N]) {
    double soma = 0;
    x[0] = b[0]/a[0][0];
    for (int k = 1; k < N; ++k) {
        soma = b[k];

        for (int j = 0; j <= k; ++j)
            soma-= a[k][j]*(x[j]);
        
        x[k]=(soma*1.0)/a[k][k];
    }


    
    return 0;
}


int main(int argc, char const *argv[]) {
    double a[N][N] = { 1, 0,  2, 
                       2,  -1, 3, 
                      4, 1,  8},
      b[N] = {2, 1, 3};
      double x1[N],x2[N],x3[N];
      double y1[N],y2[N],y3[N];
      double l[N][N], u[N][N];

    elimina(a,l,u);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            printf("%lf ",a[i][j] );
        }
        printf("\n");
    }
    printf("\n");
    b[0] = 1;
    b[1] = 2;
    b[2] = 3;
    resolveInf(l,y1,b);
    b[0] = 1;
    b[1] = 2;
    b[2] = 3;
    resolveInf(l,y2,b);
    b[0] = 1;
    b[1] = 2;
    b[2] = 6;
    resolveInf(l,y3,b);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            printf("%lf ",a[i][j] );
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < N; ++i)
    {
        printf("%.1lf %.1lf %.1lf\n",y1[i],y2[i],y3[i] );
    }
    printf("\n");

    resolveSup(u,x1,y1);
    resolveSup(u,x2,y2);
    resolveSup(u,x3,y3);

    for (int i = 0; i < N; ++i)
    {
        printf("%.1lf %.1lf %.1lf\n",x1[i],x2[i],x3[i] );
    }


    return 0;
}