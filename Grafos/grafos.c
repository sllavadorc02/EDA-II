/*
 * grafos.c
 *
 *  Created on: 21/04/2014
 *      Author: MJ Polo
 */
#include <stdio.h>
#include <stdlib.h>
#include "cola.h"
#include "monticulo.h"
#include "grafos.h"
/**********************************************
/ Inicia correctamente directorio de vertices *
***********************************************/
void iniciar(tipoGrafo *g)
{
  //recorrer grafo y asignar valores de cada vertice (alc=0 oTop=0 G.ent=(primer rec a 0)nº aristas que terminan en el vertice,
  //recorrer el directorio de vertices y para cade vertice la lista de adyacencia, cada vertice nos vamos a él y se incrementa en 1
  //Hay veces que el directorio de vertices solo ponen varios campos (pej: solo vector de punteros, capo adicc y punteros de ady)
  //distancia=infinito, peso=infinito)
  int i,j;
  for(i=1; i<=g->orden ; i++){
    g->directorio[i].alcanzado=0;
    g->directorio[i].ordenTop=0;
    g->directorio[i].gradoEntrada=0;
    g->directorio[i].distancia=INF;
    g->directorio[i].peso=INF;
    g->directorio[i].anterior=0;
  }

  for(i=1; i<=g->orden; i++){
    if(g->directorio[i].lista !=NULL){
      pArco aux=g->directorio[i].lista;
      while(aux!=NULL){
        g->directorio[aux->v].gradoEntrada++;
        aux=aux->sig;
      }

    }

  }


}
void profundidadMejorado(int v_inicio,tipoGrafo *g)
{
  //corregir que no sea conexo
  //campo alcanzado se pone a 1 si se han visitado todos los nodos
  //buscar el primer vertice que no ha sido alcanzado(0), invoca la funcion profundidad ese que no se ha visitado
  iniciar(g);
  profundidad(v_inicio, g);
  for(int i=1; i<=g->orden; i++){
    if(g->directorio[i].alcanzado ==0){
      profundidad(i, g);
      
    }
  }

}
void amplitudMejorado(int v_inicio,tipoGrafo *g)
{
  //buscar el primer vertice que no ha sido alcanzado (0), invoca la funcion profundidad ese que no se ha visitado
  //todos los que tienen un 0 en alzanzado
  iniciar(g);
  amplitud(v_inicio, g);
  for(int i=1; i<=g->orden; i++){
    if(g->directorio[i].alcanzado ==0){
      amplitud(i, g);
    
    }
  }

}

/***************/
/* Ejercicio 2 */
/***************/

int ordenTop1(tipoGrafo *grafo)
{
  //recorrer y que esten ordenados (orden n²)
  //itera el numero de vertices
  //dos bucles anidados que recorre el mismo grafo
  //si hay un vertice del que no puedes establecer orden topologico hay un ciclo
  //return -1
  int orden;
  pArco p;
  int v,w;
  iniciar(grafo);
  for(orden=1; orden<=grafo->orden; orden++){
    v=buscarVerticeGradoCeroNoOrdenTop(grafo);
    if(v==-1){
      return -1;
    }else{
      grafo->directorio[v].ordenTop=orden;
      p=grafo->directorio[v].lista;
      while(p!=NULL){
        w=p->v;
        grafo->directorio[w].gradoEntrada=grafo->directorio[w].gradoEntrada - 1;
        p=p->sig;
      }

    }

  }


}

int buscarVerticeGradoCeroNoOrdenTop(tipoGrafo *g){
  for(int i=1; i<=g->orden;i++){
    if(g->directorio[i].gradoEntrada==0 && g->directorio[i].ordenTop==0){
      return i;
    }

  }

  return -1;

}



int ordenTop2(tipoGrafo *grafo)
{
  //con una cola se elimina la busqueda secuencial (orden n)
  //aplicar cuando el vertice es -1, no encontró, hay un ciclo
  //no aparece en el pseudocódigo
  //return 0 en exito y -1 en fallo
  //mientras iteraría el numero de vertices, salvo que la cola se vacíe y sigas algunos vertices con el orden topologico
  //orden se inicia a uno y cada uno que econtremos con grado de entrada y topologico a 0 incrementa y asigna el orrdem
  //si hay un ciclo el bucle mientras acaba antes, orden tendrá un 
  //si orden==orden grafo perfe, si no pues ha habido ciclo
}


/***************/
/* Ejercicio 3 */
/***************/


//Camino minimo-> diapositivas
//importante llamar a la funcion inicia() -> O(n²)
//trayectoria guardado en anterior y se guarda inversamente
//yistra -< en evz de sumar en uno la distancia se suman los pesos
//quita un bucle y añade una cola  (nueva version) -> O(n)
//tambien se guarda en orden inverso

//para probar implemenatar los apartados a) y b) finales
//proporcional la trayectoria en orden correcto, costes ya calculados en directorio vertices
//interpretar anterior en fichero vertices
//estructura dinamica->  pila (guardar los anteriores)
//cuando vacíe la pila da el recorrido de trayectoria en orden directo
//penaliza si usamos un vector

//coste y trayectoria a todos los vertices menos vinicio
//dijkstra -> O(n²)
//se usa un monticulo para la mejora
//clave -> clave de ordenacion, criterio
//informacion -> destino de esa arista
//(mas adelante guardar la arista, es decir, guardando los dos vertices struct con dos vertices)
//mas adelante modificar el algoritmo

//sin mejora
void caminos1(int vInicio, tipoGrafo *g){
  pArco p;
  int v,w;
  int distanciaActual;
  iniciar(g);
  g.directorio[vInicio].distancia=0;
  for(distanciaActual=0; distanciaActual<g.orden; distanciaActual++){
    for(v=1; v<=g.orden; v++){
      if(!(g.directorio[v].alcanzado) && (g.directorio[v].distancia==distanciaActual)){
        g.directorio[v].alcanzado=1;
        p=g.directorio[v].lista;
        while(p!=NULL){
          w=p->v;
          if(g.directorio[w].distancia=INF){
            g.directorio[w].distancia=g.directorio[v].distancia + 1;
            g.directorio[w].anterior=v;

          }
          p=p->sig;
        }
      }
    }
  }

}

//con mejora
void caminos2(int vInicio, tipoGrafo *g){
  pArco p;
  int v,w;
  Cola c;
  iniciar(g);
  g.directorio[vInicio].distancia=0;
  colaCreaVacia(&c);
  colaInserta(&c, vInicio);
  while(!colaVacia(&c)){
    v=colaSuprime(&c);
    p=g.directorio[v].lista;
    while(p!=NULL){
      w=p->v;
      if(g.directorio[w].distancia=INF){
        g.directorio[w].distancia=g.directorio[v].distancia + 1;
        g.directorio[w].anterior=v;
        colaInserta(&c, w);

      }

      p=p->sig;

    }
  }

}


/* b) PONDERADOS */
//sin mejora
void dijkstra1(int vInicio, tipoGrafo *g){
  pArco p;
  int v,w;
  int distanciaActual;
  int i;
  iniciar(g);
  g.directorio[vInicio].distancia=0;
  for(i=1; i<=g.orden; i++){
    v=buscarVerticeDistanciaMinimaNoAlcanzado(g);
    g.directorio[v].alcanzado=1;
    p=g.directorio[v].lista;
    while(p!=NULL){
      w=p->v;
      if(!g.directorio[w].alcanzado){
        if(g.directorio[v].distancia + p->peso < g.directorio[w].distancia){
          g.directorio[w].distancia=g.directorio[v].distancia+p->peso;
          g.directorio[w].anterior=v;

        }
      }
      p=p->sig;
    }
  }

}

//con mejora
void dijkstra2(int vInicio, tipoGrafo *g){
  Monticulo m;
  tipoElementoM x;
  int v, w;
  iniciar(g);
  g.directorio[vInicio].distancia=0;
  iniciaMonticulo(&m);
  x.clave=0;
  x.informacion=vInicio;
  insertar(x, &m);
  while(!vacioMonticulo(m)){
    int err=eliminarMinimo(&m, &x);
    v=x.informacion;
    if(!g.directorio[v].alcanzado){
      g.directorio[v].alcanzado=1;
      p=g.directorio[v].lista;
      while(p!=NULL){
        w=p->v;
        if(!g.directorio[w].alcanzado){
          if(g.directorio[v].distancia+p->peso < g.directorio[w].distancia){
            g.directorio[w].distancia=g.directorio[v].distancia+ p->peso;
            g.directorio[w].anterior=v;
            x.clave=g.directorio[w].distancia;
            x.informacion=w;
            insertar(x, &m);
          }
        }
        p=p->sig;
      }
    }
  }
}

/* Interpretación de los algoritmos ¡Secuencia de vértices en caminos mínimos y distancias !!! */

int buscarVerticeDistanciaMinimaNoAlcanzado(tipoGrao *g){

}


int costeyTrayectoria(int vIni, int vFin, tipoGrafo *g){

}
void todosCaminosMin(int vIni, tipoGrafo *g){

}

/******************************************************************************/
/* Recorrido en PROFUNDIDAD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/*********************************************************************************/
void profundidad(int v_inicio,tipoGrafo * grafo)
{ int w;
  pArco  p;
  printf("%d ",v_inicio);
  grafo->directorio[v_inicio].alcanzado=1;
  p = grafo->directorio[v_inicio].lista;
  while (p!=NULL)
  { w=p->v;
    if (!grafo->directorio[w].alcanzado)
        profundidad(w,grafo);
    p = p->sig;
  }
}
/************************************************************************************************/
/* Recorrido en AMPLITUD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/************************************************************************************************/
void amplitud(int v_inicio,tipoGrafo *grafo)
{ int w;
  pArco  p;
  Cola c;

  colaCreaVacia(&c);
  colaInserta(&c,v_inicio);
  while (!colaVacia(&c))  {
	w =colaSuprime(&c);
        if (!grafo->directorio[w].alcanzado) {
		printf("%d ",w);
	        grafo->directorio[w].alcanzado=1;
        	p =grafo->directorio[w].lista;
 		while (p!=NULL){
			w = p->v;
			colaInserta(&c,w);
			p = p->sig;
		}
	}
  }
	  
}
/**********************************************************************************************/
/* Función auxiliar para ver el contenido de la estructura que representa un grafo en memoria */
/**********************************************************************************************/
void verGrafo(tipoGrafo *g)
{  int i;
   pArco p;

   printf("\nGrafo  (Orden %d)\n\n",g->orden);
   printf("       alc gEnt oTop dist peso ant \n");
   printf("     +----+----+----+----+----+----+\n");

   for(i=1;i<=g->orden;i++)
   {  printf("  %2d | %2d | %2d | %2d |", i, g->directorio[i].alcanzado,
                       g->directorio[i].gradoEntrada, g->directorio[i].ordenTop);
       if (g->directorio[i].distancia == INF) printf("  * |");
       else   printf(" %2d |", g->directorio[i].distancia);
       if (g->directorio[i].peso == INF) printf("  * |");
       else   printf(" %2d |", g->directorio[i].peso);
       printf(" %2d |",g->directorio[i].anterior);
       p = g->directorio[i].lista;
       while (p != NULL)
       {   printf(" ->%2d", p->v);	// Grafos no ponderados
           //printf(" ->%2d, %2d", p->v, p->peso); // Grafos ponderados
           p = p->sig;
       }
       printf("\n");
   }
   printf("     +----+----+----+----+----+----+\n\n");
}


//Hay veces que dicen en los examenes que nos digan porque se mejoró la segunda version
//de que orden sería y como mejora, como sé que tiene un ciclo

//liberarListas(tipoGrafo *g){
//  pArco aix, aBorrar;
//  int i;
//  for
//}