#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Link {
	int hop, dest, wt;
};

struct Network {
	int H, L;
	struct Link *link;
};

int main() {
	int H, L, S, i, j;
	
	printf("Enter The Number Of Hops: ");
	scanf("%d", &H);
	printf("Enter The Number Of Links: ");
	scanf("%d", &L);
	printf("Enter The Source Node: ");
	scanf("%d", &S);
	
	// Memory Allocation For Network
	struct Network *n = (struct Network *)malloc(sizeof(struct Network));
	n -> H = H;
	n -> L = L;
	n -> link = (struct Link *)malloc(L * sizeof(struct Link));
	
	// Distance Array Initialization
	int *dist = (int *)malloc(H * sizeof(int));
	for (i = 0; i < H; i++) {
		dist[i] = INT_MAX;
	}
	dist[S] = 0;
	
	// Links Initialization
	for (i = 0; i < L; i++) {
		printf("\nLink %d: Enter Source, Destination & Weight: ", i + 1);
		scanf("%d %d %d", &n -> link[i].hop, &n -> link[i].dest, &n -> link[i].wt);
	}
	
	// Bellman - Ford Algorithm
	for (i = 0; i < H; i++) {
		for (j = 0; j < L; j++) {
			int u = n -> link[j].hop;
			int v = n -> link[j].dest;
			int wt = n -> link[j].wt;
			
			if (dist[u] != INT_MAX && dist[u] + wt < dist[v])
				dist[v] = dist[u] + wt;
		}
	}	
		
	// Checking For Negative Weights
	for (i = 0; i < L; i++) {
		int u = n -> link[i].hop;
		int v = n -> link[i].dest;
		int wt = n -> link[i].wt;
			
		if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
			printf("Network Contains Negative Weight Cycle\n");
			free(n -> link);
			free(n);
			free(dist);
			return 0;
		}
	}
	
	printf("\nHop\tDistance From Source\n");
	for (i = 0; i < H; i++) {
		printf("%d\t%d\n", i, dist[i]);
	}
	
	free(n -> link);
	free(n);
	free(dist);
	
	return 0;
}
