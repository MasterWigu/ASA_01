#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "list.h"
#include <math.h>

#define inf -1

extern graph graph1;
int numComp;
LLElem* SCC;
LLElem* L;
int *aux; 

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

void merge(int *a, int l, int m, int r) {  
	int i, j, k; 
	for (i = m+1; i > l; i--)  
    	aux[i-1] = a[i-1]; 
	for (j = m; j < r; j++) 
    	aux[r+m-j] = a[j+1]; 
  	for (k = l; k <= r; k++) 
    	if (min(aux[j], aux[i])) 
      		a[k] = aux[j--]; 
    	else 
      		a[k] = aux[i++]; 
}

void mergesort(int *a, int l, int r) {  
	int m = (r+l)/2;
	if (r <= l) 
		return; 
	mergesort(a, l, m); 
	mergesort(a, m+1, r); 
	merge(a, l, m, r); 
}

void tarjan() {
	int i;
	for (i=0; i<getNumVer(); i++)//each vertex u ∈ V[G]
		graph1.v[i].d = inf;      //∞ = -1 para simplificar
	for (i=0; i<getNumVer(); i++)//each vertex u ∈ V[G]
		if (graph1.v[i].d == inf)
			visit(i);
}



void visit(int u) {
	static int visited = 0;
	int i, v, smallest;
	graph1.v[u].d = visited;
	graph1.v[u].low = visited;

	visited++;

	push(&L, u, 1);
	//printf("AAAA %d\n", visited);
	for (i=0; i<getNumAdjs(u); i++) {//each v ∈ Adj[u]
		if (graph1.v[getAdjs(u)[i]].d == inf || graph1.v[getAdjs(u)[i]].inList > 0) {//(d[v] = ∞ || v ∈ L)
			// Ignora vértices de SCCs já identificados
			if (graph1.v[getAdjs(u)[i]].d == inf) {
				visit(getAdjs(u)[i]);
			}
			graph1.v[u].low = min(graph1.v[u].low, graph1.v[getAdjs(u)[i]].low);
		}
	}
	if (graph1.v[u].d == graph1.v[u].low) { //d[u] = low[u] Raiz do SCC
		//graph1.v[u].root = u;
		smallest = u;
		graph1.v[u].numSCC = numComp;
		do {
			v = pop(&L, 1);
			if (v < smallest)
				smallest = v;
			graph1.v[v].numSCC = numComp;
			//graph1.v[v].root = u;
			//printf("%d\n", v+1);
			//Vértices retirados definem SCC
		} while(v != u); //until u = v
		push(&SCC, smallest, 0);
		numComp++;
	}
}

void printAdjComp(int* adj) {
	int N = adj[1];
	int i;
	int in=0;
	int numLigComp = 0;

	printf("%d\n", numComp);

	int comps[numComp];
	for (i=numComp-1; i>=0; i--) {
		comps[i] = pop(&SCC, 0);
		//printf("AA %d\n", comps[i]);
	}

	//ordenar adj
	aux = (int*) malloc((N+2)*sizeof(int));
	//mergesort(adj, 2, 2*N+2);

	for (i=2; i<(2*N)+2; i+=2) {
		if (graph1.v[adj[i]-1].low != graph1.v[adj[i+1]-1].low)
			numLigComp++;
	}

	int comps2[2*numLigComp];
	for (i=2; i<(2*N)+2; i+=2) {
		if (graph1.v[adj[i]-1].low != graph1.v[adj[i+1]-1].low) {
			if (in==0 || 
				comps2[in-2] != comps[graph1.v[adj[i]-1].numSCC]+1 || 
				comps2[in-1] != comps[graph1.v[adj[i+1]-1].numSCC]+1) {
				//printf("A I=%d  IN=%d  ADJ=%d  ADJ2=%d\n", i, in, adj[i], adj[i+1]);

				comps2[in] = comps[graph1.v[adj[i]-1].numSCC]+1;
				comps2[in+1] = comps[graph1.v[adj[i+1]-1].numSCC]+1;
				//printf("B I=%d  IN=%d  ADJ=%d  ADJ2=%d\n", i, in, adj[i], adj[i+1]);
				in+=2;
			}
		}
	}


	printf("%d\n", in/2);
	for (i=0; i<in; i+=2)
		printf("%d %d\n", comps2[i], comps2[i+1]);

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

	for (i=2; i<(2*N)+2; i+=2) {
		scanf("%d %d", &res[i], &res[i+1]);
	}
	return res; 
}

int main(int argc, char** argv) {
	int* nums;
	numComp = 0;
	nums = lerFich();
	createGraph(nums);

	tarjan();
	printAdjComp(nums);
	//printGraph();
	return 0;
}
