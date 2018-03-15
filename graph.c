#include <stdlib.h>
#include "graph.h"
#include "list.h"

/*link* createLink(char* v1, char* v2) { //
	link* new = (link*) malloc(sizeof(link));
	sscanf(v1, "%d", &new->from);
	sscanf(v2, "%d", &new->to);
	return new;
}

int linkOrigin(link *l1) {
	return l1->from;
}

int linkDestination(link *l1) {
	return l1->to;
}

*/

graph graph1;

int createGraph(char** argv ) {
	int i;
	link* linkTemp;

	int N; //num vertex
	int M; //num links
	sscanf(argv[i], "%d", &N);
	sscanf(argv[i+1], "%d", &M);
	
	graph1.nVert = N;

	graph1.v = (vertex*) malloc(sizeof(vertex)*N);

	for (i=0; i<N; i++) {
		graph1.v[i].nTo = 0;
		graph1.v[i].nFrom = 0;
		graph1.v[i].vNum = i+1;
	}

	int fromTemp, toTemp;
	int numFroms[N];
	int numTos[N];
	for (i=0; i<N; i++) {
		numFroms[i]=0;
		numTos[i]=0;
	}

	for (i=2; i<M+2; i+=2) {
		sscanf(argv[i], "%d", &fromTemp);
		sscanf(argv[i+1], "%d", &toTemp);
		numFroms[fromTemp]++;
		numTos[toTemp]++;
	}

	for (i=0; i<N; i++) {
		graph1.v[i].froms = (int*) malloc(numFroms[i]*sizeof(int));
		graph1.v[i].tos = (int*) malloc(numTos[i]*sizeof(int));
	}

	for (i=2; i<M+2; i+=2) {
		sscanf(argv[i], "%d", &fromTemp);
		sscanf(argv[i+1], "%d", &toTemp);

		graph1.v[fromTemp].tos[graph1.v[fromTemp].nTo] = toTemp;
		graph1.v[toTemp].froms[graph1.v[toTemp].nFrom] = fromTemp;
		graph1.v[fromTemp].nTo++;
		graph1.v[toTemp].nFrom++;
	}
	return 0;
}

int getNumAdjs(int vertNum) {
	return graph1.v[vertNum-1].nTo;
}

int* getAdjs(int vertNum) {
	return graph1.v[vertNum-1].tos;
}

void printGraph() {
	int i, j;
	for (i=0; i<graph1.nVert; i++) {
		printf("\n\nVertice %d\n", graph1.v[i].vNum);
		printf("Tos: %d\n", graph1.v[i].nTo);
		printf("Froms: %d\n", graph1.v[i].nFrom);
		printf("Ligacoes:\n");
		printf("Para:\n");
		for (j=0; j<graph1.v[i].nTo; j++)
			printf("%d\n", graph1.v[i].tos[j]);
		for (j=0; j<graph1.v[i].nFrom; j++)
			printf("%d\n", graph1.v[i].froms[j]);
	}

}