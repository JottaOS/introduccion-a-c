/**
 * (5pts)Dada la matriz MxN donde M y N son distintos y generados al azar (5 a 12) genere el siguiente patrón
 * de la matriz de ejemplo: 11x9
 *
 * Alumno: Juan Mendoza
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int numero_aleatorio(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

void inicializarMatriz(int **matriz, int n, int m)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            matriz[i][j] = (int)pow(j, i);
        }
    }
}

void imprimirMatriz(int **matriz, int n, int m)
{
    int i, j;
    printf("[\n");
    for (i = 0; i < n; i++)
    {
        printf("\t[");
        for (j = 0; j < m; j++)
        {
            printf("%-10d", matriz[i][j]);
        }
        printf("\t]\n");
    }
    printf("]\n");
}

void proceso()
{
    int n = 0, m = 0, i, j;

    n = numero_aleatorio(5, 12);
    do
    {
        m = numero_aleatorio(5, 12);
    } while (n == m);

    printf("Desde proceso: n->%d\tm->%d\n", n, m);

    int **matriz = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
    {
        matriz[i] = (int *)malloc(m * sizeof(int));
    }

    inicializarMatriz(matriz, n, m);
    imprimirMatriz(matriz, n, m);
}

int main()
{
    srand(time(NULL));
    proceso();
    return 0;
}
