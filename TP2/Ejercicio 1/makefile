CC=gcc
EJ1=Ejercicio1

$(EJ1): 		$(EJ1).o
				$(CC) -o $(EJ1) $(EJ1).o

$(EJ1).o:	$(EJ1).c
				$(CC) -o $(EJ1).o -c $(EJ1).c

.PHONY: clean
	rm -f *.o 

clean:
	rm -f *.o
