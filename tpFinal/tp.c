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

bool validar_movimiento(Carta origen, Carta destino, bool es_pila) {
    if (es_pila) {
        // Validación para pilas (P, R, S, T)
        if (origen.valor == 1) {
            // As se puede colocar en una pila vacía
            return destino.valor == -1;  // Pila vacía
        } else if (destino.valor == -1 || destino.valor == origen.valor - 1) {
            // La carta debe ser 1 mayor que la carta superior en la pila
            return origen.valor == destino.valor + 1;
        }
        return false;
    } else {
        // Validación para movimiento entre columnas
        return origen.color != destino.color && origen.valor == destino.valor + 1;
    }
}

void realizar_movimiento(char string[], Carta tablero[7][19], Carta mazo_ordenado[4][13], Carta mazo_desordenado[52])
{
    int pos, po, pd;
    char origen, destino;
    pos = encuentra_guion(string);

    switch (pos)
    {
    case 0:
        // Movimiento del mazo desordenado al tablero
        sscanf(string, "%c-%c%d", &origen, &destino, &pd);
        if (origen == 'M' && destino >= 'A' && destino <= 'G') {
            int columna = destino - 'A';
            for (int i = 0; i < 52; i++) {
                if (mazo_desordenado[i].estado == 0) {
                    tablero[columna][pd - 1] = mazo_desordenado[i];
                    mazo_desordenado[i].estado = 1;
                    break;
                }
            }
        }
        break;
    case 1:
        // Movimiento del mazo ordenado a las pilas P, T, R, S
        sscanf(string, "%c-%c%d", &origen, &destino, &pd);
        if (origen >= 'A' && origen <= 'G' && destino >= 'P' && destino <= 'S') {
            int columna = origen - 'A';
            int pila = destino - 'P';
            if (tablero[columna][pd - 1].estado == 1) {
                mazo_ordenado[pila][pd - 1] = tablero[columna][pd - 1];
                tablero[columna][pd - 1].estado = 0;
            }
        }
        break;
    case 2:
        // Movimiento entre columnas del tablero
        sscanf(string, "%c%d-%c%d", &origen, &po, &destino, &pd);
        if (origen >= 'A' && origen <= 'G' && destino >= 'A' && destino <= 'G') {
            int col_origen = origen - 'A';
            int col_destino = destino - 'A';
            if (validar_movimiento_columna(tablero, col_origen, po - 1, col_destino, pd - 1)) {
                intercambiar(&tablero[col_origen][po - 1], &tablero[col_destino][pd - 1]);
            }
        }
        break;
    case 3:
        // Movimiento entre una columna y una pila (P, T, R, S)
        sscanf(string, "%c%d-%c", &origen, &po, &destino);
        if (origen >= 'A' && origen <= 'G' && destino >= 'P' && destino <= 'S') {
            int columna = origen - 'A';
            int pila = destino - 'P';
            if (validar_movimiento_pila(tablero, columna, po - 1, pila)) {
                mazo_ordenado[pila][0] = tablero[columna][po - 1];
                tablero[columna][po - 1].estado = 0;
            }
        }
        break;
    }
}

bool validar_movimiento_columna(Carta tablero[7][19], int col_origen, int fila_origen, int col_destino, int fila_destino) {
    if (tablero[col_origen][fila_origen].valor == -1 || tablero[col_destino][fila_destino].valor == -1) {
        return false; // Si alguna de las cartas no es válida, no se puede mover
    }

    return (tablero[col_origen][fila_origen].valor == tablero[col_destino][fila_destino].valor + 1 &&
            tablero[col_origen][fila_origen].color != tablero[col_destino][fila_destino].color);
}

bool validar_movimiento_pila(Carta tablero[7][19], int columna, int fila, int pila) {
    if (tablero[columna][fila].valor == -1) {
        return false; // No hay carta para mover
    }

    return (mazo_ordenado[pila][0].valor == tablero[columna][fila].valor + 1 || mzo_ordenado[pila][0].valor == 0); // Requiere que la pila esté vacía o que sea 1 mayor
}

int main()
{
    srand(time(NULL));

    Carta Mazo[52];
    Carta mazo_desordenado[52]; // Declarar mazo_desordenado aquí
    Carta tablero[7][19];
    Carta mazo_ordenado[4][13] = {{{0}}}; // Inicializar el mazo ordenado

    cargar_mazo(Mazo);
    mezclar(Mazo, mazo_desordenado); // Esta función mezcla en el mazo_desordenado

    cargar_tablero(mazo_desordenado, tablero);
    imprimir_tablero(tablero);

    char string[8];
    int i;

    for (i = 0; i < 4; i++)
    {
        capturar(string);
        imprimir_accion(string);
        realizar_movimiento(string, tablero, mazo_ordenado, mazo_desordenado); // Llama a la función para realizar el movimiento
        imprimir_tablero(tablero); // Mostrar el estado del tablero después del movimiento
        printf("\n");
    }
    return 0;
}