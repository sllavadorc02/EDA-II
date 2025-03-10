#include <stdlib.h>
#include <stdio.h>
#include "monticulo.h"
int main(void){ 
  Monticulo m;
  tipoElemento elemento;
  int i,n=10;

  iniciaMonticulo(&m);
  elemento.clave=12;
  elemento.informacion=0;

  i=insertar(elemento,&m);

  while (m.tamanno<n){ 
    elemento.clave=rand()%100;
    i = insertar(elemento,&m);
  }
  printf("Los elementos del arbol: \n");
  for (i=1;i<=m.tamanno;i++){
    printf("%d ",m.elemento[i].clave);
  }

  printf("\n");
  int orden=esMonticulo(m);
  if(orden==0){
    printf("El monticulo NO sigue la propiedad del orden...\n");
  }else if(orden==1){
    printf("El monticulo sigue la propiedad del orden...\n");
  }else{
    printf("Error al comprobar el orden...\n");
  }
  printf("\n");

  printf("Los elementos del arbol despues de DECREMENTAR \n");
  decrementarClave(2,10,&m);
  for (i=1;i<=m.tamanno;i++){
    printf("%d ",m.elemento[i].clave);
    
  }
  printf("\n");

  orden=esMonticulo(m);
  if(orden==0){
    printf("El monticulo NO sigue la propiedad del orden...\n");
  }else if(orden==1){
    printf("El monticulo sigue la propiedad del orden...\n");
  }else{
    printf("Error al comprobar el orden...\n");
  }
  printf("\n");

  printf("Los elementos del arbol despues de INCREMENTAR: \n");
  incrementarClave(2,100,&m);
  for (i=1;i<=m.tamanno;i++){
    printf("%d ",m.elemento[i].clave);
    
  }
  printf("\n");

  incrementarClave(2,100,&m);
  for (i=1;i<=m.tamanno;i++){
    printf("%d ",m.elemento[i].clave);
    
  }
  printf("\n");
  orden=esMonticulo(m);
  if(orden==0){
    printf("El monticulo NO sigue la propiedad del orden...\n");
  }else if(orden==1){
    printf("El monticulo sigue la propiedad del orden...\n");
  }else{
    printf("Error al comprobar el orden...\n");
  }
  printf("\n");



  tipoElemento minimo;
  int min=eliminarMinimo(&m, &minimo);
  printf("Los elementos del arbol despues de eliminar el menor (%d): \n", minimo.clave);
  for (i=1;i<=m.tamanno;i++){
    printf("%d ",m.elemento[i].clave);
  }
  printf("\n");

  orden=esMonticulo(m);
  if(orden==0){
    printf("El monticulo NO sigue la propiedad del orden...\n");
  }else if(orden==1){
    printf("El monticulo sigue la propiedad del orden...\n");
  }else{
    printf("Error al comprobar el orden...\n");
  }


  int elm[10]={1,5,32,2,56,22,45,69,54,30};
  Monticulo mm=contruirMonticulo(elm, 10);
  for (i=1;i<=m.tamanno;i++){
    printf("%d ",mm.elemento[i].clave);
  }
  printf("\n");
  orden=esMonticulo(mm);
  if(orden==0){
    printf("El monticulo NO sigue la propiedad del orden...\n");
  }else if(orden==1){
    printf("El monticulo sigue la propiedad del orden...\n");
  }else{
    printf("Error al comprobar el orden...\n");
  }

}




