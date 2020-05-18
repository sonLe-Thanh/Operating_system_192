#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "ex1.h"

void *simple_malloc(size_t size){
	void *p;
	p=sbrk(0);
	if (sbrk(size)==NULL)
		return NULL;
	return p;
}
int main(){
	int *p1=(int *)aligned_malloc(10,512);
	*p1=12;
	printf("The address is :%p\n", p1);
	printf("The value is: %d\n", *p1);
	aligned_free(p1);
	int *p2=(int *)aligned_malloc(10,512);
	*p2=13;
	
	printf("The address is :%p\n", p2);
	printf("The value is: %d\n", *p2);
	//p=NULL;
	printf("The address is :%p\n", p1);
	printf("The value is: %d\n", *p1);
	aligned_free(p2);
	printf("The address is :%p\n", p2);
	printf("The value is: %d\n", *p2);
}
