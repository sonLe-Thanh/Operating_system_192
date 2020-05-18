all: findsubstr.o readline.o main.o
	gcc findsubstr.o readline.o main.o -o mygrep
findsubstr.o: findsubstr.c  findsubstr.h
	gcc -c findsubstr.c
readline.o: readline.c readline.h
	gcc -c readline.c
main.o: readline.h findsubstr.h main.c
	gcc -c main.c
clean:
	rm  -f *.o mygrep
