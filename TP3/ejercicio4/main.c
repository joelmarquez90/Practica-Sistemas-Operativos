////////////////////////////////////////
//NOMBRE DEL PROGRAMA: main.c							
//TRABAJO PRACTICO N°3                  
//EJERCICIO 4.	                        
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
#include<signal.h>
#include <pthread.h>
#define MAX_RECIBIDO 1000000
#define MAX_SEGMENTO 23

void activarThread(int);
void *threadPromedio(void *);

int j = 0, n, id = 0;

int main(int argc, char * argv[])
{	
	int i, marc = 0, jTemp;
	float random, max, min, acum = 0.;
	if (argv[1]==NULL)
	{
		printf("ERROR. Modo: ./EJ4 n (n=cantidad de numeros aleatorios a calcular en cada rango)\n");
		exit(1);
	}
	n = atoi(argv[1]);								//Convierte el número pasado como parámetro a entero
	srand(getpid());
	signal(SIGUSR1, activarThread);
	if (n <= MAX_RECIBIDO)							//Si el número es menor o igual a 1000000
	{		
		printf ("PID: %d\n", getpid());
		while (j < MAX_SEGMENTO)					//Mientras j sea menor que 23 (el rango de cálculo de los números, 0-2300)
		{
			jTemp = j;									//Almaceno el j porque si se crean threads la pueden llegar a modificar
			for (i = 0; i < n; i++)
			{	
				random = ((float)rand()/RAND_MAX) * 100 + jTemp * 100;		//aca, entonces no calcularía los números de su rango
				if (marc == 0)
				{
					max = random;
					min = random;
					marc = 1;
				}
				else if (random > max)
					max = random;
				else if (random < min)
					min = random;			
				acum += random;		
			}
			printf("HILO 0\nMáximo: %.4f\nMínimo: %.4f\nPromedio: %.4f\n", max, min, acum/n);
			marc = 0;
			acum = 0;
			sleep(1);
			j++;
		}
	}
	else
	{
		printf("Se debe pasar un N menor a 1000000\n");
		exit(1);
	}
	return 0;
}

void activarThread(int sig)
{
	int res;
	pthread_t hilo;
	if (sig == SIGUSR1)
		if (j < MAX_SEGMENTO)						//Puede pasar que ya hayan threads calculando todos los segmentos
		{
			id++;
			res = pthread_create(&hilo, NULL, threadPromedio, (void *)&id);
		}
		else
			printf("No se pueden crear mas Threads\n");
}

void *threadPromedio(void *idHilo)
{	
	int i, marc = 0, jTemp, nroHilo;
	float random, max, min, acum = 0.;
	nroHilo = *((int *)idHilo);
	while (j < MAX_SEGMENTO)
	{
		jTemp = j;
		for (i = 0; i < n; i++)
		{	
			random = ((float)rand()/RAND_MAX) * 100 + jTemp * 100;
			if (marc == 0)
			{
				max = random;
				min = random;
				marc = 1;
			}
			else if (random > max)
				max = random;
			else if (random < min)
				min = random;			
			acum += random;
		}
		printf("HILO %d\nMáximo: %.4f\nMínimo: %.4f\nPromedio: %.4f\n", nroHilo, max, min, acum/n);
		marc = 0;
		acum = 0;
		sleep(1);
		j++;
	}
}
