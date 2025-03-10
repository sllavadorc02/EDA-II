#include "conjuntos.h"
#include <stdio.h>
/// Incluir aqui las funciones que implementan las tres operaciones básicas 
/// en la representación de CONJUNTOS DISJUNTOS mediante MATRICES
/// ......................................................................




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


//crear, cada celda su mismo indice
//indice(numeros, valores) elementos(equivalendiaS)
void crea(particion P){
    for(int i=0; i<MAXIMO; i++){
        P[i]=i;
    }
}



//no se puede usar dentro de unir
//particion y del indice devuelves lo que hay en el elemento
tipoConjunto buscar(tipoElemento x, particion P){
    return P[x];
}



//reciben siempre representantes de eq
//el primero es el nuevo representante(x) de clase eq resultante
//el y pasa a ser de clase de x
//buscar todos los elementos que tengan 'y' y sustituirlo por 'x'
//devuelve verd -> cuando dos recibidos son representante, falso -> alguno de los dos no representante
//si el elemento 'y' no tiene almacenado en su celda 'y' entonces no es representante
int unir(tipoConjunto x, tipoConjunto y, particion P){
    if(P[x]!=x || P[y]!=y){
        return 0;
    }

    for(int i=0; i<MAXIMO; i++){
        if(P[i]==y){
            P[i]=x;
        }
    }

    return 1;
}