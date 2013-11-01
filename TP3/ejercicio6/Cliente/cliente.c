#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include<signal.h>
#define TAMBUF 1024
#define PORT 51244

int msj=0;
void handler (int S)
{
  if(S==SIGUSR1)
 {
   exit(0);
 }

}

void* rutina_hilo(void *);
int main(int argc, const char *argv[]) {

pthread_t hilo;
pid_t pid;

int caller_socket1 = 0;
unsigned short int listen_port = 0;
unsigned long int listen_ip_address = 0;
struct sockaddr_in listen_address;

signal(SIGUSR1,handler);

// Creación del socket
caller_socket1 = socket(AF_INET, SOCK_STREAM, 0);

// Asignandole una dirección a éste
listen_address.sin_family = AF_INET;

listen_port = htons(PORT);
listen_address.sin_port = listen_port;

listen_ip_address = inet_addr("127.0.0.1");
listen_address.sin_addr.s_addr = listen_ip_address;

bzero(&(listen_address.sin_zero), 8);

// Se conecta con el servidor
connect(caller_socket1, (struct sockaddr *)&listen_address, sizeof(struct sockaddr));


pid=getpid();
srand(pid);

while(!msj)
{  recv(caller_socket1,&msj,sizeof(msj),0);
	sleep(rand()%10+1);
   if(!msj)
   {
		if(pthread_create(&hilo,NULL,rutina_hilo,NULL)!=0)
		{ 
			printf("\n Error al crear el hilo");
			exit(1);
		}
		    else
		   		printf("\nHilo creado.\n ");
   }
	
}

exit(0);
	

}

void* rutina_hilo(void *param)
{
int caller_socket = 0;
unsigned short int listen_port = 0;
unsigned long int listen_ip_address = 0;
struct sockaddr_in listen_address;
// Creación del socket
caller_socket = socket(AF_INET, SOCK_STREAM, 0);

// Asignandole una dirección a éste
listen_address.sin_family = AF_INET;

listen_port = htons(PORT);
listen_address.sin_port = listen_port;

listen_ip_address = inet_addr("127.0.0.1");
listen_address.sin_addr.s_addr = listen_ip_address;

bzero(&(listen_address.sin_zero), 8);

// Se conecta con el servidor
connect(caller_socket, (struct sockaddr *)&listen_address, sizeof(struct sockaddr));

	
	system("df >log.txt && cat log.txt");
// Cerramos el socket como corresponde.

close(caller_socket);
pthread_exit(0);
}

