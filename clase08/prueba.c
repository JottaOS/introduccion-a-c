/**
 *
 * Dada una lista de 15 alumnos, cuyos nombres y apellidos son definidos por las siguientes reglas:
 *      nombre_alumno --> "Alumno #numero de inscripcion"
 *      posee edad de entre 22 a 25 años
 *      peso entre 40kg a 250kg
 *      estatura en cm 130 a 230
 * Todos los datos menos el nombre generados al azar.
 * Cada uno de ellos posee 4 materias donde cada materias donde cada materia posee 3 parciales y un final,
 * con su respectivo promedio general de los examenes
 * Genere la lista con un menu para ver las notas de cada alumno
 *  Nombre_apellido: Alumno 1
 *  Edad: 23
 *  Peso: 65
 *  Estatura: 175
 *  CI: 1234567
 *  P1: 55  P2: 75  P3: 85  F: 100  Prom: 78.75
 *  Cada alumno cuenta con cédula de identidad de 3.500.000 a 7.500.000
 *  Todo debe ser tratado como una variable por alumno
 *
 * */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct PERSONA
{
    char nombre_alumno[10];
    int edad, estatura, peso, ci;
    float examenes[5];
} Persona;

int generar_ci(Persona lista[], int i)
{
    // asumimos que las ci están todas ceradas
    int ci_aux, b, j;
    do
    {
        b = 0;
        // numero aleatorio entre 3.500.000 a 7.500.000
        ci_aux = 3500000 + rand() % 2001 * rand() % 2001;
        for (j = 0; j < i; j++)
        {
            if (lista[j].ci == ci_aux)
                b = 1;
        }

    } while (b);
}

int principal()
{
    Persona lista[15];
    int i, j;
    for (i = 0; i < 15; i++)
    {
        lista[i].ci = 0;
        lista[i].edad = 22 + rand() % 4;
        lista[i].estatura = 130 + rand() % 201;
        lista[i].peso = 40 + rand() % 211;
        generar_ci(lista, i);
        sprintf(lista[i].nombre_alumno, "Alumno %d\n", i++);
        for (j = 0; j < 4; j++)
        {
            lista[i].examenes[j] = rand() % 101;
            lista[i].examenes[4] += lista[i].examenes[j];
        }
        lista[i].examenes[4] = lista[i].examenes[4] / 4;
        }
}

int main()
{
    printf("hola\n");
    principal();
    return 1;
}