#include "semaforos.h"

int obtenermutex (key_t clave)
{ 
  int idsem;
  union semun ctlsem;
  
  idsem = semget (clave, 1, IPC_CREAT | 0600);
  ctlsem.val = 1;
  semctl(idsem, 0, SETVAL , ctlsem);
  return idsem;

}

int obtenersemaforo (key_t clave, int val)
{
 
 int idsem;
 union semun ctlsem;
 
 idsem = semget (clave, 1, IPC_CREAT | 0600);
 ctlsem.val = val;
 semctl (idsem, 0, SETVAL, ctlsem);
 return idsem;

}


void pedirsem (int id)
{

 struct sembuf opsem;
 opsem.sem_num= 0 ;
 opsem.sem_op = -1;
 opsem.sem_flg= 0;
 semop (id , &opsem , 1);

}



void devolversem (int id)
{

 struct sembuf opsem;

 opsem.sem_num = 0;
 opsem.sem_op = 1;
 opsem.sem_flg = 0;
 
 semop (id, &opsem , 1 );   
 
}

void eliminarsem (int id)
{ 
 semctl(id, 0, IPC_RMID);
}
