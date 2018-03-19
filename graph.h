#ifndef _GRAPH_
#define _GRAPH_

#include "list.h"

typedef struct {
	//int vNum;
	int d;
	int low;
	int nTo;
	int nFrom;
	int inList; //1 se estiver no stack, 0 se nao
	int* tos;
	int* froms;
} vertex;


typedef struct {
	int nVert;
	vertex* v;
} graph;

int createGraph();
int getNumAdjs(int vertNum);
int getNumVer();
int* getAdjs(int vertNum);
void printGraph();

#endif