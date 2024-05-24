#include <stdio.h> 

typedef struct NODO  
{ 
    int dato; 
    struct NODO* sgte; 
} Nodo; 
  

struct Nodo* intercambiar(Nodo* ptr1,Nodo* ptr2) ;
int burbuja(Nodo** cabecera, int contador) ;
void imprimir(Nodo* n) ;
void insertar_comienzo(Nodo** comienzo, int dato) ;

int main() 
{ 
    int vec[] = { 78, 20, 10, 32, 1, 5 }; 
    int tam, i; 
  
    
    Nodo* comienzo = NULL; 
    tam = sizeof(vec) / sizeof(vec[0]); 
  
    
    for (i = 0; i < tam; i++) 
        insertar_comienzo(&comienzo, vec[i]); 
  
    
   printf("Lista antes de ordenar:\n");
    imprimir(comienzo); 
    printf("\n");
  
    
    burbuja(&comienzo, tam); 
  
    
   printf("Lista despues de ordenar:\n");
    imprimir(comienzo); 
  printf("\n");
    return 0; 
} 
  
struct Nodo* intercambiar(Nodo* ptr1,Nodo* ptr2) 
{ 
    Nodo* tmp = ptr2->sgte; 
    ptr2->sgte = ptr1; 
    ptr1->sgte = tmp; 
    return ptr2; 
} 
  

int burbuja(Nodo** cabecera, int contador) 
{ 
    Nodo** h; 
    int i, j, intercambio; 
  
    for (i = 0; i <= contador; i++) 
    { 
  
        h = cabecera; 
        intercambio = 0; 
  
        for (j = 0; j < contador - i - 1; j++)  
        { 
  
            Nodo* p1 = *h; 
            Nodo* p2 = p1->sgte; 
  
            if (p1->dato > p2->dato) 
            { 
  

                *h = intercambiar(p1, p2); 
                intercambio = 1; 
            } 
  
            h = &(*h)->sgte; 
        } 
  

        if (intercambio == 0) 
            break; 
    } 
} 
  

void imprimir(Nodo* n) 
{ 
    while (n != NULL) 
    { 
        printf("%d ->",n->dato) ;
        n = n->sgte; 
    } 

} 
  
void insertar_comienzo(Nodo** comienzo, int dato) 
{ 
     Nodo* ptr1 = (struct NODO*) malloc(sizeof(struct NODO*)); 
  
    ptr1->dato = dato; 
    ptr1->sgte = *comienzo; 
    *comienzo = ptr1; 
} 
  
 
