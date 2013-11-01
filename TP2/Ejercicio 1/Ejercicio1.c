////////////////////////////////////////
//NOMBRE DEL SCRIPT:Ejercicio1.c							
//TRABAJO PRACTICO N°2                  
//EJERCICIO 1.	                        
//INTEGRANTES:                         
//Joel Marquez             35.367.125  
//Maria Eugenia Brea       35.272.169  
//Maria Victoria Trimboli  35.723.767  
//Soledad Suarez           35.387.379  
//Marlene Lauria           35.423.458  
//PRIMERA ENTREGA												
////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pidHijo;
	pid_t pidNieto;
	int ran, i, j, status1 = 0, status2 = 0;
	for (i = 0; i < 5; i++)			//ciclo que crea los 5 hijos
	{
		pidHijo = fork();
		switch (pidHijo)
		{
			case -1:	exit(1);
								break;
			case 0: 	srand(getpid());		//siembra la semilla aleatoria con el pid de cada hijo así el algoritmo rand 																				funciona correctamente
								ran = rand() % 10 + 1;
								for (j = 0; j < ran; j++)	//ciclo de cada hijo que crea ran (nro aleatorio entre 1 y 10) nietos
								{
									pidNieto = fork();
									switch (pidNieto)
									{
										case -1:	exit(1);
															break;
										case 0: 	printf("\t\tSoy nieto, mi pid es %d y el pid de mi padre es %d\n", getpid(), getppid());
															exit(0);
															break;
										default:	wait(&status2);		//cada hijo espera a la finalización de cada nieto
															break;
									}
								}
								printf("\tTengo el PID: %d y han finalizado todos mis hijos\n", getpid());
								exit(0);
								break;
			default:	wait(&status1);	//el padre espera a la finalización de cada hijo
								break;					
		}
	}
	printf("Soy el padre, mi pid es %d y finalizaron mis 5 hijos y todos mis nietos\n", getpid());
	return (0);
}
