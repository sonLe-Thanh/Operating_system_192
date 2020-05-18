#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define NUM_THREADS 100
long countRes=0;
long numPointThread;
//Mutex lock
pthread_mutex_t var1 = PTHREAD_MUTEX_INITIALIZER;

void *calculatePi_thread(){
	double randX, randY;
	long countResThread=0;
	long i;
	unsigned int rand_t=rand();

	for (i=0;i<numPointThread;i++){
		//Using rand_r() for generating threadsafe pseudo-random number
		randX=rand_r(&rand_t)/(double)RAND_MAX*2.0-1.0;
		randY=rand_r(&rand_t)/(double)RAND_MAX*2.0-1.0;
		if (randX*randX+randY*randY<1)
		{
			countResThread++;
		}
	}
	//Lock set, no other thread can access countRes after this
	pthread_mutex_lock(&var1);
	countRes+=countResThread;
	pthread_mutex_unlock(&var1);
	return NULL;
}

int main(int argc, char * argv[]){

	

	time_t begin=time(NULL);

	pthread_t threads[NUM_THREADS];
	int rc,t;
	long totalPoint=atol(argv[1]);
	
	numPointThread=totalPoint/NUM_THREADS;
	
	
	for (t=0;t<NUM_THREADS;t++){
		
		int rc=pthread_create(&threads[t], NULL, calculatePi_thread, NULL);
		
		if (rc){
			printf("Error while creating thread!\n");
			exit(-1);
		}
		//
	}

	for (t=0;t<NUM_THREADS;t++){
		pthread_join(threads[t],NULL);
	}
	pthread_mutex_destroy(&var1);
	
	
	double piEst=4.0*(double)countRes/((double)numPointThread*NUM_THREADS);
	printf("Estimated the value of pi: %0.9f\n", piEst);
	time_t end = time(NULL);
	printf("The execution time is: %ld seconds\n", end-begin);

	pthread_exit(0);
}