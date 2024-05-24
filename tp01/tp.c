/* Trabajo práctico Nro. 1
 * Ordenamiento de cables
 * Integrantes:
 *   1. Juan Mendoza
 *   2. Alan Vera
 *   3. Franco Portillo
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h> // para windows, include <windows.h> y Sleep(1000); 1000 ms
#include <string.h>
#include <limits.h>

void proceso();
int menu_alumnos(char **); // recibir lista de alumnos
void imprimir_cabecera(char **);
void limpiar_pantalla();
void aguardar_enter();
int obtener_input(int min, int max);
int numero_aleatorio(int min, int max);
void generar_cables(int vector[], int longitud);
bool vector_contiene(int elemento, int vector[], int longitud);
bool chequear_ordenado(int vector[], int longitud);
void imprimir_cables(int vector[], int longitud);
int ordenar_burbuja(int vector[], int longitud);
int ordenar_seleccion(int vector[], int longitud);
void procesar_alumno(int vector[], int longitud, int *pasos); 
void generar_matriz(int f, int c, int mat[f][c]);
void ordenar_alfabeticamente(char *vector_alumnos[], int num_alumnos, int cables[][20], int pasos[]);
void menu_principal(char *vector_alumnos[], int cables[][20], int pasos[]);
void ordenar_cables_alumno(char *vector_alumnos[], int cables[][20], int pasos[]);
void ordenar_todos_cables(char *vector_alumnos[], int cables[][20], int pasos[]);
void mostrar_pasos_ordenamiento(char *vector_alumnos[], int cables[][20], int pasos[]);
void actualizar_nombre_alumno(char *vector_alumnos[], int cables[][20], int pasos[]);

int main()
{
  srand(time(NULL));
  proceso();
  return 0;
}


void proceso()
{
  char *vector_alumnos[] = {
    "Juan", "Daniela", "Gustavo", "Carlos", "Hilda",
    "Ignacio", "Eugenio", "Fabiola", "Agustin", "Beatriz"
  };
  int cables[10][20];
  int pasos[10] = {0};
  generar_matriz(10, 20, cables);
  menu_principal(vector_alumnos, cables, pasos);
}

void menu_principal(char *vector_alumnos[], int cables[][20], int pasos[]) 
{
  int opcion;
  do {
    limpiar_pantalla();
    imprimir_cabecera(vector_alumnos);
    printf("\nElija una opcion: \n");
    printf("1 - Ordenar los cables de un alumno\n");
    printf("2 - Ordenar todos los cables\n");
    printf("3 - Ordenar la lista de alumnos (alfabeticamente)\n");
    printf("4 - Mostrar alumnos con mayor y menor cantidad de pasos de ordenamiento\n");
    printf("5 - Actualizar el nombre de un alumno\n");
    printf("0 - Salir\n");
    opcion = obtener_input(0, 5);
    switch (opcion) {
      case 0:
        break;
      case 1:
        ordenar_cables_alumno(vector_alumnos, cables, pasos);
        break;
      case 2:
        ordenar_todos_cables(vector_alumnos, cables, pasos);
        break;
      case 3:
        ordenar_alfabeticamente(vector_alumnos, 10, cables, pasos);
        break;
      case 4:
        mostrar_pasos_ordenamiento(vector_alumnos, cables, pasos);
        break;
      case 5:
        actualizar_nombre_alumno(vector_alumnos, cables, pasos);
        break;
    }
  } while (opcion != 0);

  printf("Fin del programa.\n");
}

void ordenar_cables_alumno(char *vector_alumnos[], int cables[][20], int pasos[]) 
{
  int opcion_alumno = menu_alumnos(vector_alumnos);
  while (opcion_alumno != 0) {
    int indice = opcion_alumno - 1;
    limpiar_pantalla();
    printf("Alumno %d: %s\n", opcion_alumno, vector_alumnos[indice]);
    procesar_alumno(cables[indice], 20, &pasos[indice]);
    opcion_alumno = menu_alumnos(vector_alumnos);
  }
}

void ordenar_todos_cables(char *vector_alumnos[], int cables[][20], int pasos[])
{
  int i;
  for (i = 0; i < 10; i++) {
    limpiar_pantalla();
    printf("Alumno %d: %s\n", i + 1, vector_alumnos[i]);
    procesar_alumno(cables[i], 20, &pasos[i]);
  }
}

void mostrar_pasos_ordenamiento(char *vector_alumnos[], int cables[][20], int pasos[]) 
{
  int indice_max = -1, indice_min = -1;
  int valor_max = INT_MIN, valor_min = INT_MAX;
  int i;
  for(i = 0; i < 10; i++) {
    bool es_ordenado = chequear_ordenado(cables[i], 20);
    if(pasos[i] > valor_max && es_ordenado) {
      indice_max = i;
      valor_max = pasos[i];
    }
    if(pasos[i] < valor_min && es_ordenado) {
      indice_min = i;
      valor_min = pasos[i];
    }
  }
  if(indice_max == -1 || indice_min == -1) {
    printf("\nAún no se ha ordenado ningún alumno. Realice el ordenamiento, y luego intente de vuelta.\n");
  } else {
    printf("Mayor cantidad de pasos: %d\t\tAlumno: %s\n", pasos[indice_max], vector_alumnos[indice_max]);
    printf("Menor cantidad de pasos: %d\t\tAlumno: %s\n", pasos[indice_min], vector_alumnos[indice_min]);
  }
  aguardar_enter();
}

void actualizar_nombre_alumno(char *vector_alumnos[], int cables[][20], int pasos[])
{
  printf("\nSeleccione alumno a actualizar (presione 0 para cancelar)\n");
  int opcion_actualizar = obtener_input(0, 10);
  if(opcion_actualizar == 0) return;
  int indice_actualizar = opcion_actualizar - 1;
  printf("Nombre actual: %s\n", vector_alumnos[indice_actualizar]);
  char nombre[15];
  printf("Ingrese nuevo nombre: \n>");
  scanf("%s", nombre);
  getch();
  printf("Nombre ingresado: %s\n", nombre);
  vector_alumnos[indice_actualizar] = nombre;
  printf("Alumno actualizado!\n");
  aguardar_enter();
}

void ordenar_alfabeticamente(char *vector_alumnos[], int num_alumnos, int cables[][20], int pasos[])
{
  int i, j, k;
  char *temp;
  for (i = 0; i < num_alumnos - 1; i++) {
    for (j = 0; j < num_alumnos - i - 1; j++) {
      if (*vector_alumnos[j] > *vector_alumnos[j + 1]) {

        temp = vector_alumnos[j];
        vector_alumnos[j] = vector_alumnos[j + 1];
        vector_alumnos[j + 1] = temp;

        int temp_cables[20];
        for (k = 0; k < 20; k++) {
          temp_cables[k] = cables[j][k];
          cables[j][k] = cables[j + 1][k];
          cables[j + 1][k] = temp_cables[k];
        }

        int temp_pasos = pasos[j];
        pasos[j] = pasos[j + 1];
        pasos[j + 1] = temp_pasos;
      }
    }
  }
}

void imprimir_cabecera(char **alumnos)
{
  printf("\t\t\t**************************\n");
  printf("\t\t\t* ORDENAMIENTO DE CABLES *\n");
  printf("\t\t\t**************************\n");
  printf("\nLista de alumnos:\n");
  int i;
  for(i = 0; i < 10; i++)
  {
    printf("\t%d - %s\n", i + 1, alumnos[i]);
  }
}

int menu_alumnos(char **alumnos)
{
  limpiar_pantalla();
  imprimir_cabecera(alumnos);
  printf("Elija un alumno (Presione 0 para volver)\n");
  int opcion = obtener_input(0, 10);
  return opcion;
}

void procesar_alumno(int vector[], int longitud, int *pasos)
{
  imprimir_cables(vector, longitud);
  printf("Desea ordenar los cables? (1 - SI, 2 - NO):\n");
  int opcion = obtener_input(1, 2);

  if(opcion == 2)
    return;

  if(chequear_ordenado(vector, longitud))
  {
    printf("Los cables ya fueron ordenados previamente en %d pasos.\n", *pasos);
  } else {
    printf("\nElija un algoritmo de ordenamiento:\n1 - Burbuja\n2 - Seleccion\n");
    opcion = obtener_input(1, 2);
    *pasos = opcion == 1 
      ? ordenar_burbuja(vector, longitud) 
      : ordenar_seleccion(vector, longitud);
  }
  aguardar_enter();
}

bool chequear_ordenado(int vector[], int longitud)
{
  int i;
  for(i = 0; i < longitud - 1; i++)
  {
    if(vector[i] > vector[i + 1])
      return false;
  }
  return true;
}

void generar_matriz(int f, int c, int mat[f][c])
{
  int i, j;
  for(i = 0; i < f; i++)
  {
    generar_cables(mat[i], c);
  }
}

void generar_cables(int vector[], int longitud)
{
  int valores_generados[longitud];
  int i;
  for (i = 0; i < 20; i++)
  {
    do
    {
      vector[i] = numero_aleatorio(1, 35);
    }while(vector_contiene(vector[i], valores_generados, longitud));
    valores_generados[i] = vector[i];
  }

}

bool vector_contiene(int elemento, int vector[], int longitud)
{
  int i;
  for (i = 0; i < longitud; i++)
  {
    if (vector[i] == elemento)
    {
      return true;
    }
  }
  return false;
}

int numero_aleatorio(int min, int max)
{
  return (rand() % max - min + 1) + min;
}

void imprimir_cables(int vector[], int longitud)
{
  int i, j;
  char caracter = '*';

  for(i = 0; i < longitud; i++)
  {
    for(j = 0; j < vector[i]; j++)
    {
      printf("%c", caracter);
    }
    printf(" %d\n", vector[i]);
  }
}

int ordenar_burbuja(int vector[], int longitud)
{
  int i, j, aux, pasos = 0;
  for(i = 0; i < longitud - 1; i++)
  {
    for(j = 0; j < longitud - i - 1; j++)
    {
      if(vector[j] > vector[j + 1])	
      {
        aux = vector[j];
        vector[j] = vector[j + 1];
        vector[j + 1] = aux;
        pasos++;
        limpiar_pantalla();
        imprimir_cables(vector, longitud);
        usleep(50000);
      }
    }
  }
  printf("Ordenado en %d pasos\n", pasos);
  return pasos;
}


int ordenar_seleccion(int vector[], int longitud)
{
  int i, j, indice_minimo, aux, pasos = 0;

  for (i = 0; i < longitud - 1; i++)
  {
    indice_minimo = i;
    for (j = i+1; j < longitud; j++)
    {
      if (vector[j] < vector[indice_minimo])
        indice_minimo = j;
    }

    if(indice_minimo != i)
    {
      aux = vector[indice_minimo];
      vector[indice_minimo] = vector[i];
      vector[i] = aux;
      pasos++;
      limpiar_pantalla();
      imprimir_cables(vector, longitud);
      usleep(50000);
    }
  }
  printf("Ordenado en %d pasos\n", pasos);	
  return pasos;
}

void limpiar_pantalla()
{
  system("cls");
}

int obtener_input(int min, int max)
{
  int opcion;
  do 
  {
    printf("> ");
    scanf("%d", &opcion);
    if(opcion < min || opcion > max)
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
  while( getchar() != '\n' );
}

