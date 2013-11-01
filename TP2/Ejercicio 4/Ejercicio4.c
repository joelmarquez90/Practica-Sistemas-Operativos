#include "libreria.c"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

pid_t alarma[5]; // vector donde se guardaran los identificadores de cada alarma(pid del proceso), elejimos 5 a modo de ejemplo.

int contador=0; //contador para ver cuantas alarmas hemos instanciado.
void capturar_senal(int iNumSen, siginfo_t *info, void *ni) {
if(iNumSen==SIGUSR1)
{	
	
	
	alarma[contador] =info->si_pid;//guardamos el identificador de la alarma.
	contador++;
	
}
}

int main()
{
	int status=0;

	pid_t padre=getpid();
	pid_t pidHijo;
	
	struct sigaction act;
	act.sa_sigaction=capturar_senal;
	act.sa_flags=SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);



	if(getpid()==padre)
		printf("\n Soy el padre y mi pid es:%d \n",padre);

	
	NuevaAlarma(10,padre,0); //creamos una alarma "por unica vez" a modo de ejemplo.
	pause();
	NuevaAlarma(2,padre,1); // creamos una alarma recurrente a modo de ejemplo.
	pause();
 
	
	if(getpid()==padre)
	{
		sleep(50); // para visualizar varias instancias de la alarma recurrente ejecutamos el comando sleep.
		CancelarAlarma(alarma[0]);
		CancelarAlarma(alarma[1]);
	}
	




	
wait(&status);
exit(0);		
}
