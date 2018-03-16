#include <stdlib.h>
#include "list.h"
#include "graph.h"

extern graph graph1;
LLElem* L;

void push(int vNum) {
	graph1.v[vNum].inList++;
	LLElem* new = (LLElem*) malloc(sizeof(LLElem)); 
	new->vNum= vNum; 
	new->next = L; 
	L = new; 
} 

int pop() {
	int vNum = L->vNum;
	graph1.v[vNum].inList--;
	LLElem *temp = L->next;
	free(L);
	L = temp;
	return vNum;
}
 