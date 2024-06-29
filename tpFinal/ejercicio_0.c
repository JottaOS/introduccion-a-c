/**
 * Ejercicio 0
 * Genere un mazo de 52 cartas, donde cada carta posea todas sus características
 * Una vez que cargue las 52 cartas, imprima.
 * 3 - Corazon -- rojo
 * 4 - Diamante -- rojo
 * 5 - Trebol -- negro
 * 6 - Espada -- negro
 */

#define WHTB "\e[47m" // fondo blanco
#define RED "\e[0;31m"
#define BLK "\e[0;30m"

#include <stdio.h>
#include <stdlib.h>

typedef struct CARTA
{
    int valor;
    int palo;
    int estado;
    int color; /* 0 es rojo, 1 es negro */
    char impresion[4];
} Carta;

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
}

void cargar_mazo(Carta Mazo[])
{
    int i, j, c = 0;

    for (i = 3; i <= 6; i++)
    {
        for (j = 0; j < 13; j++)
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

void imprimir_carta(Carta carta)
{
    printf("%s\n", carta.impresion);
}

int main()
{
    printf("%s", WHTB);
    Carta mazo[52];
    cargar_mazo(mazo);
    int i;
    for (i = 0; i < 52; i++)
    {
        imprimir_carta(mazo[i]);
    }

    return 0;
}
