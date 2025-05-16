#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbolBB.h"


#ifdef EJERCICIO1
/******************************************************************
* Árboles Binarios de Búsqueda SIN CLAVES REPETIDAS
* Se incluye un poco de código para mostrar la diferencia entre   *
* insertar (paso por referencia) y buscar                         * 
*******************************************************************/

int insertar(tipoArbolBB *raiz,tipoClave clave){ 
  	if (*raiz==NULL){
		tipoNodo *nuevo= creaNodo(clave, 1);
		if(!nuevo){
			return -1;
		}
		*raiz=nuevo;
		return 0;
	}else if(clave == (*raiz)->clave){
		(*raiz)->info++;
		return -1;
  	} else if (clave < (*raiz)->clave){
        return insertar(&(*raiz)->izq, clave);
	}else if (clave > (*raiz)->clave){
        return insertar(&(*raiz)->der, clave);
	}
	
}

int buscar(tipoClave clave,tipoArbolBB raiz, tipoNodo **nodo){
	if (raiz==NULL){
		*nodo=NULL;
		return 0;
	}else if(clave==raiz->clave){
		*nodo=raiz;
		return raiz->info;
	}else if (clave < raiz->clave){
        return buscar(clave, raiz->izq, nodo);
	}else if(clave > raiz->clave){
		return buscar(clave, raiz->der, nodo);
	}

  return -1;
}

int eliminar(tipoArbolBB *raiz, tipoClave clave){
	if(*raiz==NULL){
		return -1;
	}

	if(clave < (*raiz)->clave){
		return eliminar(&(*raiz)->izq, clave);
	}else if(clave > (*raiz)->clave){
		return eliminar(&(*raiz)->der, clave);
	}else{
		tipoArbolBB *aux=raiz;
		if((*aux)->der==NULL){
			*raiz=(*aux)->izq;
			free(aux);
		}else if((*aux)->izq==NULL){
			*raiz=(*aux)->der;
			free(aux);
		}else{
			tipoNodo *sucesor=(*aux)->der;
			tipoNodo *padreSucesor=*aux;
				//más a la izq del subarbol derecho
			while(sucesor->izq !=NULL){
				padreSucesor=sucesor;
				sucesor=sucesor->izq;
			}
				
			(*raiz)->clave=sucesor->clave;
			(*raiz)->info=sucesor->info;
					
			if(padreSucesor==*raiz){
				padreSucesor->der=sucesor->der;
			}else{
				padreSucesor->izq=sucesor->der;
			}
			free(sucesor);
		}
		return 0;
	}
}



#endif

#ifdef EJERCICIO3
/******************************************************
* Árboles Binarios de Búsqueda CON CLAVES REPETIDAS   *
******************************************************/
int insertar(tipoArbolBB *raiz,tipoClave clave, tipoInfo info){ 
	if (*raiz==NULL){
		tipoNodo *nuevo= creaNodo(clave, info);
		if(!nuevo){
			return -1;
		}
		*raiz=nuevo;
		return 0;
	}else if(clave == (*raiz)->clave){
		tipoNodo *nuevo= creaNodo(clave, info);
		if(!nuevo){
			return -1;
		}
		nuevo->der=(*raiz)->der;
		(*raiz)->der=nuevo;
		return 0;
  	} else if (clave < (*raiz)->clave){
        return insertar(&(*raiz)->izq, clave, info);
	}else if (clave > (*raiz)->clave){
        return insertar(&(*raiz)->der, clave, info);
	}
  
}


int eliminar(tipoArbolBB *raiz, tipoClave clave) {
    int contador=0;
	
	while(*raiz!=NULL){
		if(clave < (*raiz)->clave){
			raiz=&(*raiz)->izq;
		}else if(clave > (*raiz)->clave){
			raiz=&(*raiz)->der;
		}else{
			contador++;
			tipoNodo *actual=*raiz;

			if(actual->der==NULL){
				*raiz=actual->izq;
				free(actual);
			}else if(actual->izq==NULL){
				*raiz=actual->der;
				free(actual);
			}else{
				tipoNodo *sucesor=actual->der;
				tipoNodo *padreSucesor=actual;
				//más a la izq del subarbol derecho
				while(sucesor->izq !=NULL){
					padreSucesor=sucesor;
					sucesor=sucesor->izq;
				}
					
				actual->clave = sucesor->clave;
				strcpy(actual->info, sucesor->info);
				

				if(padreSucesor==actual){
					padreSucesor->der=sucesor->der;
				}else{
					padreSucesor->izq=sucesor->der;
				}
				free(sucesor);
			}
			
		}
	}
	return contador;
}

#endif
/*****************************************************************************************
* Funciones GENERALES adaptadas a los dos ejercicios mediante DIRECTIVAS DE COMPILACIÓN  *
/*****************************************************************************************/
tipoNodo *creaNodo(tipoClave clave, tipoInfo info)
{ tipoNodo * nuevo;
  
  //   nuevo =(tipoNodo *)calloc(1, sizeof(tipoNodo));
  if ((nuevo =(tipoNodo *)malloc(sizeof(tipoNodo)))==NULL)
	return NULL;
  else 
  {	nuevo->clave = clave;
  	#ifdef EJERCICIO1
	nuevo->info=info;
  	#endif
  	#ifdef EJERCICIO3
	strcpy(nuevo->info,info);
  	#endif
  	nuevo->izq=NULL;
  	nuevo->der=NULL;
  return nuevo;
  }
}

void preOrden(tipoArbolBB a)
{ if (a) { 
  	#ifdef EJERCICIO1
	printf("%d %d \n", a->clave,a->info);
	#endif
  	#ifdef EJERCICIO3
	printf("%d %s \n", a->clave,a->info);
  	#endif
  	preOrden(a->izq);
  	preOrden(a->der);
  }
} 

void enOrden(tipoArbolBB a)
{ if (a) { 
	enOrden(a->izq);
   	#ifdef EJERCICIO1
	printf("%d %d \n", a->clave,a->info);
   	#endif
   	#ifdef EJERCICIO3
	printf("%d %s \n", a->clave,a->info);
   	#endif
    	enOrden(a->der);
  }
} 

void posOrden(tipoArbolBB a)
{ if (a) {
  	enOrden(a->izq);
  	enOrden(a->der);
   	#ifdef EJERCICIO1
	printf("%d %d \n", a->clave,a->info);
   	#endif
   	#ifdef EJERCICIO3
	printf("%d %s \n", a->clave,a->info);
   	#endif
  }
} 

