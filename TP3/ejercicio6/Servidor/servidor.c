#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <signal.h>
#define TAMBUF 1024
#define MAXQ 10 //maximo de conexiones en espera
#define PORT 51244 

int socketpadre;
int msj=0;

void comparar_informar();
void handlerserver(int S)
{
  if (S==SIGUSR1)
{ printf("Soy el servidor y termino ");
  msj=1;
  send(socketpadre,&msj,sizeof(msj),0);
  close(socketpadre);
   exit(0); }
}

int main() {
int listen_socket = 0, comm_socket = 0;
unsigned short int listen_port = 0;
unsigned long int listen_ip_address = 0;
struct sockaddr_in listen_address, con_address;
socklen_t con_addr_len;
char buffer[TAMBUF];

signal(SIGUSR1,handlerserver);
// Creación del socket
listen_socket = socket(AF_INET, SOCK_STREAM, 0);

// Asignandole una dirección a éste
bzero(&listen_address, sizeof(listen_address));
listen_address.sin_family = AF_INET;
listen_port = htons(PORT); 
listen_address.sin_port = listen_port;
listen_ip_address = htonl(INADDR_ANY);
listen_address.sin_addr.s_addr = listen_ip_address;
bind(listen_socket,(struct sockaddr *)&listen_address,sizeof(struct sockaddr));
listen(listen_socket, MAXQ);  //socket que se utilizara para recibir conexiones

printf("Comenzamos a escuchar conexiones\n");
printf("mi pid es %d\n", getpid());

bzero(&con_address, sizeof(con_address));
socketpadre= accept(listen_socket, (struct sockaddr *)(&con_address),&con_addr_len);

printf("Conexion padre recibida");


while (1) {
bzero(&con_address, sizeof(con_address));
send(socketpadre,&msj,sizeof(msj),0);
comm_socket = accept(listen_socket, (struct sockaddr *)(&con_address),&con_addr_len);

printf("Conexión recibida\n");
//bzero(buffer, TAMBUF);
//recv(comm_socket, buffer, TAMBUF, 0);

system("df >logservidor.txt");
comparar_informar(); //FUNCION QUE COMPARA E INFORMA LO QUE OCURRIO CON EL FILESYSTEM
close(comm_socket);
}

close(listen_socket);
printf("Se desconectó\n");
return 0;
}


void comparar_informar()//ABRE EL ARCHIVO CREADO POR EL SERVIDOR Y LO COMPARA CON EL DEL CLIENTE
{
  FILE* pflog;FILE *pflogserv;
  char linea1[400], linea2[400];
 int modi=0;

   pflog=fopen("../Cliente/log.txt","rt");
   if(!pflog)
	{ printf("Error. Se termina todo. \n ");
	exit(1);
	}
  

   pflogserv=fopen("logservidor.txt","rt"); //ABRIMOS AMBOS ARCHIVO Y COMPARAMOS LINEA A LINEA
    if(!pflogserv)
	{ printf("Error. Se termina todo. \n ");
	exit(1); }

  printf("Modificaciones de filesystem: \n");
  while(!feof(pflogserv))
  {
	fgets(linea1,sizeof(linea1),pflog);
	fgets(linea2,sizeof(linea2),pflogserv);
	
	if(strcmp(linea1,linea2))//SI DA != 0 HUBO CAMBIOS, ENTONCES SE MUESTRA.
	{ printf("%s \n",linea2);
		modi =1;}
	
  }
 if(!modi)
 printf("No hubo modificaciones de filesystem \n\n");
 fclose(pflog);
 fclose(pflogserv);
}

