#ifndef COLAENLISTA_H_INCLUDED
#define COLAENLISTA_H_INCLUDED
#define TODO_OK 1
#define NO_MEM 0
#define COLA_VACIA 3

typedef struct{pid_t pid;}t_dato;

typedef struct s_nodo{t_dato info;
                      struct s_nodo *psig;}t_nodo;

typedef t_nodo* t_lista;

int poner_en_cola(t_lista*, const t_dato*);
int sacar_de_cola(t_lista*, t_dato *);
void crear_cola(t_lista*);
//int cola_vacia(const t_lista*);
int vaciar_cola(t_lista*);
int frente_de_cola(const t_lista*,t_dato*);



#endif // COLAENLISTA_H_INCLUDED
