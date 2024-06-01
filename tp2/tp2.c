/**
 * Trabajo practico Nro 2
 * Consulta de alumnos
 * Integrantes:
 *  - Juan Mendoza
 *  - Alan Vera
 *  - Franco Portillo
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

void mostrar_estadisticas(Ficha *ficha);
Ficha *cargar_alumnos(int cantidad_nodos);
void proceso();
int generar_nro_cedula(Ficha *ficha);
void imprimir_ficha(Ficha *ficha, int nroOrden);
void imprimir_cabecera();
int numero_aleatorio(int min, int max);
void imprimir_lista(Ficha *alumnos);
void aguardar_enter();
int obtener_input(int min, int max);
int comparar_ci(const void *a, const void *b);
int comparar_apellido(const void *a, const void *b);
int comparar_edad(const void *a, const void *b);

int comparar_ci(const void *a, const void *b)
{
    Ficha *fa = *(Ficha **)a;
    Ficha *fb = *(Ficha **)b;
    return (fa->ci - fb->ci);
}

int comparar_apellido(const void *a, const void *b)
{
    Ficha *fa = *(Ficha **)a;
    Ficha *fb = *(Ficha **)b;
    return strcmp(fa->apellidoynombre, fb->apellidoynombre);
}

int comparar_edad(const void *a, const void *b)
{
    Ficha *fa = *(Ficha **)a;
    Ficha *fb = *(Ficha **)b;
    return (fa->edad - fb->edad);
}

int obtener_input(int min, int max)
{
    int opcion;
    do
    {
        printf("> ");
        scanf("%d", &opcion);
        if (opcion < min || opcion > max)
        {
            printf("\nOpcion no valida. Vuelva a ingresar un numero\n");
        }
        getchar();
    } while (opcion < min || opcion > max);

    return opcion;
}

void aguardar_enter()
{
    printf("\n\nPresione [ENTER] para continuar...");
    while (getchar() != '\n')
        ;
}

int numero_aleatorio(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

int generar_nro_cedula(Ficha *alumnos)
{
    int ci = 2500000 + ((rand() % 1871) * (rand() % 1871) - 641);
    if (alumnos == NULL)
    {
        return ci;
    }

    Ficha *ptr = alumnos;
    while (ptr != NULL)
    {
        if (alumnos->ci == ci)
        {
            ci = 2500000 + ((rand() % 1871) * (rand() % 1871) - 641);
            ptr = alumnos;
            continue;
        }
        ptr = ptr->siguiente;
    }

    return ci;
}

void imprimir_cabecera()
{
    printf("%-10s %-40s %-10s %-20s %-25s\n",
           "Nro orden",
           "Nombres y Apellidos",
           "Edad",
           "Cedula de identidad",
           "Ciudad");
}

void imprimir_ficha(Ficha *ficha, int nroOrden)
{
    printf("%-10d %-40s %-10d %-20d %-25s\n",
           nroOrden,
           ficha->nombreyapellido,
           ficha->edad,
           ficha->ci,
           ficha->ciudad);
}

void imprimir_lista(Ficha *alumnos)
{
    imprimir_cabecera();
    int i = 0;
    Ficha *ptr = alumnos;
    while (ptr != NULL)
    {
        i++;
        imprimir_ficha(ptr, i);
        ptr = ptr->siguiente;
    }
}

void liberar_lista(Ficha *alumnos)
{
    Ficha *actual = alumnos;
    while (actual != NULL)
    {
        Ficha *siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
}

void ordenar_lista(Ficha **alumnos, int cantidad, int (*comparar)(const void *, const void *))
{
    Ficha **arreglo = (Ficha **)malloc(cantidad * sizeof(Ficha *));
    Ficha *actual = *alumnos;
    int i;
    for (i = 0; i < cantidad; i++)
    {
        arreglo[i] = actual;
        actual = actual->siguiente;
    }

    qsort(arreglo, cantidad, sizeof(Ficha *), comparar);

    for (i = 0; i < cantidad - 1; i++)
    {
        arreglo[i]->siguiente = arreglo[i + 1];
    }
    arreglo[cantidad - 1]->siguiente = NULL;
    *alumnos = arreglo[0];

    free(arreglo);
}

Ficha *copiar_lista(Ficha *alumnos)
{

    Ficha *cabeza = NULL;
    Ficha *actual = NULL;

    while (alumnos != NULL)
    {
        Ficha *nuevo = (Ficha *)malloc(sizeof(Ficha));
        *nuevo = *alumnos;
        nuevo->siguiente = NULL;

        if (cabeza == NULL)
        {
            cabeza = nuevo;
        }
        else
        {
            actual->siguiente = nuevo;
        }
        actual = nuevo;
        alumnos = alumnos->siguiente;
    }

    return cabeza;
}

void mostrar_menu(Ficha *alumnos)
{
    printf("\n============================================\n");
    mostrar_estadisticas(alumnos);
    printf("\nINGRESE UNA OPCION:\n");
    printf("1. Lista original (orden de inscripcion)\n");
    printf("2. Lista ordenada por numero de cedula\n");
    printf("3. Lista ordenada por apellido\n");
    printf("4. Lista ordenada por edad\n");
    printf("5. Salir\n");
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
        nuevo_nodo->ci = generar_nro_cedula(tope);
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

int misma_edad(Ficha *a, Ficha *b)
{
    return a->edad == b->edad;
}

int mismo_primer_apellido(Ficha *a, Ficha *b)
{
    return strcmp(a->papellido, b->papellido) == 0;
}

int mismo_apellido(Ficha *a, Ficha *b)
{
    return strcmp(a->papellido, b->papellido) == 0 && strcmp(a->sapellido, b->sapellido) == 0;
}

int misma_ciudad(Ficha *a, Ficha *b)
{
    return strcmp(a->ciudad, b->ciudad) == 0;
}

int mismo_nombre(Ficha *a, Ficha *b)
{
    return strcmp(a->pnombre, b->pnombre) == 0 || strcmp(a->snombre, b->snombre) == 0;
}

int contar_por_criterio(Ficha *alumnos, int (*criterio)(Ficha *, Ficha *))
{
    Ficha *ptr1 = alumnos;
    int contador = 0;
    while (ptr1 != NULL)
    {
        Ficha *ptr2 = alumnos;
        while (ptr2 != NULL)
        {
            if (ptr1 != ptr2 && criterio(ptr1, ptr2))
            {
                contador++;
                break;
            }
            ptr2 = ptr2->siguiente;
        }
        ptr1 = ptr1->siguiente;
    }
    return contador;
}

void mostrar_estadisticas(Ficha *alumnos)
{
    printf("\nEstadisticas:\n");
    printf("Alumnos con misma edad: %d\n", contar_por_criterio(alumnos, misma_edad));
    printf("Alumnos que son primos: %d\n", contar_por_criterio(alumnos, mismo_primer_apellido));
    printf("Alumnos que son hermanos: %d\n", contar_por_criterio(alumnos, mismo_apellido));
    printf("Alumnos que son de la misma ciudad: %d\n", contar_por_criterio(alumnos, misma_ciudad));
    printf("Alumnos que tienen el mismo nombre: %d\n", contar_por_criterio(alumnos, mismo_nombre));

    int varones = 0, mujeres = 0;
    Ficha *ptr = alumnos;
    while (ptr != NULL)
    {
        if (ptr->genero == 'M')
        {
            varones++;
        }
        else
        {
            mujeres++;
        }
        ptr = ptr->siguiente;
    }
    printf("Alumnos varones: %d\n", varones);
    printf("Alumnas mujeres: %d\n", mujeres);
}

void proceso()
{
    printf(" === Consulta de Alumnos ===\n");
    printf("Ingrese cantidad de alumnos (entre 60 y 70)\n");
    int cantidad_alumnos = obtener_input(60, 70);
    Ficha *alumnos = cargar_alumnos(cantidad_alumnos);
    Ficha *copia_alumnos = NULL;

    printf("\n");
    int opcion;
    do
    {
        mostrar_menu(alumnos);
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Lista original (orden de inscripcion):\n");
            imprimir_lista(alumnos);
            break;
        case 2:
            printf("Lista ordenada por numero de cedula:\n");
            copia_alumnos = copiar_lista(alumnos);
            ordenar_lista(&copia_alumnos, cantidad_alumnos, comparar_ci);
            imprimir_lista(copia_alumnos);
            liberar_lista(copia_alumnos);
            break;
        case 3:
            printf("Lista ordenada por apellido:\n");
            copia_alumnos = copiar_lista(alumnos);
            ordenar_lista(&copia_alumnos, cantidad_alumnos, comparar_apellido);
            imprimir_lista(copia_alumnos);
            liberar_lista(copia_alumnos);
            break;
        case 4:
            printf("Lista ordenada por edad:\n");
            copia_alumnos = copiar_lista(alumnos);
            ordenar_lista(&copia_alumnos, cantidad_alumnos, comparar_edad);
            imprimir_lista(copia_alumnos);
            liberar_lista(copia_alumnos);
            break;
        case 5:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion no valida, intente de nuevo.\n");
        }
    } while (opcion != 5);

    liberar_lista(alumnos);
}

int main()
{
    srand(time(NULL));
    proceso();
    return 0;
}