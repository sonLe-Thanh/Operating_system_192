all: ex1.o main.o
	gcc ex1.o main.o -o main
ex1.o: ex1.c
	gcc -c ex1.c
main.o: main.c
	gcc -c main.c
clean:
	rm -f *o main
