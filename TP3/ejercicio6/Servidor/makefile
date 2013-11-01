.PHONY: clean
FLAGS = -ggdb


servidor: servidor.o

cliente.o: servidor.c
	gcc $(FLAGS)	-c	servidor.c

clean:
	rm -f *.o servidor
