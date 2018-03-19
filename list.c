#include <stdlib.h>
#include "list.h"
#include "graph.h"

extern graph graph1;

void push(LLElem **head, int vNum) {
	graph1.v[vNum].inList++;
	LLElem* new = (LLElem*) malloc(sizeof(LLElem)); 
	if (new==NULL)
		printf("Fodeu1\n");
	new->vNum= vNum; 
	new->next = *head; 
	*head = new; 
} 

int pop(LLElem **head) {
	int vNum = (*head)->vNum;
	graph1.v[vNum].inList--;
	LLElem *temp = (*head)->next;
	free(*head);
	*head = temp;
	return vNum;
}
 