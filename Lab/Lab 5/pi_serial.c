#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double calculatePi(long long numPoint){
	//double sum=0.0;
	double randX, randY, piEst;
	long long i, count;
	for (i=0;i<numPoint;i++){
		randX=rand()/(double)RAND_MAX*2.0-1.0;
		randY=rand()/(double)RAND_MAX*2.0-1.0;
		if (randX*randX+randY*randY<=1)
		{
			count++;
		}
	}
	piEst=4.0*count/numPoint;
	return piEst;
}

int main(int argc, char ** argv){
	time_t begin=time(NULL);
	double piEst=calculatePi(atoi(argv[1]));
	printf("Estimated the value of pi: %0.9f\n", piEst);
	time_t end = time(NULL);
	printf("The execution time is: %ld seconds\n", end-begin);
}