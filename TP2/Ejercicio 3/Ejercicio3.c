////////////////////////////////////////
//NOMBRE DEL SCRIPT:Ejercicio3.c							
//TRABAJO PRACTICO N°2                  
//EJERCICIO 3.	                        
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
#include <signal.h>
#include "cola.c"

int cantviajes=0;
t_lista cola;
t_dato dato;
pid_t piddem;
int numerodehijo;

void manejador(int);
void manejador_alarma(int, siginfo_t *,void *);

int main (int argc, char * argv[])
{
	pid_t sid, pidhijo;
	int status=0, i, fd;
	struct sigaction act;
	act.sa_sigaction=manejador_alarma;
	act.sa_flags=SA_SIGINFO; 

	piddem=fork();
 	
	if(piddem==-1)
	{
	 printf("Error al crear el demonio\n");
	 exit(1);
     }
	if(piddem>0)						//el proceso padre debe finalizar
	{
	 exit(0);
	}
	piddem=getpid();
	printf("PID Demonio: %d",getpid());	//para acceder a todos los archivos creados por el demonio
	if(getpid()==piddem)
	{
	crear_cola(&cola);	
	

	sid=setsid();   //se crea una nueva sesión.
	if(sid<0)
	{exit(1);}

	if(chdir("/")<0)
	{exit(1);}
	
	for(i=0;i<6;i++)
	{	
	pidhijo=fork();        
		if(pidhijo==-1)
		{
		 printf("Error al crear el hijo\n");
		 exit(1);
    	 	}
		if(pidhijo>0)						//el proceso padre debe finalizar
		{
		 dato.pid=pidhijo;
		 if(!poner_en_cola(&cola,&dato))
		 {
        	   exit(0);
		 }
		}
  		else
		{
		 numerodehijo=i+1;
		 signal(SIGUSR1,manejador);			//cada hijo espera por las señales que le enviara el demonio
		 signal(SIGTERM,manejador);
		 while(1)
  		 {pause();}
		}
	}	
	signal(SIGTERM,manejador);			//el demonio espera por cualquiera de las tres señales
	signal(SIGUSR1,manejador);
	sigaction(SIGALRM, &act, NULL);               
	if(getpid()==piddem)
	{	while(1)
 	 		 pause();
	}	
   }	
}

void manejador(int sig)
{
 int status=0,i;
 if(sig==SIGUSR1)
 {
   if(getpid()==piddem)					//cuando el demonio recibe esta señal activa al primer auto de la lista
    {
	if(sacar_de_cola(&cola,&dato))
	{
	  kill(dato.pid,SIGUSR1);
	}
    }
   else
    {
       cantviajes++;					//el auto es activado por el demonio y realiza el viaje de tiempo variable	
       srand(getpid());					
       sleep(rand()%10+1);
       kill(getppid(),SIGALRM);				//al terminar el viaje envia una alarma al demonio para que lo vuelva a agregar al final de la cola
    }

 }
	if(sig==SIGTERM)
	{	
		if(getpid()==piddem)			//el demonio saca de la cola todos los pid y finaliza a todos los autos
		{ 
		  for(i=0;i<6;i++)
		  {
			if(sacar_de_cola(&cola,&dato))
			 {
	  	  	 kill(dato.pid,SIGTERM);
                 	  wait(&status);
		 	 }
		  }
                  for(i=0;i<6;i++)
		  {wait(&status);}
                  exit(0);	          
               }
		else					//antes de finalizar cada hijo informa la cantidad de viajes que realizo
		{
		  printf("El remis numero %d viajo %d veces\n",numerodehijo,cantviajes);
                  exit(0);
		}	
			
	}		
}

void manejador_alarma(int sig, siginfo_t *info, void *ni)
{
  t_dato dato;
	if(sig==SIGALRM)		
	{
		if(getpid()==piddem)			//el demonio recibe la alarma y agrega el pid, del auto que envio la alarma, al final de la cola
		{
			dato.pid=info->si_pid;
			if(!poner_en_cola(&cola,&dato)	)
			{exit(0);}
		}
	}
}


