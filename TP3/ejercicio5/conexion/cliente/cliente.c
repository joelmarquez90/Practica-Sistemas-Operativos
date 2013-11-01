////////////////////////////////////////
//NOMBRE DEL PROGRAMA: cliente.c							
//TRABAJO PRACTICO N°3                  
//EJERCICIO 5 (conexion).	                        
//INTEGRANTES:                         
//Joel Marquez             35.367.125  
//Maria Eugenia Brea       35.272.169  
//Maria Victoria Trimboli  35.723.767  
//Soledad Suarez           35.387.379  
//Marlene Lauria           35.423.458  
//PRIMERA ENTREGA												
////////////////////////////////////////

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define TAMBUF 1024
#define PORT 53210

struct mensaje{
float cpu_usage;
long int mem_free;
char aux[5];
};

struct respuesta{
char fecha[50];
char rpta[10];
};

char * substr(char *,int,int);
int indexOf(char *,char);

int main(int argc, const char * argv[]) {
int caller_socket = 0;
unsigned short int listen_port = 0;
unsigned long int listen_ip_address = 0;
struct sockaddr_in listen_address;
struct mensaje mens;
struct respuesta resp;
char buffer[TAMBUF];
FILE * archivo;
char aux[200];
char * aux2;
int i,pos,pos2;

//llamada al comando top para averiguar el uso de la cpu y la mem libre.
system("top -b -n 1 | head -n 5 | sed -n '/Cpu/,/Mem/p' -> top.txt");

archivo = fopen("top.txt","r");

if(argv[2]!=NULL)
	strcpy(mens.aux,argv[2]);
fgets(aux,sizeof(aux),archivo);
pos = indexOf(aux,'%');
aux2 = substr(aux,9,pos-9);
mens.cpu_usage = atof(aux2);

fgets(aux,sizeof(aux),archivo);
pos = indexOf(aux, 'd');
pos2 = indexOf(aux,'f');
aux2 = substr(aux,pos+6,pos2-2-(pos+6));
mens.mem_free = atol(aux2);

//creacion del socket
caller_socket = socket(AF_INET, SOCK_STREAM, 0);

//asignandole una direccion a este
listen_address.sin_family = AF_INET;

listen_port = htons(PORT);
listen_address.sin_port = listen_port;

listen_ip_address = inet_addr(argv[1]);
listen_address.sin_addr.s_addr = listen_ip_address;

bzero(&(listen_address.sin_zero),8);

//se conecta con el servidor

connect(caller_socket, (struct sockaddr *)&listen_address, sizeof(struct sockaddr));

printf("se enviaran: cpu_usage: %f mem_free: %li\n",mens.cpu_usage, mens.mem_free);
//enviamos el mensaje
send(caller_socket, &mens, sizeof(mens), 0);

//recibimos la respuesta
recv(caller_socket, &resp, sizeof(resp), 0);
printf("Respuesta recibida: %s %s\n",resp.rpta, resp.fecha);

//cerramos el socket como corresponde
close(caller_socket);

return 0;
}

char * substr(char * cadena, int comienzo, int longitud)
{
	if(longitud == 0)
		longitud = strlen(cadena)-comienzo-1;
	
	char *nuevo = (char*)malloc(sizeof(char) * longitud);
	strncpy(nuevo, cadena + comienzo, longitud);
	
	return nuevo;
}

int indexOf(char * cadena, char caracter)
{
	int pos=0;	
	while(cadena != NULL)
	{
		if(*cadena == caracter)
			return pos;
		cadena++;
		pos++;
	}
	return -1;
}

















