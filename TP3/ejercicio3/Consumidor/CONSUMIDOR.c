///////////////////CONSUMIDOR

#include<string.h>
#include<stdio.h>
#include "estructuras.h"
#include "semaforos.c"
#define TAMBUF 1000


int main() {
t_mensaje message1;
FILE* filepointer2;
char *buffer3;
char buffer4[TAMBUF];
int memidauxid,i=0;
key_t memidauxkey;
char *aux1;

memidauxkey=ftok("/home",6004);
message1.keylimite1=ftok("/",6008);      ///// SEMAFORO
message1.keylimite2=ftok("/",6009);
message1.keymem=ftok("/home",6006);      ///// MEMORIA COMPARTIDA
	

message1.memid=shmget(message1.keymem,4096,IPC_CREAT  | 0660);

if(message1.memid==-1)
{
	printf("Error . Se suspende el programa .. \n");
}

message1.limiteid1=obtenersemaforo(message1.keylimite1,0);
message1.limiteid2=obtenersemaforo(message1.keylimite2,1);

buffer3 =(char*)shmat(message1.memid,NULL,0);	

        filepointer2=fopen("copia.txt","w+t");
	if(!filepointer2)
	{ printf("TODO MAL\n");
        shmctl(message1.memid, IPC_RMID, 0);
        eliminarsem(message1.limiteid1);
        eliminarsem(message1.limiteid2);
	exit(1);}

	
	memidauxid=shmget(memidauxkey,1024,IPC_CREAT | 0777 );
	aux1=(char*)shmat(memidauxid,NULL,0);

	if(memidauxid == -1)
	{
	printf("Se suspende el programa\n");
        shmctl(message1.memid, IPC_RMID, 0);
        eliminarsem(message1.limiteid1);
        eliminarsem(message1.limiteid2);	
	exit(1);
	}
	strcpy(aux1,"nofin");

	while(!strcmp(aux1,"nofin")){
	pedirsem(message1.limiteid1);
	strcpy(buffer4,buffer3);
	fprintf(filepointer2,"%s",buffer4);
        devolversem(message1.limiteid2);

}
	
 	
	fclose(filepointer2);	
	shmctl(message1.memid, IPC_RMID, 0);
        eliminarsem(message1.limiteid1);
        eliminarsem(message1.limiteid2);
	shmctl(memidauxid, IPC_RMID,0);
	printf("El archivo se copio de forma satisfactoria\n");
	exit(0);
}
