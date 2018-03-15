#ifndef _LIST_
#define _LIST_

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

typedef struct node { 
	void *elem; 
	struct node *next; 
} *LLElem;

int push(LLElem head, void* elem);
void* pop(LLElem head);

#endif