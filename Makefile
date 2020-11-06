all: Array.o ArrayLong.o Sentence.o Text.o main.o
	gcc *.o -o cw1

Array.o: Array.h Array.c
	gcc -c Array.c

ArrayLong.o: ArrayLong.h ArrayLong.c
	gcc -c ArrayLong.c

Sentence.o: Sentence.h Sentence.c
	gcc -c Sentence.c

Text.o: Text.h Text.c
	gcc -c Text.c

main.o: main.c Text.h
	gcc -c main.c

clean:
	rm *.o
