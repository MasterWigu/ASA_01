#include <stdlib.h>
#include "list.h"
#include "graph.h"
#include "list.h"

int push(LLElem head, void* elem) {
	LLElem new = (LLElem) malloc(sizeof(struct node)); 
	new->elem = elem; 
	new->next = head; 
	return 0; 
} 

void* pop(LLElem head) {
	void* elem = head->elem;
	LLElem temp = head->next;
	free(head);
	head = temp;
	return elem;
}
 /*
void freeList() {
	return;
}
*/