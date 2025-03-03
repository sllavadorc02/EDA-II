#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

int main(void)
{ Arbol varArbol;

/* Creación arbol ejemplo de las transparencias de recorridos */
  varArbol = creaNodo('A');
  varArbol->izq=creaNodo('B');
  varArbol->der = creaNodo('C');
  varArbol->izq->izq=creaNodo('D');
  varArbol->izq->der=creaNodo('E');
  varArbol->der->izq=creaNodo('F');
  varArbol->der->der=creaNodo('G');

/* Aplicación de recorridos al arbol ejemplo */

  printf("Recorrido en PRE_ORDEN: ");
  preOrden(varArbol);
  printf("\n");
  printf("Recorrido en ORDEN: ");
  enOrden(varArbol);
  printf("\n");
  printf("Recorrido en POST_ORDEN: ");
  postOrden(varArbol);
  printf("\n");
  printf("Recorrido en AMPLITUD: ");
  amplitud(varArbol);
  printf("\n");

/* Comenzar a implementar y probar las funciones del ejercicio 2 ... y segunda parte del ejercicio 3 */
 
  printf("El arbol tiene de altura: %d\n", altura(varArbol));
  printf("Tiene %d nodos \n", numNodos(varArbol));
  int sust=sustiuye(varArbol, 'F', 'D');
  printf("Se hacen un total de %d sustituciones\n", sust);
  preOrden(varArbol);
  printf("\n");
  printf("Hay %d nodos hoja \n", numNodosHoja(varArbol));
  printf("Hay %d nodos internos \n", numNodosInternos(varArbol));
  printf("Hay %d hijos únicos\n", numHijoUnico(varArbol));
  Arbol max=buscarMax(varArbol);
  Arbol min = buscarMin(varArbol);
  printf("El valor maximo es %c y el minimo %c \n", max->info, min->info);
  
  Arbol nuevo;
  nuevo=creaNodo('a');
  int sim=similares(varArbol, nuevo);
  if(sim==0){
    printf("Estos árboles no son similares\n");
  }else{
    printf("Los arboles son similares\n");
  }

  int eq=equivalentes(varArbol, varArbol);
  if(eq==0){
    printf("Estos árboles no son equivalentes\n");
  }else{
    printf("Los arboles son equivalentes\n");
  }

  Arbol esp=especular(varArbol);
  printf("El arbol especulado: ");
  preOrden(esp);
  printf("\n");


  varArbol=anula(varArbol);
  if(varArbol ==NULL){
    printf("Arbol anulado...\n");
  }
    
  return 1;
}

