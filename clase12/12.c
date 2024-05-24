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

typedef struct NODO
{
    char *nombre;
    char *apellido;
    char genero;
    int edad;
    Nodo *siguiente;
} Nodo;

int numero_aleatorio(int min, int max)
{
    return rand() % ((max - min + 1) + 1);
}

Nodo *generar_nodos()
{

    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    char nombre_hombre[][25] = {"ADRIAN", "ALBERTO", "ALEJANDRO", "ALVARO", "ANDRES", "ANGEL", "ANTONIO", "CARLOS", "DANIEL", "DAVID", "DIEGO", "EDUARDO", "ENRIQUE", "FERNANDO", "FRANCISCO", "IVAN", "JAVIER", "JESUS", "JOAQUIN", "JORGE", "JOSE", "JUAN", "LUIS", "MANUEL", "MIGUEL", "OSCAR", "PABLO", "PEDRO", "RAFAEL", "RAMON", "RAUL", "RUBEN", "SANTIAGO", "SERGIO", "VICENTE", "VICTOR"};
    char nombre_mujer[][25] = {"ANA", "ANDREA", "ANGELA", "ANTONIA", "BEATRIZ", "CARMEN", "CONCEPCION", "CRISTINA", "DOLORES", "ELENA", "ENCARNACION", "FRANCISCA", "IRENE", "ISABEL", "JOSEFA", "JUANA", "JULIA", "LAURA", "LUCIA", "MANUELA", "MARIA", "MARTA", "MERCEDES", "MONICA", "MONTSERRAT", "NURIA", "PATRICIA", "PAULA", "PILAR", "RAQUEL", "ROCIO", "ROSA", "ROSARIO", "SARA", "SILVIA", "TERESA"};
    char pos_apellidos[][25] = {"ALONSO", "ALVAREZ", "BLANCO", "CANO", "CASTILLO", "CASTRO", "CORTES", "DELGADO", "DIAZ", "DOMINGUEZ", "FERNANDEZ", "GARCIA", "GARRIDO", "GIL", "GOMEZ", "GONZALEZ", "GUERRERO", "GUTIERREZ", "HERNANDEZ", "IGLESIAS", "JIMENEZ", "LOPEZ", "LOZANO", "MARIN", "MARTIN", "MARTINEZ", "MEDINA", "MOLINA", "MORALES", "MORENO", "MUNOZ", "NAVARRO", "NUNEZ", "ORTEGA", "ORTIZ", "PEREZ", "RAMIREZ", "RAMOS", "RODRIGUEZ", "ROMERO", "RUBIO", "RUIZ", "SANCHEZ", "SANTOS", "SANZ", "SERRANO", "SUAREZ", "TORRES", "VAZQUEZ"};

    int genero = numero_aleatorio(0, 1);
    printf("genero:  %n\n", genero);
    int cantidad_nodos = numero_aleatorio(10, 15);
    printf("Cantidad nodos: %n\n", cantidad_nodos);

    int i;
    for (i = 0; i < cantidad_nodos; i++)
    {
        }

    if (genero == 0) // masculino
    {
    }
}

int main()
{
}
