.PHONY: clean
FLAGS = -ggdb

PRODUCTOR: PRODUCTOR.o  
	gcc $(FLAGS)	-o	PRODUCTOR	PRODUCTOR.o	 	

PRODUCTOR.o: PRODUCTOR.c semaforos.c 
	gcc $(FLAGS)	-c	PRODUCTOR.c	estructuras.h	 

semaforos.o: semaforos.c
	gcc $(FLAGS)	-c	semaforos.c	semaforos.h


clean:
	rm -f *.o PRODUCTOR 
