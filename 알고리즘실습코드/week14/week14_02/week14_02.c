#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int edgeId;
    struct node *next;
} Node;     // 부착리스트의 노드
typedef struct vertex {
    int vname;
    int d;      // s로부터의 거리
    Node *incid_list;
} Vertex;   // 정점 배열의 원소
typedef struct edge {
    int ename;  // edge
    int vtx1, vtx2; // vtx1 : 시작점, vtx2 : 종점
    int weight;
} Edge;
typedef struct graph {
    Vertex *vertices;   // 정점 배열 (동적 할당)
    int vsize;          // 정점 배열의 크기
    Edge *edges;        // 간선 배열 (동적 할당)
    int esize;          // 간선 배열의 크기
    int s; // 시작정점 
} Graph;    // 그래프의 구성 요소

//  <기본 요소 함수>
// 부착 리스트의 node를 할당하고 주어진 인자로 초기화
Node *get_node(int eid, Node *next) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->edgeId = eid;
    node->next = next;
    
    return node;
}
// input : G, 부착리스트 노드, 진출 정점 / 부착 리스트의 노드(출발 정점은 vs)가 나타내는 간선의 반대쪽 정접 찾기
int opposite(Graph *G, Node *node, int vs) {
    Edge e = G->edges[node->edgeId];
    return (e.vtx1 == vs) ? e.vtx2 : e.vtx1; // e.vtx1이 출발정점이면 e.vtx2 반환, e.vtx2가 출발정점이면 e.vtx1 반환
}
// <간선 추가와 관련된 함수들 >
// 간선 배열의 eid 원소로 간선 (v1, v2) 설정
void set_edges_arr(Graph *G, int eid, int v1, int v2, int w) {
    G->edges[eid].ename = eid;
    G->edges[eid].vtx1 = v1;
    G->edges[eid].vtx2 = v2;
    G->edges[eid].weight = w;
}
// 노드 vs의 부착리스트에 간선 (vs, vd)에 대한 노드 추가
void insert_incid_node(Graph *G, int eid, int vs, int vd) {
    Node *node = G->vertices[vs].incid_list;    
    Node *new_node;

    // 반대쪽 정점 번호의 오름차순으로 부착리스트 유지하기 위해
    // 삽입할 위치의 앞 노드 찾기 (헤더 노드 있는 연결리스트라서 코드가 단순함)
    // --> 해당 문제에서는 부착리스트의 순서가 상관 없기때문에 아래 코드 상관 X
    while (node->next && opposite(G, node->next, vs) < vd) node = node->next;
    // while문 종료 후 node는 삽입할 위치의 앞 노드
    
    new_node = get_node(eid, node->next);   // 삽입할 노드의 정보 설정
    node->next = new_node;                  // node-->new_node로 링크 설정
}
// 그래프에 간선 (v1, v2) 추가
void add_edge(Graph *G, int eid, int v1, int v2, int w) {
    set_edges_arr(G, eid, v1, v2, w);       // 간선 배열의 eid 원소에 간선 정보 저장
    
    insert_incid_node(G, eid, v1, v2);  // 정점 v1의 부착리스트에 노드 추가
}
// <그래프 구축을 위한 상위 레벨 함수>
// 그래프 정점 정보 설정
void set_vertices(Graph *G, int vsize) {
    G->vertices = (Vertex *)malloc(sizeof(Vertex)*(vsize+1));   // 정점 배열 할당
    G->vsize = vsize;

    for (int i=1;i<=vsize;i++) {    // 정점 배열의 인덱스(== vname 정점 번호)는 1 ~ vsize
        G->vertices[i].incid_list = get_node(-1, NULL); // 헤더 노드 달기
        G->vertices[i].vname = i; // 정점 이름 설정
    }
}
//그리프 간선 정보 설정
void set_edges(Graph *G, int esize) {
    G->edges = (Edge *)malloc(sizeof(Edge)*esize);  // 간선 배열 할당
    G->esize = esize;

    for (int i=0;i<=esize;i++) {    // 간선 배열의 인덱스는 0 ~ esize-1
        G->edges[i].ename = -1; // 미사용 원소는 -1로 초기화
        G->edges[i].vtx1 = -1;
        G->edges[i].vtx2 = -1;
    }
    
    int vtx1, vtx2, weight;
    for  (int i=0;i<esize;i++) {
        scanf("%d %d %d", &vtx1, &vtx2, &weight);
        add_edge(G, i, vtx1, vtx2, weight); // edges[i] : vtx1 <--> vtx2, 무게는 weight인 간선
    }
}
// 그래프 구축
void build_graph(Graph *G) {
    int vsize, esize, s;
    scanf("%d %d %d", &vsize, &esize, &s);
    
    G->s = s;
    set_vertices(G, vsize); // 정점 정보 설정
    set_edges(G, esize);    // 간선 정보 설정
}

// <그래프의 정보 출력과 메모리 해제 관련 함수>
// 특정 정점의 정보(인접 정점 번호와 간선의 가중치) 출력
void print_adj_vertices(Graph *G, int vid) {
    Node *node = G->vertices[vid].incid_list->next; // 헤드의 다음 노드

    printf("%d:", vid);
    while(node) {
        printf("[%d,", opposite(G, node, vid));     // 반대쪽 정점 번호 출력
        printf(" %d] ", G->edges[node->edgeId].weight); // 가중치 출력
        node = node->next;
    }
    printf("\n");
}
// 그래프의 정보 출력
void print_graph(Graph *G) {
    int i;
    for (i = 1; i <= G->vsize; ++i) print_adj_vertices(G, i);
}
// 부착리스트의 노드들 해제
void free_incid_list(Node *node) { // node : 헤더가 넘어옴
    Node *p;

    while(node) {       // node가 NULL일 때까지(끝까지)
        p = node->next; // 다음 노드 주소 임시 저장
        free(node);     // node 해제
        node = p;       // 다음 노드 주소를 node 변수에 저장
    }
}
// 그래프에 할당된 메모리 해제
void free_graph(Graph *G) {
    int i;
    for (i=0;i<G->vsize;i++) {
        free_incid_list(G->vertices[i].incid_list); // 부착리스트 해제
    }
    free(G->vertices);  // 정점 배열 해제
    free(G->edges);     // 간선 배열 해제
}

// <Bellman-FordShortestPaths> 알고리즘 관련 함수>
int Min(int x, int y) {
    if (x>y) return y;
    else return x;
}
// G->s 로부터의 최단 거리들을 저장해놓음
void BellmanFordShortestPaths(Graph *G) { // 시작정점 s
    // 모든 정점의 거리 무한대로 초기화
    for (int i=1;i<=G->vsize;i++) {
        G->vertices[i].d = 30000;
    }
    int s = G->s;
    G->vertices[s].d = 0;
    
    int u, z, e; 
    for (int i=1;i<G->vsize;i++) { // 완화 작업을 n-1번 반복
        for (int j=0;j<G->esize;j++) { // 모든 간선들을 완화시킬거임
            e = j;
            u = G->edges[e].vtx1; // u는 진출 정점
            z = G->edges[e].vtx2; // z는 진입 정점
            // 무한대 < 무한대-2 연산은 하면 안되므로 무한대일때는 스킵!
            if (G->vertices[u].d != 30000) { // 만약 진출 정점의 거리가 무한대가 아니면
                G->vertices[z].d = Min(G->vertices[z].d, G->vertices[u].d + G->edges[e].weight);
            }
        }
    }
    
}
// s->vertices[i] 거리 출력
void print_short_distance(Graph *G){
    for (int i=1;i<=G->vsize;i++) {
        if (i == G->s || G->vertices[i].d == 30000) continue;
        printf("%d %d\n", i, G->vertices[i].d);
    }
}


int main() {
    Graph G;    // 그래프 변수 설정 (정적 할당)

    build_graph(&G);    // 그래프 구축

    //print_graph(&G);

    BellmanFordShortestPaths(&G);  // MST 생성되는 정점의 vname 출력, 총 무게 출력

    print_short_distance(&G); // 각 정점의 최단거리 출력

    free_graph(&G);
    return 0;
}

/*
5 7 1                     
1 2 1
1 4 5
5 1 -2
3 5 3
3 4 1
1 3 2
3 2 -3
*/