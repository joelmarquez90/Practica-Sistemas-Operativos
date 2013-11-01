////////////////////////////////////////
//NOMBRE DEL SCRIPT:Ejercicio5.c							
//TRABAJO PRACTICO N°2                  
//EJERCICIO 5.	                        
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

int main (int argc, char *argv[])
{
	pid_t hijopid;
	int status = 0;

	if(argc < 2)
	{
		printf("Error de invocacion. Uso: %s [comando a ejecutar]\n",argv[0]);  
		exit(1);
	}
	hijopid = vfork();
	switch (hijopid)
	{
		case -1: printf("Error al crear hijo \n");
					break;
		case 0: 	if(execvp(argv[1],&argv[1])<0)
					{ 
						printf("Error al ejecutar comando \n");
						_exit(1);
					}
					_exit(0);

		default: wait(&status);	// el padre espera a que termine su hijo.
	}
	exit(0);
}

/*
#################################################################################################################
#A diferencia de fork() la función vfork() al ser invocada, produce que el proceso padre quede bloqueado hasta que su #hijo ejecute una función de la famila exec, o la función _exit(), la cual indica que terminó dicho proceso hijo. 
#En ese momento se desbloquea el padre y puede seguir su ejecución.
#Al realizar la llamada a  vfork() padre e hijo comparten la memoria y también el stack, (es por eso que el padre qued# bloqueado). Un proceso hijo generado con vfork() al terminar debe ejecutar la función _exit() y no exit()
#Otra diferencia es que los manejadores de  señales son heredados pero no se comparten. Estas llegan al padre 
#cuando el hijo libera la memoria.
####################################################################################################################
*/
