#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
    int adjacencyMatrix[7][7];
}G;

void make_graph(G *graph) { // 주어진 그래프를 만드는 함수
    for (int i=0;i<6;i++) { // 인접행렬 초기화
        for (int j=0;j<6;j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }

    // 인접행렬 만들기
    graph->adjacencyMatrix[1][2] = 1;
    graph->adjacencyMatrix[1][3] = 1;
    graph->adjacencyMatrix[1][4] = 1;
    graph->adjacencyMatrix[1][6] = 2;

    graph->adjacencyMatrix[2][1] = 1;
    graph->adjacencyMatrix[2][3] = 1;

    graph->adjacencyMatrix[3][1] = 1;
    graph->adjacencyMatrix[3][2] = 1;
    graph->adjacencyMatrix[3][5] = 4;

    graph->adjacencyMatrix[4][1] = 1;
    
    graph->adjacencyMatrix[5][3] = 4;
    graph->adjacencyMatrix[5][5] = 4;
    graph->adjacencyMatrix[5][6] = 3;

    graph->adjacencyMatrix[6][1] = 2;
    graph->adjacencyMatrix[6][5] = 3;
}
void print_incidence_edge_list(G *graph, int search) {
    for (int i=1;i<=6;i++) {
        if (graph->adjacencyMatrix[search][i] != 0) printf(" %d %d", i, graph->adjacencyMatrix[search][i]);
    }
    printf("\n");
}
void add_or_fix_edge_between_two_points(G *graph, int ep1, int ep2, int fw) {
    graph->adjacencyMatrix[ep1][ep2] = fw; 
    graph->adjacencyMatrix[ep2][ep1] = fw;
}
int main() {

    char cmd;
    int search_node_id;
    int endpoint1, endpoint2, fix_worth;

    // 인접리스트 구현 
    G *graph = (G *)malloc(sizeof(G));
    make_graph(graph);

    while(1) {
        scanf("%c", &cmd);
        getchar();
        if (cmd == 'q') break;
        else if (cmd == 'a') {
            scanf("%d", &search_node_id);
            getchar();
            if (1 <= search_node_id && search_node_id <= 6) print_incidence_edge_list(graph, search_node_id);
            else printf("-1\n");
        }
        else if (cmd == 'm') {
            scanf("%d %d %d", &endpoint1, &endpoint2, &fix_worth);
            getchar();
            if (endpoint1 < 1 || 6 < endpoint1) printf("-1\n");
            else if (endpoint2 < 1 || 6 < endpoint2) printf("-1\n");
            else add_or_fix_edge_between_two_points(graph, endpoint1, endpoint2, fix_worth);
        }
    }
    
    free(graph);
    return 0;
}