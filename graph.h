#ifndef _GRAPH_
#define _GRAPH_

#include "list.h"

/*typedef struct {
	int from;
	int to;
} link;
*/

typedef struct {
	int nTo;
	int nFrom;
	int vNum;
	int* tos;
	int* froms;
} vertex;


typedef struct {
	int nVert;
	vertex* v;
} graph;

int createGraph();
int getNumAdjs(int vertNum);
int* getAdjs(int vertNum);
void printGraph();

#endif