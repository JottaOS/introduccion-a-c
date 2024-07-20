/**
 * Tema 2
 * Dada la matriz NxN donde N es mayor o igual a 7 y menor o igual a 17 generada al azar. Genere
 * el siguiente patrón mostrado en el ejemplo donde N es igual a 15.
 *
 * Alumno: Juan Mendoza
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void proceso();
int generar_n();
void cargar_matriz(int n, int matriz[n][n]);
void imprimir_matriz(int n, int matriz[n][n]);

int main()
{
    srand(time(NULL));
    proceso();
    return 0;
}

int generar_n()
{
    int n = rand() % 11 + 7;
    return n;
}

void cargar_matriz(int n, int matriz[n][n])
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            matriz[i][j] = n - (i < j ? i : j);
        }
    }
}

void imprimir_matriz(int n, int matriz[n][n])
{
    printf("Dimension aleatoria: %d\n", n);
    printf("\n=== Matriz generada === \n");
    int i, j;
    for (i = 0; i < n; i++)
    {
        printf("[");
        for (j = 0; j < n; j++)
        {
            printf("%3d", matriz[i][j]);
        }
        printf("  ]\n");
    }
}

void proceso()
{
    int n = generar_n();
    int matriz[n][n];
    cargar_matriz(n, matriz);
    imprimir_matriz(n, matriz);
}
