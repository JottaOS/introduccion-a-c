/**
 * Dado un vector de 25  elementos que contiene strings como elementos, donde los strings tienen una longitud fija
 * 15 letras generadas las lettras al azar, una vez cargadas las palabras imprima el vector de strings,
 * luego ordénelo y vuelva a imprimirlo
 *
 * Alumno: Juan Mendoza
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimirVector(char vector[][15], int longitud)
{
    printf("[\n");
    int i;
    for (i = 0; i < longitud; i++)
    {
        printf("\t%s,\n", vector[i]);
    }
    printf("]\n");
}

void ordenarVector(char vector[][15], int longitud)
{
    int i, j;
    for (i = 0; i < longitud - 1; i++)
    {
        for (j = 0; j < longitud - i - 1; j++)
        {
            if (strcmp(vector[j], vector[j + 1]) > 0)
            {
                char temp[15];
                strcpy(temp, vector[j]);
                strcpy(vector[j], vector[j + 1]);
                strcpy(vector[j + 1], temp);
            }
        }
    }
}

int proceso()
{
    char vector[25][15];
    int i, j;
    for (i = 0; i < 25; i++)
    {
        for (j = 0; j < 14; j++)
        {
            vector[i][j] = 'A' + rand() % 26;
        }
        vector[i][14] = '\0';
    }

    printf("Vector antes de ordenar: \n");
    imprimirVector(vector, 25);

    ordenarVector(vector, 25);

    printf("Vector ordenado:\n");
    imprimirVector(vector, 25);

    return 0;
}

int main()
{
    proceso();
    return 0;
}