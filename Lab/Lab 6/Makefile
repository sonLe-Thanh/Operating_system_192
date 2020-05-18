all: pi_multi-thread
pi_multi-thread: pi_multi-thread.o
	gcc pi_multi-thread.o -o pi_multi-thread
pi_multi-thread.o: pi_multi-thread.c
	gcc -c pi_multi-thread.c
clean: 
	rm -f *.o pi_multi-thread