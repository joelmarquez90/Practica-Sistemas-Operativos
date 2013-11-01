#ifndef SEMAFOROS_H
#define SEMAFOROS_H
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<sys/sem.h>
#include<fcntl.h>

union semun 
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

int obtenerSemaforo(key_t clave, int valor);
void pedirSemaforo(int IdSemaforo);
void devolverSemaforo(int IdSemaforo);
void eliminarSemaforo(int IdSemaforo);

#endif
