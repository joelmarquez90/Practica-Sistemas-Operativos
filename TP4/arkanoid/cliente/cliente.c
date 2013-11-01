////////////////////////////////////////
//NOMBRE DEL PROGRAMA: cliente.c							
//TRABAJO PRACTICO N°4                  
//INTEGRANTES:                         
//Joel Marquez             35.367.125  
//Maria Eugenia Brea       35.272.169  
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
#include <pthread.h>
#include "libsocket.h"
#include "estructuras.h"
#include "pantalla.h"
#include <ncurses.h>
#include <signal.h>

pthread_t IDpantalla;
int puerto_socket=0,caller_socket=0;
char IPSERVER[16],creditos[]="BREA - LAURIA - MARQUEZ - SUAREZ",error1[]="NO SE PUDO INICIAR EL JUEGO.. PRESIONE UNA TECLA PARA CONTINUAR",error2[]="NO HAY LUGAR PARA OTRO JUGADOR.. PRESIONE UNA TECLA PARA CONTINUAR";
int FIN_THREAD=0;
t_pintar pint;

int leer_configuracion();
void *thread_pantalla(void);
void terminar(char *);

int main() 
{
	int cant_player,lleno;
	char c;
	inicializar_pantalla();	
	signal(SIGINT,SIG_IGN);
	signal(SIGTERM,SIG_IGN);
	if(!leer_configuracion())
	{
		printf("ERROR CONFIGURACION\n");
		exit(1);
	}
	caller_socket=conectar_al_server(puerto_socket,IPSERVER);		
	if (caller_socket==-1)
	{
		close(caller_socket);
		attron(A_BOLD);
		attron(A_BLINK);	
		mvprintw(ALTO/2-2,(ANCHO-strlen(error1))/2,error1);
		mvprintw(ALTO/2+2,(ANCHO-strlen(creditos))/2,creditos);
		getch();
		clear();
		refresh();
		endwin();
		exit(2);
	}	
	recv(caller_socket,&cant_player,sizeof(int),0);
	if(cant_player == 4) //Lleno, no se puede entrar
	{
		lleno = 1;
		send(caller_socket,&lleno,sizeof(int),0);
		close(caller_socket);
		attron(A_BOLD);
		attron(A_BLINK);	
		mvprintw(ALTO/2-2,(ANCHO-strlen(error2))/2,error2);
		mvprintw(ALTO/2+2,(ANCHO-strlen(creditos))/2,creditos);
		getch();
		clear();
		refresh();
		endwin();
		exit(2);
	}
	else
	{
		lleno = 0;
		send(caller_socket,&lleno,sizeof(int),0);	
	}
	presentacion();
	sleep(2);
	pthread_create(&IDpantalla,NULL,(void*)&thread_pantalla,NULL);

	while(!FIN_THREAD)
	{
		c=getch();
		send(caller_socket, &c,sizeof(int),0);
		fflush(stdin);       
	}

	pthread_join(IDpantalla, NULL);
	endwin();
	return 0;
}

void *thread_pantalla(void)
{
	while(!FIN_THREAD)
	{		
		recv(caller_socket, &pint,sizeof(t_pintar),0);
		if (pint.valor>=-4&&pint.valor<=12)
			pintar(pint);
		else if (pint.valor>=20&&pint.valor<=23)
		{
			pintar_zona(pint);
			actualizar_puntajes(pint);
		}
		else if (pint.valor>=30&&pint.valor<=33)	
			actualizar_puntajes(pint);
		else if (pint.valor>=40&&pint.valor<=43)
			pintar_puntajes(pint);
		else if (pint.valor==99)//el cliente apreto la tecla f para salir
			terminar("HAS SALIDO DEL JUEGO.. PRESIONE UNA TECLA PARA CONTINUAR");
		else if (pint.valor==98)//el servidor apreto CTRL+C
			terminar("HUBO UN PROBLEMA CON EL SERVIDOR.. PRESIONE UNA TECLA PARA CONTINUAR");
		else if (pint.valor==97)//perdio el cliente
			terminar("GAME OVER.. PRESIONE UNA TECLA PARA CONTINUAR");
	}
	pthread_exit(0);
}

int leer_configuracion()
{
  	FILE * pfile;
	int largo;
	int retorno=1;
	char linea[300];
	if(!(pfile=fopen("configuracion.ini","r")))
		return 0;
	while(fgets(linea,300,pfile))
	{
		if(*linea=='#'||*linea=='\n')
			continue;
		largo=strlen(linea);
		if(linea[largo-1]=='\n')
			linea[largo-1]='\0';
		if(strstr(linea,"IP_SERVIDOR: "))
			retorno=sscanf(linea+strlen("IP_SERVIDOR: "),"%s",IPSERVER);							
		if(strstr(linea,"Puerto_socket: "))
			retorno=sscanf(linea+strlen("Puerto_socket: "),"%d",&puerto_socket);			
		if(!retorno || retorno==-1) //SI NO ENCONTRE ALGUNO DE LOS PARAMETROS
		{
			fclose(pfile);
			return 0;
		}
	}	
	fclose(pfile);
	return 1;
}

void terminar(char *cad)
{
	FIN_THREAD=1;	
	close(caller_socket);
	clear();
	attron(A_BOLD);
	attron(A_BLINK);	
	mvprintw(ALTO/2-2,(ANCHO-strlen(cad))/2,cad);
	mvprintw(ALTO/2+2,(ANCHO-strlen(creditos))/2,creditos);
	refresh();
	pthread_cancel(IDpantalla);
	getch();
	clear();
	refresh();
	endwin();
	exit(0);
}
