#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pila.h"



int pilaCreaVacia(Pila *p){
    if(p==NULL){
        return -1;
    }

    *p=NULL;
    return 0;
}


int pilaVacia(Pila *p){
    if(*p==NULL || p==NULL){
        return 1;
    }
    
    return 0;
}


int pilaInserta(Pila *p,tipoElemento elemento){
    if(p==NULL){
        return -1;
    }


    tipoCelda *nuevo=(tipoCelda *)malloc(sizeof(tipoCelda));
    if(nuevo== NULL){
        return -2;
    }

    nuevo->elemento=elemento;
    nuevo->sig=*p;
    *p=nuevo;

    return 0;
}

tipoElemento pilaSuprime(Pila *p){
   if(*p==NULL || p==NULL){
        return NULL;
   }
    tipoElemento el;
    tipoCelda *aBorrar;
    aBorrar=*p;
    *p=aBorrar->sig;
    el=aBorrar->elemento;
    free(aBorrar);

    return el;

}


/*
void imprimirp(Pila *p){
    tipoCelda *imprimir;

    if(pilaVacia(p)){
        printf("La pila esta vacia...");
    }else{
        imprimir=*p;
        while(imprimir!=NULL){
            printf("%d ", imprimir->elemento);
            imprimir=imprimir->sig;
        }
    }
    printf("\n");

}

*/


void liberarp(Pila *p) {
    tipoCelda *aBorrar;
    if (p == NULL || *p == NULL) {
        printf("\nPila vacía...\n");
        return;
    }

    
    while (*p != NULL) {
        aBorrar = *p;       
        *p = (*p)->sig;     
        free(aBorrar);      
    }

    printf("\nPila liberada...\n");
}
