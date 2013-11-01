.PHONY: clean
FLAGS = -ggdb

CLIENTE: cliente.o
		gcc $(FLAGS) -o CLIENTE cliente.o

cliente.o: cliente.c
		gcc $(FLAGS) -o cliente.o -c cliente.c

clean:
	rm -f *.o
