#include "libreria.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


void  NuevaAlarma(int seg,pid_t padre,int recurrente)  //si recurrente =1 es recurrente

{
	
	pid_t pidHijo;
	int status=0;
	if(getpid()==padre)
	{	

		struct sigaction act;
		SetearActYConjSen(&act);

	
		sigaction(SIGCHLD, &act, NULL);

		pidHijo = fork();
				
					
		if(pidHijo == 0)
		//estoy en el proceso hijo, ejecuto la alarma.
 		{	
		     sigaction(SIGALRM, &act, NULL);
	             sigaction(SIGTERM, &act, NULL);
	             kill(getppid(),SIGUSR1);
		     if(recurrente==1)   
			{
			
		        for(;;)	
				{
					printf("\n Comienza la alarma.%d \n",getpid());		
					alarm(seg);
					pause();
				//	sleep(1);
				}
			}
			else
			{		printf("Comienza la alarma: %d \n",getpid());
					alarm(seg);
					pause();
					exit(0);
			}
			
		

		}
		else
		{
			if(pidHijo == -1)
			{
			printf("\n Error al crear el proceso hijo.");
			exit(1);
			}
			
		}
	}
	
	
}

void CancelarAlarma(pid_t pid)
{	
	kill(pid,SIGTERM);
}

	
	
	
void handler(int sig, siginfo_t *info, void *ni)
{
	if(sig==SIGALRM)
        {
	
			
		printf("\n Ha finalizado el tiempo de la alarma:%d \n",getpid());
	}
	else
	if(sig==SIGTERM)
	{ 
		printf("\nAlarma cancelada: %d",getpid());
		
		exit(0);	
	}
	
	else
	if(sig==SIGCHLD) 
	{
		switch(info->si_code)
		{
			case CLD_EXITED:
					printf("\n Finalizo proceso hijo.\n");
					break;
			case CLD_STOPPED:
					printf("\n proceso hijo se detuvo.\n");
					break;
		}		
	}
	

}

void SetearActYConjSen(struct sigaction * act)
{
	act->sa_sigaction=handler;
	act->sa_flags=SA_SIGINFO;
}














