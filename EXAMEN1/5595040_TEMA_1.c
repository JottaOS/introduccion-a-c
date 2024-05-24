/*
 * Tema 1 (5p)
 * El número 6174 es conocido como la Constante de Kaprekar en honor de su
 * descubridor el matemático indio Dattatreya Ramachandra Kaprekar.
 * Dado un número de 4 dígitos (NU) donde no pueden ser todos iguales (si pueden haber tres dígitos
 * iguales, así como ceros delante) cargado por el usuario, haga un programa que permita indicar en
 * cuantos pasos se llega la constante de Kaprekar.
 * Para hallar la constante se debe repetir n veces (pasos a hallar) los siguientes pasos: guardar en 2
 * variables numéricas el numero resultante de ordenar de mayor a menor los dígitos de NU (M) y el
 * numero resultante de ordenar de menor a mayor los dígitos de NU(m), realice D=M-m si el numero D
 * es 6174 diga en cuantos pasos lo halló si no, NU=D y se debe repetir el proceso con las dos variables.
 *
 *
 */

#include <stdio.h>

void proceso();
int ingresar_numero();
int chequear_repetidos(int n);
int obtener_numero_ascendente(int digitos[]);
int obtener_numero_descendente(int digitos[]);

int main()
{
  proceso();
  return 0;
}
 
void proceso() {
  int nu = ingresar_numero();
  int pasos = 0;
  int i, j;
  while (nu != 6174) {

    int digitos[4];
    digitos[0] = nu / 1000;
    digitos[1] = (nu % 1000) / 100;
    digitos[2] = (nu % 100) / 10;
    digitos[3] = nu % 10;

    int m = obtener_numero_ascendente(digitos);
    int M = obtener_numero_descendente(digitos);
    int diferencia = M - m;

    printf("paso:%d max:%d min:%d diferencia:%d\n", pasos + 1, M, m, diferencia);
	pasos++;
    if (diferencia == 6174)
      break;

    nu = diferencia;
    
  }

  printf("Pasos: %d", pasos);

}

int obtener_numero_ascendente(int digitos[]) {
	int i, j;
    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 4; j++) {
            if (digitos[j] < digitos[i]) {
                int temp_val = digitos[i];
                digitos[i] = digitos[j];
                digitos[j] = temp_val;
            }
        }
    }

    return digitos[0] * 1000 + digitos[1] * 100 + digitos[2] * 10 + digitos[3];
}

int obtener_numero_descendente(int digitos[]) {
	int i, j;

    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 4; j++) {
            if (digitos[j] > digitos[i]) {
                int temp_val = digitos[i];
                digitos[i] = digitos[j];
                digitos[j] = temp_val;
            }
        }
    }

    return digitos[0] * 1000 + digitos[1] * 100 + digitos[2] * 10 + digitos[3];
}

int chequear_repetidos(int n)
{
  if(n < 999 && n > 0)
  {
    return 0; 
  }
  
  int digito = n % 10;
  while (n != 0)
  {
    int digito_actual = n % 10;
    n = n / 10;
    if (digito_actual != digito)
    {
      return 0;
    }
  }

  return 1;
}

int ingresar_numero() 
{
    int n;
    
    do {
        printf("Cargue el numero de 4 digitos (se rellenara con 0 a la izquierda): ");
        scanf("%d", &n);
        printf("Numero ingresado: %04d\n", n);

        if(n > 9999)
        {
          printf("El numero ingresado no puede ser superior a 4 digitos. ");
        }

        if (chequear_repetidos(n)) {
            printf("Digitos repetidos.");
        }
        printf("\n");
    } while (chequear_repetidos(n) || n > 9999);

    return n;
}

