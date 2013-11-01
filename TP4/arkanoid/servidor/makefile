.PHONY: clean
FLAGS = -lncurses -lpthread

SERVIDOR: servidor.o libsocket.o pantalla.o cola.o semaforos.o
		gcc $(FLAGS) -o  SERVIDOR servidor.o libsocket.o pantalla.o cola.o semaforos.o

servidor.o: servidor.c libsocket.h semaforos.h
		gcc $(FLAGS) -o servidor.o -c servidor.c

libsocket.o: libsocket.c libsocket.h
	gcc $(FLAGS) -o libsocket.o -c libsocket.c

pantalla.o: pantalla.c pantalla.h cola.h
	gcc -o pantalla.o -c pantalla.c

cola.o: cola.c cola.h
	gcc -o cola.o -c cola.c

semaforos.o: semaforos.c semaforos.h
	gcc -o semaforos.o -c semaforos.c

clean:
	rm -f *.o
