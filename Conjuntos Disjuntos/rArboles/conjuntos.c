#include "conjuntos.h"
#include <stdio.h>


/// Incluir aqui las funciones que implementan las tres operaciones básicas 
/// en la representación de CONJUNTOS DISJUNTOS mediante ÁRBOLES
/// ......................................................................

// ARBITRARIO

/*
void crea(particion P){
    for (int i = 0; i < MAXIMO; i++)
    {
        P[i]=i;
    }

}

tipoConjunto buscar(tipoElemento x, particion P){

    while(P[x]!=x){
        x=P[x];
    }

    return x;
}


int unir(tipoConjunto x, tipoConjunto y, particion P){
    if(P[x]!=x || P[y]!=y){
        return -1;
    }

    P[y]=x;
    return 0;
}
*/



/*
// POR TAMAÑO
void crea(particion P){
    for (int i = 0; i < MAXIMO; i++)
    {
        P[i]=-1;
    }

}

tipoConjunto buscar(tipoElemento x, particion P){

    while(P[x]>=0){
        x=P[x];
    }

    return x;
}

int unir(tipoConjunto x, tipoConjunto y, particion P){
    if(P[x]>=0 || P[y]>=0){
        return 0;
    }

    if(x==y){
        return 0;
    }

    if(P[x]<=P[y]){ //si son iguales el primero la raiz, sino el de menor tamaño
        P[x]+=P[y];   //sumo los tamaños
        P[y]=x;
        
    }else{
        P[y]+=P[y];   
        P[x]=y;
        
    }
    
    return 1;

}

*/


// ALTURA

void crea(particion P){
    for (int i = 0; i < MAXIMO; i++)
    {
        P[i]=-1;
    }

}

tipoConjunto buscar(tipoElemento x, particion P){

    while(P[x]>=0){
        x=P[x];
    }

    return x;
}

int unir(tipoConjunto x, tipoConjunto y, particion P){
    if(P[x]>=0 || P[y]>=0){
        return 0;
    }


    if(P[x]>=P[y]){
        P[x]--;
        P[y]=x;
    }else{
        P[x]=y;
    }


    return 1;

}







//
// Función auxiliar para ver contenido de Partición 
//
void verParticion(particion P)
{ int i;
    printf("\n");
    for (i =0;i<MAXIMO;i++) printf("|%2d",P[i]);
    printf("| contenido  vector\n");
    for (i =0;i<MAXIMO;i++) printf("---");
    printf("\n");
    for (i =0;i<MAXIMO;i++) printf(" %2d",i);
    printf("  índices vector\n\n");
}
