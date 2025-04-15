#include "dispersion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Crea un fichero hash inicialmente vacio seg�n los criterios especificados en la pr�ctica
// Primera tarea a realizar para  crear un fichero organizado mediante DISPERSI�N
void creaHvacio(char *fichHash)
{ FILE *fHash;
  tipoCubo cubo;
  int j;
  int numCubos =CUBOS+CUBOSDESBORDE;

  memset(&cubo,0,sizeof(cubo));

  fHash = fopen(fichHash,"wb");
  for (j=0;j<numCubos;j++) fwrite(&cubo,sizeof(cubo),1,fHash);
  fclose(fHash);
}
// Lee el contenido del fichero hash organizado mediante el m�todo de DISPERSI�N seg�n los criterios
// especificados en la pr�ctica. Se leen todos los cubos completos tengan registros asignados o no. La
// salida que produce esta funci�n permite visualizar el m�todo de DISPERSI�N

int leeHash(char *fichHash)
{ FILE *f;
  tipoCubo cubo;
  int j,i=0;
  size_t numLee;

   f = fopen(fichHash,"rb");
   rewind(f);
   fread(&cubo,sizeof(cubo),1,f);
   while (!feof(f)){
	for (j=0;j<C;j++) {
        if (j==0)    	printf("Cubo %2d (%2d reg. ASIGNADOS)",i,cubo.numRegAsignados);
        else  	printf("\t\t\t");
	if (j < cubo.numRegAsignados) 
		    printf("\t%s %s %s %s %s\n",
	    		cubo.reg[j].dni,
			cubo.reg[j].nombre,
			cubo.reg[j].ape1,
		  	cubo.reg[j].ape2,
  	                cubo.reg[j].provincia);
	else printf ("\n");
        }
       i++;
       fread(&cubo,sizeof(cubo),1,f);
   }
   fclose(f);
   return i;
}


int creaHash(char *fichEntrada,char *fichHash){
    FILE *fEntrada=fopen(fichEntrada, "rb");
    if(fEntrada ==NULL){
        return -1;
    }
    creaHvacio(fichHash);
    FILE *fHash=fopen(fichHash, "r+b");
    if(fHash ==NULL){
        return -1;
    }
    int desbordados=0;

    tipoAlumno reg;
    fread(&reg, sizeof(tipoAlumno), 1, fEntrada);
    while(!feof(fEntrada)){
        int numCubo=atoi(reg.dni)%CUBOS;
        fseek(fHash, numCubo*sizeof(tipoCubo), SEEK_SET);
        tipoCubo unCubo;
        if(fread(&unCubo, sizeof(tipoCubo), 1, fHash)!=1){
            printf("Error leyendo cubo principal");
            return -1;
        }
        
        if(unCubo.numRegAsignados<C){
            unCubo.reg[unCubo.numRegAsignados]=reg;
            unCubo.numRegAsignados++;
            fseek(fHash, numCubo*sizeof(tipoCubo), SEEK_SET); //reposicionar el puntero en el anterior
            if(fwrite(&unCubo, sizeof(tipoCubo), 1, fHash)!=1){//del cubo al fichero hash
                printf("Error escribiendo cubo principal\n");
                return -1;
            }

        }else{
            desbordados++;
            
            int numCuboD=0;
            while(numCuboD<CUBOSDESBORDE){
                fseek(fHash, (CUBOS+numCuboD)*sizeof(tipoCubo), SEEK_SET);
                tipoCubo unCuboD;
                if(fread(&unCuboD, sizeof(tipoCubo), 1, fHash)!=1){
                    printf("Error leyendo cubo desborde %d\n", numCuboD);
                    break;
                }

                if(unCuboD.numRegAsignados<C){
                    unCuboD.reg[unCuboD.numRegAsignados]=reg;
                    unCuboD.numRegAsignados++;
                    fseek(fHash, (CUBOS+numCuboD)*sizeof(tipoCubo), SEEK_SET); //reposicionar el puntero en el anterior
                    if(fwrite(&unCuboD, sizeof(tipoCubo), 1, fHash)!=1){ //del cubo al fichero hash
                        printf("Error escribiendo cubo desborde %d\n", numCuboD);
                        
                    }
                    unCubo.numRegAsignados++;
                    fseek(fHash, numCubo * sizeof(tipoCubo), SEEK_SET);
                    if (fwrite(&unCubo, sizeof(tipoCubo), 1, fHash) != 1) {
                        printf("Error actualizando cubo principal\n");
                    }

                    break;
                }else{
                    unCuboD.numRegAsignados++;
                    fseek(fHash, (CUBOS+numCuboD)*sizeof(tipoCubo), SEEK_SET); //reposicionar el puntero en el anterior
                    if(fwrite(&unCuboD, sizeof(tipoCubo), 1, fHash)!=1){ //del cubo al fichero hash
                        printf("Error escribiendo cubo desborde %d\n", numCuboD);
                    }
                    numCuboD++;
                }
            }
        }
         
        fread(&reg, sizeof(tipoAlumno), 1, fEntrada);
        
    }




    fclose(fHash);
    fclose(fEntrada);
    return desbordados;

}


int buscaReg(FILE *fHash, tipoAlumno *reg,char *dni){
    int idCubo=atoi(dni)%CUBOS;

    fseek(fHash,idCubo*sizeof(tipoCubo), SEEK_SET);
    tipoCubo unCubo;
    fread(&unCubo, sizeof(tipoCubo), 1, fHash);

    if(unCubo.numRegAsignados ==0){
        return -1;
    }else{
        for(int i=0; i<C && i<unCubo.numRegAsignados; i++){
            if(0==strcmp(unCubo.reg[i].dni, dni)){
                *reg=unCubo.reg[i];
                return idCubo;
            }
        }
        if(unCubo.numRegAsignados>= C){
            int idCubosDesborde=0;
            fseek(fHash, CUBOS*sizeof(tipoCubo), SEEK_SET);
            fread(&unCubo, sizeof(tipoCubo), 1, fHash);
            while(!feof(fHash) && unCubo.numRegAsignados > 0){
                for( int i=0; i<C && i< unCubo.numRegAsignados; i++){
                    if(0==strcmp(unCubo.reg[i].dni, dni)){
                        *reg=unCubo.reg[i];
                        return CUBOS+idCubosDesborde;
                    }
                }
                fread(&unCubo, sizeof(tipoCubo), 1, fHash);
                idCubosDesborde++;
            }   

        }

    }


    return -1;
}



int insertarReg(FILE *f, tipoAlumno *reg){
    rewind(f);
    int numCubo=atoi(reg->dni)%CUBOS;
    fseek(f, numCubo*sizeof(tipoCubo), SEEK_SET);
    tipoCubo unCubo;
    if(fread(&unCubo, sizeof(tipoCubo), 1, f)!=1){
        printf("Error leyendo cubo principal");
        return -1;
    }
        
    if(unCubo.numRegAsignados<C){
        unCubo.reg[unCubo.numRegAsignados]=*reg;
        unCubo.numRegAsignados++;
        fseek(f, numCubo*sizeof(tipoCubo), SEEK_SET); //reposicionar el puntero en el anterior
        if(fwrite(&unCubo, sizeof(tipoCubo), 1, f)!=1){//del cubo al fichero hash
            printf("Error escribiendo cubo principal\n");
            return -1;
        }
        fflush(f);
        return numCubo;

    }else{
        int numCuboD=0;
        
        while(numCuboD<CUBOSDESBORDE){
            fseek(f, (CUBOS+numCuboD)*sizeof(tipoCubo), SEEK_SET);
            tipoCubo unCuboD;
            if(fread(&unCuboD, sizeof(tipoCubo), 1, f)!=1){
                printf("Error leyendo cubo desborde %d\n", numCuboD);
                numCuboD++;
                continue;
            }

            if(unCuboD.numRegAsignados<C){
                unCuboD.reg[unCuboD.numRegAsignados]=*reg;
                unCuboD.numRegAsignados++;
                fseek(f, (CUBOS+numCuboD)*sizeof(tipoCubo), SEEK_SET); //reposicionar el puntero en el anterior
                if(fwrite(&unCuboD, sizeof(tipoCubo), 1, f)!=1){ //del cubo al fichero hash
                    printf("Error escribiendo cubo desborde %d\n", numCuboD);     
                }

                unCubo.numRegAsignados++;
                fseek(f, numCubo * sizeof(tipoCubo), SEEK_SET);
                if (fwrite(&unCubo, sizeof(tipoCubo), 1, f) != 1) {
                    printf("Error actualizando cubo principal\n");
                }
                fflush(f);
                return CUBOS+numCuboD;
            }
            unCuboD.numRegAsignados++;
            fseek(f, (CUBOS+numCuboD)*sizeof(tipoCubo), SEEK_SET); //reposicionar el puntero en el anterior
            if(fwrite(&unCuboD, sizeof(tipoCubo), 1, f)!=1){ //del cubo al fichero hash
                printf("Error escribiendo cubo desborde %d\n", numCuboD);
            }
            fflush(f);
            numCuboD++;
            
        }
        
    }
         
    return -1;

}