#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char  ** argv){
	/* We have to create a process as following tree
				A
			 /	|  \
		    B	C   D
		  /   \   \  
		 E     F   G
				  /
				 H
	The order is alphabetical */

	//The main process is A
	pid_t cPID;
	//Create process B
	pid_t bPID=fork();

	//If we are in main process
	if (bPID>0){
		//Create process C
		cPID=fork();

		//If we are in main process
		if (cPID>0){
			//Create process D
			pid_t dPID=fork();

		}
	}

	//If we are in process B
	else if (bPID==0){
		//Create process E
		pid_t ePID=fork();

		//If we are in process B
		if (ePID>0){
			//Create process F
			pid_t fPID=fork();

		}
	}
	//If we are in process C
	if (cPID==0 && bPID>0){
		sleep(1);
		//Create process G
		pid_t gPID=fork();

		//If we are in process G
		if (gPID==0){
			//Create process H
			pid_t hPID=fork();
		}
	}
	while (1) sleep(1);
}