CC=gcc
EJ=Ejercicio3

$(EJ): 		$(EJ).o
				$(CC) -o $(EJ) $(EJ).o

$(EJ).o:	$(EJ).c cola.c
				$(CC) -c $(EJ).c

cola.o: cola.c cola.h
			$(CC) -c cola.c

.PHONY: clean
	rm -f *.o 

clean:
	rm -f *.o

