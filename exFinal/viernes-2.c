#include <stdio.h>

int main()
{
    int N;

    // Solicitar al usuario ingresar el tamaño de la matriz
    printf("Ingrese el tamaño de la matriz (N): ");
    scanf("%d", &N);

    // Verificar que el tamaño de la matriz esté dentro del rango permitido
    if (N < 7 || N > 17)
    {
        printf("El tamaño de la matriz debe ser mayor o igual a 7 y menor o igual a 17.\n");
        return 1;
    }

    // Generar la matriz con el patrón
    int matriz[N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matriz[i][j] = N - (i < j ? i : j);
        }
    }

    // Imprimir la matriz
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%2d ", matriz[i][j]);
        }
        printf("\n");
    }

    return 0;
}
