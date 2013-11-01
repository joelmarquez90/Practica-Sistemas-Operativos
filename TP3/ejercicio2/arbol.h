#include <stdio.h>
#include <stdlib.h>

#define SIN_MEMORIA 0
#define TODO_BIEN 1
#define CLAVE_DUPLICADA 2
#define FIN_ARCHIVO SIN_MEMORIA

typedef struct
{
	char empresa[21];
	char apynom[31];
	long dni;
	float sueldo;
	int antiguedad;
	char posee_tarjeta [2];
	long tel; 
}t_info;

typedef struct s_nodo
{
   t_info info;
   struct s_nodo 	*izq,
                  *der;
}t_nodo;

typedef t_nodo *t_arbol;

int comparar (const t_info *, const t_info *);
void crearArbol (t_arbol *);
int cargarenArbol (t_arbol *, const t_info *);
void eliminarArbol (t_arbol *);
void grabarpreArbol (const t_arbol *, FILE *);
