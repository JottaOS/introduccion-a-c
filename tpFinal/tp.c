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

typedef struct
{
    Carta cartas[13];
    int top;
} MazoOrdenado;

void inicializar_mazo_ordenado(MazoOrdenado *mazo)
{
    mazo->top = -1;
}

void mover_mazo_a_tablero(Carta mazo_desordenado[], int *indice_mazo, Carta tablero[7][19], int columna, int fila)
{
    if (*indice_mazo < 52)
    {
        tablero[columna][fila] = mazo_desordenado[*indice_mazo];
        tablero[columna][fila].estado = 1; // Hacer visible la carta
        (*indice_mazo)++;
    }
}

void mover_mazo_a_ordenado(Carta mazo_desordenado[], int *indice_mazo, MazoOrdenado *mazo_ordenado)
{
    if (*indice_mazo < 52)
    {
        mazo_ordenado->cartas[++(mazo_ordenado->top)] = mazo_desordenado[*indice_mazo];
        (*indice_mazo)++;
    }
}

void mover_tablero_a_ordenado(Carta tablero[7][19], int col, int fila, MazoOrdenado *mazo_ordenado)
{
    if (tablero[col][fila].valor != -1)
    {
        mazo_ordenado->cartas[++(mazo_ordenado->top)] = tablero[col][fila];
        tablero[col][fila].valor = -1; // Marcar la carta como removida
    }
}

void mover_tablero_a_tablero(Carta tablero[7][19], int col_origen, int fila_origen, int col_destino, int fila_destino)
{
    if (tablero[col_origen][fila_origen].valor != -1)
    {
        tablero[col_destino][fila_destino] = tablero[col_origen][fila_origen];
        tablero[col_origen][fila_origen].valor = -1; // Marcar la carta como removida
    }
}

void mover_ordenado_a_tablero(MazoOrdenado *mazo_ordenado, Carta tablero[7][19], int col, int fila)
{
    if (mazo_ordenado->top >= 0)
    {
        tablero[col][fila] = mazo_ordenado->cartas[(mazo_ordenado->top)--];
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
    if (carta.estado == 0)
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
        for (j = 0; j <= i; j++) // cambiar la condición para seguir la regla del tablero
        {
            tablero[i][j] = Mazo_desordenado[c];
            tablero[i][j].estado = (j == i) ? 1 : 0; // Última carta visible, el resto ocultas
            c++;
        }
        for (j = i + 1; j < 19; j++) // llenar el resto con cartas no válidas
        {
            tablero[i][j].valor = -1; // Indicar que no hay carta
        }
    }
}

void imprimir_tablero(Carta tablero[7][19])
{
    int i, j;

    // Imprimir espacios para el mazo desordenado y las 4 pilas de mazos ordenados
    printf("   M\t\tP\tT\tR\tS\n");

    // Imprimir etiquetas de las columnas
    printf("   A\tB\tC\tD\tE\tF\tG\n");

    // Imprimir las filas del tablero
    for (j = 0; j < 19; j++)
    {
        printf("%2d ", j + 1); // Números de fila

        // Imprimir cada columna
        for (i = 0; i < 7; i++)
        {
            if (tablero[i][j].valor != -1)
            {
                imprimir_carta(tablero[i][j]); // Imprimir carta si está presente
            }
            else
            {
                printf("\t"); // Espacio si no hay carta
            }
        }
        printf("\n");
    }
}

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
    printf("Validacion: %d\n", validar_ingreso(string));
}

int main()
{
    srand(time(NULL));

    Carta Mazo[52];
    Carta Mazo_desordenado[52];
    Carta tablero[7][19];
    MazoOrdenado mazo_ordenado[4];

    cargar_mazo(Mazo);
    mezclar(Mazo, Mazo_desordenado);

    cargar_tablero(Mazo_desordenado, tablero);
    int i;
    for (i = 0; i < 4; i++)
    {
        inicializar_mazo_ordenado(&mazo_ordenado[i]);
    }

    imprimir_tablero(tablero);

    char string[8];
    int indice_mazo = 0;

    for (i = 0; i < 4; i++)
    {
        capturar(string);

        if (strcmp(string, "M") == 0)
        {
            // Mueve la siguiente carta del mazo desordenado al mazo
            indice_mazo++;
        }
        else if (string[0] == 'M' && string[1] == '-')
        {
            // Movimiento de mazo desordenado a mazo ordenado o tablero
            if (string[2] == 'P' || string[2] == 'T' || string[2] == 'R' || string[2] == 'S')
            {
                mover_mazo_a_ordenado(Mazo_desordenado, &indice_mazo, &mazo_ordenado[string[2] - 'P']);
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
            // Movimiento dentro del tablero o del tablero a mazo ordenado
            int col_origen = string[0] - 'A';
            int fila_origen = atoi(&string[1]) - 1;
            if (string[2] == '-')
            {
                if (string[3] == 'P' || string[3] == 'T' || string[3] == 'R' || string[3] == 'S')
                {
                    mover_tablero_a_ordenado(tablero, col_origen, fila_origen, &mazo_ordenado[string[3] - 'P']);
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
            // Movimiento de mazo ordenado a tablero
            int col = string[2] - 'A';
            int fila = atoi(&string[3]) - 1;
            mover_ordenado_a_tablero(&mazo_ordenado[string[0] - 'P'], tablero, col, fila);
        }

        imprimir_accion(string);
        printf("\n");
        imprimir_tablero(tablero);
    }

    return 0;
}