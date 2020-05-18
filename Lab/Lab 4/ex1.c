#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include <pthread.h>

#include "ex1.h"

header_t *get_free_block_first_fit(unsigned int size){
	//Using first fit algorithm to implement this
	header_t *p_curr=head;
	while (p_curr){
		if ((p_curr->is_free == 1) && (p_curr->size >= size)) 
			return p_curr;
		p_curr=p_curr->next;
	}
}

void *allocate_block(unsigned int size, unsigned int align){
	//Allocate aligned block

	void *p_curr, *p_return, *p_move;
	unsigned int currAdd, offset;
	
	//Allocate space for p_return pointer
	if (sbrk(sizeof(p_return)) == (void *)-1)
		return NULL;

	//Get p_curr some space
	p_curr=sbrk(0);
	//Get current address of p_curr
	currAdd=(uintptr_t)p_curr;
	
	//Get offset
	offset=currAdd%align;

	//We use some math here
	//currAdd=k*align+remainder
	//If offset==0, then the current address has already been divisible by align
	//If we got remainder>0 aka offset>0, then by making offset being the reduction of the align by remainder
	//We can terminate the remainder. 
	if (offset>0){
		offset=align-offset;
	}
	//Increase the heap size to align
	if (sbrk(offset) == (void *)-1)
		return NULL;
	
	//Move the pointer to the disired memory block address
	p_move=sbrk(0);
	
	//Also increase the heap size as in normal malloc
	if (sbrk(size) == (void *)-1)
		return NULL;
	//move the p_return for room for the header
	p_return=p_move-sizeof(header_t);	

	return p_return;
	
}
void *aligned_malloc(unsigned int size, unsigned int align){
	void *p_ult, *p_return;
	header_t *header;
	if (size==0) return NULL;
	
	//Find the block satisfied the requirement
	header = get_free_block_first_fit(size);
	if (header){
		//If found  a free and previously satisfield block
		header->is_free=0;	//Used this block
		//+1 to hide the existence of header
		p_return = (void*)(header+1);	
		return p_return;
	}
	//If not found, allocate normally
	p_ult=allocate_block(size,align);
	if (p_ult == NULL) return NULL;
	
	//Store information
	header=p_ult;
	header->size=size;
	header->is_free=0;
	header->next=NULL;
	
	//Update head and tail
	if (!head) head = header;
	if (tail) tail->next = header;
	tail = header;

	p_return =(void *)(header+1);
	return p_return;
}

void *aligned_free(void * ptr){
	if (ptr == NULL)
		return NULL;
	header_t *header, *tmp;
	void *program_break;

	//Get last block info
	header = (header_t *)(ptr-1);
	//Get the current program break
	program_break=sbrk(0);
	//If block to update in the last, srink the block, update information
	if ((char *)ptr+header->size == program_break){
		//If we only have 1 block
		if (head=tail) head=tail=NULL;
		else {
			tmp=head;
			//Find the block point to last block and update it
			while (tmp){
				if (tmp->next == tail) {
					tmp->next = NULL;
					tail=tmp;	
				}
	
				tmp=tmp->next;
			}
		}
		//Release the memory, include the header and actual block
		sbrk(0-sizeof(header_t)- header->size);
		return sbrk(0);
	}
	//If the block is inside, update the status only
	header->is_free=1;
	
	return sbrk(0);
}
