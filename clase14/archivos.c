/**
 * Dado las 10 palabras generadas al azar cuya longitud mínima de la palabra es 6 caracteres y 10 máximas,
 * cargue las 10 palabras en un archivo, luego ordene las 10 palabras y luego cargue en el mismo archivo la
 * lista de palabras ordenada de manera descendente
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generarPalabraAleatoria(char *palabra, int longitud);
void escribirPalabras(FILE *file, char palabras[][30], int num_palabras);
void leerPalabras(FILE *file, char palabras[][30], int num_palabras);
void ordenarPalabras(char palabras[][30], int num_palabras);
int proceso();

int main()
{
    srand(time(NULL));
    proceso();
    return 0;
}

int proceso()
{

    char archivo[] = "palabras.txt";
    char palabras[10][30];

    int i;
    for (i = 0; i < 10; i++)
    {
        int longitud = 6 + rand() % 5;
        generarPalabraAleatoria(palabras[i], longitud);
    }

    FILE *file = fopen(archivo, "w");
    if (file == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    escribirPalabras(file, palabras, 10);
    fclose(file);

    file = fopen(archivo, "r");
    if (file == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    leerPalabras(file, palabras, 10);
    fclose(file);

    ordenarPalabras(palabras, 10);

    file = fopen(archivo, "a");
    if (file == NULL)
    {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    escribirPalabras(file, palabras, 10);
    fclose(file);
}

void generarPalabraAleatoria(char *palabra, int longitud)
{
    int i;
    char caracteres[] = "abcdefghijklmnopqrstuvwxyz";
    for (i = 0; i < longitud; i++)
    {
        int key = rand() % (int)(sizeof(caracteres) - 1);
        palabra[i] = caracteres[key];
    }
    palabra[longitud] = '\0';
}

void escribirPalabras(FILE *file, char palabras[][30], int num_palabras)
{
    int i;
    for (i = 0; i < num_palabras; i++)
    {
        fprintf(file, "%s\n", palabras[i]);
    }
    fprintf(file, "-----------\n");
}

void leerPalabras(FILE *file, char palabras[][30], int num_palabras)
{
    int i;
    for (i = 0; i < num_palabras; i++)
    {
        if (fscanf(file, "%s", palabras[i]) == EOF)
            break;
    }
}

void ordenarPalabras(char palabras[][30], int num_palabras)
{
    char temp[30];
    int i, j;
    for (i = 0; i < num_palabras - 1; i++)
    {
        for (j = i + 1; j < num_palabras; j++)
        {
            if (strcmp(palabras[i], palabras[j]) < 0)
            {
                strcpy(temp, palabras[i]);
                strcpy(palabras[i], palabras[j]);
                strcpy(palabras[j], temp);
            }
        }
    }
}
