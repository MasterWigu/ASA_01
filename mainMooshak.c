#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define inf -1
#define True 1
#define False 0

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
	int inList; /*1 se estiver no stack, 0 se nao*/
	int nTo;
	int* tos;
} vertex;


typedef struct {
	int nVert;
	vertex* v;
} graph;

graph graph1;


LLElem* SCC;
LLElem* L;

int numComp;
int *comps2;
int arch;


typedef struct {
	int orig;
	int dest;
} merda;

int contMerda;
int contMerda2;
merda caralhinho[1000000];

/*list functions*/

void push(LLElem **head, int vNum, int L) {
	if(L) graph1.v[vNum].inList = True;
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
	int vNum = (*head)->vNum;
	if(L) graph1.v[vNum].inList = False;
	LLElem *temp = (*head)->next;
	/*free(*head);*/
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

	graph1.v = (vertex*)malloc(sizeof(vertex)*N);
	if (graph1.v == NULL) {
		printf("ERRO malloc 1 graph\n");
		exit(1);
	}

	for (i=0; i<N; i++) {
		graph1.v[i].nTo = 0;
		graph1.v[i].inList = 0;
		graph1.v[i].low = inf;
		graph1.v[i].d = inf;
		graph1.v[i].numSCC = inf;
	}

	int numTos[N];

	for (i=0; i<N; i++) {
		numTos[i]=0;
	}

	for (i=2; i<2*M+2; i+=2) {
		numTos[in[i]]++;
		
	}

	for (i=0; i<N; i++) {
		graph1.v[i].tos = (int*) malloc(numTos[i]*sizeof(int));
		if (graph1.v[i].tos == NULL) {
			printf("ERRO malloc 2 graph\n");
			exit(1);
		}
	}


	for (i=2; i<(2*M)+2; i+=2) {
		graph1.v[in[i]].tos[graph1.v[in[i]].nTo] = in[i+1];
		graph1.v[in[i]].nTo++;
	}
	return 0;
}


int getNumAdjs(int vertNum) {
	return graph1.v[vertNum].nTo; 
}

int* getAdjs(int vertNum) { /*retorna a lista de vertices acessiveis a partir desse*/
	return graph1.v[vertNum].tos;
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
 

void addmerda(int org, int dest) {
	int i = 0;
	int a=0, b=0;
	for (i=0; i < contMerda; i++) {
		if (caralhinho[i].orig == org)
			b=1;
		if (caralhinho[i].orig == org && caralhinho[i].dest == dest){
			a=1;
			break;
		}
	}
	if(a==0) {
		caralhinho[contMerda].orig = org;
		caralhinho[contMerda].dest = dest;
		contMerda++;
	}
	if (b==0)
		contMerda2++;
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void visit(int u) {
	static int visited = 0;
	int i, v, smallest;
	graph1.v[u].d = visited;
	graph1.v[u].low = visited;

	visited++;

	push(&L, u, True);

	for (i=0; i<getNumAdjs(u); i++) { /*each v in Adj[u]*/
		if (graph1.v[getAdjs(u)[i]].d == inf || graph1.v[getAdjs(u)[i]].inList == True) {/*(d[v] = inf || v in L)*/
			/* Ignora vertices de SCCs ja identificados*/
			if (graph1.v[getAdjs(u)[i]].d == inf) {
				visit(getAdjs(u)[i]);
			}
			graph1.v[u].low = min(graph1.v[u].low, graph1.v[getAdjs(u)[i]].low);
		}
	}
	if (graph1.v[u].d == graph1.v[u].low) { /*d[u] = low[u] Raiz do SCC*/
		smallest = u;
		graph1.v[u].numSCC = numComp;
		do {
			v = pop(&L, True);
			if (v < smallest)
				smallest = v;
			graph1.v[v].numSCC = numComp;
			/*Vertices retirados definem SCC*/
		} while(v != u); /*until u = v*/

		push(&SCC, smallest, False);
		numComp++; 
	}
}

void tarjan() {
	int i;
	for (i=0; i<getNumVer(); i++) /*each vertex u in V[G]*/
		if (graph1.v[i].d == inf)
			visit(i);
}

void printAdjComp(int* adj) {

	int N = adj[1];
	int i;
	int in = 0;
	int numLigComp = 0;

	printf("%d\n", numComp);

	int *comps;
	comps = (int*) malloc(numComp*sizeof(int));
	if (comps == NULL) {
		printf("ERRO malloc 1 print\n");
		exit(1);
	}

	for (i=numComp-1; i>=0; i--) {
		comps[i] = pop(&SCC, False);
	}

 	for (i=2; i<(2*N)+2; i+=2) {
    	if (graph1.v[adj[i]].numSCC != graph1.v[adj[i+1]].numSCC)
      		numLigComp++;
  	}

	comps2 = (int*) malloc((2*numLigComp)*sizeof(int));
	if (comps2 == NULL) {
		printf("ERRO malloc 2 print\n");
		exit(1);
	}

	for (i=2; i<(2*N)+2; i+=2) {
		if (graph1.v[adj[i]].numSCC != graph1.v[adj[i+1]].numSCC) { 
    		if (in==0 ||  
        		comps2[in-2] != comps[graph1.v[adj[i]].numSCC] ||  
        		comps2[in-1] != comps[graph1.v[adj[i+1]].numSCC]) { 
 
	        	comps2[in] = comps[graph1.v[adj[i]].numSCC]; 
    	    	comps2[in+1] = comps[graph1.v[adj[i+1]].numSCC]; 
    	    	in+=2;
      		} 
    	} 
	}

	int *ind;
	ind = (int*) malloc((in/2)*sizeof(int));
	if (ind == NULL) {
		printf("ERRO malloc 3 print\n");
		exit(1);
	}



	for (i=0; i<in/2; i++)
		ind[i]=i;


	mergeSort(ind, 0, (in/2)-1);

	int comps3[in];
	int in2 = 0;


	for (i=0; i<in/2; i++) {
    	if (i==0 || comps3[in2-2] != comps2[2*ind[i]]
    		  || comps3[in2-1] != comps2[(2*ind[i])+1] ) {


    		comps3[in2] = comps2[2*ind[i]];
    		comps3[in2+1] = comps2[(2*ind[i])+1];
    		in2+=2;
    	} 
	}

	printf("%d\n", in2/2);
	for (i=0; i<in2; i+=2)
		printf("%d %d\n", comps3[i]+1, comps3[i+1]+1);

}


int* lerFich() {
	int M;
	int N;
	int i;
	int *res;
	int err;  /*apenas para silenciar compilador acerca de ignorar o output do scanf*/
	err = scanf("%d", &M);
	err = scanf("%d", &N);
	res = (int*) malloc((2+(2*N))*sizeof(int)); 
	if (res == NULL) {
		printf("ERRO malloc 1 lerFich\n");
		exit(1);
	}
	res[0] = M;
	res[1] = N;

	for (i=2; i<(2*N)+2; i+=2) {
		err = scanf("%d %d", &res[i], &res[i+1]);
		res[i]--;
		res[i+1]--;
	}
	err++; /*tambem para silenciar complilador*/
	return res; 
}
 

int main(int argc, char** argv) {
	contMerda =0;
	contMerda2 = 0;
	arch = 0;
	/*int i;*/
	int* adj;
	L = NULL;
	SCC = NULL;
	numComp = 0;
	adj = lerFich();
	createGraph(adj);

	/*for (i=0; i<adj[0]; i++)
		printf("%d\n", graph1.v[i].nTo);*/

	tarjan();
	printAdjComp(adj);

	return 0;
}

