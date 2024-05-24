/*
 * Dado un vector de 5 a 15 elementos (generados al azar) cargue con números enteros de tres
 * dígitos generados al azar, una vez cargado el vector imprímalo, luego ordénelo de menor a mayor
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int numero_aleatorio(int min, int max);
void cargar_vector(int longitud, int vector[]);
void imprimir_vector(int longitud, int vector[]);
void ordenar_vector(int longitud, int vector[]);

int main()
{
    srand(time(NULL)); // inicialización
    printf("Generando un vector de longitud aleatoria (entre 5 y 15)...\n");
    int longitud = numero_aleatorio(5, 15);
    printf("Longitud: %d\n", longitud);
    int vector[longitud];
    cargar_vector(longitud, vector);
    printf("Vector antes de ordenar:\n");
    imprimir_vector(longitud, vector);
    ordenar_vector(longitud, vector);
    printf("Vector despues de ordenar:\n");
    imprimir_vector(longitud, vector);
    return 0;
}

int numero_aleatorio(int min, int max)
{
    int num = (rand() % (max - min + 1)) + min;
    return num;
}

void cargar_vector(int longitud, int vector[])
{
    int i;
    for (i = 0; i < longitud; i++)
    {
        vector[i] = numero_aleatorio(100, 999);
    }
}

void imprimir_vector(int longitud, int vector[])
{
    int i = 0;
    printf("[");
    while (i < longitud)
    {
        printf("%d ", vector[i]);
        i++;
    }
    printf("]\n");
}

void ordenar_vector(int longitud, int vector[])
{
    int aux;
    for (int i = 0; i < longitud; i++)
    {
        for (int j = 0; j < longitud; j++)
        {
            if (vector[i] < vector[j])
            {
                aux = vector[i];
                vector[i] = vector[j];
                vector[j] = aux;
            }
        }
    }
}
