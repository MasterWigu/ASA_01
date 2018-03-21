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
int *comps2;

void visit(int u);

int adjMenor(int i, int j) {
	if (comps2[2*i] < comps2[2*j])
		return 1;
	if (comps2[2*i] > comps2[2*j])
		return 0;
	if (comps2[2*i+1] <= comps2[2*j+1])
		return 1;
	return 0;
}

int min(int a, int b) {
	if (a==inf)
		return b;
	if (b==inf)
		return a;
	if (a<b)
		return a;
	return b;
}


// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
//VEIO DE https://www.geeksforgeeks.org/merge-sort/
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (adjMenor(L[i], R[j])) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
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
/*
	printf("\n");
	for (i=0; i<N; i++)
		printf("%d ", ind[i]);
	printf("\n");
*/
	/*
	for (i=0; i<N; i++) {
		if (graph1.v[adj[2*ind[i]]-1].low != graph1.v[adj[2*ind[i]+1]-1].low)
			numLigComp++;
	}*/
 	for (i=2; i<(2*N)+2; i+=2) {
    	if (graph1.v[adj[i]-1].low != graph1.v[adj[i+1]-1].low)
      		numLigComp++;
  	}

	comps2 = (int*) malloc((2*numLigComp)*sizeof(int));
	/*
	for (i=0; i<N; i++) {
		if (graph1.v[adj[2*ind[i]]-1].low != graph1.v[adj[2*ind[i]+1]-1].low) {
			if (in==0 || 
				comps2[in-2] != comps[graph1.v[adj[2*ind[i]]-1].numSCC]+1 || 
				comps2[in-1] != comps[graph1.v[adj[2*ind[i]+1]-1].numSCC]+1) {
				//printf("A I=%d  IN=%d  ADJ=%d  ADJ2=%d\n", i, in, adj[i], adj[i+1]);

				comps2[in] = comps[graph1.v[adj[2*ind[i]]-1].numSCC]+1;
				comps2[in+1] = comps[graph1.v[adj[2*ind[i]+1]-1].numSCC]+1;
				//printf("B I=%d  IN=%d  ADJ=%d  ADJ2=%d\n", i, in, adj[i], adj[i+1]);
				in+=2;
			}
		}
	}*/
	for (i=2; i<(2*N)+2; i+=2) {
		if (graph1.v[adj[i]-1].low != graph1.v[adj[i+1]-1].low) { 
    		if (in==0 ||  
        		comps2[in-2] != comps[graph1.v[adj[i]-1].numSCC]+1 ||  
        		comps2[in-1] != comps[graph1.v[adj[i+1]-1].numSCC]+1) { 
 
	        	comps2[in] = comps[graph1.v[adj[i]-1].numSCC]+1; 
    	    	comps2[in+1] = comps[graph1.v[adj[i+1]-1].numSCC]+1; 
    	    	in+=2;
      		} 
    	} 
	}

	int ind[in/2];
	for (i=0; i<in/2; i++)
		ind[i]=i;


	mergeSort(ind, 0, (in/2)-1);

	int comps3[in];
	int in2 = 0;

/*
	for (i=0; i<in/2; i++)
		printf("B=%d\n", ind[i]);
	for(i=0; i<in; i+=2)
		printf("AAA %d %d\n", comps2[i], comps2[i+1]);
*/
	for (i=0; i<in/2; i++) {
    	if (i==0 || comps3[in2-2] != comps2[2*ind[i]]
    		  || comps3[in2-1] != comps2[2*ind[i]+1] ) {


    		comps3[in2] = comps2[2*ind[i]];
    		comps3[in2+1] = comps2[2*ind[i]+1];
    		//printf("A= %d\n",comps2[2*ind[i]]);
    		//printf("A= %d\n",comps2[2*ind[i]]+1);
    		in2+=2;
    	} 
	}

	printf("%d\n", in2/2);
	for (i=0; i<in2; i+=2)
		printf("%d %d\n", comps3[i], comps3[i+1]);

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
	int* adj;
	numComp = 0;
	adj = lerFich();
	createGraph(adj);

	tarjan();
	printAdjComp(adj);
	//printGraph();
	return 0;
}
