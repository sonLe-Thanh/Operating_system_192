#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char ** argv){
	//Read input from file
	FILE *fFile;
	//char * fileName="number.txt";
	int arr[10000];
	int counter=0;
	char *temp;

	fFile=fopen("number.txt","r");
	if (fFile==NULL){
		printf("File is not avaiable in this directory\n");
		return -1;
	}
	else {
		while (fscanf(fFile, "%d\n", &arr[counter++])>0){
			//
		}
	}

	//Adjust the counter variable after read all the lines
	counter--;

	int numDivide3=0;
	int numDivide7=0;
	int numDivide11=0;

	//main is the parents process
	//it will count the numbers divisible by 3

	//Create the first process
	pid_t parentsPID=fork();

	if (parentsPID==0){
		//This is the first child
		//it will count the numbers divisible by 7
		for (int i=0; i<counter; i++){
			if (arr[i]%7==0){
				numDivide7++;
			}
		}
		printf("%d\n", numDivide7);
		//while (1) sleep(1);
	}
	else if (parentsPID>0){
		//This is the main process
		//Create one more process
		pid_t childPID=fork();
		if (childPID==0){
			//This is the second child
			//it will count the numbers divisible by 11
			for (int i=0; i<counter; i++){
				if (arr[i]%11==0){
					numDivide11++;
				}
			}
			printf("%d\n", numDivide11);
			//while (1) sleep(1);
		}
		else if (childPID>0){
			//This is the main process
			for (int i=0; i<counter;i++){
				if (arr[i]%3==0){
					numDivide3++;
				}
			}
			printf("%d\n", numDivide3);
			//while (1) sleep(1);
		}
		else{
			return 0;
		}
	}
	else {
		return 0;
	}

	fclose(fFile);

	return 0;
}