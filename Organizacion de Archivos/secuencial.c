#include "secuencial.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int leeSecuencial(char *fichero){
    FILE *fp=fopen(fichero, "rb");
    if(fp ==NULL){
        return -1;
    }

    int nrr=0;
    tipoAlumno reg;
    fread(&reg, sizeof(tipoAlumno), 1, fp);
    while(!feof(fp)){
        printf("%d \t %s %s %s %s %s \n", nrr, reg.dni, reg.nombre, reg.ape1, reg.ape2, reg.provincia);
        nrr++;
        fread(&reg, sizeof(tipoAlumno), 1, fp);
    }

    fclose(fp);
    return nrr;

}



int buscaReg(FILE *fSecuencial, tipoAlumno *reg,char *dni){
    int nrr=0;
    long curVal=ftell(fSecuencial);
    rewind(fSecuencial);

    fread(reg, sizeof(tipoAlumno), 1, fSecuencial);
    while(!feof(fSecuencial)){
        if(strcmp(dni,reg->dni)==0){
            fseek(fSecuencial, curVal, SEEK_SET);
            return nrr;
        }
        nrr++;
        fread(reg, sizeof(tipoAlumno), 1, fSecuencial);
    }

    fseek(fSecuencial, curVal, SEEK_SET);
    return -1;

}



int insertaReg(char *fSecuencial, tipoAlumno *reg){
    FILE *fp=fopen(fSecuencial, "ab");
    if(fp ==NULL){
        return -1;
    }

    fwrite(reg, sizeof(tipoAlumno), 1, fp);
    fflush(fp);
    fclose(fp);

    FILE *fp2=fopen(fSecuencial, "rb");
    if(fp2 ==NULL){
        return -1;
    }
    
    tipoAlumno temp;
    int nrr=buscaReg(fp2, &temp, reg->dni);
    fclose(fp2);

    return nrr;


}