#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "arbol.h"
#include "cola.h"
#include "pila.h"

//
// Reserva de memoria para un nuevo nodo de árbol binario
//
Arbol creaNodo(tipoInfo info)
{ tipoNodo * nuevo;

  //   nuevo =(tipoNodo *)calloc(1, sizeof(tipoNodo));
  if ((nuevo =(tipoNodo *)malloc(sizeof(tipoNodo)))==NULL)
	return NULL;
  else
  { 	nuevo->info=info;
	nuevo->izq=NULL;
	nuevo->der=NULL;
	return nuevo;
   }
}

//
// Recorrido en amplitud o por niveles: necesita una cola de punteros a nodos de árbol binario!!!
//

void amplitud(Arbol raiz)
{ Cola c;
  tipoNodo *nodo;
  colaCreaVacia(&c);
  nodo = raiz;
  if (raiz!=NULL) colaInserta(&c,nodo);	//tipo info de la cola es de tipo arbol
  while (!colaVacia(&c))
  { nodo = (Arbol) colaSuprime(&c);
    printf(" %c ", nodo->info);	//imprime por niveles
    if (nodo->izq!=NULL) colaInserta(&c,nodo->izq); 
    if (nodo->der!=NULL) colaInserta(&c,nodo->der);
  }
}
// 
// Recorridos en profundidad "recursivos"
//
void preOrden(Arbol raiz)	//ABDECFG
{ if (raiz!=NULL)	//con while bucle infinito, siempre if
  { printf("%c ",raiz->info);	//procesamiento del nodo actual (hacer otros ejercicios con esto)
    preOrden(raiz->izq);	//no comprobar antes de llamar a preOrden(izq) si es la raiz null
    preOrden(raiz->der);	//porque cuando se llama ya se comprueba esa condición (redundante)
  }
}
void enOrden(Arbol raiz)	//DBEAFCG
{ if (raiz!=NULL)	//No realizar comprobaciones redundantes (solo esta)
  { enOrden(raiz->izq);
    printf("%c ",raiz->info);
    enOrden(raiz->der);
  }
}
void postOrden(Arbol raiz)	//DEBFGCA
{ if (raiz!=NULL)
  { postOrden(raiz->izq);
    postOrden(raiz->der);
    printf("%c ",raiz->info);
  }
}


int altura(Arbol raiz){
	if(raiz==NULL){
		return -1;
	}
	
	int alturai=altura(raiz->izq);
	int alturad=altura(raiz->der);
	
	if(alturai>=alturad){
		alturai++;
		return alturai;
	}else{
		alturad++;
		return alturad;
	}
}



int numNodos(Arbol raiz){
	if (raiz == NULL){
    return 0;
  }

  int num;
  num=numNodos(raiz->izq)+numNodos(raiz->der)+1;
  return num;

	
}


Arbol anula(Arbol raiz){
  if(raiz == NULL){
    return NULL;
  }


  raiz->der=anula(raiz->der);
  raiz->izq=anula(raiz->izq);

  free(raiz);
  return NULL;

}


int sustiuye(Arbol raiz, tipoInfo x, tipoInfo y){
  if(raiz ==NULL){
    return 0;
  }
  int final;
  int sustitucion1=sustiuye(raiz->der,x,y);
  int sustitucion2=sustiuye(raiz->izq,x,y);

  if (sustitucion1>sustitucion2){
    final=sustitucion1;
  }else{
    final=sustitucion2;
  }
  
  if(raiz->info ==x){
    raiz->info=y;
    final++;
  }
  
  return final;
}

int numNodosHoja(Arbol raiz){
  if(raiz==NULL){
    return 0;
  }

  int nder=numNodosHoja(raiz->der);
  int nizq=numNodosHoja(raiz->izq);
  if(nder==0 && nizq==0){
    return 1;
  }else{
    return nizq+nder;
  }

}

int numNodosInternos(Arbol raiz){
  if(raiz==NULL){
    return 0;
  }
  int nder=numNodosInternos(raiz->der);
  int nizq=numNodosInternos(raiz->izq);
  if(raiz->der!= NULL || raiz->izq !=NULL){
    return nder+nizq+1;
  }else{
    return nder+nizq;
  }


}



int numHijoUnico(Arbol raiz){
  if(raiz==NULL){
    return 0;
  }

  int nder=numHijoUnico(raiz->der);
  int nizq=numHijoUnico(raiz->izq);
  if(raiz->der!= NULL && raiz->izq ==NULL){
    return nder+nizq+1;
  }else if(raiz->der== NULL && raiz->izq !=NULL){
    return nder+nizq+1;
  }else{
    return nder+nizq;
  }


}

Arbol buscarMax(Arbol raiz){
  if(raiz==NULL){
    return NULL;
  }

  Arbol der=buscarMax(raiz->der);
  Arbol izq=buscarMax(raiz->izq);
  Arbol max=raiz;
  if(der!=NULL && der->info > max->info){
    max=der;
  }

  if(izq!=NULL && izq->info > max->info){
    max=izq;
  }

  return max;

}

Arbol buscarMin(Arbol raiz){
  if(raiz==NULL){
    return NULL;
  }

  Arbol der=buscarMin(raiz->der);
  Arbol izq=buscarMin(raiz->izq);
  Arbol min=raiz;
  if(der!=NULL && der->info < min->info){
    min=der;
  }

  if(izq!=NULL && izq->info < min->info){
    min=izq;
  }

  return min;

}



int similares(Arbol r1, Arbol r2){
  if(r1==NULL || r2 ==NULL){
    return -1;
  }
  

  if(r1->der!=NULL){
    if(r2->der==NULL){
      return 0;
    }

  }else{
    if(r2->der!=NULL){
      return 0;
    }
  }

  if(r1->izq!=NULL){
    if(r2->izq==NULL){
      return 0;
    }

  }else{
    if(r2->izq!=NULL){
      return 0;
    }
  }



  int der=similares(r1->der, r2->der);
  int izq=similares(r1->izq, r2->izq);

  if(der==0 || izq==0){
    return 0;
  }else{
    return 1;
  }


}


int equivalentes(Arbol r1,Arbol r2){
if(r1==NULL || r2 ==NULL){
    return -1;
  }
  

  if(r1->der!=NULL){  //rama der
    if(r2->der==NULL){
      return 0;
    }

  }else{
    if(r2->der!=NULL){
      return 0;
    }
  }

  if(r1->izq!=NULL){  //rama izq
    if(r2->izq==NULL){
      return 0;
    }

  }else{
    if(r2->izq!=NULL){
      return 0;
    }
  }

  if(r1->info != r2->info){
    return 0;
  }


  int der=equivalentes(r1->der, r2->der);
  int izq=equivalentes(r1->izq, r2->izq);

  if(der==0 || izq==0){
    return 0;
  }else{
    return 1;
  }

}

Arbol especular(Arbol raiz){
  if(raiz ==NULL){
    return NULL;
  }

  Arbol nuevo=creaNodo(raiz->info);
  nuevo->der=especular(raiz->izq);
  nuevo->izq=especular(raiz->der);

  return nuevo;

}



int evaluar(Arbol raiz){
	if(raiz==NULL){
    return 0;
  }

  if (raiz->info!='+' && raiz->info!='*') {
    return raiz->info - '0';  // Convertir char a int
  }

  int resultadod=evaluar(raiz->izq);
  int resultadoi=evaluar(raiz->der);

  if(raiz->info=='*'){
    return (resultadod)*(resultadoi);
  }else if(raiz->info == '+'){
    return (resultadod)+(resultadoi);
  }
  
}



Arbol reconstruir(char preorden[], char inorden[], int iniciop, int finp, int inicioi, int fini){
  if(iniciop>finp || inicioi>fini){
    return NULL;
  }

  Arbol raiz=creaNodo(preorden[iniciop]);

  if(inicioi==fini || iniciop==finp){
    return raiz;
  }

  
  int indiceO;
  for(int i=inicioi; i<=fini; i++){
    if(inorden[i]==raiz->info){
      indiceO=i;
      break;
    }

  }

  int numIzq=indiceO-inicioi;
  raiz->izq=reconstruir(preorden, inorden, iniciop+1, iniciop+numIzq, inicioi, indiceO-1);
  raiz->der=reconstruir(preorden, inorden, iniciop+numIzq+1, finp, indiceO+1, fini);


  return raiz;

}






