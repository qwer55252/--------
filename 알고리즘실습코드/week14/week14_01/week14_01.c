#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int edgeId;
    struct node *next;
} Node;     // 부착리스트의 노드
typedef struct vertex {
    int vname;
    int d;      // 정점을 배낭과 연결시키는 가중치
    int parent_edge_idx;  // MST 부모를 향하는 간선의 인덱스
    Node *incid_list;
} Vertex;   // 정점 배열의 원소
typedef struct edge {
    int ename;  // edge
    int vtx1, vtx2; // 간선의 양 끝점
    int weight;
} Edge;
typedef struct graph {
    Vertex *vertices;   // 정점 배열 (동적 할당)
    int vsize;          // 정점 배열의 크기
    Edge *edges;        // 간선 배열 (동적 할당)
    int esize;          // 간선 배열의 크
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
// 부착 리스트의 노드(출발 정점은 vs)가 나타내는 간선의 반대쪽 정접 찾기
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
    if (v1 != v2) { // loop가 아니라면
        insert_incid_node(G, eid, v2, v1);  // 반대쪽 정점(v2)의 부착리스트에 노드 추가
    }
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

// <Prim-Jarnik 알고리즘 관련 함수>
// Q가 비었으면 1을 반환하는 함수
int isEmptyQ(int *Q) {
    if (Q[0] == 0) return 1;
    else return 0;
}
// d값이 최소인 정점 remove후 반환
int remove_Min(Graph *G, int *Q, int Q_size) { 
    // Q는 비어있을 수 없음
    int min_vtx = 0, min = 1000000000, min_Q_idx;
    
    // 큐에는 정점들이 저장되어있음
    int vtx;
    for (int i=0;i<Q_size;i++) {
        vtx = Q[i]; // Q에 저장된 정점을 vtx에 대입
        if (G->vertices[vtx].d <= min) { // 해당 정점이 min보다 거리값이 작으면
            min_Q_idx = i; // min_Q_idx 에 Q에서의 인덱스 저장(나중에 맨 뒤에값을 넣어주려고)
            min = G->vertices[vtx].d;
            min_vtx = vtx;
        }
        //printf("try <<%d>>\n", i+1);
        //printf("min_Q_idx : %d,   min : %d,   min_vtx : %d\n", min_Q_idx, min, min_vtx);
    }// min_vtx에는 d값이 최소인 정점 저장
    
    // Q의 맨 뒤의 값을 최소 인덱스로 대치
    Q[min_Q_idx] = Q[Q_size-1];
    Q[Q_size-1] = 0;
    
    return min_vtx;
}
// Q에 정점 z가 존재하면 1 반환하는 함수
int is_in_Q(int *Q, int z) {
    int *p = Q;
    
    while(*p != 0) { // Q의 마지막 정점까지
        //printf("*p : %d\n", *p);
        if (*p == z) return 1;
        p++;
    }
    return 0;
}
// MST 생성시 추가되는 정점 출력 + 간선의 총 무게 출력
void DijkstraShortestPaths(Graph *G) { // 시작정점 s
    
    int sum_weight=0;
    for (int i=1;i<=G->vsize;i++) {
        G->vertices[i].d = 1000000000;  // 무한대로 어떻게 하지?
        G->vertices[i].parent_edge_idx = -1;      // 정점의 부모로 향하는 간선의 인덱스를 -1로 초기화
    }

    int s = G->s;
    G->vertices[s].d = 0;
    
    int *Q = (int *)malloc(sizeof(int) * (G->vsize + 1)); // 정점의 idx를 담는 Q
    int Q_size = G->vsize;

    for (int i=0;i<G->vsize;i++) {
        Q[i] = i+1; 
        //printf("Q[%d] : %d\n",i, Q[i]);
    }// init Q(Q에 모든 정점 넣기)
    Q[Q_size] = 0;
    //printf("Q[%d] : %d\n",G->vsize, Q[G->vsize]);
    
    while(!isEmptyQ(Q)) {
        int u = remove_Min(G, Q, Q_size);   // Q에서 d값이 최소인 정점(의 인덱스) 반환
        Q_size--;
        //sum_weight = sum_weight + G->vertices[u].d;
        //printf(" %d", u);
        
        Node *e = G->vertices[u].incid_list; // 정점 u의 간선들
        //printf("e->next->next->next : %d\n", e->next->next->next->edgeId);
        while(e->next != NULL) {
            e = e->next;
            //printf("e : %d\n", e->edgeId);
            int z = opposite(G, e, u); // z : u의 간선 e의 반대편 정점
            //printf("z : %d\n", z);
            //printf("is_in_Q(Q, z) : %d\n", is_in_Q(Q, z));
            if (is_in_Q(Q, z)) {
                // s->u의 최소 거리 + u->z로의 거리 < 다른 경로의 s->z의 거리보다 작으면
                // 더 작은 경로를 찾았으므로 바꿔준다
                if (G->vertices[u].d + G->edges[e->edgeId].weight <= G->vertices[z].d) {
                    G->vertices[z].d = G->vertices[u].d + G->edges[e->edgeId].weight; // 새로운 최단거리 저장
                    //G->vertices[z].parent_edge_idx = e->edgeId;
                    
                }
            }
        }
    }
    
}

void print_short_distance(Graph *G){
    for (int i=1;i<=G->vsize;i++) {
        if (i == G->s) continue;
        if (G->vertices[i].d == 1000000000) continue;
        printf("%d %d\n", i, G->vertices[i].d);
    }
}


int main() {
    Graph G;    // 그래프 변수 설정 (정적 할당)

    build_graph(&G);    // 그래프 구축

    //print_graph(&G);


    DijkstraShortestPaths(&G);  // MST 생성되는 정점의 vname 출력, 총 무게 출력

    print_short_distance(&G); // 각 정점의 최단거리 출력

    free_graph(&G);
    return 0;
}

/*
5 7 1
1 2 1
1 4 5
5 1 10
3 5 3
4 3 1
3 1 2
2 3 2

8 12 7
1 2 1
2 4 2
4 7 7
3 6 1
6 1 4
7 6 9
7 8 1
1 3 2
2 7 5
1 4 1
2 5 2
7 5 2

*/



/*
실패 케이스 - 비연결 그래프
5 3 2
1 2 1
1 3 1
1 4 1
*/