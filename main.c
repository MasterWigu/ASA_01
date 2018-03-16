#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "list.h"
#include <math.h>
#include <unistd.h>

//#define min(a, b) a<b ? a: b
#define inf -1

extern graph graph1;
int visited;

void visit(int u);

int min(int a, int b) {
	if (a==inf)
		return b;
	if (b==inf)
		return a;
	if (a<b)
		return a;
	return b;
}

void tarjan() {
	visited = 0;
	int i;
	for (i=0; i<getNumVer(); i++)//each vertex u ∈ V[G]
		graph1.v[i].d = inf;      //∞ = -1 para simplificar
	for (i=0; i<getNumVer(); i++)//each vertex u ∈ V[G]
		if (graph1.v[i].d == inf)
			visit(i);
}



void visit(int u) {
	int i, v;
	graph1.v[u].d = visited;
	graph1.v[u].low = visited;

	visited++;

	push(u);
	for (i=0; i<getNumVer(); i++)//each v ∈ Adj[u]
		if (graph1.v[i].d == inf || graph1.v[i].inList > 0) //(d[v] = ∞ || v ∈ L)
			// Ignora vértices de SCCs já identificados
			if (graph1.v[i].d == inf) {
				visit(i);
				graph1.v[u].low = min(graph1.v[u].low, graph1.v[i].low);
			}
	if (graph1.v[u].d == graph1.v[u].low) //d[u] = low[u] ✄ Raiz do SCC
		printf("CCCC\n");
		do { //then repeat
			v = pop();
			printf("%d\n", v);
			//✄ Vértices retirados definem SCC
		} while(v != u); //until u = v
}


int* lerFich() {
	int M;
	int N;
	int i;
	int *res;
	scanf("%d", &M);
	scanf("%d", &N);
	res = (int*) malloc((2+(2*N))*sizeof(int)); 
	res[0] = M;
	res[1] = N;

	int cont = 2;
	for (i=2; i<(2*N)+2; i+=2) {
		scanf("%d %d", &res[i], &res[i+1]);
	}
	return res; 
}

int main(int argc, char** argv) {
	int* nums;
	int i;
	nums = lerFich();
	createGraph(nums);

	printf("COMECA\n");
	tarjan();

	//printGraph();
	return 0;
}
