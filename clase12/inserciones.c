
#include <stdio.h> 
#include <stdlib.h> 
  

typedef struct NODO 
{ 
  int numero; 
  struct NODO *siguiente; 
} Nodo; 
  
void push(Nodo** cabecera_ref, int nuevo_nro) 
{ 
    
    Nodo *nuevo_nodo = (Nodo*) malloc(sizeof(Nodo)); 
  
    
    nuevo_nodo->numero  = nuevo_nro; 
  
    
    nuevo_nodo->siguiente = (*cabecera_ref); 
  
   (*cabecera_ref)    = nuevo_nodo; 
} 
  

void inserta_despues(Nodo* nodo_previo, int nuevo_nro) 
{ 
    
    if (nodo_previo == NULL) 
    { 
      printf("El anterior no puede estar vacio"); 
      return; 
    } 
  
    
    Nodo* nuevo_nodo =(Nodo*) malloc(sizeof(Nodo)); 
  
    
    nuevo_nodo->numero  = nuevo_nro; 
  
    
    nuevo_nodo->siguiente = nodo_previo->siguiente; 
  
    
    nodo_previo->siguiente = nuevo_nodo; 
} 
  
void append(Nodo** cabecera_ref, int nuevo_nro) 
{ 
  
    Nodo* nuevo_nodo = (Nodo*) malloc(sizeof(Nodo)); 
  
    Nodo *ultimo = *cabecera_ref; 
  
    
    nuevo_nodo->numero  = nuevo_nro; 
  
   
    nuevo_nodo->siguiente = NULL; 
  
    if (*cabecera_ref == NULL) 
    { 
       *cabecera_ref = nuevo_nodo; 
       return; 
    } 
      
    while (ultimo->siguiente != NULL) 
        ultimo = ultimo->siguiente; 
  
   
    ultimo->siguiente = nuevo_nodo; 
    return; 
} 
  
void imprimir(Nodo *nodo) 
{ 
  while (nodo != NULL) 
  { 
     printf(" %d ", nodo->numero); 
     nodo = nodo->siguiente; 
  } 
} 
  

int main() 
{ 

  Nodo *cabecera = NULL; 
  
  // Inserta 6.  lista: 6->NULL 
  append(&cabecera, 6); 
  
  // Inserta 7 al comienzo. Lista: 7->6->NULL 
  push(&cabecera, 7); 
  
  // Inserta 1 al comienzo. lista:1->7->6->NULL 
  push(&cabecera, 1); 
  
  // Inserta 4 al final. lista: 1->7->6->4->NULL 
  append(&cabecera, 4); 
  
  // Inserta 8, despues de 7. lista: 1->7->8->6->4->NULL 
  inserta_despues(cabecera->siguiente, 8); 
  
  printf("\n lista enlazada: "); 
  imprimir(cabecera); 
  
  return 0; 
} 
