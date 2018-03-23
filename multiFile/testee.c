#include <stdio.h>
#include <stdlib.h>


int main() {
	int M;
	int i;
	int N;
	scanf("%d", &M);
	scanf("%d", &N);
	int adjs[2*N];
	for (i=0; i<2*N; i+=2)
		scanf("%d %d", &(adjs[i]), &(adjs[i+1]));

	int conts[M];

	for (i=0; i<M; i++)
		conts[i]=0;

	for (i=0; i<2*N; i+=2)
		conts[adjs[i]-1]++;

	for (i=0; i<M; i++)
		printf("%d\n", conts[i]);

}