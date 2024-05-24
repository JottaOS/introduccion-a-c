#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ALUMNO
{
    char nombre[20];
    int edad;
    long ci;
    float notas[4][3];
    float notas_finales[4];
    float promedio_general;
} Alumno;

int generar_numero_aleatorio(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

int generar_ci()
{
    return 2500000 + (rand() % 1870) * (rand() % 1870) + (rand() % 3101);
}

float generar_nota_aleatoria()
{
    return (float)(rand() % 101);
}

void inicializar_alumno(Alumno *alumno, int numero)
{
    sprintf(alumno->nombre, "Alumno %d", numero);
    alumno->edad = generar_numero_aleatorio(20, 40);
    alumno->ci = generar_ci();
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            alumno->notas[i][j] = generar_nota_aleatoria();
        }

        float suma_notas = 0;
        for (j = 0; j < 3; j++)
        {
            suma_notas += alumno->notas[i][j];
        }
        alumno->notas_finales[i] = suma_notas / 3;
    }

    float suma_promedios = 0;
    for (i = 0; i < 4; i++)
    {
        suma_promedios += alumno->notas_finales[i];
    }
    alumno->promedio_general = suma_promedios / 4;
}

void imprimir_alumno(Alumno alumno)
{
    int i;
    printf("Nro. de Lista: %d\n", alumno.ci % 100);
    printf("Nombre: %s\n", alumno.nombre);
    printf("Edad: %d\n", alumno.edad);
    printf("CI: %ld\n", alumno.ci);
    for (i = 0; i < 4; i++)
    {
        printf("Materia %d: %.1f\n", i + 1, alumno.notas_finales[i]);
    }
    printf("Promedio General: %.1f\n\n", alumno.promedio_general);
}

int main()
{
    srand(time(NULL));
    int i;
    int cantidad_alumnos;
    printf("Ingrese la cantidad de alumnos (entre 10 y 40): ");
    scanf("%d", &cantidad_alumnos);

    if (cantidad_alumnos < 10 || cantidad_alumnos > 40)
    {
        printf("La cantidad de alumnos debe estar entre 10 y 40.\n");
        return 1;
    }

    Alumno alumnos[cantidad_alumnos];

    for (i = 0; i < cantidad_alumnos; i++)
    {
        inicializar_alumno(&alumnos[i], i + 1);
    }

    for (i = 0; i < cantidad_alumnos; i++)
    {
        imprimir_alumno(alumnos[i]);
    }

    return 0;
}