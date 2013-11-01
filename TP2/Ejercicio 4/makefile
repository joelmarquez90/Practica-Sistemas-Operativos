CC=gcc
EJ=Ejercicio4

$(EJ): 		$(EJ).o
				$(CC) -o $(EJ) $(EJ).o

$(EJ).o:	$(EJ).c libreria.c
				$(CC) -c $(EJ).c

libreria.o: libreria.c libreria.h
	gcc -c libreria.c

.PHONY: clean
	rm -f *.o 

clean:
	rm -f *.o

