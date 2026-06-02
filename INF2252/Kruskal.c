#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int src, dest, weight;
} Edge;
typedef struct {
    int V, E;
    Edge* edges;
} Graph;
typedef struct {
    int parent;
    int rank;
} Subset;
Graph* createGraph(int V, int E);
void kruskalMST(Graph* graph);
int find(Subset subsets[], int i);
void Union(Subset subsets[], int x, int y);
int compareEdges(const void* a, const void* b);
int main() {
    int V, E, i;
    printf("Enter number of vertices and edges: ");
    if (scanf("%d %d", &V, &E) != 2 || V <= 0 || E <= 0) {
        printf("Invalid input parameters.\n");
        return 1;
    }
    Graph* graph = createGraph(V, E);
    printf("Enter edges data (source destination weight):\n");
    for (i = 0; i < E; i++) {
        scanf("%d %d %d", &graph->edges[i].src, &graph->edges[i].dest, &graph->edges[i].weight);
    }
    kruskalMST(graph);
    free(graph->edges);
    free(graph);
    return 0;
}
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (Edge*)malloc(E * sizeof(Edge));
    return graph;
}
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}
void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
int compareEdges(const void* a, const void* b) {
    Edge* aEdge = (Edge*)a;
    Edge* bEdge = (Edge*)b;
    return aEdge->weight - bEdge->weight;
}
void kruskalMST(Graph* graph) {
    int V = graph->V;
    Edge* result = (Edge*)malloc((V - 1) * sizeof(Edge));
    int e = 0;
    int i = 0;
    qsort(graph->edges, graph->E, sizeof(Edge), compareEdges);
    Subset* subsets = (Subset*)malloc(V * sizeof(Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edges[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }
    printf("\nEdges in the Minimum Cost Spanning Tree:\n");
    int minimumCost = 0;
    for (i = 0; i < e; i++) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("Total Cost of MST: %d\n", minimumCost);
    free(subsets);
    free(result);
}
