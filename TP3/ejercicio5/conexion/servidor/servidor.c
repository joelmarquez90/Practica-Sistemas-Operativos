////////////////////////////////////////
//NOMBRE DEL PROGRAMA: servidor.c							
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
int listen_socket = 0, comm_socket = 0;
unsigned short int listen_port = 0;
unsigned long int listen_ip_address = 0;
struct sockaddr_in listen_address, con_address;
struct mensaje mens;
struct respuesta resp;
socklen_t con_addr_len;
char buffer[TAMBUF];
char * aux;
int pos;
FILE * pf;

//creacion del socket
listen_socket = socket(AF_INET, SOCK_STREAM, 0);

//asignandole una direccion a este
bzero(&listen_address, sizeof(listen_address));
listen_address.sin_family = AF_INET;
listen_port = htons(PORT);
listen_address.sin_port = listen_port;
listen_ip_address = htonl(INADDR_ANY);
listen_address.sin_addr.s_addr = listen_ip_address;
bind(listen_socket, (struct sockaddr *)&listen_address, sizeof(struct sockaddr));

listen(listen_socket, MAXQ);

printf("Comenzamos a escuchar conexiones\n");

while(strcasecmp(mens.aux, "fin")!=0) {
	bzero(&con_address, sizeof(con_address));
		comm_socket = accept(listen_socket, (struct sockaddr *)(&con_address), &con_addr_len);
	printf("Conexion recibida\n");
	bzero(buffer, TAMBUF);
	recv(comm_socket, &mens, sizeof(mens), 0);
	printf("%s :Recibido: cpu_usage: %f mem_free:%li \n", inet_ntoa(con_address.sin_addr), mens.cpu_usage,mens.mem_free);
	
	///////
	pos = indexOf(buffer,' ');
	aux = substr(buffer,0,pos);
	bzero(buffer, TAMBUF);
	if(mens.cpu_usage<1.3)
		strcpy(resp.rpta,"OK");
	else
		strcpy(resp.rpta,"WARNING");

	//obtengo la fecha del sistema a traves del comando date, luego lo leo del .txt en el que se guardo.
	system("date +'%d/%m/%y %T' | head -n 1 -> fecha.txt");
	pf = fopen("fecha.txt","r");
	fgets(resp.fecha,sizeof(resp.fecha),pf);

	send(comm_socket, &resp, sizeof(resp), 0);
	printf("respuesta enviada: %s %s\n",resp.fecha, resp.rpta);
	//////
	close(comm_socket);
	}
	
	close(listen_socket);
	printf("Se desconecto\n");
	return 0;
}

//PASAR FUNCIONES A BIBLIOTECAAAAAA!!!!

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
	
