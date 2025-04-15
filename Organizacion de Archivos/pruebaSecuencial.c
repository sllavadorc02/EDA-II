#include "secuencial.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main()
{int i,numReg;
 FILE *f;
 tipoAlumno reg;
 char dni[10];

  numReg=leeSecuencial("alumnos.dat");
  printf("Numero de Registros: %d \n\n\n",numReg);

  // B�squeda de registros
  f=fopen("alumnos.dat","rb");

  strcpy(dni,"7389298"); // Registro con NRR 37
  i=buscaReg(f,&reg,dni);
  if (i<0) printf("No existe alumno con dni %s\n",dni);
  else { printf("Registro con NRR %d",i);
  	     printf("\t %s %s %s %s %s\n\n",reg.dni,reg.nombre,reg.ape1,reg.ape2,reg.provincia);
        }

  strcpy(dni,"123456789"); // No existe
  i=buscaReg(f,&reg,dni);
  if (i<0) printf("\nNo existe alumno con dni %s\n",dni);
  else { printf("Registro con NRR %d",i);
  	     printf("\t %s %s %s %s %s\n\n",reg.dni,reg.nombre,reg.ape1,reg.ape2,reg.provincia);
        }
  fclose(f);

  //Fin de B�squeda

  tipoAlumno al;
  strcpy(al.nombre,"Sandr");
  strcpy(al.ape1,"Llavador");
  strcpy(al.ape2,"Cano");
  strcpy(al.dni,"0727337V");
  strcpy(al.provincia,"Badajoz");

  int nrrr=insertaReg("alumnos.dat", &al);
  if(nrrr==-1){
      printf("No se ha podido insertar el regustro...\n");
  }else{
      printf("Alumno añadido con exito en posicion %d...\n", nrrr);
  }
  

}



