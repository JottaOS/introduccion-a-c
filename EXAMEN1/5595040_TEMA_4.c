/*
* Tema 4 (5p)
* Dados 5 números cargados por el usuario de 3 dígitos, ordénelos de mayor a menor, una vez ordenados
* tome los números en la posición 1, 3 y 5; y haga las siguientes operaciones: hallar el MCD (Máximo
* Común Divisor) y MCM (Mínimo Común Múltiplo). En caso de que los 3 números sean primos entre sí,
* es decir, su MCD es 1, imprima los divisores de cada número
* 
* Alumno: Juan Mendoza
*/

#include <stdio.h>
#include <stdlib.h>

int mcd(int n1, int n2);
int mcm(int n1, int n2);
void cargar_numeros(int vector[], int longitud);
int ordenar(int vector[], int longitud);
void imprimir_vector(int vector[], int longitud);
void procesar_mcd(int n1, int n2, int n3);
void proceso();


int main()
{
  proceso();
  return 0;
}

void proceso()
{
  int vector[5];
  cargar_numeros(vector, 5);
  ordenar(vector, 5);
  printf("Numeros cargados: \n");
  imprimir_vector(vector, 5);
  printf("Numeros seleccionados: %d, %d, %d.\n", vector[0], vector[2], vector[4]);
  procesar_mcd(vector[0], vector[2], vector[4]);
  int resultado_mcm = mcm(mcm(vector[0], vector[2]), vector[4]);
  printf("MCM: %d\n", resultado_mcm);

  printf("Fin del programa.\n");
}

void procesar_mcd(int n1, int n2, int n3)
{
  int resultado = mcd(mcd(n1, n2), n3);
  printf("MCD: %d\n", resultado);

  if(resultado == 1)
  {
    printf("Divisores: %d, %d, %d\n", n1, n2, n3);
  }

}


int mcd(int n1, int n2)
{
  int aux;
  while (n2 != 0) {
    aux = n2;
    n2 = n1 % n2;
    n1 = aux;
  }
  return n1;
}

int mcm(int n1, int n2)
{
  return (n1 * n2) / mcd(n1, n2);
}

void imprimir_vector(int vector[], int longitud)
{
  int i;
  printf("[");
  for (i = 0;i < longitud; i++) 
  {
    printf(" %d ", vector[i]);
  }
  printf("]\n");
}

int ordenar(int vector[], int longitud)
{
  int i, j, aux;
  for(i = 0; i < longitud - 1; i++)
  {
    for(j = 0; j < longitud - i - 1; j++)
    {
      if(vector[j] > vector[j + 1])
      {
        aux = vector[j];
        vector[j] = vector[j + 1];
        vector[j + 1] = aux;
      }
    }
  }
}

void cargar_numeros(int vector[], int longitud)
{
  int i;
  printf("Ingrese 5 numeros de 3 digitos\n");
  for(i = 0; i < longitud; i++)
  {
    int n;
    do
    {
      printf("> ");
      scanf("%d", &n);
      if(n < 100 || n > 999)
      {
        printf("\nEl numero ingresado no es de 3 digitos\n");
      }
    } while(n < 100 || n > 999);
    vector[i] = n;
  }
}

