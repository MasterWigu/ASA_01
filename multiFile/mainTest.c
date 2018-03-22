#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define inf -1

#define min(a,b) (( (a)<(b) ) ? (a) : (b))



/*list*/

typedef struct node { 
	int vNum;
	struct node *next; 
}LLElem;

/*graph*/

typedef struct {
	int d;
	int numSCC;
	int low;
	int nAdjs;
	int inList; /*1 se estiver no stack, 0 se nao*/
	int* adjs;
} vertex;


typedef struct {
	int nVert;
	vertex* v;
} graph;

graph graph1;

int numComp;
LLElem* SCC;
LLElem* L;

int *comps2;
int curr_index = 0;

int cont = 0;

/*list functions*/

void push(LLElem **head, int vNum, int L) {
	if(L) graph1.v[vNum].inList++;
	LLElem* new = (LLElem*) malloc(sizeof(LLElem)); 
	if (new==NULL) {
		printf("Erro malloc pilha\n");
		exit(1);
	}
	new->vNum= vNum; 
	new->next = *head; 
	*head = new; 
} 

int pop(LLElem **head, int L) {
	if (*head==NULL) return -1;
	int vNum = (*head)->vNum;
	if(L) graph1.v[vNum].inList--;
	LLElem *temp = (*head)->next;
	//free(*head);
	*head = temp;
	return vNum;
}


int adjMenor(int i, int j) { 
  if (comps2[2*i] < comps2[2*j]) 
    return 1; 
  if (comps2[2*i] > comps2[2*j]) 
    return 0; 
  if (comps2[2*i+1] <= comps2[2*j+1]) 
    return 1; 
  return 0; 
} 


/*graph functions*/

int createGraph(int* in) {
	int i;
	int N = in[0]; /*num vertex*/
	int M = in[1]; /*num links*/

	graph1.nVert = N;

	graph1.v = (vertex*) malloc(sizeof(vertex)*N);

	for (i=0; i<N; i++) {
		graph1.v[i].nAdjs = 0;
		graph1.v[i].inList = 0;
	}

	int fromTemp, toTemp;
	int numAdjs[N]; 

	for (i=0; i<N; i++) {
		numAdjs[i]=0;
	}

	for (i=2; i<2*M+2; i+=2) {
		numAdjs[in[i+1]]++;  /*No vetor in , em cada ligacao ele incrementa o "to" da posicao i e o "from" da posicao i+1 (ex: 1,4)*/
		numAdjs[in[i]]++;
	}

	for (i=0; i<N; i++) {
		graph1.v[i].adjs = (int*) malloc(numAdjs[i]*sizeof(int));
	}

	for (i=2; i<2*M+2; i+=2) {
		fromTemp = in[i];
		toTemp = in[i+1];

		graph1.v[fromTemp-1].adjs[graph1.v[fromTemp-1].nAdjs++] = toTemp; /*vamos preenchendo as ligacoes, sendo que os nTo e nFrom servem como referencia para termos o indice certo*/
		graph1.v[toTemp-1].adjs[graph1.v[toTemp-1].nAdjs++] = -fromTemp;
	}
	return 0;
}


int getNumAdjs(int vertNum) {
	return graph1.v[vertNum].nAdjs;
}

int* getAdjs(int vertNum) { /*retorna a lista de vertices acessiveis a partir desse*/
	return graph1.v[vertNum].adjs;
}

int getNumVer() {
	return graph1.nVert;
}


void merge(int arr[], int l, int m, int r) {
/*VEIO DE https://www.geeksforgeeks.org/merge-sort/*/
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
 
    i = 0; 
    j = 0;
    k = l;
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

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}



void scc(int v) {
    int i, c, n;
    graph1.v[v].d = curr_index;
    graph1.v[v].low = curr_index;
    ++curr_index;

    push(&L, v, 1);

    for (i = 0, c = getNumAdjs(v); i < c; ++i)
		if (getAdjs(v)[i] > 0) {
	    	n = getAdjs(v)[i] - 1;
	    	if (graph1.v[n].d == -1) {
				scc(n);
				graph1.v[v].low = min(graph1.v[v].low, graph1.v[n].low);
	    	} else if (graph1.v[n].inList) {
				graph1.v[v].low = min(graph1.v[v].low, graph1.v[n].d);
	    	}
		}
    
    if (graph1.v[v].d == graph1.v[v].low) {
		//printf("scc: ");
		cont++;
		while ((n = pop(&L, 1)) != -1) {
    		//printf("%d ", n + 1);
	    	if (n == v) {
				//printf("\n");
				break;
	    	}
		}
   	}
}



//void visit(int u) {
//	static int visited = 0;
//	int i, v, smallest;
//	graph1.v[u].d = visited;
//	graph1.v[u].low = visited;
//
//	visited++;
//
//	push(&L, u, 1);
//	for (i=0; i<getNumAdjs(u); i++) { /*each v in Adj[u]*/
//		if (graph1.v[getAdjs(u)[i]].d == inf || graph1.v[getAdjs(u)[i]].inList > 0) {/*(d[v] = inf || v in L)*/
//			/* Ignora vertices de SCCs ja identificados*/
//			if (graph1.v[getAdjs(u)[i]].d == inf) {
//				visit(getAdjs(u)[i]);
//			}
//			graph1.v[u].low = min(graph1.v[u].low, graph1.v[getAdjs(u)[i]].low);
//		}
//	}
//	if (graph1.v[u].d == graph1.v[u].low) { /*d[u] = low[u] Raiz do SCC*/
//		smallest = u;
//		graph1.v[u].numSCC = numComp;
//		do {
//			v = pop(&L, 1);
//			if (v < smallest)
//				smallest = v;
//			graph1.v[v].numSCC = numComp;
//			/*Vertices retirados definem SCC*/
//		} while(v != u); /*until u = v*/
//		push(&SCC, smallest, 0);
//		numComp++; 
//	}
//}

void tarjan() {
	int i;
	for (i=0; i<getNumVer(); i++) { /*each vertex u in V[G]*/
		graph1.v[i].d = -1;      /*inf = -1 para simplificar*/
		graph1.v[i].low = -1;
		graph1.v[i].inList = 0;
	}
	for (i=0; i<getNumVer(); i++) /*each vertex u in V[G]*/
		if (graph1.v[i].d == inf)
			scc(i);
}




/*

void printAdjComp(int* adj) {

	int N = adj[1];
	int i;
	int in= 0;
	int numLigComp = 0;

	printf("%d\n", numComp);

	int comps[numComp];
	for (i=numComp-1; i>=0; i--) {
		comps[i] = pop(&SCC, 0);
	}

 	for (i=2; i<(2*N)+2; i+=2) {
    	if (graph1.v[adj[i]-1].low != graph1.v[adj[i+1]-1].low)
      		numLigComp++;
  	}

	comps2 = (int*) malloc((2*numLigComp)*sizeof(int));

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


	for (i=0; i<in/2; i++) {
    	if (i==0 || comps3[in2-2] != comps2[2*ind[i]]
    		  || comps3[in2-1] != comps2[2*ind[i]+1] ) {


    		comps3[in2] = comps2[2*ind[i]];
    		comps3[in2+1] = comps2[2*ind[i]+1];
    		in2+=2;
    	} 
	}

	printf("%d\n", in2/2);
	for (i=0; i<in2; i+=2)
		printf("%d %d\n", comps3[i], comps3[i+1]);

}*/


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

void printGraph() {
	int i, j;
	for (i=0; i<graph1.nVert; i++) {
		printf("\n\nVertice %d\n", i+1);
		printf("Componente: %d\n", graph1.v[i].low);
		printf("SCC num: %d\n", graph1.v[i].numSCC);
		printf("Num Adjs: %d\n", graph1.v[i].nAdjs);
		printf("Adjs:\n");
		for (j=0; j<graph1.v[i].nAdjs; j++)
			printf("%d\n", graph1.v[i].adjs[j]);
	}
}
 

int main(int argc, char** argv) {
	int* adj;
	numComp = 0;
	adj = lerFich();
	createGraph(adj);

	tarjan();
	printf("AAA %d\n", cont);
	//printAdjComp(adj);
	//printGraph();
	return 0;
}

