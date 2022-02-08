#include <stdio.h>
#include <stdlib.h>

typedef struct incidentEdge {
    int end_id;
    int lable; // 0 : Fresh, 1 : Tree, 2 : Back
    struct incidentEdge *next;
}IE; // 부착리스트의 노드
typedef struct vertex{ // 정점의 정보 : id, 간선들의 리스트(오름차순)
    int id; 
    int lable; // 0 : Fresh, 1 : Visited
    struct incidentEdge *header;
}V; // 정점 배열의 원소
typedef struct edge { // 무방향 그래프이므로 ep1, ep2 무작위임
    int ename;
    int lable; // 0 : Fresh, 1 : Tree, 2 : Back
    int vtx1, vtx2;
}E; // 간선 배열의 원소
typedef struct graph {
    struct vertex *vertices[101]; // 그래프의 정점들의 배열
    struct edge *edges[1001]; // 그래프의 간선들의 배열
    int esize;
    int vsize;
}G; // 그해프의 구성 요소
void get_header(V *v){//정점 v에 부착리스트 헤더노드 생성
    IE *header = (IE *)malloc(sizeof(IE));
    header->next = NULL;
    header->end_id = -1; 
    header->lable = 0; 
    v->header = header;
}
V *get_vertex(int vertex_id) { // 함수 인자를 정점번호로하는 정점 생성    
    V *new_vertex = (V *)malloc(sizeof(V));
    new_vertex->id = vertex_id; 
    new_vertex->lable = 0; 
    get_header(new_vertex); // 정점의 헤더 생성
    return new_vertex;
}// id = vertex_id를 갖고, 헤더를 갖는 정점 생성
void make_vertices(G *graph) {// graph에 n개의 정점을 만들고 vertices까지 만듬
    //graph->vertices = (V *)malloc(sizeof(V)*(graph->vsize + 1)); // 인덱스1부터 사용할 예정

    for (int i=1;i<=graph->vsize;i++) {
        // 정점 생성(인접노드 헤더도 생성), vertices 배열에 대입
        graph->vertices[i] = get_vertex(i);        
    } 
}// 정점에 관한건 모두 생성
IE *get_incidentEdge(int end_id, IE *next) { // next앞에 인접노드(end_id를 향하는) 만들어서 삽입
    IE *new_node = (IE *)malloc(sizeof(IE));
    new_node->end_id = end_id;
    new_node->next = next;
    new_node->lable = 0;
    return new_node;
}// 인접노드 만들어주는 함수
void insert_incidentEdge(G *graph, int start_vtx, int end_vtx) { // graph에 start_vtx->end_vtx 인접노드 생성
    IE *node = graph->vertices[start_vtx]->header;
    IE *new_node;
    
    // 인접 노드를 삽입해야할 곳으로 node를 이동
    // node->next가 존재하고 다음 부착노드의 정점이 작으면 커질 때 까지 이동
    while(node->next && node->next->end_id < end_vtx) node = node->next;
    new_node = get_incidentEdge(end_vtx, node->next); // node->next 앞에 new_node 삽입
    node->next = new_node; // node->next로 연결
}
void make_incidenceList(G *graph) { // 간선들을 입력받으면서 인접리스트에 저장
    int vtx1, vtx2;
    for (int i=0;i<graph->esize;i++) {
        scanf("%d %d", &vtx1, &vtx2);
        insert_incidentEdge(graph, vtx1, vtx2);
        if (vtx1 != vtx2) { // loop가 아니면
            insert_incidentEdge(graph, vtx2, vtx1); // 반대쪽으로 향하는 부착리스트에 노드 추가
        }
    }
    
}// 간선에 관한 관한 것 모두 생성(edges, incidentedges)
void init_graph(G *graph, int n, int m) {// graph 초기화 n : 정점의 개수, m : 간선의 개수
    graph->vsize = n;
    graph->esize = m;
    make_vertices(graph);
    make_incidenceList(graph); // 입력받으면서 
}// vertices, edges 생성함 (incidentedges는 아직 없음)

V* opposite(G *graph, IE *node) { // node : 정점 v의 인접노드
    V *opposite_vertex = graph->vertices[node->end_id]; 
    return opposite_vertex;
}// 인접노드 node 반대방향 반환 없으면 NULL 반환
void rDFS(G *graph, V *v) { // 그래프와 정점을 인자로하는 재귀적인 순회
    v->lable = 1; // 정점의 lable : Fresh->Visited
    printf("%d\n", v->id);
    IE *node = v->header->next;
    while(node) { // 부착노드가 존재하면
        if (node->lable == 0) { // 부착 노드가 Fresh하면
            V *w = opposite(graph, node); // w에 node가 가리키는 정점 대입
            if (w->lable == 0) { // 반대편 정점이 후레시하면
                node->lable = 1; // 인접노드를 Tree로 라벨링하고
                rDFS(graph, w); // 반대편 정점에 대하여 재귀 실행
            }
            else { // 반대편 정점이 후레시하지 않으면
                node->lable = 2; // 인접노드를 Back으로 라벨링함
            }
        }
        node = node->next; // 다음 인접노드로 이동
    }
    
}
void DFS(G *graph, int start_vertex) {
    // 모든 정점들과 인접노드들의 label은 생성과 동시에 초기화해줌
    for (int i=1;i<=graph->vsize;i++) { // vertices의 모든 원소에
        if (graph->vertices[i]->lable == 0) {// Fresh면
            rDFS(graph, graph->vertices[start_vertex]);
        }
    }
}
int main() {
    int n, m, s; // n : 정점의 개수, m : 간선의 개수, s : 시작 정점의 번호
    scanf("%d %d %d", &n, &m, &s);
    G *graph = (G *)malloc(sizeof(G));
    init_graph(graph, n, m);

    DFS(graph, s);
    
    // graph free해주기
}