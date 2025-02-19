#include <stdio.h>
#include <limits.h>

#define MAX 10
#define INF 9999

void dijkstra(int graph[MAX][MAX], int nodes, int start) {
    int cost[MAX][MAX], distance[MAX], visited[MAX], next_hop[MAX];
    int i, j, count, min_distance, next_node;

    // Initialize cost matrix
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            if (graph[i][j] == 0) {
                cost[i][j] = INF;
            } else {
                cost[i][j] = graph[i][j];
            }
        }
    }

    // Initialize distance, visited, and next_hop arrays
    for (i = 0; i < nodes; i++) {
        distance[i] = cost[start][i];
        visited[i] = 0;
        if (distance[i] != INF && i != start) {
            next_hop[i] = i; // Initially, the next hop is the direct neighbor
        } else {
            next_hop[i] = -1; // No route yet
        }
    }

    distance[start] = 0;
    visited[start] = 1;
    count = 1;

    // Main loop to calculate shortest paths
    while (count < nodes - 1) {
        min_distance = INF;
        next_node = -1;

        // Find the node with the smallest tentative distance
        for (i = 0; i < nodes; i++) {
            if (!visited[i] && distance[i] < min_distance) {
                min_distance = distance[i];
                next_node = i;
            }
        }

        if (next_node == -1) {
            break; // No more reachable nodes
        }

        visited[next_node] = 1;

        // Update distances for neighbors of the next node
        for (i = 0; i < nodes; i++) {
            if (!visited[i] && cost[next_node][i] != INF) {
                if (distance[next_node] + cost[next_node][i] < distance[i]) {
                    distance[i] = distance[next_node] + cost[next_node][i];
                    next_hop[i] = next_hop[next_node]; // Update next hop
                }
            }
        }
        count++;
    }

    printf("\nRouting Table for Router %d:\n", start + 1);
    printf("Destination\tCost\tNext Hop\n");
    for (i = 0; i < nodes; i++) {
        if (i != start) {
            printf("%d\t\t%d\t", i + 1, distance[i]);
            if (next_hop[i] != -1) {
                printf("%d\n", next_hop[i] + 1);
            } else {
                printf("No route\n");
            }
        }
    }
}

int main() {
    int graph[MAX][MAX], nodes, i, j, start;

    printf("Enter the number of routers: ");
    scanf("%d", &nodes);

    printf("Enter the cost adjacency matrix (use 0 for no direct link):\n");
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the source router: ");
    scanf("%d", &start);

    dijkstra(graph, nodes, start - 1);

    return 0;
}
