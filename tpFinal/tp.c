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
    int oculto;
    int color; /* 0 es rojo, 1 es negro */
    char impresion[4];
} Carta;

typedef struct
{
    Carta cartas[13];
    int tope;
} Palo;

void inicializar_mazo_ordenado(Palo *mazo)
{
    mazo->tope = -1;
}

void mover_mazo_a_tablero(Carta mazo_desordenado[], int *indice_mazo, Carta tablero[7][19], int columna, int fila)
{
    while (mazo_desordenado[*indice_mazo].estado == 2)
        (*indice_mazo)++;
    if (*indice_mazo < 52)
    {
        tablero[columna][fila] = mazo_desordenado[*indice_mazo];
        tablero[columna][fila].oculto = 0;
        mazo_desordenado[*indice_mazo].estado = 2;
        (*indice_mazo)++;
    }
}

void mover_mazo_a_ordenado(Carta mazo_desordenado[], int *indice_mazo, Palo *mazo_ordenado)
{
    while (mazo_desordenado[*indice_mazo].estado == 2)
        (*indice_mazo)++;
    if (*indice_mazo < 52)
    {
        mazo_ordenado->cartas[++(mazo_ordenado->tope)] = mazo_desordenado[*indice_mazo];
        mazo_desordenado[*indice_mazo].estado = 2;
        (*indice_mazo)++;
    }
}

void mover_tablero_a_ordenado(Carta tablero[7][19], int col, int fila, Palo *mazo_ordenado)
{
    if (tablero[col][fila].valor != -1)
    {
        mazo_ordenado->cartas[++(mazo_ordenado->tope)] = tablero[col][fila];
        tablero[col][fila].valor = -1;
        mazo_ordenado->cartas[mazo_ordenado->tope].estado = 2;
        if (fila > 0 && tablero[col][fila - 1].valor != -1)
        {
            tablero[col][fila - 1].oculto = 0;
        }
    }
}

void mover_tablero_a_tablero(Carta tablero[7][19], int col_origen, int fila_origen, int col_destino, int fila_destino)
{
    if (tablero[col_origen][fila_origen].valor != -1)
    {
        tablero[col_destino][fila_destino] = tablero[col_origen][fila_origen];
        tablero[col_origen][fila_origen].valor = -1;

        if (fila_origen > 0 && tablero[col_origen][fila_origen - 1].valor != -1)
        {
            tablero[col_origen][fila_origen - 1].oculto = 0;
        }
    }
}

void mover_ordenado_a_tablero(Palo *mazo_ordenado, Carta tablero[7][19], int col, int fila)
{
    if (mazo_ordenado->tope >= 0)
    {
        tablero[col][fila] = mazo_ordenado->cartas[(mazo_ordenado->tope)--];
        tablero[col][fila].oculto = 0;
        tablero[col][fila].estado = 2;
    }
}

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
    char palos[] = {'P', 'T', 'C', 'D'}; // Picas, Tréboles, Corazones, Diamantes

    for (i = 0; i < 4; i++) // Iteramos sobre los palos
    {
        for (j = 1; j <= 13; j++) // Iteramos sobre los valores de las cartas
        {
            Mazo[c].valor = j;
            Mazo[c].palo = palos[i];
            Mazo[c].estado = 0;
            Mazo[c].oculto = 1;

            if (i <= 1) // Los dos primeros palos (Picas y Tréboles) son negros
            {
                Mazo[c].color = 1;
            }
            else // Los dos últimos palos (Corazones y Diamantes) son rojos
            {
                Mazo[c].color = 0;
            }

            if (j == 1 || j >= 11)
            {
                sprintf(Mazo[c].impresion, "%c%c", letra(j), palos[i]);
            }
            else
            {
                sprintf(Mazo[c].impresion, "%d%c", j, palos[i]);
            }

            c++;
        }
    }
}

/*void cargar_mazo(Carta Mazo[])
{
    int i, j, c = 0;
    char palos[] = {'♠', '♣', '♥', '♦'}; // Picas, Tréboles, Corazones, Diamantes

    for (i = 0; i < 4; i++) // Iteramos sobre los palos
    {
        for (j = 1; j <= 13; j++) // Iteramos sobre los valores de las cartas
        {
            Mazo[c].valor = j;
            Mazo[c].palo = palos[i];
            Mazo[c].estado = 0;
            Mazo[c].oculto = 1;

            if (i <= 1) // Los dos primeros palos (Picas y Tréboles) son negros
            {
                Mazo[c].color = 1;
            }
            else // Los dos últimos palos (Corazones y Diamantes) son rojos
            {
                Mazo[c].color = 0;
            }

            if (j == 1 || j >= 11)
            {
                sprintf(Mazo[c].impresion, "%c%c", letra(j), palos[i]);
            }
            else
            {
                sprintf(Mazo[c].impresion, "%d%c", j, palos[i]);
            }

            c++;
        }
    }
}*/

void mezclar(Carta Mazo[], Carta Mazo_desordenado[])
{
    int i, r;
    for (i = 0; i < 52; i++)
    {
        Mazo[i].estado = 0;
    }

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
    if (carta.valor == -1) {
        printf(" \t");
        return;
    }

    if (carta.oculto == 1)
    {
        printf("#\t");
    }
    else
    {
        char *color = carta.color == 0 ? RED : BLK;
        printf("%s%s%s\t", color, carta.impresion, COLOR_RESET);
    }
}

void cargar_tablero(Carta Mazo_desordenado[52], Carta tablero[7][19])
{
    int i, j, c = 0;
    for (i = 0; i < 7; i++)
    {
        for (j = 0; j <= i; j++)
        {
            while (Mazo_desordenado[c].estado == 2)
                c++;
            tablero[i][j] = Mazo_desordenado[c];
            tablero[i][j].oculto = (j == i) ? 0 : 1;
            Mazo_desordenado[c].estado = 2;
            c++;
        }
        for (j = i + 1; j < 19; j++)
        {
            tablero[i][j].valor = -1;
        }
    }
}

void imprimir_tablero(Carta tablero[7][19], Carta mazo_desordenado[52], int indice_mazo, Palo palos[4])
{
    int i, j;

    printf("\tM\tP\tT\tR\tS\n");
    printf("\t");

    if (indice_mazo < 52)
    {
        mazo_desordenado[indice_mazo].oculto = 0;
        imprimir_carta(mazo_desordenado[indice_mazo]);
    }
    else
    {
        printf(" \t");
    }

    // Imprimir el estado de los mazos ordenados P, T, R, S
    for (i = 0; i < 4; i++) {
        if (palos[i].tope >= 0) {
            imprimir_carta(palos[i].cartas[palos[i].tope]);
        } else {
            printf(" \t");
        }
    }
    printf("\n\n");
    
    printf("   A\tB\tC\tD\tE\tF\tG\n");

    for (j = 0; j < 19; j++)
    {
        printf("%2d ", j + 1);

        for (i = 0; i < 7; i++)
        {
            if (tablero[i][j].valor != -1)
            {
                imprimir_carta(tablero[i][j]);
            }
            else
            {
                printf("\t");
            }
        }
        printf("\n");
    }
}
/*void imprimir_tablero(Carta tablero[7][19], Carta mazo_desordenado[52], int indice_mazo)
{
    int i, j;

    printf("\tM\t\tP\tT\tR\tS\n");
    printf("\t");
    if (indice_mazo < 52)
    {
        mazo_desordenado[indice_mazo].oculto = 0;
        imprimir_carta(mazo_desordenado[indice_mazo]);
    }
    printf("\n\n");
    printf("   A\tB\tC\tD\tE\tF\tG\n");

    for (j = 0; j < 19; j++)
    {
        printf("%2d ", j + 1);

        for (i = 0; i < 7; i++)
        {
            if (tablero[i][j].valor != -1)
            {
                imprimir_carta(tablero[i][j]);
            }
            else
            {
                printf("\t");
            }
        }
        printf("\n");
    }
}*/

int encuentra_guion(char string[])
{
    int pos = 0, len;
    len = strlen(string);
    while ((string[pos] != '-') && (len > 1))
    {
        pos++;
    }

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

bool validar_ingreso(char *movimiento)
{
    int len = strlen(movimiento);
    if (len == 1)
    {
        return movimiento[0] == 'M';
    };

    if (len < 3 || len > 7)
    {
        return false;
    }

    if (!((movimiento[0] >= 'A' && movimiento[0] <= 'G') ||
          movimiento[0] == 'M' ||
          movimiento[0] == 'P' ||
          movimiento[0] == 'T' ||
          movimiento[0] == 'R' ||
          movimiento[0] == 'S'))
    {
        return false;
    }

    char *guion = strchr(movimiento, '-');
    if (guion == NULL)
    {
        return false;
    }

    int pos_guion = guion - movimiento;
    if (movimiento[0] >= 'A' && movimiento[0] <= 'G')
    {
        if (pos_guion == 1 || !isdigit(movimiento[1]))
        {
            return false;
        }
        int fila_origen = atoi(movimiento + 1);
        if (fila_origen < 1 || fila_origen > 19)
        {
            return false;
        }
    }
    else if (movimiento[0] == 'M' || movimiento[0] == 'P' || movimiento[0] == 'T' || movimiento[0] == 'R' || movimiento[0] == 'S')
    {
        if (pos_guion != 1)
        {
            return false;
        }
    }

    char destino = *(guion + 1);
    if (!((destino >= 'A' && destino <= 'G') ||
          destino == 'P' || destino == 'T' ||
          destino == 'R' || destino == 'S'))
    {
        return false;
    }

    char *fila_str = guion + 2;
    int fila = atoi(fila_str);
    if (destino >= 'A' && destino <= 'G')
    {
        if (fila < 1 || fila > 19)
        {
            return false;
        }
    }
    else
    {
        if (fila != 0)
        {
            return false;
        }
    }

    return true;
}

void capturar(char string[])
{
    printf("posicion: ");
    scanf("%s", string);
    getchar();
}

int juego(Carta Mazo[52], Carta Mazo_desordenado[52], Carta tablero[7][19], Palo palos[4])
{
    char string[8];
    int indice_mazo = 0;
    int juego_finalizado = 0;
    while (!juego_finalizado)
    {
        capturar(string);
        if (!validar_ingreso(string))
        {
            printf("El movimiento %s no es valido.\n", string);
            continue;
        }
        if (strcmp(string, "M") == 0)
        {
            indice_mazo++;
        }
        else if (string[0] == 'M' && string[1] == '-')
        {
            if (string[2] == 'P' || string[2] == 'T' || string[2] == 'R' || string[2] == 'S')
            {
                mover_mazo_a_ordenado(Mazo_desordenado, &indice_mazo, &palos[string[2] - 'P']);
            }
            else
            {
                int col = string[2] - 'A';
                int fila = atoi(&string[3]) - 1;
                mover_mazo_a_tablero(Mazo_desordenado, &indice_mazo, tablero, col, fila);
            }
        }
        else if (string[0] >= 'A' && string[0] <= 'G')
        {
            int col_origen = string[0] - 'A';
            int fila_origen = atoi(&string[1]) - 1;
            if (string[2] == '-')
            {
                if (string[3] == 'P' || string[3] == 'T' || string[3] == 'R' || string[3] == 'S')
                {
                    mover_tablero_a_ordenado(tablero, col_origen, fila_origen, &palos[string[3] - 'P']);
                }
                else
                {
                    int col_destino = string[3] - 'A';
                    int fila_destino = atoi(&string[4]) - 1;
                    mover_tablero_a_tablero(tablero, col_origen, fila_origen, col_destino, fila_destino);
                }
            }
        }
        else if (string[0] == 'P' || string[0] == 'T' || string[0] == 'R' || string[0] == 'S')
        {

            int col = string[2] - 'A';
            int fila = atoi(&string[3]) - 1;
            mover_ordenado_a_tablero(&palos[string[0] - 'P'], tablero, col, fila);
        }

        printf("indice mazo %d\n", indice_mazo);
        imprimir_accion(string);
        printf("\n");
        imprimir_tablero(tablero, Mazo_desordenado, indice_mazo, palos);
    }
}

int main()
{
    srand(time(NULL));

    Carta Mazo[52];
    Carta Mazo_desordenado[52];
    Carta tablero[7][19];
    Palo palos[4];

    cargar_mazo(Mazo);
    mezclar(Mazo, Mazo_desordenado);

    cargar_tablero(Mazo_desordenado, tablero);
    int i;
    for (i = 0; i < 4; i++)
    {
        inicializar_mazo_ordenado(&palos[i]);
    }
    
    
    imprimir_tablero(tablero, Mazo_desordenado, 28, palos);

    juego(Mazo, Mazo_desordenado, tablero, palos);

    return 0;
}