#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conjuntos.h"

/// Incluir aqui las funciones que implementan las tres operaciones básicas 
/// en la representación de CONJUNTOS DISJUNTOS mediante LISTAS
/// ......................................................................





void verParticion(particion P)
{ int i;
   tipoCelda *aux;
    for (i =0;i<MAXIMO;i++) {
         aux = P[i].primero;
         if (aux!=NULL)  printf("\n\nClase equivalencia representante %d: ",i);
        while (aux!=NULL)
        { printf("%d ",aux->elemento);
         aux=aux->sig;
        }
    }
}

void verClaseEquivalencia(tipoElemento x,particion P)
{ int representante;
  tipoCelda *aux;
  
    representante = buscar(x,P);
    printf("\n\nClase de Equivalencia de %d cuyo representante es %d: ", x,representante);
    aux = P[representante].primero;
    while (aux)
        { printf(" %d ",aux->elemento);
          aux=aux->sig;
        }
    printf("\n\n");
}

//crear, cada celda una estructura tipo lista (primero y último) con su nodo conteniendo el valor
//si hay fallo en reserva, liberar todos los nodos anteriores y devolver error
void crea(particion P){
  for(int i=0; i<MAXIMO; i++){
    tipoLista *cel=malloc(sizeof(tipoLista));

    if (cel==NULL){
      printf("Error al crear la particion...\n");
      liberarParticion(P);
      return;
    }

    tipoCelda *nuevo=malloc(sizeof(tipoCelda));
    if(nuevo==NULL){
      printf("Error al crear nodo particion...\n");
      liberarParticion(P);
      return;
    }
    nuevo->elemento=i;
    cel->primero=nuevo;
    cel->ultimo=nuevo;
    P[i]=*cel;

  }

}

//recorrer el vector y si existe recorrer la lista enlazada mirando tipo elemento
//cuando encuentras uno, devuelves el indice del vector
//comprobar que es representanet de él mismo
tipoConjunto buscar(tipoElemento x, particion P){
  tipoCelda *aux;
  for(int i=0; i<MAXIMO; i++){
    if(P[i].primero!=NULL){
      aux=P[i].primero;
      while(aux!=NULL){
        if(aux->elemento==x){
          return i;
        }
        aux=aux->sig;
      }

    }
   
  }
  
  return -1;

}

//comprobar que son representantes 'x' e 'y'
//basta con saber que primero y último no son null (y ver tipoElemento)
//concatenar la lista, y el que se queda sin ser representante se apuntan su primero y ultimo a null
//comp -> conjuntos dentro del vector, cada uno representante, distintos, 

int unir(tipoConjunto x, tipoConjunto y, particion P){
  if(P[x].primero==NULL || P[y].primero==NULL || y==x ){
    return 0;
  }
  
  P[x].ultimo->sig=P[y].primero;
  P[x].ultimo=P[y].ultimo;

  P[y].ultimo=NULL;
  P[y].primero=NULL;
  return 1;
}

//hacer funcion para hacer free de todos los nodos (liberarParticion/destruirParticion)

int liberarParticion(particion P){

  for(int i=0; i<MAXIMO; i++){
    
    while(P[i].primero !=NULL){
      tipoCelda *temp=P[i].primero;
      P[i].primero=P[i].primero->sig;
      free(temp);
    }

    P[i].primero=NULL;
    P[i].ultimo=NULL;
      
    
    
  }

  return 1;
}