.PHONY: clean
FLAGS = -ggdb
EJ=EJ4

$(EJ): main.o
		gcc $(FLAGS) -o $(EJ) main.o -lpthread

main.o: main.c
		gcc $(FLAGS) -o main.o -c main.c -lpthread

clean:
		rm -f *.o $(EJ)

