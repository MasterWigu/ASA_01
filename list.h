#ifndef _LIST_
#define _LIST_

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"


typedef struct node { 
	int vNum;
	struct node *next; 
}LLElem;

void push(LLElem** head, int vNum);
int pop(LLElem** head);

#endif