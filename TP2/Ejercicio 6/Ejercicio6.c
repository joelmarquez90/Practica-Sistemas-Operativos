////////////////////////////////////////
//NOMBRE DEL SCRIPT:Ejercicio6.c							
//TRABAJO PRACTICO N°2                  
//EJERCICIO 6.	                        
//INTEGRANTES:                         
//Joel Marquez             35.367.125  
//Maria Eugenia Brea       35.272.169  
//Maria Victoria Trimboli  35.723.767  
//Soledad Suarez           35.387.379  
//Marlene Lauria           35.423.458  
//PRIMERA ENTREGA												
////////////////////////////////////////

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

char** aux;    // vector global para que use cada hijo
int esopcion(char**);

int main (int argc, char *argv[])
{
	int i = argc - 1;
	int opcion = 0;
	int cantarch = 0;
	pid_t padre, hijopid;
	int status = 0;
	int tam = 0;
	int cantopc = 0;

	padre = getpid();
	if (getpid() == padre)
	{
		if (argc < 2)
		{
			printf("Error de invocacion. Uso: %s [comando a ejecutar]\n",argv[0]);  
			exit(1);
		}

		while (opcion == 0 && i > 0)
		{
			opcion = esopcion(&argv[i]);
			i--;
			cantarch++;					//cuenta la cantidad de archivos recibidos
		}

		cantopc = argc - cantarch - 1;  // la cantidad de opciones son la cantidad de parametros menos el comando
		tam = cantopc + 3;
		aux = (char **) malloc (tam * sizeof(char *));

		for (i = 0; i <= cantopc; i++)
			aux[i] = argv[i+1];         //armo el vector con el comando y las opciones

		aux[tam - 1] = NULL;    //termino el vector con NULL

		for (i = 0; i < cantarch - 1; i++)
		{ 
			cantopc = argc - cantarch - 1;
			if (getpid() == padre)
			{     
				aux[cantopc + 1] = argv[cantopc + 2 + i];   //lleno el lugar con el nombre del archivo que corresponde al hijo
				hijopid = vfork();
				switch (hijopid)
				{
					case -1:	printf("Error al crear hijo \n");
								break;
					case 0:  if(execvp(aux[0], &aux[0]) < 0)				//el hijo ejecuta el comando con su archivo correspondiente
								{ 
									printf("Error al ejecutar comando \n");
									_exit(1);
								}
								_exit(0);
					default: wait(&status);
				}
			}
		}	
	}
	for(i = 0; i < cantarch - 1; i++)
		wait(&status);
	exit(0);
}

int esopcion(char** cad)			//verifica si la primer letra del campo es un '-'
{
	int i, modif = 0;
	if (*(*cad) == '-')
		modif=1;
	return modif;
}

		
