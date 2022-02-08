#include <stdio.h>
#include <stdlib.h>


typedef struct Vertex {
    
}V;
typedef struct Edge {

}E;
typedef struct Graph {
    int w;

}G;

int n, m;
G *graph;

int main() {
    graph = (G *)malloc(sizeof(G));
    graph->w=10;
    printf("%d", graph->w);


    return 0;
}