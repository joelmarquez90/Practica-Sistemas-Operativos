////////////////////////////////////////
//NOMBRE DEL PROGRAMA: servidor.c							
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
#include <curses.h>
#include <signal.h>
#include <pthread.h>
#include "libsocket.h"
#include "pantalla.h"

typedef struct
{
	int numJug;
	int idThread;
}t_thread;

t_jugador jugadoresant[4];
t_pintar pint;
t_thread envio;

pthread_t IDmatriz,IDcontabilidad,IDteclas[4],IDpelotas[4];

pthread_mutex_t mutex_mat=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_pelota=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_cli=PTHREAD_MUTEX_INITIALIZER;

int listen_socket=0,comm_socket=0;
int FIN_THREAD=0,cantcli=0,numJug,cayoUltiPelota;
int jug[CANTCLI]={0,0,0,0},nivel=0,FIN_PELOTAS[4],PELOTAS=0;

void *thread_matriz(void);
void *thread_contabilidad(void);
void *thread_teclas(void*);
void *thread_pelotas(void*);

int iniciar_pantalla(void);
int leer_configuracion(void);
void enviar_matriz(int,int);
int asignar_jugador(void);
void terminar_jugador(int,int,int);
void cambiar_nivel(int);
void terminar();

int main()
{	
	int numJug,lleno;
	signal(SIGINT,terminar);
	signal(SIGTERM,terminar);
	if(!leer_configuracion())
	{
		printf("ERROR CONFIGURACION\n");
		exit(1);
	}	
	if(!iniciar_pantalla())
	{
		printf("ERROR DE PANTALLA. MINIMO 24 DE ALTO Y 80 DE ANCHO\n");
		exit(2);
	}
	pintar_pantalla();
	pintar_nivel(nivel);
	nivel?nivel--:nivel++;
	envio.idThread=0;
	listen_socket=abrir_socket_escucha(CONFIG.id_puerto);
	pthread_create(&IDmatriz,NULL,(void*)&thread_matriz,NULL);	
	pthread_create(&IDcontabilidad,NULL,(void*)&thread_contabilidad,NULL);
	while(!FIN_THREAD)
	{
		comm_socket = aceptar_conexion(listen_socket);
		send(comm_socket,&cantcli,sizeof(int),0); //Le envía al cliente la cantidad de jugadores
		recv(comm_socket,&lleno,sizeof(int),0); 	
		if (!lleno)
		{
			pthread_mutex_lock(&mutex_cli);
			cantcli++;
			pthread_mutex_unlock(&mutex_cli);
			envio.numJug=asignar_jugador();
			pthread_mutex_lock(&mutex_mat);
			agregar_jugador(envio.numJug,comm_socket,2,0);
			enviar_matriz(envio.numJug,jugadores[envio.numJug].socket);
			pthread_mutex_unlock(&mutex_mat);
			envio.idThread++;
			pthread_create(&IDteclas[envio.numJug],NULL,(void*)&thread_teclas,(void *)&envio);
		}
	}
	pthread_join(IDmatriz,NULL);
	pthread_join(IDcontabilidad,NULL);
	exit(0);
}                                            

void *thread_matriz(void)  //ESTE THREAD ES EL ENCARGADO DE LA CONEXION Y COMUNICACION CON EL CLIENTE
{	
	int i;
	t_dato dato;
	while(!FIN_THREAD)
	{	
		pedirSemaforo(idMatriz);
		pthread_mutex_lock(&mutex_mat);
		if(sacar_de_cola(&cola,&dato))
			for(i=0;i<CANTCLI;i++)
				if (jug[i]!=0)
					send(jugadores[i].socket,&dato.pint,sizeof(t_pintar),0);
		pthread_mutex_unlock(&mutex_mat);
	}	
	pthread_exit(0);
}

void *thread_contabilidad(void)
{
	int i,j,solto,vidas,puntos,socket;
	t_pintar mens;
	while(!FIN_THREAD)
	{
		usleep(10000);
		solto=0;
		for(i=0;i<CANTCLI;i++)
		{
			if(jugadoresant[i].puntos!=jugadores[i].puntos||jugadoresant[i].vidas!=jugadores[i].vidas) 
			{
				mens.valor=30+i;
				mens.x=jugadores[i].vidas;
				mens.y=jugadores[i].puntos;
				for(j=0;j<CANTCLI;j++)
					if(jug[j]!=0)
						send(jugadores[j].socket,&mens,sizeof(t_pintar),0);
				jugadoresant[i].vidas=jugadores[i].vidas;
				jugadoresant[i].puntos=jugadores[i].puntos;
			}
		}
		if(!PELOTAS&&cantcli) //para saber si no hay pelotas, pero hay clientes
		{
			for(i=0;i<CANTCLI;i++)
				if(jug[i]!=0)
					if(jugadores[i].soltar==0) //y todos ya soltaron sus pelotas
						solto=1;
			if(!solto) //si ya todos las soltaron, quiere decir que ya perdio alguno una vida
			{
				for(i=0;i<CANTCLI;i++)
					if(jug[i]!=0)
					{
						vidas=jugadores[i].vidas;
						puntos=jugadores[i].puntos;
						socket=jugadores[i].socket;
						pthread_mutex_lock(&mutex_mat);
						borrar_jugador(i);
						pthread_mutex_unlock(&mutex_mat);
						if(i!=cayoUltiPelota)
						{
							pthread_mutex_lock(&mutex_mat);
							agregar_jugador(i,socket,vidas,puntos);
							pthread_mutex_unlock(&mutex_mat);
						}
						else
						{
							vidas--;
							if(vidas>0)
							{
								pthread_mutex_lock(&mutex_mat);	
								agregar_jugador(i,socket,vidas,puntos);
								pthread_mutex_unlock(&mutex_mat);
							}
							else
								terminar_jugador(97,i,socket);
						}
					}
			}			
		}
	}
	pthread_exit(0);
}

void *thread_teclas(void *param)
{
	t_thread recibo = *((t_thread *)param);
	int numJug,i,vidas,puntos,socket;	
	t_pintar fin;
	char c;
	numJug=recibo.numJug;
	do
	{
		recv(jugadores[numJug].socket,&c,sizeof(int),0);
		if(c==CONFIG.tecla_soltar&&jugadores[numJug].soltar==0)//si la tecla recibida es para soltar la pelota y todavía no la solto
		{
			pthread_create(&IDpelotas[numJug],NULL,(void*)&thread_pelotas,(void *)&numJug); //crea el thread de la pelota
			jugadores[numJug].soltar=1;
			pthread_mutex_lock(&mutex_pelota);
			PELOTAS++;	
			pthread_mutex_unlock(&mutex_pelota);
		}
		else
		{
			pthread_mutex_lock(&mutex_mat);
			mover_barra(&jugadores[numJug].bar,c,&jugadores[numJug].pel,jugadores[numJug].soltar);
			pthread_mutex_unlock(&mutex_mat);
		}
	}while(c!=CONFIG.tecla_fin&&!FIN_THREAD);
	fin.valor=99;
	if(jugadores[numJug].cayoPel==0&&jugadores[numJug].soltar==1)
	{
		pthread_mutex_lock(&mutex_pelota);
		PELOTAS--;
		pthread_mutex_unlock(&mutex_pelota);
	}
	send(jugadores[numJug].socket,&fin,sizeof(t_pintar),0);
	close(socket);
	pthread_mutex_lock(&mutex_mat);
	borrar_jugador(numJug);
	pthread_mutex_unlock(&mutex_mat);
	pthread_mutex_lock(&mutex_cli);
	cantcli--;
	pthread_mutex_unlock(&mutex_cli);
	jug[numJug]=0;
	FIN_PELOTAS[numJug]=1;
	if(!PELOTAS&&cantcli)
	{
		for(i=0;i<CANTCLI;i++)
			if(jug[i]!=0)
			{
				vidas=jugadores[i].vidas;
				puntos=jugadores[i].puntos;
				socket=jugadores[i].socket;
				pthread_mutex_lock(&mutex_mat);
				borrar_jugador(i);
				agregar_jugador(i,socket,vidas,puntos);
				pthread_mutex_unlock(&mutex_mat);
			}
	}
	pthread_exit(0);
}

void *thread_pelotas(void *param)
{
	int numJug = *((int *)param);
	int ret=-1;
	cayoUltiPelota=-1;
	FIN_PELOTAS[numJug]=0;
	while (!FIN_THREAD&&ret==-1&&!FIN_PELOTAS[numJug])
	{
		pthread_mutex_lock(&mutex_mat);
		ret=puede_mover(&jugadores[numJug].pel);
		pthread_mutex_unlock(&mutex_mat);
		if(jugadores[numJug].pel.tra==11||jugadores[numJug].pel.tra==12) //si la tray es 90 der o izq q vaya mas rapido
			usleep(CONFIG.tiempo_pelota*500);
		else if(jugadores[numJug].pel.tra>=5&&jugadores[numJug].pel.tra<=8)//si la tray es de 45 q vaya mas lento
			usleep(CONFIG.tiempo_pelota*1200);
		else
			usleep(CONFIG.tiempo_pelota*1000);
	}
	if(ret>=1&&ret<=4)//la pelota llego a alguna zona de color
	{
		pthread_mutex_lock(&mutex_pelota);
		PELOTAS--;
		jugadores[numJug].cayoPel=1;
		if(PELOTAS==0)
			cayoUltiPelota=ret-1;
		pthread_mutex_unlock(&mutex_pelota);
	}
	else if(ret==0)//la pelota llego a exit
		cambiar_nivel(numJug);
	pthread_exit(0);
}

void terminar_jugador(int valor,int numJug,int socket)
{
	t_pintar fin;
	fin.valor=valor;
	send(socket,&fin,sizeof(t_pintar),0);
	close(socket);
	pthread_cancel(IDteclas[numJug]);
	pthread_mutex_lock(&mutex_mat);
	borrar_jugador(numJug);
	pthread_mutex_unlock(&mutex_mat);
	pthread_mutex_lock(&mutex_cli);
	cantcli--;
	pthread_mutex_unlock(&mutex_cli);
	jug[numJug]=0;
}

void cambiar_nivel(int numJug)
{
	int i,vidas,puntos,socket,jugExit;
	pintar_nivel(nivel);
	nivel?nivel--:nivel++;
	switch(jugadores[numJug].pel.col)
	{
		case PAZUL:
				jugExit=0;
				break;
		case PVERDE:
				jugExit=1;
				break;
		case PMAGEN:
				jugExit=2;
				break;
		case PROJA:
				jugExit=3;
				break;
	}
	jugadores[jugExit].vidas++;
	jugadores[jugExit].puntos+=EXI;	
	pthread_mutex_lock(&mutex_pelota);
	PELOTAS=0;
	pthread_mutex_unlock(&mutex_pelota);
	for(i=0;i<CANTCLI;i++)
		if(jug[i]!=0)
		{
			FIN_PELOTAS[i]=1;
			vidas=jugadores[i].vidas;
			puntos=jugadores[i].puntos;
			socket=jugadores[i].socket;
			pthread_mutex_lock(&mutex_mat);
			borrar_jugador(i);
			agregar_jugador(i,socket,vidas,puntos);
			pthread_mutex_unlock(&mutex_mat);
		}
}

int iniciar_pantalla(void)
{
	initscr();
	getmaxyx(stdscr,ALTO,ANCHO);
	printf("INICIANDO SERVIDOR\n");
	clear();
	refresh();
	endwin();
	crear_cola(&cola);
	claveMatriz=ftok("/",6000);
	idMatriz=obtenerSemaforo(claveMatriz,0);
	return ALTO>=24&&ANCHO>=80;
}  

int leer_configuracion() // lee archivo de configuración.
{
	FILE * pfile;
	int largo;
	int retorno=1;
	char linea[300];
	if(!(pfile=fopen("configuracion.ini","r")))
		return 0;
	while(fgets(linea,300,pfile))
	{
		if(*linea=='#' || *linea=='\n')
			continue;
		largo=strlen(linea);
		if(linea[largo-1]=='\n')
			linea[largo-1]='\0';
		if(strstr(linea,"Puerto_socket: "))
			retorno=sscanf(linea+strlen("Puerto_socket: "),"%d",&CONFIG.id_puerto);	
		if(strstr(linea,"Tecla_soltar_pelota: "))
			retorno=sscanf(linea+strlen("Tecla_soltar_pelota: "),"%c",&CONFIG.tecla_soltar);		
		if(strstr(linea,"Tecla_fin: "))
			retorno=sscanf(linea+strlen("Tecla_fin: "),"%c",&CONFIG.tecla_fin);	
		if(strstr(linea,"Tecla_aba: "))
			retorno=sscanf(linea+strlen("Tecla_aba: "),"%d",&CONFIG.tecla_aba);
		if(strstr(linea,"Tecla_arr: "))
			retorno=sscanf(linea+strlen("Tecla_arr: "),"%d",&CONFIG.tecla_arr);
		if(strstr(linea,"Tecla_izq: "))
			retorno=sscanf(linea+strlen("Tecla_izq: "),"%d",&CONFIG.tecla_izq);	
		if(strstr(linea,"Tecla_der: "))
			retorno=sscanf(linea+strlen("Tecla_der: "),"%d",&CONFIG.tecla_der);	
		if(strstr(linea,"Tiempo_pelota: "))
			retorno=sscanf(linea+strlen("Tiempo_pelota: "),"%d",&CONFIG.tiempo_pelota);
		if(!retorno || retorno==-1)
		{
			fclose(pfile);
			return 0;
		}
	}	
	fclose(pfile);
	return 1;
}

void enviar_matriz(int numJug, int socket)
{
	int i,j;
	t_pintar mens;
	for(i=0;i<ALTO;i++)
		for(j=0;j<ANCHO;j++)
			{	
				mens.valor=MATRIZ[i][j];
				mens.x=i;
				mens.y=j;								
				send(socket,&mens,sizeof(t_pintar),0);
			}		
	mens.valor=40+numJug;
	send(socket,&mens,sizeof(t_pintar),0);
	for(i=0;i<CANTCLI;i++)
	{
		if(jug[i]!=0)
		{
			mens.valor=20+i;
			mens.x=jugadores[i].vidas;
			mens.y=jugadores[i].puntos;
			for(j=0;j<CANTCLI;j++)
				if(jug[j]!=0)
					send(jugadores[j].socket,&mens,sizeof(t_pintar),0);
		}
		jugadoresant[i].vidas=jugadores[i].vidas;
		jugadoresant[i].puntos=jugadores[i].puntos;		
	}     		
}

int asignar_jugador()
{
	int i;
	for (i=0;i<CANTCLI;i++)
		if(jug[i]==0)
		{
			jug[i]=1;
			return i;
		}
}

void terminar()
{
	int i;
	t_pintar fin;
	for(i=0;i<CANTCLI;i++)
		if(jug[i]!=0)
			terminar_jugador(98,i,jugadores[i].socket);
	pthread_mutex_destroy(&mutex_mat);
	pthread_mutex_destroy(&mutex_pelota);
	pthread_mutex_destroy(&mutex_cli);
	eliminarSemaforo(idMatriz);
	vaciar_cola(&cola);
	close(listen_socket);
	FIN_THREAD=1;
	clear();
	printf("HA FINALIZADO EL JUEGO\n");
	exit(0);
}
