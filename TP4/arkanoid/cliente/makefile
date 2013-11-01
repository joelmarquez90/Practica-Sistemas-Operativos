.PHONY: clean
FLAGS = -lpthread -lncurses

CLIENTE: cliente.o libsocket.o pantalla.o
		gcc -o CLIENTE cliente.o libsocket.o pantalla.o $(FLAGS)

cliente.o: cliente.c libsocket.h
		gcc -o cliente.o -c cliente.c

libsocket.o: libsocket.c libsocket.h
	gcc -o libsocket.o -c libsocket.c

pantalla.o:	pantalla.c	pantalla.h
	gcc -o pantalla.o -c pantalla.c

clean:
	rm -f *.o
