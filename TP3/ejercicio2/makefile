.PHONY: clean
FLAGS = -ggdb

EJ2: main.o semaforos.o arbol.o
		gcc $(FLAGS) -o EJ2 main.o semaforos.o arbol.o

main.o: main.c semaforos.h arbol.h
		gcc $(FLAGS) -o main.o -c main.c

semaforos.o: semaforos.c semaforos.h
		gcc $(FLAGS) -o semaforos.o -c semaforos.c

arbol.o: arbol.c arbol.h
		gcc $(FLAGS) -o arbol.o -c arbol.c

clean:
		rm -f *.o EJ2

