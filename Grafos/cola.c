#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "cola.h"



int colaCreaVacia(Cola *c){
    if(c==NULL){
        return -1;
    }
    c->fondo=c->frente=NULL;
    return 0;
    
}

int colaVacia(Cola *c) {
    if (c->frente == NULL && c->fondo == NULL) {
        return 1; 
    }
    return 0; 
}


int colaInserta(Cola *c,tipoElemento elemento){
    if(c==NULL){
        return -1;
    }
    
    tipoCelda * nuevo=(tipoCelda *)malloc(sizeof(tipoCelda));
    if(nuevo==NULL){
        return -1;
    }

    if(c->frente==NULL){
        nuevo->elemento=elemento;
        nuevo->sig=NULL;
        c->frente=nuevo;
        c->fondo=nuevo;

    }else{
        nuevo->elemento=elemento;
        nuevo->sig=NULL;
        c->fondo->sig=nuevo;
        c->fondo=nuevo;
    }

    return 0;

    
}

tipoElemento colaSuprime(Cola *c){
    if(colaVacia(c)){
        return -1;
    }

    tipoCelda *aBorrar=c->frente;
    c->frente=c->frente->sig;
    tipoElemento elemento=aBorrar->elemento;
    free(aBorrar);

    if (c->frente == NULL) {
        c->fondo = NULL;
    }

    return elemento;
    
}




void imprimirc(Cola *c){
    tipoCelda *imprimir;
    if(colaVacia(c)){
        printf("La cola esta vacia...");
    }else{
        imprimir=c->frente;
        while(imprimir!=NULL){
            printf("%d ", imprimir->elemento);
            imprimir=imprimir->sig;
        }
    }
    printf("\n");


}


void liberarColac(Cola *c) {
    tipoCelda *aBorrar;
    if (c->fondo == NULL || c->frente == NULL) {
        printf("\nCola vacía...\n");
        return;
    }

    
    while (c->frente != NULL) {
        aBorrar = c->frente;       
        c->frente = c->frente->sig;     
        free(aBorrar);      
    }

    c->fondo=NULL;
    printf("\nCola liberada...\n");
}
