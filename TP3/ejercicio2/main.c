////////////////////////////////////////
//NOMBRE DEL PROGRAMA: main.c							
//TRABAJO PRACTICO N°3                  
//EJERCICIO 2.	                        
//INTEGRANTES:                         
//Joel Marquez             35.367.125  
//Maria Eugenia Brea       35.272.169  
//Maria Victoria Trimboli  35.723.767  
//Soledad Suarez           35.387.379  
//Marlene Lauria           35.423.458  
//PRIMERA ENTREGA												
////////////////////////////////////////

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include <string.h>
#include "arbol.h"
#include "semaforos.h"

void cargarArchivo(FILE *, t_arbol *);

int main () 
{
	key_t claveMutex, claveInferior, claveSuperior, claveMemoria;
	int IdMemoria, IdMutex, IdInferior, IdSuperior, i;
	pid_t idPadre, IdProceso;
	t_info *buffer, reg;
	t_arbol raiz;
	FILE * fp;
	char ap[20];
	int n;

	claveMemoria = ftok("/", 5000);
	IdMemoria = shmget(claveMemoria, sizeof(t_info) * 3, IPC_CREAT | 0600);
	buffer = (t_info *) shmat(IdMemoria, NULL, 0);
	claveMutex = ftok("/", 6000);
	claveInferior = ftok("/", 6001);
	claveSuperior = ftok("/", 6002);
	IdMutex = obtenerSemaforo(claveMutex, 0);
	IdInferior = obtenerSemaforo(claveInferior, 0);
	IdSuperior = obtenerSemaforo(claveSuperior, 3);
	idPadre = getpid();
	printf("Cantidad de actualizaciones a realizar: ");
	scanf("%d",&n);

	if((IdProceso = fork()) < 0) //Hijo. Productor
	{			
		printf("ERROR creando hijo\n");
		exit(1);
	}
	else if (IdProceso == 0)
	{
		if (!(fp = fopen("empleados.txt","rt")))
		{
			if (!(fp = fopen("empleados.txt", "wt")))
			{
				printf("ERROR creando archivo escritura");
				exit(2);
			}
			close(fp);
		}
		for (i = 0; i < n; i++)
		{			
			printf("\nActualización %d\n", i + 1);
			printf("Ingrese DNI: ");
			scanf("%li", &(reg.dni));
			fflush(stdin);
			printf("Ingrese nombre: ");
			scanf("%s", reg.apynom);
			fflush(stdin);
			printf("Ingrese apellido: ");
			scanf("%s", ap);
			fflush(stdin);
			strcat(reg.apynom, " ");
			strcat(reg.apynom, ap);
			printf("Ingrese empresa: ");
			scanf("%s", reg.empresa);
	      fflush(stdin);
			printf("Ingrese sueldo: ");
			scanf("%f", &(reg.sueldo));
			fflush(stdin);
			printf("Ingrese antiguedad en meses: ");
			scanf("%d", &(reg.antiguedad));
			fflush(stdin);	
			printf("Posee o no tarjeta: ");
			scanf("%s", reg.posee_tarjeta);
			fflush(stdin);
			printf("Ingrese telefono: ");
			scanf("%li", &(reg.tel)) ;
			fflush(stdin);

			pedirSemaforo(IdSuperior);
			pedirSemaforo(IdMutex);
			buffer->dni = reg.dni;
			strcpy(buffer->empresa, reg.empresa);
			strcpy(buffer->apynom, reg.apynom);
			strcpy(buffer->posee_tarjeta, reg.posee_tarjeta);
			buffer->sueldo = reg.sueldo;
			buffer->antiguedad = reg.antiguedad;
			buffer->tel = reg.tel;
			devolverSemaforo(IdMutex);
			devolverSemaforo(IdInferior);
		}
	}
	else // Padre. Consumidor
	{
		crearArbol(&raiz);
		if (fp = fopen("empleados.txt","rt"))
			cargarArchivo(fp, &raiz);			
		devolverSemaforo(IdMutex);
		for(i = 0; i < n; i++)
		{
			pedirSemaforo(IdInferior);
			pedirSemaforo(IdMutex);
			strcpy(reg.empresa, buffer->empresa);
			strcpy(reg.apynom, buffer->apynom);
			strcpy(reg.posee_tarjeta, buffer->posee_tarjeta);
			reg.dni = buffer->dni;
			reg.sueldo = buffer->sueldo;
			reg.antiguedad = buffer->antiguedad;
			reg.tel = buffer->tel;
			devolverSemaforo(IdMutex);
			devolverSemaforo(IdSuperior);
			if (!cargarenArbol(&raiz, &reg))
			{
				printf("ERROR al cargar en arbol");
				exit(1);
			}
		}		
		if (!(fp = fopen("empleados.txt", "wt")))
		{
			printf("ERROR creando archivo escritura");
			exit(2);
		}
		grabarpreArbol (&raiz, fp);			
		eliminarArbol(&raiz);
		fclose(fp);
		shmdt(buffer);
		shmctl(IdMemoria, IPC_RMID, 0);
		eliminarSemaforo(IdInferior);
		eliminarSemaforo(IdSuperior);
		eliminarSemaforo(IdMutex);
		wait(NULL);
	}
	return 0;
}

void cargarArchivo(FILE *fp, t_arbol *raiz)
{
	char linea[500], *aux;
	t_info reg;
	while (fgets (linea, sizeof (linea), fp))
	{
		aux = strchr (linea, '\n');
		if (!aux)
		{
			fcloseall ();
			exit (2);
		}
		*aux='\0';
		aux=strrchr (linea, ':');
		sscanf (aux, ":%ld", &reg.tel);
		*aux='\0';
		aux=strrchr (linea, ':');
		strcpy (reg.posee_tarjeta, aux+1);
		*aux='\0';
		aux=strrchr (linea, ':');
		sscanf (aux, ":%d", &reg.antiguedad);
		*aux='\0';
		aux=strrchr (linea, ':');
		sscanf (aux, ":%f", &reg.sueldo);
		*aux='\0';
		aux=strrchr (linea, ':');
		sscanf (aux, ":%ld", &reg.dni);
		*aux='\0';
		aux=strrchr (linea, ':');
		strcpy (reg.apynom, aux+1);
		*aux='\0';
		strcpy (reg.empresa, linea);
		if (!cargarenArbol(raiz, &reg))
		{
			printf("ERROR al cargar en arbol");
			exit(1);
		}
	}
	close(fp);
}
