#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int edgeId;
    struct node *next;
} Node;     // 부착리스트의 노드
typedef struct vertex {
    int vname;
    int label;
    int removed; // removed == 1 -> 삭제됨
    Node *incid_list;
} Vertex;   // 정점 배열의 원소
typedef struct edge {
    int ename;  // edge 필요할까...?
    int vtx1, vtx2; // 간선의 양 끝점
    int label;
    int removed;
} Edge;
typedef struct graph {
    Vertex *vertices;   // 정점 배열 (동적 할당)
    int vsize;          // 정점 배열의 크기
    Edge *edges;        // 간선 배열 (동적 할당)
    int esize;          // 간선 배열의 크기
    int is_cycle;
    int eccentricity;
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
void set_edges_arr(Graph *G, int eid, int v1, int v2) {
    G->edges[eid].ename = eid;
    G->edges[eid].vtx1 = v1;
    G->edges[eid].vtx2 = v2;
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
    
    new_node = get_node(eid, node->next);   // 삽입할 노드의 정보 설정 get_node->next : node->next
    node->next = new_node;                  // node-->new_node로 링크 설정
}
// 그래프에 간선 (v1, v2) 추가
void add_edge(Graph *G, int eid, int v1, int v2) {
    set_edges_arr(G, eid, v1, v2);       // 간선 배열의 eid 원소에 간선 정보 저장
    
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
    
    int vtx1, vtx2;
    for  (int i=0;i<esize;i++) {
        scanf("%d %d", &vtx1, &vtx2);
        add_edge(G, i, vtx1, vtx2); // edges[i] : vtx1 <--> vtx2, 무게는 weight인 간선
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
        printf(" %d", opposite(G, node, vid));     // 반대쪽 정점 번호 출력
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


// <DFS 관련 함수>
void rDFS(Graph *G, int v) { // 그래프와 정점을 인자로하는 재귀적인 순회
    G->vertices[v].label = 1;
    Node *node = G->vertices[v].incid_list;
    int e;
    while(node->next) {
        node = node->next;
        e = node->edgeId;
        if (G->edges[e].label == 0) {
            int w = opposite(G, node, v);
            if (G->vertices[w].label == 0) {
                G->edges[e].label = 1;
                rDFS(G, w);
            }
            else {
                G->edges[e].label = 2;
            }
        }
    } 
}
// 모든 정점, 간선 label 초기화 함수
void init_graph_label(Graph *G) {
    for (int i=1;i<=G->vsize;i++) {
        G->vertices[i].label = 0; // 0 : Fresh, 1 : Visited
    }
    for (int i=0;i<G->esize;i++) {
        G->edges[i].label = 0; // 0 : Fresh, 1 : Tree, 2 : Back(후향간선)
    }
}
void DFS(Graph G) {
    init_graph_label(&G); // label 초기화
    for (int i=1;i<=G.vsize;i++) {
        if (G.vertices[i].label == 0) {
            rDFS(&G, i);
        }
    }
}

// <그래프 복사 관련 함수>
void dpc_set_edges(Graph *G1, Graph *G, int esize) {
    G1->edges = (Edge *)malloc(sizeof(Edge)*esize);  // 간선 배열 할당
    G1->esize = esize;

    for (int i=0;i<=esize;i++) {    // 간선 배열의 인덱스는 0 ~ esize-1
        G1->edges[i].ename = -1; // 미사용 원소는 -1로 초기화
        G1->edges[i].vtx1 = -1;
        G1->edges[i].vtx2 = -1;
    }
    
    int vtx1, vtx2;
    for  (int i=0;i<esize;i++) {
        vtx1 = G->edges[i].vtx1;
        vtx2 = G->edges[i].vtx2;
        add_edge(G1, i, vtx1, vtx2); // edges[i] : vtx1 <--> vtx2, 무게는 weight인 간선
    }
}
void dpc_build_graph(Graph *G1, Graph *G) {
    int vsize, esize;
    vsize = G->vsize;
    esize = G->esize;
    
    set_vertices(G1, vsize); // 정점 정보 설정
    dpc_set_edges(G1, G, esize);    // 간선 정보 설정
}

// 그래프 복사해주는 함수
Graph duplicate(Graph G) {
    Graph G1;
    dpc_build_graph(&G1, &G);
    return G1;
}

// 사이클이 있는지 확인해주는 함수(확인 후 G->is_cycle 변수에 저장)
void have_cycle(Graph *G, int v) {
    G->vertices[v].label = 1;
    Node *node = G->vertices[v].incid_list;
    int e;
    while(node->next) {
        node = node->next;
        e = node->edgeId; // v의 인접 간선 e에 저장
        if (G->edges[e].label == 0) {  // 처음 들린 간선이라면 
            int w = opposite(G, node, v); // w에 간선e의 반대 정점 저장
            if (G->vertices[w].label == 0) { // 해당 정점이 처음 들린 정점이면
                G->edges[e].label = 1;  // 간선의 label 수정
                have_cycle(G, w); // 다음 정점 재귀 호출
            }
            else { // e : Fresh, w : Visited -> 싸이클
                G->is_cycle = 1;
            }
        }
    } 
}
// 그래프가 트리이면 1 반환 함수
int is_Tree(Graph G) { // call by value
    Graph G1 = duplicate(G); // G1은 포인터이면 안됨!
    // 사이클이 없는지 검사
    G1.is_cycle = 0;
    have_cycle(&G1, 1); 
    if (G1.is_cycle) return 0; // 싸이클이 존재하면 트리가 아님

    // 모든 정점이 연결되어 있는지 검사
    rDFS(&G1, 1);
    for (int i=1;i<=G1.vsize;i++) {
        if (G1.vertices[i].label == 0) { // 방문 안 한 정점이 있다면 트리가 아님
            return 0;
        }
    }
    return 1; // 모든 정점들이 방문되었으면 트리
    free_graph(&G1);
}

// <자유트리 관련 함수>
// <결과 출력 함수>
void print_Num_of_Tree(Graph G) {
    int cnt=0;
    Graph G2 = duplicate(G);
    for (int i=1;i<=G2.vsize;i++) {
        if (G2.vertices[i].label == 0) { // 방문 안 한 정점이 있다면 트리가 아님
            //printf("Fresh vtx is %d\n", i);
            cnt++;
            rDFS(&G2, i);
        }   
    }
    printf("%d", cnt);
    free_graph(&G2);
}

// 
void ramoveLeaves(Graph *G, int v, int p) { // v의 부모 p
    int c=0;
    Node *node = G->vertices[v].incid_list;
    int e;
    while(node->next) { // 다음 인접노드가 있을 떄까지 이동
        node = node->next; // v의 다음 인접리스트로 이동
        e = node->edgeId;
        if(G->edges[e].removed == 1) continue;
        c++; // 인접 리스트 수만큼 증가 (잎은 인접리스트가 1개있음)
        int w = opposite(G, node, v); // w에 opposite(v, e) 저장
        if (w != p) { // w의 부모가 p가 아니면
            ramoveLeaves(G, w, v);
        }
    }
    if (c == 1) { // 모든 인접 노드를 들렸는데 1개였으면
        G->vertices[v].removed = 1; // 해당 노드 삭제
        G->edges[e].removed = 1;
        G->vsize--;
        node = NULL;
        //printf("삭제된 정점 : %d , 남은 정점 수 : %d\n", v, G->vsize);
    }
}

// 중심, 이심률 찾아서 출력해주는 함수
void find_Center(Graph G) {
    Graph G4 = duplicate(G);
    // removed, 이심률 초기화
    for (int i=1;i<=G4.vsize;i++) G4.vertices[i].removed=0;
    for (int i=0;i<G4.esize;i++) G4.edges[i].removed =0;
    G4.eccentricity = 0;

    while(G4.vsize > 2) {
        int a_vtx;
        for (int i=1;i<=G.vsize;i++) { // 남아있는 아무 정점이나 a_vtx에 저장
            if (G4.vertices[i].removed == 0) a_vtx = i;
        }

        ramoveLeaves(&G4, a_vtx, 0); // 정점이 2개 이하로 남을 때까지 잎 제거
        // printf("남은 정점들 : ");
        // for (int i=1;i<=G.vsize;i++) {
        //     if(G4.vertices[i].removed ==0) {
        //         printf("%d ", i);
        //     }
        // }
        // printf("  ... 남은 정점의 수 %d\n", G4.vsize);
        G4.eccentricity++;
    }
    if (G4.vsize == 2) G4.eccentricity++;
    
    // 남은 정점들 출력
    //printf("남은 정점들 : ");
    for (int i=1;i<=G.vsize;i++) {
        if(G4.vertices[i].removed == 0) {
            printf("%d ", i);
        }
    }
    printf("\n%d", G4.eccentricity);
    free_graph(&G4);
}


int main() {
    Graph G;    // 그래프 변수 설정 (정적 할당)

    build_graph(&G);    // 그래프 구축
    
    //graph 생성 검사 : 성공
    //print_graph(&G);
    
    //is_Tree(G) 함수 작동 검사 : 성공
    //printf("is_Tree : %d", is_Tree(G));
    
    if (is_Tree(G)) { // 그래프가 트리이면
        find_Center(G);
        //print_eccentricity(G);
    }
    else { // 트리가 아니면
        print_Num_of_Tree(G);
    }

    free_graph(&G);
    return 0;
}

/*
9 8 
6 4
8 7
3 1
3 4
1 6
3 2
5 7
4 2

9 8
8 5
1 4
3 7
6 4
4 3
9 6
1 2
6 8
*/


/*
8 7
1 3
3 4
5 2
4 2
8 1
7 2
5 6
*/