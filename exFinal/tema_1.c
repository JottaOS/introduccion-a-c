/**
 * TEMA 1: Estadísticas de torneos de futbol
 *
 * Alumno: Juan Mendoza
 *
 * OBSERVACIÓN: Los nombres de los países con más de una palabra en su nombre (Ej: El Salvador, Republica Dominicana)
 * se juntaron para que se lea correctamente el archivo de historial.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct partido
{
    char pais_1[21];
    int goles_1;
    char pais_2[21];
    int goles_2;
    char ganador[21];
} Partido;

void proceso();
void obtener_paises(char paises[19][21]);
void generar_datos(int anio);
void generar_estadisticas();

int main()
{
    srand(time(NULL));
    proceso();
    return 0;
}

void obtener_paises(char paises[19][21])
{
    char *temp_paises[19] = {
        "Argentina", "Bolivia", "Brasil", "Colombia", "CostaRica", "Cuba",
        "Chile", "Ecuador", "ElSalvador", "Guatemala", "Honduras", "Mexico",
        "Nicaragua", "Panama", "Paraguay", "Peru", "RepublicaDominicana",
        "Uruguay", "Venezuela"};
    int i;
    for (i = 0; i < 19; i++)
    {
        strcpy(paises[i], temp_paises[i]);
    }
}

void proceso()
{
    int anio;
    for (anio = 1950; anio <= 2024; anio++)
    {
        generar_datos(anio);
    }

    generar_estadisticas();
}

void generar_estadisticas()
{
    FILE *archivo_historial;
    archivo_historial = fopen("historia_torneo.txt", "r");

    if (archivo_historial == NULL)
    {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    int goles_paises[19] = {0};
    int victorias_paises[19] = {0};
    int torneos_ganados[19] = {0};
    int participacion_paises[19] = {0};

    char paises[19][21];
    obtener_paises(paises);

    char linea[128];
    int anio_anterior = 1949;
    int ganador_torneo = -1;
    int i;

    while (fgets(linea, sizeof(linea), archivo_historial))
    {
        int anio, ronda, goles_1, goles_2;
        char pais_1[21], pais_2[21], ganador[21];

        sscanf(linea, "%d %d %s %d %s %d %s", &anio, &ronda, pais_1, &goles_1, pais_2, &goles_2, ganador);

        for (i = 0; i < 19; i++)
        {
            if (strcmp(pais_1, paises[i]) == 0)
            {
                goles_paises[i] += goles_1;
                participacion_paises[i] = 1;
                if (strcmp(ganador, paises[i]) == 0)
                {
                    victorias_paises[i]++;
                    if (ronda == 4)
                    {
                        ganador_torneo = i;
                    }
                }
            }

            if (strcmp(pais_2, paises[i]) == 0)
            {
                goles_paises[i] += goles_2;
                participacion_paises[i] = 1;
                if (strcmp(ganador, paises[i]) == 0)
                {
                    victorias_paises[i]++;
                }
            }
        }

        if (anio_anterior != anio)
        {
            if (ganador_torneo != -1)
            {
                torneos_ganados[ganador_torneo]++;
            }
            anio_anterior = anio;
        }
    }

    fclose(archivo_historial);

    FILE *archivo_resultados;
    archivo_resultados = fopen("Resultados_1950_2024.txt", "w");

    if (archivo_resultados == NULL)
    {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    fprintf(archivo_resultados, "Goles anotados por cada país:\n");
    for (i = 0; i < 19; i++)
    {
        fprintf(archivo_resultados, "%s: %d goles\n", paises[i], goles_paises[i]);
    }

    fprintf(archivo_resultados, "\nVictorias en partidos por cada selección:\n");
    for (i = 0; i < 19; i++)
    {
        fprintf(archivo_resultados, "%s: %d victorias\n", paises[i], victorias_paises[i]);
    }

    fprintf(archivo_resultados, "\nTorneos ganados por cada país:\n");
    for (i = 0; i < 19; i++)
    {
        fprintf(archivo_resultados, "%s: %d torneos\n", paises[i], torneos_ganados[i]);
    }

    fprintf(archivo_resultados, "\nPaíses con más torneos ganados:\n");
    int max_torneos = 0;
    for (i = 0; i < 19; i++)
    {
        if (torneos_ganados[i] > max_torneos)
        {
            max_torneos = torneos_ganados[i];
        }
    }

    for (i = 0; i < 19; i++)
    {
        if (torneos_ganados[i] == max_torneos)
        {
            fprintf(archivo_resultados, "%s: %d torneos, %d goles\n", paises[i], torneos_ganados[i], goles_paises[i]);
        }
    }

    int contador_participacion = 0;
    for (i = 0; i < 19; i++)
    {
        if (participacion_paises[i] == 0)
        {
            if (contador_participacion == 0)
                fprintf(archivo_resultados, "\nPaíses que nunca participaron:\n");
            contador_participacion++;
            fprintf(archivo_resultados, "%s\n", paises[i]);
        }
    }

    if (contador_participacion == 0)
        fprintf(archivo_resultados, "\nTodos los países participaron en al menos un torneo.\n");

    fclose(archivo_resultados);
}

void generar_datos(int anio)
{
    FILE *archivo_historial;
    archivo_historial = fopen("historia_torneo.txt", "a");

    if (archivo_historial == NULL)
    {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    int i, j, ronda;
    char paises[19][21];
    obtener_paises(paises);

    int seleccionados[16];
    for (i = 0; i < 16; i++)
    {
        int indice_pais;
        int repetido;
        do
        {
            repetido = 0;
            indice_pais = rand() % 19;
            for (j = 0; j < i; j++)
            {
                if (seleccionados[j] == indice_pais)
                {
                    repetido = 1;
                    break;
                }
            }
        } while (repetido);
        seleccionados[i] = indice_pais;
    }

    for (ronda = 0; ronda < 4; ronda++)
    {
        int num_partidos = ronda == 0   ? 8
                           : ronda == 1 ? 4
                           : ronda == 2 ? 2
                                        : 1;

        for (i = 0; i < num_partidos; i++)
        {
            Partido p;
            int indice_pais_1 = i * 2;
            int indice_pais_2 = indice_pais_1 + 1;

            strcpy(p.pais_1, paises[seleccionados[indice_pais_1]]);
            strcpy(p.pais_2, paises[seleccionados[indice_pais_2]]);
            p.goles_1 = rand() % 21;
            p.goles_2 = rand() % 21;

            while (p.goles_1 == p.goles_2)
            {
                p.goles_2 = rand() % 21;
            }

            if (p.goles_1 > p.goles_2)
            {
                strcpy(p.ganador, p.pais_1);
                seleccionados[i] = seleccionados[indice_pais_1];
            }
            else
            {
                strcpy(p.ganador, p.pais_2);
                seleccionados[i] = seleccionados[indice_pais_2];
            }

            char *nueva_linea = anio == 2024 && ronda == 3 ? "" : "\n";
            fprintf(archivo_historial, "%d %d %s %d %s %d %s%s",
                    anio, ronda + 1, p.pais_1, p.goles_1, p.pais_2, p.goles_2, p.ganador, nueva_linea);
        }
    }

    fclose(archivo_historial);
}
