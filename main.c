#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "list.h"

/*pseudo-codigo do Tarjan - passar para C*/

/*s
void tarjan(graph G) {
	int visited = 0;
	visited = 0
	L = 0/
	for each vertex u ∈ V[G]
	do d[u] = ∞
	for each vertex u ∈ V[G]
	do if d[u] = ∞
	then Tarjan_Visit(u)}

*/

/*
Tarjan_Visit(u)
	d[u] = low[u] = visited
	visited = visited + 1
	Push(L, u);
	for each v ∈ Adj[u]
	do if (d[v] = ∞ || v ∈ L)
6 ✄ Ignora vértices de SCCs já identificados
	then if d[v] = ∞
	then Tarjan_Visit(v)
	low[u] = min(low[u], low[v])
	if d[u] = low[u] ✄ Raiz do SCC
	then repeat
	v = Pop(L)
	✄ Vértices retirados definem SCC
	until u = v
*/

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
	printf("Entrou\n");
	int* nums;
	int i;
	nums = lerFich();
	createGraph(nums);
	
	printGraph();
	printf("\n\nSaiu\n");
	return 0;
}
