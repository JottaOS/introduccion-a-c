#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODO
{
    char *nombre;
    struct NODO *siguiente;
    int pos;

} Nodo;

Nodo *crear_nodo();
Nodo *primer = NULL; // eliminar esta variable global
Nodo *ultimo = NULL; // eliminar esta variable global

void agregar(Nodo *_nodo)
{
    _nodo->siguiente = NULL;
    if (primer == NULL)
    {
        primer = _nodo;
        ultimo = _nodo;
    }
    else
    {
        ultimo->siguiente = _nodo;
        ultimo = _nodo;
    }
}

int main()
{

    char *p;

    int n = 10;
    p = (char *)malloc(n * sizeof(char)); /*Reserva memoria para 10 caracteres*/

    agregar(crear_nodo());
    printf("Primer: %p\n", primer);
    printf("Ultimo: %p\n", ultimo);
    agregar(crear_nodo());
    printf("Primer: %p\n", primer);
    printf("Ultimo: %p\n", ultimo);
    agregar(crear_nodo());
    printf("Primer: %p\n", primer);
    printf("Ultimo: %p\n", ultimo);
    agregar(crear_nodo());
    printf("Primer: %p\n", primer);
    printf("Ultimo: %p\n", ultimo);

    Nodo *i = primer;
    while (i != NULL)
    {

        printf("%s\n", i->nombre);
        i = i->siguiente;
    }
    getchar();
    return 0;
}

Nodo *crear_nodo()
{

    char nombre[50];

    printf("Cargue nombre: ");
    scanf("%s", nombre);
    getchar();
    Nodo *i = (Nodo *)malloc(sizeof(Nodo));
    int n = strlen(nombre);
    i->nombre = (char *)malloc(n * sizeof(char));

    strcpy(i->nombre, nombre);

    return i;
}