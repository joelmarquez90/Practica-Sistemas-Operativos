#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H


typedef struct
{
	int id_puerto;
	int tecla_izq;
	int tecla_der;
	int tecla_arr;
	int tecla_aba;
	int tiempo_pelota;
	char tecla_soltar;
	char tecla_fin;
}t_config;

typedef struct
{
	int tecla;
	int njug;
}t_mensaje;

typedef struct
{
int valor,x,y;
}t_pintar;

typedef struct 
{
	int rot;
	int col;
	int cod;
	int x;
	int y;
	int tra;
}t_pieza;

typedef struct
{
	int vidas;
	int puntos;
	int socket;
	int nro;
	t_pieza bar;
	t_pieza pel;
	int soltar;
	int cayoPel;
}t_jugador;



#endif
