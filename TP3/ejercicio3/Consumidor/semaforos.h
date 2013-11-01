#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


union semun { int val;
              struct semid_ds *buf;
              unsigned short *array;
              struct seminfo *__buf;
            };

int obtenermutex (key_t );
int obtenersemaforo (key_t , int );
void pedirsem (int );
void devolversem(int);
void eliminarsem(int);
void eliminarmut(int);

