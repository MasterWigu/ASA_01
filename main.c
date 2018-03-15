#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "list.h"

void tarjan() {
	int visited = 0;
	return;
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
	printf("Entrou\n");
	int* nums;
	int i;
	nums = lerFich();
	createGraph(nums);
	printf("M=%d; N=%d\n", nums[0], nums[1]);
	for (i=0; i<2*nums[1]; i++)
		printf("%d\n", nums[i+2]);
	
	printGraph();
	printf("\n\nSaiu\n");
	return 0;
}
