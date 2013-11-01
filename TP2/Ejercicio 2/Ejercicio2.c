////////////////////////////////////////
//NOMBRE DEL SCRIPT:Ejercicio2.c							
//TRABAJO PRACTICO N°2                  
//EJERCICIO 2.	                        
//INTEGRANTES:                         
//Joel Marquez             35.367.125  
//Maria Eugenia Brea       35.272.169  
//Maria Victoria Trimboli  35.723.767  
//Soledad Suarez           35.387.379  
//Marlene Lauria           35.423.458  
//PRIMERA ENTREGA												
////////////////////////////////////////


#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<signal.h>
#include <stdlib.h>
#define MAX_PROCESOS 20		//cantidad maxima de procesos a crear

void handler (int);

int contador = 0;
pid_t padre;

int main (int argc, char * argv[])
{ 
	int x, y, i, status = 0; 
	pid_t aux, pid_hijos[MAX_PROCESOS];
	if (argc == 3)				//controla que la cantidad de argumentos que se le pasan al main sean válidos
	{
		if ((x = atoi(argv[1])) > MAX_PROCESOS)	//pasa a entero el parámetros de cantidad de hijos (x) y verifica que sea < que 20
		{
			printf("Error. El primer parametro debe ser menor o igual a 20\n");
			exit(1);
		}	
		y = atoi(argv[2]);
		padre = getpid();
		for (i = 0; i < x ; i++)
		{	
			aux = fork();
			switch (aux)
			{
				case -1:	printf("No se pudo crear hijo");
							exit(1);
							break;
				case 0:	signal(SIGTERM,handler);		//si es un hijo usa un manejador de señal SIGTERM así el padre le avisa cuando finalizar
							while(1)
							{
								sleep(1);						//se duerme 1 segundo y cuenta y así infinitamente o hasta que el padre le mande la señal
								contador++;
							}
							break;
				default: pid_hijos[i] = aux;				//el padre va guardando los pids de los hijos y durmiendose la cantidad de tiempo que se le paso (y)
							sleep(y);
							break;
			}
		}	
		if (getpid() == padre)
		{
			sleep(10);       								//cuando termina de crear los X procesos, se duerme 10 segundos y después va mandando
			for (i = 0; i < x; i++)
				kill(pid_hijos[i],SIGTERM);			//la señal de finalización a cada hijo
			for (i = 0; i < x; i++)	
				wait(&status);
			printf("Soy el padre mi pid es: %d y finalizo\n", padre);
			exit(0);         
		}	
	}
	else
		printf("Parametros erroneos. Uso: ./Ejercicio2 cantHijos tiempoEntreHijos\n");
}

void handler (int sig)
{
	if (sig == SIGTERM)						//cuando el hijo recibe la señal SIGTERM del padre, muestra hasta donde llego a contar y demás y finaliza
	{ 
		printf("Soy el hijo numero %d mi pid es %d conte hasta %d\n", getpid() - padre, getpid(), contador);
		exit(0);
	}  
} 
