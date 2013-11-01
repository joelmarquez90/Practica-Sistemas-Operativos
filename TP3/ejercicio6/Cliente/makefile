.PHONY: clean
FLAGS = -ggdb


cliente: cliente.o -lpthread

cliente.o: cliente.c
	gcc $(FLAGS)	-c	cliente.c 

clean:
	rm -f *.o cliente
