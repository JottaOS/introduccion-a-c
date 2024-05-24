#include<stdio.h> 
#include<stdlib.h> 

typedef struct NODO 
{ 
    int numero; 
    struct NODO *siguiente; 
} Nodo;

void insertar_al_comienzo(Nodo **inicio_ptr, int numero); 

void burbuja(Nodo *inicio); 
  

void intercambiar(Nodo *a, Nodo *b); 
  

void imprimir(Nodo *inicio); 



int main() 
{ 
    //int arr[] = {12, 56, 2, 11, 1, 90}; 
    
	int i,nro,k=6; 
  
    /* lista vacia */
    Nodo *inicio = NULL; 
  
    
    
    for (i = 0; i< k; i++) 
    {
	 printf("inserte un numero:");
	 scanf("%d",&nro);
	 getchar();
	
     insertar_al_comienzo(&inicio, nro); 
    
	}
  
    /* print list before sorting */
    printf("\n Lista enlazada antes de ordenamiento "); 
    imprimir(inicio); 
  
    /* sort the linked list */
    burbuja(inicio); 
  
    /* print list after sorting */
    printf("\n Lista enlazada posterior a ordenamiento "); 
    imprimir(inicio); 
  
    getchar(); 
    return 0; 
} 

void insertar_al_comienzo(Nodo **inicio_ptr, int numero)
{ 
    Nodo *puntero = (Nodo*)malloc(sizeof(Nodo)); 
    puntero->numero = numero; 
    puntero->siguiente = *inicio_ptr; 
    *inicio_ptr = puntero; 
} 

void imprimir(Nodo *inicio) 
{ 
    Nodo *i = inicio; 
    printf("\n"); 
    while (i!=NULL) 
    { 
        printf("%d ", i->numero); 
        i = i->siguiente; 
    } 
} 


void burbuja(Nodo *inicio) 
{ 
    int intercambio=1, i; 
    Nodo *puntero; 
    Nodo *lista_puntero = NULL; 
  
    /* verifica si la lista esta vacio */
    if (inicio == NULL) 
        return; 
  
    while (intercambio)
    { 
        intercambio = 0; 
        puntero = inicio; 
  
        while (puntero->siguiente != lista_puntero) 
        { 
            if (puntero->numero > puntero->siguiente->numero) 
            {  
                intercambiar(puntero, puntero->siguiente); 
                intercambio = 1; 
            } 
            puntero = puntero->siguiente; 
        } 
        lista_puntero = puntero; 
    } 
    
} 

void intercambiar(Nodo *a, Nodo *b) 
{ 
    int aux = a->numero; 
    a->numero = b->numero; 
    b->numero = aux; 
}
