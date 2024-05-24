#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODO
{
    int numero;
    struct NODO *siguiente;
} Nodo;

/* Agrega un nodo a lista enlazada */
void agregar_nodo(Nodo **puntero)
{
    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo)); // se crea un nodo y este espacio en la memoria se enlaza
    nodo->siguiente = *puntero;
    *puntero = nodo;
    nodo->numero = 1 + rand() % 4000;
}

/* Remueve un elemento de la lista enlazada */
void remover(Nodo **puntero)
{
    if (*puntero != NULL)
    {
        Nodo *nodo = *puntero;
        *puntero = (*puntero)->siguiente;
        free(nodo);
    }
}

/* Busca la posicion del nodo que contiene el valor sugerido, dicha posicion se utilizar para eliminar en la otra funcion */
Nodo **buscar(Nodo **nodo, int i)
{
    while (*nodo != NULL)
    {
        if ((*nodo)->numero == i)
        {
            return nodo;
        }
        nodo = &(*nodo)->siguiente;
    }
    return NULL;
}

void imprimir(Nodo *nodo)
{
    if (nodo == NULL)
    {
        printf("lista esta vacia\n");
    }
    /* Recorre la lista para ir imprimiendo los numeros generados al azar */
    while (nodo != NULL)
    {
        printf("Pos. Mem: %016p Pos. sig: %016p Valor cont:%d\n", (void *)nodo, (void *)nodo->siguiente, nodo->numero);
        nodo = nodo->siguiente;
    }
}

void bubble_sort(Nodo **tope)
{
    if (*tope == NULL)
        return;

    int swapped;
    Nodo *pivote;
    Nodo *base = NULL;

    do
    {
        swapped = 0;
        pivote = *tope;
        Nodo *prev = NULL;

        while (pivote->siguiente != base)
        {
            if (pivote->numero > pivote->siguiente->numero)
            {
                Nodo *aux = pivote->siguiente;
                pivote->siguiente = aux->siguiente;
                aux->siguiente = pivote;

                if (prev == NULL)
                {
                    *tope = aux;
                }
                else
                {
                    prev->siguiente = aux;
                }

                prev = aux;
                swapped = 1;
            }
            else
            {
                prev = pivote;
                pivote = pivote->siguiente;
            }
        }
        base = pivote;
    } while (swapped);
}

void recorrer_nodo(Nodo **nodo)
{

    while ((*nodo)->siguiente != NULL)
    {
        printf("\nNodo actual: %p\t\tSiguiente: %p\t\tValor: %n\n", *nodo, (*nodo)->siguiente, (*nodo)->numero);
        *nodo = (*nodo)->siguiente;
    }
    printf("\nfin\n");
}

int main()
{
    Nodo *nodo = NULL;
    srand(time(NULL));
    int i, num;

    /* Se cargan los elementos al azar de la lista en este caso 5 elementos */
    for (i = 0; i < 5; i++)
    {
        agregar_nodo(&nodo);
        // imprimir(nodo);
        printf("\n");
    }

    printf("\n\nLista cargada\n");
    imprimir(nodo);

    recorrer_nodo(&nodo);
    /* Ordenar la lista utilizando burbuja */
    bubble_sort(&nodo);

    printf("\n\nLista ordenada\n");
    imprimir(nodo);

    /* Elimina el elemento que se desea de la lista */
    /*printf("\nQue valor desea remover: ");
    scanf("%d", &num);
    getchar();*/

    /* Elimina el n�mero especificado de la lista */
    remover(buscar(&nodo, num));
    printf("\n\n");
    imprimir(nodo);

    /* Elimina el primer n�mero de la lista */
    remover(&nodo);
    printf("\n\n");
    imprimir(nodo);

    /* Elimina el primer n�mero de la lista */
    remover(&nodo);
    printf("\n\n");
    imprimir(nodo);

    getchar();
    return 0;
}
