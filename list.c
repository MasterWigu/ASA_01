#include <stdlib.h>
#include "list.h"
#include "graph.h"

extern graph graph1;

int push(LLElem *head, int vNum) {
	graph1.v[vNum-1].inList++;
	LLElem* new = (LLElem*) malloc(sizeof(LLElem)); 
	new->vNum= vNum; 
	new->next = head; 
	return 0; 
} 

int pop(LLElem *head) {
	int vNum = head->vNum;
	graph1.v[vNum-1].inList--;
	LLElem *temp = head->next;
	free(head);
	head = temp;
	return vNum;
}
 