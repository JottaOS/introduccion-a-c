/**
 *
 * Trabajo práctico Nro 2
 * Consulta de ficha de alumnos
 * Integrantes:
 *  - Juan Mendoza
 *  - Alan Vera
 *  - Franco Portillo
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct ficha
{
    char genero;
    char pnombre[50];
    char snombre[50];
    char papellido[50];
    char sapellido[50];
    char nombreyapellido[102];
    char apellidoynombre[102];
    int edad;
    int ci;
    char ciudad[25];
    struct ficha *siguiente;
} Ficha;

void mostrar_estadisticas(Ficha **ficha);
Ficha *cargar_alumnos(int cantidad_nodos);
void proceso();
void generarNroCedula(Ficha **ficha, int);
void imprimirFicha(Ficha *ficha, int nroOrden);
void imprimirCabecera();
int ingresar_cantidad();
int numero_aleatorio(int min, int max);

int numero_aleatorio(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

int ingresar_cantidad()
{
    int n;
    printf("Ingrese cantidad de alumnos (entre 60 y 70):");
    do
    {
        printf("\n> ");
        scanf("%d", &n);
        if (n < 60 || n > 70)
        {
            printf("\nValor no valido.");
        }
    } while (n < 60 || n > 70);

    getchar();
    return n;
}

/*
int generarNroCedula(Ficha alumnos[], int a)
{
    int ci = 0, i = 0, b = 1;

    ci = 2500000 + ((rand() % 1871) * (rand() % 1871) - 641);
    for (i = 0; i < a; i++)
    {
        if (alumnos[i].ci == ci)
        {
            ci = 2500000 + ((rand() % 1871) * (rand() % 1871) - 641);
            i = 0;
        }
    }
    return ci;
}
*/

void imprimirCabecera()
{
    printf("%-10s %-40s %-10s %-20s %-25s\n",
           "Nro orden",
           "Nombres y Apellidos",
           "Edad",
           "Cedula de identidad",
           "Ciudad");
}

void imprimirFicha(Ficha *ficha, int nroOrden)
{
    printf("%-10d %-40s %-10d %-20d %-25s\n",
           nroOrden,
           ficha->nombreyapellido,
           ficha->edad,
           ficha->ci,
           ficha->ciudad);
}

Ficha *cargar_alumnos(int cantidad_nodos)
{
    char nombre_hombre[][25] = {"ADRIAN", "ALBERTO", "ALEJANDRO", "ALVARO", "ANDRES", "ANGEL", "ANTONIO", "CARLOS", "DANIEL", "DAVID", "DIEGO", "EDUARDO", "ENRIQUE", "FERNANDO", "FRANCISCO", "IVAN", "JAVIER", "JESUS", "JOAQUIN", "JORGE", "JOSE", "JUAN", "LUIS", "MANUEL", "MIGUEL", "OSCAR", "PABLO", "PEDRO", "RAFAEL", "RAMON", "RAUL", "RUBEN", "SANTIAGO", "SERGIO", "VICENTE", "VICTOR"};
    char nombre_mujer[][25] = {"ANA", "ANDREA", "ANGELA", "ANTONIA", "BEATRIZ", "CARMEN", "CONCEPCION", "CRISTINA", "DOLORES", "ELENA", "ENCARNACION", "FRANCISCA", "IRENE", "ISABEL", "JOSEFA", "JUANA", "JULIA", "LAURA", "LUCIA", "MANUELA", "MARIA", "MARTA", "MERCEDES", "MONICA", "MONTSERRAT", "NURIA", "PATRICIA", "PAULA", "PILAR", "RAQUEL", "ROCIO", "ROSA", "ROSARIO", "SARA", "SILVIA", "TERESA"};
    char pos_apellidos[][25] = {"ALONSO", "ALVAREZ", "BLANCO", "CANO", "CASTILLO", "CASTRO", "CORTES", "DELGADO", "DIAZ", "DOMINGUEZ", "FERNANDEZ", "GARCIA", "GARRIDO", "GIL", "GOMEZ", "GONZALEZ", "GUERRERO", "GUTIERREZ", "HERNANDEZ", "IGLESIAS", "JIMENEZ", "LOPEZ", "LOZANO", "MARIN", "MARTIN", "MARTINEZ", "MEDINA", "MOLINA", "MORALES", "MORENO", "MUNOZ", "NAVARRO", "NUNEZ", "ORTEGA", "ORTIZ", "PEREZ", "RAMIREZ", "RAMOS", "RODRIGUEZ", "ROMERO", "RUBIO", "RUIZ", "SANCHEZ", "SANTOS", "SANZ", "SERRANO", "SUAREZ", "TORRES", "VAZQUEZ"};
    char ciudad[][25] = {"ASUNCION", "LAMBARE", "CAACUPE", "ITAUGUA", "MARIANO ROQUE ALONSO", "CAPIATA", "LUQUE", "SAN LORENZO"};

    Ficha *tope = NULL;
    Ficha *actual = NULL;

    int i;
    for (i = 0; i < cantidad_nodos; i++)
    {
        Ficha *nuevo_nodo = (Ficha *)malloc(sizeof(Ficha));

        int valor_genero = numero_aleatorio(0, 1);
        char genero = valor_genero == 0 ? 'M' : 'F';
        char(*nombre_genero)[25] = valor_genero == 0 ? nombre_hombre : nombre_mujer;
        char nombres[25];
        char apellidos[25];

        int index = numero_aleatorio(0, 35);
        strcpy(nuevo_nodo->pnombre, nombre_genero[index]);

        do
        {
            index = numero_aleatorio(0, 35);
            strcpy(nuevo_nodo->snombre, nombre_genero[index]);
        } while (strcmp(nuevo_nodo->pnombre, nuevo_nodo->snombre) == 0);

        index = numero_aleatorio(0, 45);
        strcpy(nuevo_nodo->papellido, pos_apellidos[index]);

        do
        {
            index = numero_aleatorio(0, 45);
            strcpy(nuevo_nodo->sapellido, pos_apellidos[index]);
        } while (strcmp(nuevo_nodo->papellido, nuevo_nodo->sapellido) == 0);

        nuevo_nodo->genero = genero;
        nuevo_nodo->edad = numero_aleatorio(20, 25);
        index = numero_aleatorio(0, 7);
        strcpy(nuevo_nodo->ciudad, ciudad[index]);
        sprintf(nombres, "%s %s", nuevo_nodo->pnombre, nuevo_nodo->snombre);
        sprintf(apellidos, "%s %s", nuevo_nodo->papellido, nuevo_nodo->sapellido);
        sprintf(nuevo_nodo->nombreyapellido, "%s %s", nombres, apellidos);
        sprintf(nuevo_nodo->apellidoynombre, "%s, %s", apellidos, nombres);
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

void proceso()
{
    printf("Consulta de Alumnos\n");
    int cantidad_alumnos = ingresar_cantidad();
    Ficha *alumnos = cargar_alumnos(cantidad_alumnos);

    imprimirCabecera();
    int i = 0;
    while (alumnos->siguiente != NULL)
    {
        Ficha *temp = alumnos->siguiente;
        i++;
        imprimirFicha(alumnos, i);
        alumnos = temp->siguiente;
    }
}

int main()
{
    srand(time(NULL));
    proceso();
    return 0;
}