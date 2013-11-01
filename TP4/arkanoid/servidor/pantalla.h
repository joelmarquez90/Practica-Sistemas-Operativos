#ifndef PANTALLA_H
#define PANTALLA_H

#include "cola.h"
#include "semaforos.h"

#define AL 90
#define AN 200
#define BORDE 0
#define ZEXIT 12
#define ZAZUL -1
#define ZVERDE -2
#define ZMAGEN -3
#define ZROJA -4
#define BAZUL 1
#define BVERDE 2
#define BMAGEN 3
#define BROJA 4
#define FONDO 5
#define PAZUL 6
#define PVERDE 7
#define PMAGEN 8
#define PROJA 9
#define BLOQUE1 10
#define BLOQUE2 11
#define CANTCLI 4
#define P5 5
#define P10 10
#define EXI 100

int ALTO,ANCHO,idMatriz;
short MATRIZ[AL][AN];
t_jugador jugadores[CANTCLI];
t_config CONFIG;
t_cola cola;
key_t claveMatriz;

void pintar_pantalla(void);
void pintar_nivel(int);
int encolar(int,int,int);
void pieza_barra(int,int,int,int);
void pieza_pelota(int,int,int);
void dibujar_pieza(t_pieza); 
void mover_barra(t_pieza *,int,t_pieza*,int);
void cambiar_trayectoria(t_pieza *,int,int,int);
int puede_mover(t_pieza*);
void calcular_rebote(int,t_pieza*);
void agregar_jugador(int,int,int,int);
void borrar_jugador(int);
void sumar_puntaje(t_pieza*,int);

#endif
