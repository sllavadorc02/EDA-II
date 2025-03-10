#include "monticulo.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void iniciaMonticulo(Monticulo *m){ //se pasa por referencia porque se va a modificar
    m->tamanno=0;

}

int vacioMonticulo(Monticulo m){    
    //se pasa por valor porque no se va a modificar
    //También se puede pasar por referencia, de hecho es más eficiente, porque así no se crea una copia
    if(m.tamanno==0){
        return 1;
    }

    return 0;

}



int insertar(tipoElemento x, Monticulo *m){
    if(m->tamanno>= MAX-1){
        return -1;
    }else{
        m->tamanno++;
        m->elemento[m->tamanno]=x;
        filtradoAscendente(m, m->tamanno);

    }

    return 0;
}

void filtradoAscendente(Monticulo *m, int i){
    if(m==NULL || i<=1){
        return;
    }

    while(i>1 && m->elemento[i/2].clave > m->elemento[i].clave){
        //intercambiar elemento con su padre si es menor
        tipoElemento temp=m->elemento[i];
        m->elemento[i]=m->elemento[i/2];
        m->elemento[i/2]=temp;
        i=i/2;
        
    }
}


void filtradoDescendente(Monticulo *m, int i){
    if(m==NULL || m->tamanno==0){
        return;
    }
    int hijo;
    int finFiltrado=0;
    while(2*i <= m->tamanno && !finFiltrado){
        hijo=2*i;  //hijo izquierdo
        if(hijo+1 <= m->tamanno && m->elemento[hijo+1].clave < m->elemento[hijo].clave){
            hijo++; //coge el hijo menor
            
        }
        
        if(m->elemento[hijo].clave < m->elemento[i].clave){ //compara con el ultimo
            tipoElemento temp=m->elemento[i];
            m->elemento[i]=m->elemento[hijo];
            m->elemento[hijo]=temp;
            i=hijo;

        }else{
            finFiltrado=1;
        }

    }


}


int eliminarMinimo(Monticulo *m, tipoElemento *minimo){
    if(m==NULL || m->tamanno==0){
        return -1;
    }
    int i, hijo;
    *minimo=m->elemento[1]; //guardar el minimo
    tipoElemento ultimo=m->elemento[m->tamanno];
    m->tamanno--;
    int hueco=1;
    int finFiltrado=0;
    while(2*hueco <= m->tamanno && !finFiltrado){
        hijo=2*hueco;
        if(hijo < m->tamanno){
            if(m->elemento[hijo+1].clave < m->elemento[hijo].clave){
                hijo++; //coge el hijo menor
            }
        }

        if(m->elemento[hijo].clave < ultimo.clave){ //compara con el ultimo
            m->elemento[hueco]=m->elemento[hijo];
            hueco=hijo;
        }else{
            finFiltrado=1;
        }
    }
    
    m->elemento[hueco]=ultimo;  //colocar el ultimo elemento en su posicion final

    return 0;
}

void decrementarClave(int pos, tipoClave cantidad, Monticulo *m){
    if(pos<1 || pos> m->tamanno){
        return;
    }

    m->elemento[pos].clave=m->elemento[pos].clave - cantidad;
    filtradoAscendente(m, pos);
}


void incrementarClave(int pos, tipoClave cantidad, Monticulo *m){
    if(pos<1 || pos > m->tamanno){
        return;
    }
    m->elemento[pos].clave = m->elemento[pos].clave + cantidad;
    filtradoDescendente(m, pos);
    
}

int esMonticulo(Monticulo m){
    if(m.tamanno==0){
        return -1;
    }

    int i;
    if(m.elemento[1].clave > m.elemento[2].clave){  //el mayor arriba
        for(i=1; i*2<=m.tamanno; i++){
            int hijoDer=i*2+1;
            int hijoIzq=i*2;

            if(m.elemento[i].clave < m.elemento[hijoIzq].clave){
                return 0;
            }else if(hijoDer<=m.tamanno && m.elemento[i].clave < m.elemento[hijoDer].clave){
                return 0;
            }
        }

    }else{  //el menor arriba
        for(i=1; i*2<=m.tamanno; i++){
            int hijoDer=i*2+1;
            int hijoIzq=i*2;

            if(m.elemento[i].clave > m.elemento[hijoIzq].clave){
                return 0;
            }else if(hijoDer <= m.tamanno && m.elemento[i].clave > m.elemento[hijoDer].clave){
                return 0;
            }
        }

    }
    
    return 1;
}

Monticulo contruirMonticulo(int elementos[], int n){
    Monticulo m;
    m.tamanno=n;
    if(n==1){
        m.elemento[1].clave=elementos[0];
    }

    for(int i=0; i<n; i++){
        m.elemento[i+1].clave=elementos[i];
    }

    return m;

}




//Ejercicio 2
void heapsort(Monticulo *m){
    int i;

    //ordenar con minimo en raiz
    for(i=m->tamanno/2; i>=1; i--){
        filtradoDescendente(m, i);  
    }

    int tam_original=m->tamanno;
    tipoElemento temp;
    for(i=m->tamanno; i>1; i--){
        //intercambias el mas pequeño(raiz) con el mas grande (ultimo hijo)
        //y siguiente raiz
        temp = m->elemento[1];
        m->elemento[1] = m->elemento[i];
        m->elemento[i] = temp;
        m->tamanno--;   //va quitando los ordenados
        filtradoDescendente(m,1);
    }

    m->tamanno=tam_original;
}


