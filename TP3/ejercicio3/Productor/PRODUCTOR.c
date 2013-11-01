#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include<errno.h> // variable global errno
#include "estructuras.h"
#include "semaforos.c"
#define TAMBUF 1000


int main(int argc, const char *argv[]) {
t_mensaje message;
char *buffer2;
char buffer [TAMBUF];
FILE *filepointer;
int memidauxid;
key_t memidauxkey;
char* aux;

memidauxkey=ftok("/home",6004);
message.keylimite1=ftok("/",6008);	///// SEMAFORO
message.keylimite2=ftok("/",6009);
message.keymem=ftok("/home",6006);	///// MEMORIA COMPARTIDA	
message.memid=shmget(message.keymem,4096,IPC_CREAT | 0660 );
memidauxid=shmget(memidauxkey,1024,IPC_CREAT | 0777 );
aux=(char*)shmat(memidauxid,NULL,0);

if(message.memid==-1 || memidauxid==-1)
        {

                 printf("Error al crear el segmento de memoria %d \n",errno);
		 shmdt(buffer2);
        	 shmctl(message.memid, IPC_RMID, 0);
     	         eliminarsem(message.limiteid1);
       		 eliminarsem(message.limiteid2);
		 exit(1);
        }

message.limiteid1=obtenersemaforo(message.keylimite1,0);
message.limiteid2=obtenersemaforo(message.keylimite2,1);

buffer2=(char *) shmat(message.memid,NULL,0);
filepointer=fopen(argv[1],"rt");  

if (!filepointer)
{
	printf("Error. Formato de ejecución: ./EJ3 [nombre_archivo]\n");
	shmdt(buffer2);
	shmdt(aux);
	shmctl(memidauxid,IPC_RMID,0);
	shmctl(message.memid, IPC_RMID, 0);
	eliminarsem(message.limiteid1);
	eliminarsem(message.limiteid2);
	exit(1);
}


	fgets(buffer,sizeof(buffer),filepointer);  ///PROCEDEMOS A LEER EL ARCHIVO A COPIAR.
		    

	 	while (!feof(filepointer))
		{
	  	     
		     pedirsem(message.limiteid2);
		     strcpy(buffer2,buffer);
                     devolversem(message.limiteid1);
		     fgets(buffer,sizeof(buffer),filepointer);   
		    		
	 	}
	strcpy(aux,"fin");

	shmdt(buffer2);
	shmdt(aux);
	shmctl(memidauxid, IPC_RMID, 0);
	shmctl(message.memid, IPC_RMID, 0);
	eliminarsem(message.limiteid1);
	eliminarsem(message.limiteid2);
	fclose(filepointer);
	printf("Se copio el archivo\n");
	return 0;


}




		
