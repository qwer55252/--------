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
    int vsize, esize;
    scanf("%d %d", &vsize, &esize);
    
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

// <Kruskal 알고리즘 관련 함수>

// Q가 비었으면 1을 반환하는 함수
int isEmptyQ(int *Q) {
    if (Q[0] == 0) return 1;
    else return 0;
}


int remove_Min(Graph *G, int *Q, int Q_size) { 
    // Q는 비어있을 수 없음
    int min = 1000000000, min_edge = 0, idx;
    
    for (int i=0;i<Q_size;i++) {
        if (G->edges[Q[i]].weight < min) {
            min_edge = Q[i];
            min = G->edges[Q[i]].weight;
            idx = i;
        }
    }
    for (int i=idx;i<Q_size-1;i++) Q[i] = Q[i+1];
    
    return min_edge;
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
// sack[i]의 크기를 구해주는 함수
int sack_size(int *sack) {
    int size =0;
    while(sack[size] != 0) size++;
    return size;
}
void print_sack(Graph *G,int **sack) {
    int size;
    for (int i=0;i<G->vsize;i++) {
        int j=0;
        printf("sack[%d] :", i);
        size = sack_size(sack[i]);
        for (int j=0;j<size;j++) {
            printf(" %d", sack[i][j]);
        }
        printf("\n");
    }
}

// T의 간선들의 가중치와 그 합을 출력하는 함수(오름차순)
void T_print_weight_and_sum(Graph *G, int *T, int T_size) {
    int sum=0;
    for (int i=0;i<T_size;i++) {
        printf(" %d", G->edges[T[i]].weight); // ?
        sum = sum + G->edges[T[i]].weight;
    }
    printf("\n%d", sum);
}


// 정점 vtx를 담고있는 sack번호를 찾아주는 함수
int find_sack(Graph *G, int **sack, int vtx) {
    int i, j, size;
    for (i=0;i<G->vsize;i++) {
        size = sack_size(sack[i]);
        for (j=0;j<size;j++) {
            if (sack[i][j] == vtx) return i;
        }
    }
    
    printf("there is no %d vtx in sack!\n", vtx);
    return -1;
}
// sack[v] -> sack[u] 모든 정점을 옮기는 작업
void merge_sack(Graph *G, int **sack, int u, int v) {
    int sack_u = find_sack(G, sack, u); // u를 담고있는 sack
    int sack_v = find_sack(G, sack, v); // v를 담고있는 sack
    int sack_u_size = sack_size(sack[sack_u]);
    int sack_v_size = sack_size(sack[sack_v]);

    //printf("sack_v_size : %d\n", sack_v_size);
    for (int i=0;i<sack_v_size;i++) {
        //printf("input : %d\n", i);
        sack[sack_u][sack_u_size + i] = sack[sack_v][i];
        sack[sack_v][i] = 0;
    }
}
void Kruskal(Graph *G) {
    int **sack, Q_size = G->esize;
    // sack 동적할당
    sack = (int **)malloc(sizeof(int *)*G->vsize);
    for (int i=0;i<G->vsize;i++) sack[i] = (int *)malloc(sizeof(int)*(G->vsize + 1)); // sack의 max 사이즈는 정점의 개수지만 마지막 정점 뒤에 0 추가
    for (int i=0;i<G->vsize;i++) {
        sack[i][0] = i+1; // 각 정점의 sack 만들어주기 (i+1 <- 정점의 인덱스)
        for (int j=1;j<G->vsize+1;j++) sack[i][j] = 0; // 정점을 제외한 칸은 0으로 초기화
    }
    
    int *Q = (int *)malloc(sizeof(int)*(G->esize+1)); // 모든 간선을 저장하는 Q
    for (int i=0;i<G->esize;i++) Q[i] = i; // Q에 모든 간선 저장
    Q[G->esize] = -1; // 마지막은 -1로 초기화

    int *T = (int *)malloc(sizeof(int)*G->vsize); // 간선들로 이루어진 MST
    for (int i=0;i<G->vsize;i++) T[i] = -1; // -1로 초기화
    int T_size = 0;

    while(T_size < G->vsize-1) {
        int removed_edge = remove_Min(G, Q, Q_size); // Q에서 가장 가중치가 가장 작은 간선 remove
        Q_size--;
        // 정점 u, v에 간선의 양 끝점 저장
        int u = G->edges[removed_edge].vtx1;
        int v = G->edges[removed_edge].vtx2;

        if (find_sack(G, sack, u) != find_sack(G, sack, v)) { // u와 v의 sack 넘버가 같지 않으면
            T[T_size] = removed_edge; // T에 간선 추가
            T_size++;
            merge_sack(G, sack, u, v); // 정점 u, v가 속하는 sack을 병합시켜준다
        }
        //print_sack(G, sack);
    }

    T_print_weight_and_sum(G, T, T_size);
}



int main() {
    Graph G;    // 그래프 변수 설정 (정적 할당)

    build_graph(&G);    // 그래프 구축

    //print_graph(&G);

    Kruskal(&G);  // MST 생성되는 정점의 vname 출력, 총 무게 출력

    free_graph(&G);
    return 0;
}

/* 입력 예시
6 9
1 2 3
1 3 20
2 4 25
2 5 17
3 4 34
3 5 1
3 6 12
4 5 5
5 6 37
*/