/*
 * Trabajo práctico Nro. 1
 * Ordenamiento de cables
 * Integrantes:
 * 	1. Juan Mendoza
 *	2. Alan Vera
 *  	3. Franco Portillo
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h> // para windows, include <windows.h> y Sleep(1000); 1000 ms

void proceso();
int numero_aleatorio(int min, int max);
void generar_cables(int vector[], int longitud);
bool vector_contiene(int elemento, int vector[], int longitud);
void imprimir_vector(int vector[], int longitud);
void imprimir_cables(int vector[], int longitud);
void ordenar_burbuja(int vector[], int longitud);
void limpiar_pantalla();
int menu();

int main()
{
	srand(time(NULL));
	proceso();
	return 0;
}

void proceso() 
{
	int cant_cables = 20;
	int vector[cant_cables];
	generar_cables(vector, cant_cables);
//	imprimir_cables(vector, cant_cables);	
	ordenar_burbuja(vector, cant_cables);
	// imprimir_cables(vector, cant_cables);
}

void generar_cables(int vector[], int longitud)
{
	int valores_generados[longitud];
	int i;
	for (i = 0; i < 20; i++)
	{
		do
		{
			vector[i] = numero_aleatorio(1, 35);
		}while(vector_contiene(vector[i], valores_generados, longitud));
		valores_generados[i] = vector[i];
	}

}

bool vector_contiene(int elemento, int vector[], int longitud)
{
	int i;
	for (i = 0; i < longitud; i++)
	{
		if (vector[i] == elemento)
		{
			return true;
		}
	}
	return false;
}

int numero_aleatorio(int min, int max)
{
	return (rand() % max - min + 1) + min;
}

void imprimir_vector(int vector[], int longitud)
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

void imprimir_cables(int vector[], int longitud)
{
	int i, j;	
	char caracter = '*';

	for(i = 0; i < longitud; i++)
	{
		for(j = 0; j < vector[i]; j++)
		{
			printf("%c", caracter);	
		}	
		printf(" %d\n", vector[i]);
	}
}

void ordenar_burbuja(int vector[], int longitud)
{
	int i, j, aux, pasos = 0;
	for(i = 0; i < longitud - 1; i++)
	{
		for(int j = 0; j < longitud - i - 1; j++)
		{
			if(vector[j] > vector[j + 1])	
			{
				aux = vector[j];
				vector[j] = vector[j + 1];
				vector[j + 1] = aux;
				pasos++;
			}
			limpiar_pantalla();
			imprimir_cables(vector, longitud);
			usleep(50000);
		}
	}
	printf("Ordenado en %d pasos\n", pasos);	
}

void limpiar_pantalla()
{
	system("clear"); // para windows system("cls"
}
