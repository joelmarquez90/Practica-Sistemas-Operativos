.PHONY: clean
FLAGS = -ggdb

CONSUMIDOR: CONSUMIDOR.o  
	gcc $(FLAGS)	-o	CONSUMIDOR	CONSUMIDOR.o	 	

PRODUCTOR.o: CONSUMIDOR.c semaforos.c 
	gcc $(FLAGS)	-c	CONSUMIDOR.c	estructuras.h	 

semaforos.o: semaforos.c
	gcc $(FLAGS)	-c	semaforos.c	semaforos.h


clean:
	rm -f *.o CONSUMIDOR
