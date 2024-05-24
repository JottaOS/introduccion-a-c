/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int azar();
void proceso();
int cant();

int main()
{
    srand((unsigned)time(NULL));
    proceso();
    return 0;
}

void proceso(){
    int v[15];
    int n = cant(); 
    for (int i = 0; i < n; i++) {
        v[i] = azar();
        printf("\n %d", v[i]);
    }
    int aux;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(v[i]<v[j]){
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
             
        }
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("\n %d", v[i]);
    }
}

int cant(){
    int n = 0;
    do{
        printf("Ingresa la cantidad de elementos del vector (min 5 ; max 15): ");
        scanf("%d", &n);
        if(n<5 || n>15){
            printf("Error, rango incorrecto.\n");
        }
        
    }while(n<5 || n>15);
    
    return n;
}

int azar(){
    return 100 + rand() % (999 - 100 + 1);
}

