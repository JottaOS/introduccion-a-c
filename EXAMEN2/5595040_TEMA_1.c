/**
 * GRUPO 1, TEMA 1
 *
 * Alumno: Juan Mendoza
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct pelicula
{
    int codigoBarra;
    char nombre[20];
    int cantidadCopias;
    char genero;
    int clasificacion;
    int vecesAlquilada;
    double promedioGanancia;
    struct pelicula *siguiente;
} Pelicula;

int numero_aleatorio(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

int generarCodigoBarra(Pelicula *peliculas)
{
    int codigoBarra = numero_aleatorio(0, 99999);

    Pelicula *ptr = peliculas;
    while (ptr != NULL)
    {
        if (ptr->codigoBarra == codigoBarra)
        {
            codigoBarra = numero_aleatorio(0, 99999);
            ptr = peliculas;
            continue;
        }
        ptr = ptr->siguiente;
    }

    return codigoBarra;
}

void generarPelicula(Pelicula **pelicula, Pelicula *lista)
{
    Pelicula *p = *pelicula;
    int clasificaciones[] = {10, 13, 16, 18};

    p->codigoBarra = generarCodigoBarra(lista);
    snprintf(p->nombre, sizeof(p->nombre), "Pelicula %d", p->codigoBarra);
    p->cantidadCopias = numero_aleatorio(1, 35);
    p->genero = 'A' + numero_aleatorio(0, 25);
    p->clasificacion = clasificaciones[numero_aleatorio(0, 3)];
    p->vecesAlquilada = numero_aleatorio(0, 1000);
    p->promedioGanancia = (p->vecesAlquilada * 8000.0) / p->cantidadCopias;
    p->siguiente = NULL;
}

void imprimirPelicula(Pelicula *p)
{
    printf("\t- Codigo de barra: %d\n", p->codigoBarra);
    printf("\t- Nombre: %s\n", p->nombre);
    printf("\t- Cantidad de Copias: %d\n", p->cantidadCopias);
    printf("\t- Genero: %c\n", p->genero);
    printf("\t- Clasificacion: %d\n", p->clasificacion);
    printf("\t- Veces Alquilada: %d\n", p->vecesAlquilada);
    printf("\t- Promedio de Ganancia por copia: Gs. %.2f\n", p->promedioGanancia);
}

Pelicula *generarListadoPeliculas()
{
    int cantidadPeliculas = numero_aleatorio(70, 100);
    int i;
    Pelicula *listaPeliculas = NULL;

    for (i = 0; i < cantidadPeliculas; i++)
    {
        Pelicula *nuevaPelicula = (Pelicula *)malloc(sizeof(Pelicula));
        generarPelicula(&nuevaPelicula, listaPeliculas);
        nuevaPelicula->siguiente = listaPeliculas;
        listaPeliculas = nuevaPelicula;
    }

    printf("Cantidad de peliculas generadas: %d\n", cantidadPeliculas);
    return listaPeliculas;
}

void imprimirPeliculas(Pelicula *lista)
{
    printf("%-15s %-20s %-17s %-10s %-15s %-17s %-15s\n",
           "Codigo de barra", "Nombre", "Copias",
           "Genero", "Clasificacion", "Veces Alquilada",
           "Prom. Ganancia / copia");
    printf("-------------------------------------------------------------------------------------------------------------\n");

    Pelicula *p = lista;
    while (p != NULL)
    {
        printf("%-15d %-20s %-17d %-10c %-15d %-17d %-15.2f\n",
               p->codigoBarra, p->nombre, p->cantidadCopias,
               p->genero, p->clasificacion, p->vecesAlquilada,
               p->promedioGanancia);
        p = p->siguiente;
    }
}

Pelicula *peliculaMasAlquilada(Pelicula *lista)
{
    Pelicula *p = lista;
    Pelicula *masAlquilada = p;
    while (p != NULL)
    {
        if (p->vecesAlquilada > masAlquilada->vecesAlquilada)
        {
            masAlquilada = p;
        }
        p = p->siguiente;
    }

    printf("\nPELICULA MAS ALQUILADA --> \"%s\"\n", masAlquilada->nombre);
    imprimirPelicula(masAlquilada);
    return masAlquilada;
}

void generoMasAlquilado(Pelicula *lista)
{
    int generos[26] = {0};
    Pelicula *p = lista;

    while (p != NULL)
    {
        generos[p->genero - 'A'] += p->vecesAlquilada;
        p = p->siguiente;
    }

    int maxAlquilado = generos[0];
    char genero = 'A';
    int i;

    for (i = 1; i < 26; i++)
    {
        if (generos[i] > maxAlquilado)
        {
            maxAlquilado = generos[i];
            genero = 'A' + i;
        }
    }

    printf("GENERO MAS ALQUILADO: \"%c\". CANTIDAD DE VECES ALQUILADA -> %d\n", genero, maxAlquilado);
}

void peliculasPorGenero(Pelicula *lista)
{
    int generos[26] = {0};
    Pelicula *p = lista;
    while (p != NULL)
    {
        generos[p->genero - 'A']++;
        p = p->siguiente;
    }

    printf("\nPeliculas por genero:\n");
    int i;
    for (i = 0; i < 26; i++)
    {
        if (generos[i] > 0)
        {
            printf("Genero %c: %d peliculas\n", 'A' + i, generos[i]);
        }
    }
}

void cantidadPorClasificacion(Pelicula *lista)
{
    int clasificaciones[] = {0, 0, 0, 0};
    Pelicula *p = lista;
    while (p != NULL)
    {
        if (p->clasificacion == 10)
            clasificaciones[0]++;
        if (p->clasificacion == 13)
            clasificaciones[1]++;
        if (p->clasificacion == 16)
            clasificaciones[2]++;
        if (p->clasificacion == 18)
            clasificaciones[3]++;
        p = p->siguiente;
    }

    printf("\nCANTIDAD POR CLASIFICACION\n");
    printf("Clasificacion 10: %d peliculas\n", clasificaciones[0]);
    printf("Clasificacion 13: %d peliculas\n", clasificaciones[1]);
    printf("Clasificacion 16: %d peliculas\n", clasificaciones[2]);
    printf("Clasificacion 18: %d peliculas\n", clasificaciones[3]);
}

void totalRecaudado(Pelicula *lista)
{
    double total = 0;
    Pelicula *ptr = lista;
    while (ptr != NULL)
    {
        total += ptr->vecesAlquilada * 8000.0;
        ptr = ptr->siguiente;
    }

    printf("\nTOTAL RECAUDADO: %.2f\n", total);
}

void proceso()
{
    Pelicula *tope = generarListadoPeliculas();
    imprimirPeliculas(tope);
    totalRecaudado(tope);
    generoMasAlquilado(tope);
    peliculaMasAlquilada(tope);
    peliculasPorGenero(tope);
    cantidadPorClasificacion(tope);
}

int main()
{
    srand(time(0));
    proceso();
    return 0;
}
