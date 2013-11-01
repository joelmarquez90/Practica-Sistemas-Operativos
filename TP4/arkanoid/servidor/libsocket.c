#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <poll.h>
#include "libsocket.h"

int abrir_socket_escucha(int puerto)
{
	int listen_socket,reuse=1;
	struct sockaddr_in listen_address;
	unsigned short int listen_port=0;
	unsigned long int listen_ip_address=0;

	listen_socket=socket(AF_INET,SOCK_STREAM,0);
	if(setsockopt(listen_socket,SOL_SOCKET,SO_REUSEADDR,(char*)&reuse,sizeof(reuse))<0)
		printf("ERROR AL SETEAR OPCIONES DE SOCKET ESCUCHA\n");

	bzero(&listen_address,sizeof(listen_address));
	listen_address.sin_family=AF_INET;
	listen_port=htons(puerto);
	listen_address.sin_port=listen_port;
	listen_ip_address=htonl(INADDR_ANY);
	listen_address.sin_addr.s_addr=listen_ip_address;
	bind(listen_socket,(struct sockaddr*)&listen_address,sizeof(struct sockaddr));
	listen(listen_socket,4);

	return listen_socket;
}

int conectar_al_server(int puerto, char *IP_server)
{
	int caller_socket;
	struct sockaddr_in listen_address;
	unsigned short int listen_port=0;
	unsigned long int listen_ip_address=0;

	caller_socket=socket(AF_INET,SOCK_STREAM,0);
	bzero(&listen_address,sizeof(listen_address));
	listen_address.sin_family=AF_INET;
	listen_port=htons(puerto);
	listen_address.sin_port=listen_port;
	listen_ip_address=htonl(INADDR_ANY);
	listen_address.sin_addr.s_addr=inet_addr(IP_server);
	if((connect(caller_socket,(struct sockaddr*)&listen_address,sizeof(struct sockaddr)))==-1)
		return -1;

	return caller_socket;
}

int aceptar_conexion(int listen_socket)
{
	int comm_socket=0;
	comm_socket=accept(listen_socket, 0, 0);
	return comm_socket;
} 
