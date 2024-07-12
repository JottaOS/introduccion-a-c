/**
 * Ejercicio 1
 * Genere un vector con todas las cartas desordenadas
 */

#define GRNB "\e[42m"
#define RED "\e[0;31m"
#define BLK "\e[0;30m"
#define COLOR_RESET "\e[0m"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct CARTA
{
    int valor;
    int palo;
    int estado;
    int color; /* 0 es rojo, 1 es negro */
    char impresion[4];
} Carta;

void intercambiar(Carta *a, Carta *b)
{
    Carta temp = *a;
    *a = *b;
    *b = temp;
}

char letra(int n)
{
    char l = NULL;
    switch (n)
    {
    case 1:
        l = 'A';
        break;
    case 11:
        l = 'J';
        break;
    case 12:
        l = 'Q';
        break;
    case 13:
        l = 'K';
        break;
    default:
        break;
    }
    return l;
}

void cargar_mazo(Carta Mazo[])
{
    int i, j, c = 0;

    for (i = 3; i <= 6; i++)
    {
        for (j = 1; j <= 13; j++)
        {
            Mazo[c].valor = j;
            Mazo[c].palo = i;
            Mazo[c].estado = 0;

            if (i <= 4)
            {
                Mazo[c].color = 0;
            }
            else
            {
                Mazo[c].color = 1;
            }

            if (j == 1 || (j >= 11))
            {
                sprintf(Mazo[c].impresion, "%c%c", letra(j), i);
            }
            else
            {
                sprintf(Mazo[c].impresion, "%d%c", j, i);
            }

            c++;
        }
    }
}

void mezclar(Carta Mazo[], Carta Mazo_desordenado[])
{

    int i, r;
    for (i = 0; i < 52; i++)
    {
        do
        {
            r = rand() % 52;
        } while (Mazo[r].estado);

        Mazo_desordenado[i] = Mazo[r];
        Mazo[r].estado = 1;
    }
}

void imprimir_carta(Carta carta)
{
    char *color = (char *)malloc(sizeof(char) * 7);
    if (carta.color == 0)
    {
        color = RED;
    }
    else
    {
        color = BLK;
    }

    printf("%s%s\n", color, carta.impresion);
}

int main()
{
    Carta Mazo[52];
    Carta Mazo_desordenado[52];
    cargar_mazo(Mazo);
    mezclar(Mazo, Mazo_desordenado);

    int i;
    printf("MAZO ORIGINAL ======\n");
    for (i = 0; i < 52; i++)
    {
        imprimir_carta(Mazo[i]);
    }

    printf("MAZO DESORDENADO ======\n");
    for (i = 0; i < 52; i++)
    {
        imprimir_carta(Mazo_desordenado[i]);
    }
    printf("%s", COLOR_RESET);
    return 0;
}