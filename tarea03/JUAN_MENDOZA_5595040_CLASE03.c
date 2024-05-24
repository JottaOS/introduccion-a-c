
/*
Dado un numero de 8 cifras diga si el mismo es palíndromo o capicua o no lo es, es decir que el formato numérico sea ABCDDCBA.
Ej: 81233218
A partir del numero cargado en el conviértalo a letras donde A es el 0, B el 1 así sucesivamente la  J el 9

ALUMNO: JUAN MENDOZA
*/

#include <stdio.h>

int capturar();
int reversar(int n);
void convertir_a_letras(int n);

int main()
{
    int n = capturar();
    int reverso = reversar(n);

    if (n != reverso)
    {
        printf("El número no es un palíndromo");
    }
    else
    {
        printf("El numero es un palindromo.\n");
        convertir_a_letras(n);
    }

    return 0;
}

int reversar(int n)
{
    int reverso = 0, resto;
    while (n != 0)
    {
        resto = n % 10;
        reverso = reverso * 10 + resto;
        n /= 10;
    }

    return reverso;
}

int capturar()
{
    int n;
    do
    {
        printf("Ingrese un numero de 8 cifras: ");
        scanf("%d", &n);
        getchar();

        if (n <= 9999999 || n > 99999999)
        {
            printf("Longitud de numero no valido");
        }
    } while (n <= 9999999 || n > 99999999);

    return n;
}

void convertir_a_letras(int n)
{
    printf("%d = ", n);
    while (n != 0)
    {
        switch (n % 10)
        {
        case 0:
            printf("A");
            break;
        case 1:
            printf("B");
            break;
        case 2:
            printf("C");
            break;
        case 3:
            printf("D");
            break;
        case 4:
            printf("E");
            break;
        case 5:
            printf("F");
            break;
        case 6:
            printf("G");
            break;
        case 7:
            printf("H");
            break;
        case 8:
            printf("I");
            break;
        case 9:
            printf("J");
            break;
        }
        n /= 10;
    }
}