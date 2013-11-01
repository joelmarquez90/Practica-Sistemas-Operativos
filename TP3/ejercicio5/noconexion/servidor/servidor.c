////////////////////////////////////////
//NOMBRE DEL PROGRAMA: servidor.c							
//TRABAJO PRACTICO N°3                  
//EJERCICIO 5 (no conexion).	                        
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

#define TAMBUF 1024
#define MAXQ 10
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

int main(){
int socket_1 = 0;
int longservidor;
unsigned short int port = 0;
unsigned long int ip_address = 0;
struct sockaddr_in address;
struct sockaddr_in client;
struct mensaje mens;
struct respuesta resp;
socklen_t con_addr_len;
char buffer[TAMBUF];
char * aux;
int pos;
FILE * pf;

//creacion del socket
socket_1 = socket(AF_INET, SOCK_DGRAM, 0);

//asignandole una direccion a este
bzero(&address, sizeof(address));
address.sin_family = AF_INET;
port = htons(PORT);
address.sin_port = port;
ip_address = htonl(INADDR_ANY);
address.sin_addr.s_addr = ip_address;
bind(socket_1, (struct sockaddr *)&address, sizeof(struct sockaddr));

printf("Apertura del socket\n");


bzero(buffer, TAMBUF);
longservidor = sizeof(client);
recvfrom(socket_1, &mens, sizeof(mens), 0, (struct sockaddr *)&client,&longservidor);
printf("%s : se recibio: cpu_usage: %f mem_free: %li \n", inet_ntoa(client.sin_addr),mens.cpu_usage,mens.mem_free );
	

if(mens.cpu_usage<0.8)
	strcpy(resp.rpta,"OK");
else
	strcpy(resp.rpta,"WARNING");

//obtengo la fecha del sistema a traves del comando date, luego lo leo del .txt en el que se guardo.
	system("date +'%d/%m/%y %T' | head -n 1 -> fecha.txt");
	pf = fopen("fecha.txt","r");
	fgets(resp.fecha,sizeof(resp.fecha),pf);

sendto(socket_1, &resp, sizeof(resp), 0, (struct sockaddr *)&client, sizeof(client));


printf("respuesta enviada: %s %s\n",resp.rpta, resp.fecha);
	
close(socket_1);
	
	

printf("Se desconecto\n");
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
	
