CC=gcc
EJ=Ejercicio6

$(EJ): 		$(EJ).o
				$(CC) -o $(EJ) $(EJ).o

$(EJ).o:	$(EJ).c
				$(CC) -o $(EJ).o -c $(EJ).c

.PHONY: clean
	rm -f *.o 

clean:
	rm -f *.o
