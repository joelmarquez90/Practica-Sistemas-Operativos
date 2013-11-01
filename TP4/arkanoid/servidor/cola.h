#ifndef COLA_H
#define COLA_H

#include "estructuras.h"

#define TODO_OK 1
#define NO_MEM 0
#define COLA_VACIA 3

typedef struct
{
	t_pintar pint;
}t_dato;

typedef struct s_nodo
{
	t_dato info;
	struct s_nodo *psig;
}t_nodo;

typedef t_nodo* t_cola;

void crear_cola(t_cola *);
int poner_en_cola(t_cola *,const t_dato*);
int sacar_de_cola(t_cola *,t_dato *);
int frente_de_cola(const t_cola *,t_dato *);
int vaciar_cola(t_cola *);

#endif
