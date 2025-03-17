#ifndef __CONJUNTOS_A_H
#define __CONJUNTOS_A_H

#define MAXIMO 16

typedef int particion[MAXIMO];
typedef int tipoConjunto;
typedef int tipoElemento;

// Funciones a implementar

// colocar indice en cada una de las celdas (0 como elemento posible de la particion)
void crea(particion P);

// busqueda recursiva del padre hastq eu la celda es igual índice
// si no es el padre, buscar el padre
// puede ser de orden n, caso peor
// secuencia de union de una única rama -> caso peor
// un nodo -> caso mejor

tipoConjunto buscar(tipoElemento x, particion P);

// Implementación de operación unir con control de representantes:
// Si x e y son los representantes de sus clases de equivalencia las unen y devuelven VERDADERO,
// en otro caso no hace nada y devuelve FALSO

// ver que son representantes(ifs), representante de la union el primero
// primero padre del segundo
// colocar el propio valor
// si es el padre absoluto está su índice almacenado
int unir(tipoConjunto x, tipoConjunto y, particion P);

// Función proporcionada
void verParticion(particion P);



// tamaños o alturas negativas, a -1 todas las celdas
// representantes -> siempre en sus celdas valores negativos(sumar tamaños)
// union por tamaños
// nuevo tamaño del árbol, se van sumando p[x]+p[y]
// en caso de iguales, el primero la raiz
//int unirTam(tipoConjunto x, tipoConjunto y, particion P);

// union por altura
// si se incorpora uno menor no varía la altura
// si es igual se incrementa la altura sumando
// arbol de menor altura, arbol de mayor altura (altura no cambia)
// si la altura es la misma, se suma uno
// no representantes -> indice del padre
// OJO!! son negativos
// uniones en prueba.c en papel para ver que funcionan
//int unirAlt(tipoConjunto x, tipoConjunto y, particion P);


// compresion por caminos
// busqueda, con arbol de altura 1
#endif