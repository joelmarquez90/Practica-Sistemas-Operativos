CC=gcc
EJ2=Ejercicio2

$(EJ2): 		$(EJ2).o
				$(CC) -o $(EJ2) $(EJ2).o

$(EJ2).o:	$(EJ2).c
				$(CC) -o $(EJ2).o -c $(EJ2).c

.PHONY: clean
	rm -f *.o 

clean:
	rm -f *.o
