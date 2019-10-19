all: main

debug: clear all run

clear:
	rm *.o

run:
	./main

main: stack.o queue.o carro.o main.o
	gcc stack.o queue.o carro.o main.o -o main

main.o:
	gcc -c main.c

stack.o:
	gcc -c stack.c

queue.o:
	gcc -c queue.c

carro.o:
	gcc -c carro.c