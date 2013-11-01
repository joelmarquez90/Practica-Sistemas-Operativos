////////////////////////////////////////
//NOMBRE DEL PROGRAMA: main.c							
//TRABAJO PRACTICO N°3                  
//EJERCICIO 1.	                        
//INTEGRANTES:                         
//Joel Marquez             35.367.125  
//Maria Eugenia Brea       35.272.169  
//Maria Victoria Trimboli  35.723.767  
//Soledad Suarez           35.387.379  
//Marlene Lauria           35.423.458  
//PRIMERA ENTREGA												
////////////////////////////////////////

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

int main () 
{
	key_t claveMutex, clavePapel, claveTabaco, claveCerillo;
	int idMutex, idPapel, idTabaco, idCerillo, i, ran;
	pid_t idHijo, idPadre;

	claveMutex = ftok("/", 6000);					//Se piden claves para los 4 semáforos
	clavePapel = ftok("/", 6001);
	claveTabaco = ftok("/", 6002);
	claveCerillo = ftok("/", 6003);
	idMutex = obtenerSemaforo(claveMutex, 0);			//Se obtienen los semáforos con sus respectivos id
	idPapel = obtenerSemaforo(clavePapel, 0);
	idTabaco = obtenerSemaforo(claveTabaco, 0);
	idCerillo = obtenerSemaforo(claveCerillo, 0);
	idPadre = getpid();
	for (i = 0; i < 3; i++)				//Ciclo que crea los 3 hijos fumadores
	{
		if ((idHijo = fork()) < 0)
		{
			printf("No se pudo crear hijo");
			exit(1);
		}
		if (idHijo == 0)			//Hijos
		{ 
			srand(getpid());
			switch (i)				//Para distinguir entre los 3 hijos
			{
				case 0: 	while (1)		//Cada fumador pide su semáforo correspondiente. Cuando este se habilita fuma un
							{													//tiempo aleatorio informando, y cuando termina habilita
								pedirSemaforo(idTabaco);				//el semáforo del dealer
								ran = rand() % 3 + 1;
								printf("Fumador %d con TABACO, fumo %d seg\n", getpid(), ran);
								sleep(ran);
								devolverSemaforo(idMutex);
							}
							break;
				case 1: 	while (1)
							{
								pedirSemaforo(idCerillo);
								ran = rand() % 3 + 1;
								printf("Fumador %d con CERILLO, fumo %d seg\n", getpid(), ran);
								sleep(ran);
								devolverSemaforo(idMutex);
							}
							break;
				case 2: 	while (1)
							{
								pedirSemaforo(idPapel);
								ran = rand() % 3 + 1;
								printf("Fumador %d con PAPEL, fumo %d seg\n", getpid(), ran);
								sleep(ran);
								devolverSemaforo(idMutex);
							}
							break;
			}
		}
	}
	if (getpid() == idPadre)		//Padre
	{
		srand(getpid());
		while (1)				//Bucle infinito que termina con CTRL + C desde consola
		{
			ran = rand() % 3;			//Elige un fumador al azar entre los 3
			switch (ran)
			{
				case 0:	printf("Soy el dealer y pongo CERILLO y PAPEL en la mesa\n");
							devolverSemaforo(idTabaco);
							pedirSemaforo(idMutex);
							break;
				case 1:	printf("Soy el dealer y pongo PAPEL y TABACO en la mesa\n");
							devolverSemaforo(idCerillo);
							pedirSemaforo(idMutex);	
							break;
				case 2:	printf("Soy el dealer y pongo TABACO y CERILLO en la mesa\n");
							devolverSemaforo(idPapel);
							pedirSemaforo(idMutex);
							break;
			}
		}
	}
	eliminarSemaforo(idMutex);	 
	eliminarSemaforo(idPapel);
	eliminarSemaforo(idTabaco);
	eliminarSemaforo(idCerillo);
	return 0;
}

