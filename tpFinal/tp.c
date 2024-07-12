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
#include <string.h>
#include <stdbool.h>

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

    printf("%s%s%s", color, carta.impresion, COLOR_RESET);
}

void cargar_tablero(Carta Mazo_desordenado[52], Carta tablero[7][7])
{
    int i, j, c = 0;
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 7; j++)
        {
            if (i <= j)
            {
                tablero[i][j] = Mazo_desordenado[c];
                c++;
            }
        }
    }
}

void imprimir_tablero(Carta tablero[7][7])
{
    int i, j;
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 7; j++)
        {
            if (i <= j)
            {
                imprimir_carta(tablero[i][j]);
            }
            printf("\t");
        }
        printf("\n");
    }
}

int encuentra_guion(char string[])
{
    int pos = 0, len;
    len = strlen(string);
    while ((string[pos] != '-') && (len > 1))
        pos++;

    return pos;
}

void imprimir_accion(char string[])
{
    int pos, longitud, po, pd;
    char origen, destino;
    pos = encuentra_guion(string);
    longitud = strlen(string);
    switch (pos)
    {
    case 0:
        printf("se llama al mazo para cambiar carta");
        break;
    case 1:
        if (longitud == 3)
        {
            sscanf(string, "%c-%c", &origen, &destino);
            printf("se pasa de mazo a palo ordenado, Mazo a palo:%c ", destino);
            break;
        }
        else
        {
            sscanf(string, "%c-%c%d", &origen, &destino, &pd);
            if (origen == 'M')
            {
                printf("se pasa de Mazo a Columna:%c fila:%d", destino, pd);
            }
            else
            {
                printf("se pasa de Palo:%c a Columna:%c fila:%d", origen, destino, pd);
            }
        }
        break;
    case 2:
        if (longitud == 4)
        {
            sscanf(string, "%c%d-%c", &origen, &po, &destino);
            printf("se pasa de tablero columna:%c fila:%d a palo:%c", origen, po, destino);
        }
        else
        {
            sscanf(string, "%c%d-%c%d", &origen, &po, &destino, &pd);
            printf("se pasa de columna:%c fila:%d a columna:%c fila:%d", origen, po, destino, pd);
        }
        break;
    case 3:
        if (longitud == 5)
        {
            sscanf(string, "%c%d-%c", &origen, &po, &destino);
            printf("se pasa de tablero columna:%c fila:%d a palo:%c", origen, po, destino);
        }
        else
        {
            sscanf(string, "%c%d-%c%d", &origen, &po, &destino, &pd);
            printf("se pasa de columna:%c fila:%d a columna:%c fila:%d", origen, po, destino, pd);
        }
    }
}

bool es_valido(char *movimiento)
{
    // Verifica longitud mínima (caso "M")
    if (strlen(movimiento) == 1)
    {
        return movimiento[0] == 'M';
    }

    // Verifica longitud válida para los otros casos
    if (strlen(movimiento) < 3 || strlen(movimiento) > 5)
    {
        return false;
    }

    // Verifica primer carácter (columna o mazo)
    if (!((movimiento[0] >= 'A' && movimiento[0] <= 'G') ||
          movimiento[0] == 'M' ||
          movimiento[0] == 'P' ||
          movimiento[0] == 'T' ||
          movimiento[0] == 'R' ||
          movimiento[0] == 'S'))
    {
        return false;
    }

    // Verifica el guión
    if (movimiento[1] != '-')
    {
        return false;
    }

    // Verifica la columna de destino y fila
    if (movimiento[2] >= 'A' && movimiento[2] <= 'G')
    {
        // Verifica la fila (puede ser 1 o 2 dígitos)
        int fila = atoi(&movimiento[3]);
        if (fila < 1 || fila > 19)
        {
            return false;
        }
    }
    else if (movimiento[2] == 'P' || movimiento[2] == 'T' ||
             movimiento[2] == 'R' || movimiento[2] == 'S')
    {
        // No se necesita verificar la fila para P, T, R, S
        return true;
    }
    else
    {
        return false;
    }

    return true;
}

void capturar(char string[])
{
    printf("posicion: ");
    scanf("%s", string);
    getchar();
    printf("%d\n", es_valido(string));
}

int main()
{
    char string[8];
    int i;

    while (true)
    {
        capturar(string);
        imprimir_accion(string);
        printf("\n");
    }
    return 0;
}

// int main()
// {
//     srand(time(NULL));

//     Carta Mazo[52];
//     Carta Mazo_desordenado[52];
//     Carta tablero[7][7];

//     cargar_mazo(Mazo);
//     mezclar(Mazo, Mazo_desordenado);

//     cargar_tablero(Mazo_desordenado, tablero);
//     imprimir_tablero(tablero);

//     char string[8];
//     int i;

//     for (i = 0; i < 4; i++)
//     {
//         capturar(string);
//         imprimir_accion(string);
//         printf("\n");
//     }
//     return 0;
// }