#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define NUM_THREADS 50

struct ThreadInfo{
	long countInThread;
} ThreadInfo;

long numPointThread;

void *calculatePi_thread(void * param){
	double randX, randY;
	struct ThreadInfo *info=(struct ThreadInfo*) param;
	long i;
	unsigned int randNum=rand();

	for (i=0;i<numPointThread;i++){
		//Using rand_r() for generating threadsafe pseudo-random number
		randX=rand_r(&randNum)/(double)RAND_MAX*2.0-1.0;
		randY=rand_r(&randNum)/(double)RAND_MAX*2.0-1.0;
		if (randX*randX+randY*randY<1)
		{
			info->countInThread++;
		}
	}
	
	pthread_exit(NULL);
}

int main(int argc, char * argv[]){

	time_t begin=time(NULL);

	pthread_t threads[NUM_THREADS];
	int rc,t;
	struct ThreadInfo infoList[NUM_THREADS];

	long totalPoint=atol(argv[1]);
	
	if (totalPoint<0) return 0;

	numPointThread=totalPoint/NUM_THREADS;
	
	
	for (t=0;t<NUM_THREADS;t++){
		infoList[t].countInThread=0;
		int rc=pthread_create(&threads[t], NULL, calculatePi_thread, &infoList[t]);
		
		if (rc){
			printf("Error while creating thread!\n");
			exit(-1);
		}
		//
	}
	//Wait for all thread to complete
	for (t=0;t<NUM_THREADS;t++){
		pthread_join(threads[t],NULL);
	}
	
	long count=0;
	for (t = 0; t < NUM_THREADS; t++)
	{
		count+=infoList[t].countInThread;
	}
	
	
	double piEst=4.0*(double)count/((double)numPointThread*NUM_THREADS);
	printf("Estimated the value of pi: %0.9f\n", piEst);
	time_t end = time(NULL);
	printf("The execution time is: %ld seconds\n", end-begin);

	pthread_exit(0);
}