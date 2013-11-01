#ifndef PANTALLA_H
#define PANTALLA_H

#include "estructuras.h"

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

int ALTO;
int ANCHO;
short MATRIZ[48][128];

void inicializar_pantalla(void);
void presentacion();
void pintar_zona(t_pintar);
void pintar_puntajes(t_pintar);
void actualizar_puntajes(t_pintar);
void pintar(t_pintar);

#endif
