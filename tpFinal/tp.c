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

typedef struct info_movimiento
{
    Carta carta_origen;
    Carta carta_destino;
    char tipo_movimiento; /* T para tablero, P para palos */
    int origen[2];
    int destino[2];
} InfoMovimiento;

void inicializar_mazo_ordenado(Palo *mazo)
{
    mazo->tope = -1;
}

void obtener_tope_palo(Carta *carta_tope, Palo palos[4], int indice)
{
    Palo palo = palos[indice];
    if (palo.tope == -1)
        carta_tope->valor = -1;
    else
        *carta_tope = palo.cartas[palo.tope];
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

    for (i = 3; i <= 6; i++)
    {
        for (j = 1; j <= 13; j++)
        {
            Mazo[c].valor = j;
            Mazo[c].palo = i;
            Mazo[c].estado = 0;
            Mazo[c].oculto = 1;

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
            tablero[i][j].color = -1;
        }
    }
}

void debug_mazo_desordenado(Carta mazo[52])
{
    int i;
    printf("Mazo desordenado\n[ ");
    for (i = 0; i < 52; i++)
    {
        if (mazo[i].estado != 2)
        {

            char *color = mazo[i].color == 0 ? RED : BLK;
            printf("%s%s%s, ", color, mazo[i].impresion, COLOR_RESET);
        }
    }
    printf("]\n");
}

void imprimir_tablero(Carta tablero[7][19], Carta mazo_desordenado[52], int indice_mazo, Palo palos[4])
{
    int i, j;

    printf("\tM\t\tP\tT\tR\tS\n");
    printf("\t");
    if (indice_mazo < 52)
    {
        mazo_desordenado[indice_mazo].oculto = 0;
        imprimir_carta(mazo_desordenado[indice_mazo]);
    }

    printf(" \t");
    for (i = 0; i < 4; i++)
    {
        Carta tope_palo;
        obtener_tope_palo(&tope_palo, palos, i);
        if (tope_palo.valor != -1)
            imprimir_carta(tope_palo);
        else
            printf("-\t");
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

InfoMovimiento obtener_info_movimiento(char *string, Carta tablero[7][19], Carta mazo_desordenado[52], Palo palos[4], int indice_mazo)
{
    char primer_caracter = string[0];
    InfoMovimiento info;

    int posicion_origen, posicion_destino;
    int pos = encuentra_guion(string);
    int longitud = strlen(string);
    char origen, destino;

    switch (pos)
    {
    case 1:
        if (longitud == 3)
        {
            sscanf(string, "%c-%c", &origen, &destino);
            info.tipo_movimiento = 'P';
        }
        else
        {
            sscanf(string, "%c-%c%d", &origen, &destino, &posicion_destino);
            info.tipo_movimiento = 'T';
        }
        break;
    case 2:
        if (longitud == 4)
        {
            sscanf(string, "%c%d-%c", &origen, &posicion_origen, &destino);
            info.tipo_movimiento = 'P';
        }
        else
        {
            sscanf(string, "%c%d-%c%d", &origen, &posicion_origen, &destino, &posicion_destino);
            info.tipo_movimiento = 'T';
        }
        break;
    case 3:
        if (longitud == 5)
        {
            sscanf(string, "%c%d-%c", &origen, &posicion_origen, &destino);
            info.tipo_movimiento = 'P';
        }
        else
        {
            sscanf(string, "%c%d-%c%d", &origen, &posicion_origen, &destino, &posicion_destino);
            info.tipo_movimiento = 'T';
        }
    }

    int fila = 0, columna = 0;

    if (primer_caracter == 'M')
    {
        // todo: corregir esto para incluir el caso de M a Palo
        info.carta_origen = mazo_desordenado[indice_mazo];
        info.destino[0] = posicion_destino - 1;
        info.destino[1] = destino - 'A';

        info.carta_destino = tablero[info.destino[1]][info.destino[0]];
        return info;
    }

    if (primer_caracter >= 'A' && primer_caracter <= 'G')
    {
        columna = primer_caracter - 'A';
        fila = posicion_origen - 1;

        info.carta_origen = tablero[columna][fila];
        info.origen[0] = fila;
        info.origen[1] = columna;

        info.destino[0] = posicion_destino - 1;
        info.destino[1] = destino - 'A';

        info.carta_destino = tablero[info.destino[1]][info.destino[0]];
        return info;
    }

    /* todo: corregir despues
        int indice_palo =
            primer_caracter == 'P'   ? 0
            : primer_caracter == 'T' ? 1
            : primer_caracter == 'R' ? 2
            : primer_caracter == 'S' ? 3
                                     : -1;

        // todo: el tope se inicializa con -1, queda pendiente ver como se actualiza el tope al mover a un palo
        return palos[indice_palo].cartas[palos->tope + 1];

    */
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

int validar_movimiento_tablero(InfoMovimiento *movimiento, Carta tablero[7][19])
{

    // las posiciones son vectores de 2 elementos que representan la fila y la columna del tablero
    int fila_destino = movimiento->destino[0];
    int columna_destino = movimiento->destino[1];

    Carta carta_anterior = tablero[columna_destino][fila_destino - 1];

    // validar que la carta no esté oculta
    if (movimiento->carta_origen.oculto)
    {
        printf("La carta esta oculta\n");
        return 0;
    }

    // no hay ninguna carta de origen
    if (movimiento->carta_origen.valor == -1)
    {
        printf("No hay una carta en la posicion de origen\n");
        return 0;
    }

    // que no reemplace una carta (la posicion de destino no está vacía)
    if (movimiento->carta_destino.valor != -1)
    {
        printf("Ya existe una carta en esa posicion\n");
        return 0;
    }

    // en caso de que la fila_destino sea 0, verificar que la carta que se pretende mover sea king
    if (fila_destino == 0)
    {
        if (movimiento->carta_origen.valor != 13)
        {

            printf("La carta debe ser King para mover a una columna vacia\n");
            return 0;
        }

        // ya no es necesario continuar con las validaciones de aquí en adelante, para este caso
        return 1;
    }

    // verificar que en tablero[fila_destino - 1][columna_destino] exista una carta
    if (carta_anterior.valor == -1)
    {
        printf("El espacio previo al destino esta vacio\n");
        return 0;
    }

    // la carta debe ser del color opuesto (si mi carta es roja, la otra debe ser negra y viceversa)
    // valores de colores: rojo = 0, negro = 1
    if (carta_anterior.color == movimiento->carta_origen.color)
    {
        printf("Ambos colores son iguales\n");
        return 0;
    }

    // el valor de la carta en la posicion tablero[fila_destino - 1][columna_destino] debe tener valor de nuestra carta de origen + 1.
    if (carta_anterior.valor != movimiento->carta_origen.valor + 1)
    {
        printf("El valor de la carta anterior debe ser igual a %d pero es %d\n", movimiento->carta_origen.valor + 1, carta_anterior.valor);
        return 0;
    }

    return 1;
}
// todo: borrar, esto es solo para debug
void imprimirInfoMovimiento(const InfoMovimiento *movimiento)
{
    printf("** DEBUG **\n");
    // Imprimir información de la carta
    printf("Carta origen: ");
    imprimir_carta(movimiento->carta_origen);
    printf("\n");
    printf("Carta destino: ");
    imprimir_carta(movimiento->carta_destino);
    printf("\n");
    // Imprimir tipo de movimiento
    printf("Tipo de movimiento: %c\n", movimiento->tipo_movimiento);
    // Imprimir origen
    printf("Origen: [%d, %d]\n", movimiento->origen[0], movimiento->origen[1]);
    // Imprimir destino
    printf("Destino: [%d, %d]\n", movimiento->destino[0], movimiento->destino[1]);
}

void imprimir_carta_log(FILE *f, Carta carta)
{
    fprintf(f, "%-8s", carta.impresion);
}

void imprimir_tablero_log(FILE *f, Carta tablero[7][19], Carta mazo_desordenado[52], int indice_mazo)
{
    int i, j;

    fprintf(f, "\tM\t\tP\tT\tR\tS\n");
    fprintf(f, "\t");
    if (indice_mazo < 52)
    {
        imprimir_carta_log(f, mazo_desordenado[indice_mazo]);
    }
    fprintf(f, "\n\n");
    fprintf(f, "   A       B       C       D       E       F       G\n");

    for (j = 0; j < 19; j++)
    {
        fprintf(f, "%2d ", j + 1);
        for (i = 0; i < 7; i++)
        {
            if (tablero[i][j].valor != -1)
            {
                imprimir_carta_log(f, tablero[i][j]);
            }
            else
            {
                fprintf(f, "%-8s", "");
            }
        }
        fprintf(f, "\n");
    }
    fprintf(f, "\n\n\n");
}

void escribir_log(Carta tablero[7][19], Carta mazo_desordenado[52], int indice_mazo, int nro_jugada)
{
    FILE *logfile = fopen("log.txt", "a");
    if (logfile != NULL)
    {
        fprintf(logfile, "Jugada Nro: %d\n", nro_jugada);
        imprimir_tablero_log(logfile, tablero, mazo_desordenado, indice_mazo);
        fclose(logfile);
    }
    else
    {
        perror("Error al abrir archivo de log");
    }
}

int juego(Carta Mazo[52], Carta Mazo_desordenado[52], Carta tablero[7][19], Palo palos[4])
{
    char string[8];
    int indice_mazo = 0;
    int juego_finalizado = 0;
    int nro_jugada = 0;
    do
    {
        indice_mazo++;
    } while (Mazo_desordenado[indice_mazo].estado == 2);

    printf("\n\n");
    imprimir_tablero(tablero, Mazo_desordenado, indice_mazo, palos);
    while (!juego_finalizado)
    {
        debug_mazo_desordenado(Mazo_desordenado);
        nro_jugada++;
        escribir_log(tablero, Mazo_desordenado, indice_mazo, nro_jugada);
        capturar(string);
        system("cls");
        if (!validar_ingreso(string))
        {
            printf("El movimiento %s no es valido.\n\n", string);
            imprimir_tablero(tablero, Mazo_desordenado, indice_mazo, palos);
            continue;
        }

        if (strcmp(string, "M") == 0)
        {
            do
            {
                if (indice_mazo + 1 >= 52)
                {
                    printf("Reiniciando indice mazo");
                    indice_mazo = 0; // Resetear el índice del mazo
                }
                indice_mazo++;
            } while (Mazo_desordenado[indice_mazo].estado == 2);
        }
        else
        {
            InfoMovimiento info_movimiento = obtener_info_movimiento(string, tablero, Mazo_desordenado, palos, indice_mazo);
            imprimirInfoMovimiento(&info_movimiento); // todo: esta funcion es solo de debug y se borra antes de entregar
            if (!validar_movimiento_tablero(&info_movimiento, tablero))
            {
                printf("El movimiento %s no es valido.\n\n", string);
                imprimir_tablero(tablero, Mazo_desordenado, indice_mazo, palos);
                continue;
            }
            if (string[0] == 'M' && string[1] == '-')
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
        }

        // printf("indice mazo %d\n", indice_mazo);
        // imprimir_accion(string);
        printf("\n");
        imprimir_tablero(tablero, Mazo_desordenado, indice_mazo, palos);
    }
}

bool verificar_victoria(Palo palos[4])
{
    int i;
    for (i = 0; i < 4; i++)
    {
        if (palos[i].tope != 12)
        {                 // 13 cartas, índice de la última carta es 12
            return false; // Si cualquier palo no está lleno, no hay victoria
        }
    }
    return true; // Todos los palos están llenos
}

// todo: borrar pq es para PRUEBA de CONDICION DE VICTORIA
void inicializar_palos_para_prueba(Palo palos[4])
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        palos[i].tope = 12; // Indica que hay 13 cartas (de 0 a 12)
        for (j = 0; j < 13; j++)
        {
            palos[i].cartas[j].valor = j + 1;
            palos[i].cartas[j].palo = i + 3; // Asignar un palo diferente a cada uno (P = 3, T = 4, R = 5, S = 6)
            palos[i].cartas[j].estado = 2;
            palos[i].cartas[j].oculto = 0;
            palos[i].cartas[j].color = (i < 2) ? 1 : 0;                    // Asignar colores (negro para P y T, rojo para R y S)
            sprintf(palos[i].cartas[j].impresion, "%d%c", j + 1, 'P' + i); // P, T, R, S
        }
    }
}

void proceso()
{
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
    inicializar_palos_para_prueba(palos); // todo: borrar esto pq es para prueba noma
    juego(Mazo, Mazo_desordenado, tablero, palos);
}

int main()
{
    srand(time(NULL));
    proceso();
    return 0;
}