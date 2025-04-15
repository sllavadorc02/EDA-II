#include "dispersion.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main()
{int i,numRegDes;
 FILE *f;
 tipoAlumno reg;
 char dni[10];
  printf("Iniciando creaHash...\n");
  numRegDes=creaHash("alumnos.dat","alumnos.hash");
  printf("%d Registros DESBORDADOS\n\n",numRegDes);

  i = leeHash("alumnos.hash");

  // B�squeda de registros
  f=fopen("alumnos.hash","r+b");

  strcpy(dni,"7389298"); // Existe en el area PRIMA
  i=buscaReg(f,&reg,dni);
  if (i<0) printf("No existe alumno con dni %s\n",dni);
  else { printf("Registro encontrado en el CUBO %d",i);
  	     printf("\t %s %s %s %s %s\n",reg.dni,reg.nombre,reg.ape1,reg.ape2,reg.provincia);
        }
  strcpy(dni,"7219752"); // Existe en el area De DESBORDE
  i=buscaReg(f,&reg,dni);
  if (i<0) printf("No existe alumno con dni %s\n",dni);
  else { printf("Registro encontrado en el CUBO %d",i);
  	     printf("\t %s %s %s %s %s\n",reg.dni,reg.nombre,reg.ape1,reg.ape2,reg.provincia);
        }
  strcpy(dni,"123456789"); // No existe
  i=buscaReg(f,&reg,dni);
  if (i<0) printf("\nNo existe alumno con dni %s\n",dni);
  else { printf("Registro encontrado en el CUBO %d",i);
  	     printf("\t %s %s %s %s %s\n",reg.dni,reg.nombre,reg.ape1,reg.ape2,reg.provincia);
        }
  

  //Fin de B�squeda
  tipoAlumno al;
  strcpy(al.nombre,"Sannnnndra");
  strcpy(al.ape1,"Llavador");
  strcpy(al.ape2,"Cano");
  strcpy(al.dni,"0727337V");
  strcpy(al.provincia,"Badajoz");

  int nrrr=insertarReg(f, &al);
  if(nrrr==-1){
      printf("No se ha podido insertar el regustro...\n");
  }else{
      printf("Alumno añadido con exito en el cubo %d...\n", nrrr);
  }

  strcpy(al.nombre,"Sandra");
  strcpy(al.ape1,"Llavador");
  strcpy(al.ape2,"Cano");
  strcpy(al.dni,"1727337V");
  strcpy(al.provincia,"Badajoz");

  nrrr=insertarReg(f, &al);
  if(nrrr==-1){
      printf("No se ha podido insertar el regustro...\n");
  }else{
      printf("Alumno añadido con exito en el cubo %d...\n", nrrr);
  }
  
  strcpy(al.nombre,"Sandra");
  strcpy(al.ape1,"Llavador");
  strcpy(al.ape2,"Cano");
  strcpy(al.dni,"6727337V");
  strcpy(al.provincia,"Badajoz");

  nrrr=insertarReg(f, &al);
  if(nrrr==-1){
      printf("No se ha podido insertar el regustro...\n");
  }else{
      printf("Alumno añadido con exito en el cubo %d...\n", nrrr);
  }

 printf("\n\n");
 i = leeHash("alumnos.hash");

  fclose(f);
}



