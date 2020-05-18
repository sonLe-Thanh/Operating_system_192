#ifndef EX1_HEADER
#define EX1_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void * aligned_malloc(unsigned int size, unsigned int align);
void * aligned_free(void * ptr);

//Implement linked list for block management
typedef struct header_t{
	size_t size;
	int is_free;
	struct header_t *next;
}	header_t;

static header_t *head, *tail;
#endif
