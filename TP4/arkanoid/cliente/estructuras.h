#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

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
  int cod;
  int rot;
  int x;
  int y;
}t_pieza;

typedef struct
{
	t_pieza pieza;
	int pos_jug;
}t_entrada;





#endif
