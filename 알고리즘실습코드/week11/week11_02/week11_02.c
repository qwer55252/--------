#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
    int  vertices[101]; // 그래프의 정점들의 배열(0 : fresh, 1 : visited)
    int adjacencyMatrix[101][101]; // (0 : not exist, 1 : fresh, 2 : visited, 3 : cross)
    int vsize;
}G; // 배열의 모든 요소들은 0으로 초기화되어있음

void set_edge(G *graph, int vtx1, int vtx2) {
    graph->adjacencyMatrix[vtx1][vtx2] = 1;
    graph->adjacencyMatrix[vtx2][vtx1] = 1;
    // 같아도(vtx1 == vtx2) 상관없음
}
void input_and_set_graph(G *graph, int n, int m) {// m개의 간선 입력 받아 graph 초기화
    int vtx1, vtx2;
    for (int i=0;i<m;i++) {
        scanf("%d %d", &vtx1, &vtx2);
        set_edge(graph, vtx1, vtx2); // 그래프에 간선의 존재 표시
    }
}
void BFS1(G *graph, int vtx, int n) { // vtx : 처음 들릴 정점, n : 정점의 개수
    int w; // 간선의 반대 정점을 저장할 변수
    int L[101][101]; // 레벨별로 들린 정점 삽입할 이차원 배열
    L[0][0] = vtx; // L배열에 들린 정점 추가
    graph->vertices[vtx] = 1;
    printf("%d\n", vtx);
    int i=0;
    while(L[i][0] != 0) { //이전 레벨에서 정점을 삽입하지 않을 때까지
        int l=0; // L[i+1] 배열을 순회할 변수
        int j=0; // L[i]배열을 순회할 변수
        while(L[i][j] !=0) { // L[i] 배열의 모든 원소(정점)에 대하여
            int v = L[i][j]; // L[i]에 넣었던 정점 차례로 v에 대입
            
            for (int k=1;k<=n;k++) { // v의 인접 행렬 중
                if (graph->adjacencyMatrix[v][k] == 1) { // v의 fresh한 간선에 대하여
                    w = k;
                    if (graph->vertices[w] == 0) {
                        graph->adjacencyMatrix[v][k] = 2; // v->k로 가는 인접노드 visited로 라벨링
                        graph->adjacencyMatrix[k][v] = 2; // k->v로 가는 인접노드 visited로 라벨링
                        graph->vertices[w] = 1; // 정점 w를 visited로 라벨링
                        printf("%d\n", w);
                        L[i+1][l] = w;
                        l++;
                    }
                    else {
                        graph->adjacencyMatrix[v][k] = 3; // v->k로 가는 인접노드 cross로 라벨링
                        graph->adjacencyMatrix[k][v] = 3; // k->v로 가는 인접노드 cross로 라벨링
                    }
                }
            }
            j++;
        }
        i++;
    }
}
void BFS(G *graph, int n, int m, int s) {
    int search_vtx;
    for (int i=0;i<n;i++) {
        search_vtx = (s+i-1)%(n) + 1; // 그래프가 끊어져 있을 수도 있음, 모든 정점을 돌기 위해
        if (graph->vertices[search_vtx] == 0) { // 해당 정점이 후레시하면 너비 우선 탐색 실행
            BFS1(graph, search_vtx, n);
        }
    }
}
int main() {
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    G *graph = (G *)malloc(sizeof(G));
    input_and_set_graph(graph, n, m); // m개의 간선 입력
    
    BFS(graph, n, m, s);
}