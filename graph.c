#include <stdlib.h>
#include "graph.h"
#include "list.h"

graph graph1;

int createGraph(int* in) {
	int i;
	int N = in[0]; //num vertex
	int M = in[1]; //num links

	graph1.nVert = N;

	graph1.v = (vertex*) malloc(sizeof(vertex)*N);

	for (i=0; i<N; i++) {
		graph1.v[i].nTo = 0;
		graph1.v[i].nFrom = 0;
		graph1.v[i].vNum = i+1; //começamos no vertice 1
		graph1.v[i].inList = 0;
	}

	int fromTemp, toTemp;
	int numFroms[N]; 
	int numTos[N];

	for (i=0; i<N; i++) {
		numFroms[i]=0;
		numTos[i]=0;
	}

	for (i=2; i<2*M+2; i+=2) {
		numFroms[in[i+1]]++;  //No vetor in , em cada ligação ele incrementa o "to" da posição i e o "from" da posicao i+1 (ex: 1,4)
		numTos[in[i]]++;
	}

	for (i=0; i<N; i++) {
		graph1.v[i].froms = (int*) malloc(numFroms[i]*sizeof(int));
		graph1.v[i].tos = (int*) malloc(numTos[i]*sizeof(int));
	}

	for (i=2; i<2*M+2; i+=2) {
		fromTemp = in[i];
		toTemp = in[i+1];

		graph1.v[fromTemp-1].tos[graph1.v[fromTemp-1].nTo++] = toTemp; //vamos preenchendo as ligaçoes, sendo que os nTo e nFrom servem como referência para termos o índice certo
		graph1.v[toTemp-1].froms[graph1.v[toTemp-1].nFrom++] = fromTemp;
	}
	return 0;
}

int getNumAdjs(int vertNum) {
	return graph1.v[vertNum-1].nTo;
}

int* getAdjs(int vertNum) { //retorna a lista de vértices acessiveis a partir desse
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
		printf("De:\n");
		for (j=0; j<graph1.v[i].nFrom; j++)
			printf("%d\n", graph1.v[i].froms[j]);
	}
}

int getNumVer() {
	return graph1.nVert;
}
