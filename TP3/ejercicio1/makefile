.PHONY: clean
FLAGS = -ggdb

EJ1: main.o semaforos.o
		gcc $(FLAGS) -o EJ1 main.o semaforos.o

main.o: main.c semaforos.h
		gcc $(FLAGS) -o main.o -c main.c

semaforos.o: semaforos.c semaforos.h
		gcc $(FLAGS) -o semaforos.o -c semaforos.c

clean:
		rm -f *.o EJ1

