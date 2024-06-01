/**
 * Resuelva de manera recursiva la sucesión de Fibonacci, donde el usuario carga N donde N es la cantidad
 * de elementos mayores a 10 menores a 25, imprima todos los resultados en pantalla
 *
 */

#include <stdio.h>
#include <stdlib.h>

int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

int ingresar()
{
    int n;
    do
    {
        printf("Ingrese un numero entre 10 y 25: ");
        scanf("%d", &n);
        if (n < 10 || n > 25)
            printf("\nNumero fuera del rango.\n");

    } while (n < 10 || n > 25);
    return n;
}

void proceso()
{
    printf("Secuencia de fibonacci\n");
    int n = ingresar();
    int i;
    for (i = 0; i < n; i++)
    {
        int resultado = fib(i);
        char *cadena = (char *)malloc(10 * sizeof(char));
        sprintf(cadena, "%d ", resultado);
        printf("%d ", resultado);
    }
    printf("\nFin\n");
}

int main()
{
    proceso();
    return 0;
}