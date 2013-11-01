.PHONY: clean
FLAGS = -ggdb

SERVIDOR: servidor.o
		gcc $(FLAGS) -o  SERVIDOR servidor.o

servidor.o: servidor.c
		gcc $(FLAGS) -o servidor.o -c servidor.c

clean:
	rm -f *.o
