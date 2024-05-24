/*
 * Ejercicio 2 
 * Dada una clase con alumnos de cantidad que puede ir de 40 a 60 alumnos, cada alumno posee 4 materias
 * donde debe rendir 1 examen final. Calcule Si el alumno pasó o no pasó cada examen.
 * Si pasó, su nota va de 60 a 100. Si no pasó, de 0 a 59. 
 * Luego imprima a cada alumno de la siguiente manera:
 * Alumno 1: M1: {nota1}	M2: {nota2}	M3:{nota3}	M4:{nota4}	Promedio: {notapromedio}
 * 
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int numero_aleatorio(int min, int max);
void carga_matriz(int f, int c, float mat[f][c]);
void calcula_promedio_notas(int f, int c, float mat[f][c]);
void imprime_matriz(int f, int c, float mat[f][c]);
void proceso();


int main()
{
	srand(time(NULL));
	proceso();
	return 0;
}

void proceso()
{
	int cantAlumnos = numero_aleatorio(40, 60);
	printf("Cantidad de alumnos: %d\n", cantAlumnos);
	float matAlumnos[cantAlumnos][5];
	carga_matriz(cantAlumnos, 5, matAlumnos);
	calcula_promedio_notas(cantAlumnos, 5, matAlumnos);
	printf("Imprimiendo matriz con notas de alumnos...\n");
	imprime_matriz(cantAlumnos, 5, matAlumnos);
	
}

void calcula_promedio_notas(int f, int c, float mat[f][c])
{
	int i, j, sum;
	float prom;	
	for(i = 0; i < f; i++)
	{
		sum = 0;
		prom = 0;
		
		for(j = 0; j < c - 1; j++)
		{
			sum += mat[i][j];
		}
		prom = (float) sum / (c-1);
		mat[i][c-1] = prom;
	}
}

void carga_matriz(int f, int c, float mat[f][c])
{
	int i, j;
	for(i = 0; i < f; i++)
	{
		for(j = 0; j < c - 1; j++)
		{
			mat[i][j] = numero_aleatorio(0, 100);
		}
		mat[i][c-1] = 0;
	}
}

void imprime_matriz(int f, int c, float mat[f][c])
{
    int i, j;
    printf("Matriz: \n[");
    for (i = 0; i < f; i++)
    {
        printf("\n Alumno %d\t[", i + 1);
        for (j = 0; j < c - 1; j++)
        {
            printf("\tM%d: %d\t", j + 1, (int)mat[i][j]); 
        }
	printf("\tPromedio: %f\t", mat[i][c-1]);
        printf("]");
    }
    printf("\n]\n");
}

int numero_aleatorio(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

