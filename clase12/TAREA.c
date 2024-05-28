/**
 *
 * Cree una lista enlazada de 10 a 15 elementos generados al azar, donde el nodo guarde dos nombres
 * y dos apellidos de personas, su genero y su edad, Una vez cargado, imprima la lista,
 * como fue cargada, luego ordene por apellidos la lista.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct NODO
{
    char primer_nombre[25];
    char segundo_nombre[25];
    char primer_apellido[25];
    char segundo_apellido[25];
    char genero;
    int edad;
    struct NODO *siguiente;
} Nodo;

int numero_aleatorio(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

Nodo *generar_nodos(int cantidad_nodos)
{
    char nombre_hombre[][25] = {"ADRIAN", "ALBERTO", "ALEJANDRO", "ALVARO", "ANDRES", "ANGEL", "ANTONIO", "CARLOS", "DANIEL", "DAVID", "DIEGO", "EDUARDO", "ENRIQUE", "FERNANDO", "FRANCISCO", "IVAN", "JAVIER", "JESUS", "JOAQUIN", "JORGE", "JOSE", "JUAN", "LUIS", "MANUEL", "MIGUEL", "OSCAR", "PABLO", "PEDRO", "RAFAEL", "RAMON", "RAUL", "RUBEN", "SANTIAGO", "SERGIO", "VICENTE", "VICTOR"};
    char nombre_mujer[][25] = {"ANA", "ANDREA", "ANGELA", "ANTONIA", "BEATRIZ", "CARMEN", "CONCEPCION", "CRISTINA", "DOLORES", "ELENA", "ENCARNACION", "FRANCISCA", "IRENE", "ISABEL", "JOSEFA", "JUANA", "JULIA", "LAURA", "LUCIA", "MANUELA", "MARIA", "MARTA", "MERCEDES", "MONICA", "MONTSERRAT", "NURIA", "PATRICIA", "PAULA", "PILAR", "RAQUEL", "ROCIO", "ROSA", "ROSARIO", "SARA", "SILVIA", "TERESA"};
    char pos_apellidos[][25] = {"ALONSO", "ALVAREZ", "BLANCO", "CANO", "CASTILLO", "CASTRO", "CORTES", "DELGADO", "DIAZ", "DOMINGUEZ", "FERNANDEZ", "GARCIA", "GARRIDO", "GIL", "GOMEZ", "GONZALEZ", "GUERRERO", "GUTIERREZ", "HERNANDEZ", "IGLESIAS", "JIMENEZ", "LOPEZ", "LOZANO", "MARIN", "MARTIN", "MARTINEZ", "MEDINA", "MOLINA", "MORALES", "MORENO", "MUNOZ", "NAVARRO", "NUNEZ", "ORTEGA", "ORTIZ", "PEREZ", "RAMIREZ", "RAMOS", "RODRIGUEZ", "ROMERO", "RUBIO", "RUIZ", "SANCHEZ", "SANTOS", "SANZ", "SERRANO", "SUAREZ", "TORRES", "VAZQUEZ"};

    Nodo *tope = NULL;
    Nodo *actual = NULL;

    int i;
    for (i = 0; i < cantidad_nodos; i++)
    {
        Nodo *nuevo_nodo = (Nodo *)malloc(sizeof(Nodo));

        int valor_genero = numero_aleatorio(0, 1);
        char genero = valor_genero == 0 ? 'M' : 'F';
        char(*nombre_genero)[25] = valor_genero == 0 ? nombre_hombre : nombre_mujer;

        int index = numero_aleatorio(0, 35);
        strcpy(nuevo_nodo->primer_nombre, nombre_genero[index]);

        do
        {
            index = numero_aleatorio(0, 35);
            strcpy(nuevo_nodo->segundo_nombre, nombre_genero[index]);
        } while (strcmp(nuevo_nodo->primer_nombre, nuevo_nodo->segundo_nombre) == 0);

        index = numero_aleatorio(0, 45);
        strcpy(nuevo_nodo->primer_apellido, pos_apellidos[index]);

        do
        {
            index = numero_aleatorio(0, 45);
            strcpy(nuevo_nodo->segundo_apellido, pos_apellidos[index]);
        } while (strcmp(nuevo_nodo->primer_apellido, nuevo_nodo->segundo_apellido) == 0);

        nuevo_nodo->genero = genero;
        nuevo_nodo->edad = numero_aleatorio(18, 40);
        nuevo_nodo->siguiente = NULL;

        if (tope == NULL)
        {
            tope = nuevo_nodo;
        }
        else
        {
            actual->siguiente = nuevo_nodo;
        }
        actual = nuevo_nodo;
    }

    return tope;
}

void imprimir(Nodo *nodo)
{
    printf("%-3c %-10d %-20s %-20s %-20s %-20s\n", nodo->genero, nodo->edad, nodo->primer_nombre, nodo->segundo_nombre, nodo->primer_apellido, nodo->segundo_apellido);
}

Nodo *intercambiar(Nodo *ptr1, Nodo *ptr2)
{
    Nodo *tmp = ptr2->siguiente;
    ptr2->siguiente = ptr1;
    ptr1->siguiente = tmp;
    return ptr2;
}

void ordenar_por_apellido(Nodo **cabecera, int contador)
{
    Nodo **h;
    int i, j, intercambio;

    for (i = 0; i < contador; i++)
    {

        h = cabecera;
        intercambio = 0;

        for (j = 0; j < contador - i - 1; j++)
        {

            Nodo *p1 = *h;
            Nodo *p2 = p1->siguiente;

            if (strcmp(p1->primer_apellido, p1->siguiente->primer_apellido) > 0)
            {

                *h = intercambiar(p1, p2);
                intercambio = 1;
            }

            h = &(*h)->siguiente;
        }

        if (intercambio == 0)
            break;
    }
}

void imprimir_nodos(Nodo *nodo)
{
    while (nodo != NULL)
    {
        imprimir(nodo);
        nodo = nodo->siguiente;
    }
}

void proceso()
{
    int cantidad_nodos = numero_aleatorio(10, 15);
    printf("Cantidad nodos: %d\n", cantidad_nodos);
    Nodo *lista_nodos = generar_nodos(cantidad_nodos);

    printf("Antes de ordenar: \n");
    imprimir_nodos(lista_nodos);

    printf("\n\nDespues de ordenar: \n");
    ordenar_por_apellido(&lista_nodos, cantidad_nodos);

    imprimir_nodos(lista_nodos);
}

int main()
{
    srand(time(NULL));
    proceso();
    return 0;
}
