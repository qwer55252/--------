#include <stdio.h>
#include <stdlib.h>

typedef struct incidenceEdgeNode {
    int endpoint;
    int worth;
    struct incidenceEdgeNode *next;
}IEN;
typedef struct vertex{ // 정점의 정보 : id, 간선들의 리스트(오름차순)
    int id;
    struct incidenceEdgeNode *next;
}V;
typedef struct graph {
    struct vertex *vertices[21]; // 그래프의 정점들의 배열
    struct edge *edges[21]; // 그래프의 간선들의 배열
}G;
void make_vertex_and_insert_in_graph (G *graph, int i){// i번 정점을 만들고 그래프에 추가
    V *new_vertex = (V *)malloc(sizeof(V));
    new_vertex->id = i;
    new_vertex->next = NULL;
    graph->vertices[i] = new_vertex;
}
void make_incidenceEdge_and_insert_in_vertex(V *vertex, int endpoint, int edge_worth) {
    // 인접한 간선을 만들고 접점에 리스트 연결
    IEN *new_incidence_edge = (IEN *)malloc(sizeof(IEN));
    new_incidence_edge->endpoint = endpoint;
    new_incidence_edge->worth = edge_worth;
    new_incidence_edge->next=NULL;
    // vertex IEN이 비어있으면
    if (vertex->next==NULL) vertex->next = new_incidence_edge;
    else {
        IEN *p = vertex->next;
        while(p->next != NULL) p = p->next; // 마지막 IEN 까지 이동
        p->next = new_incidence_edge; // 마지막 IEN 뒤에 삽입
    }

}
void make_graph(G *graph) { // 주어진 그래프를 만드는 함수
    for  (int i=1;i<=6;i++) make_vertex_and_insert_in_graph(graph, i);
    make_incidenceEdge_and_insert_in_vertex(graph->vertices[1], 2, 1);
    make_incidenceEdge_and_insert_in_vertex(graph->vertices[1], 3, 1);
    make_incidenceEdge_and_insert_in_vertex(graph->vertices[1], 4, 1);
    make_incidenceEdge_and_insert_in_vertex(graph->vertices[1], 6, 2);

    make_incidenceEdge_and_insert_in_vertex(graph->vertices[2], 1, 1);
    make_incidenceEdge_and_insert_in_vertex(graph->vertices[2], 3, 1);

    make_incidenceEdge_and_insert_in_vertex(graph->vertices[3], 1, 1);
    make_incidenceEdge_and_insert_in_vertex(graph->vertices[3], 2, 1);
    make_incidenceEdge_and_insert_in_vertex(graph->vertices[3], 5, 4);

    make_incidenceEdge_and_insert_in_vertex(graph->vertices[4], 1, 1);

    make_incidenceEdge_and_insert_in_vertex(graph->vertices[5], 3, 4);
    make_incidenceEdge_and_insert_in_vertex(graph->vertices[5], 5, 4);
    make_incidenceEdge_and_insert_in_vertex(graph->vertices[5], 6, 3);

    make_incidenceEdge_and_insert_in_vertex(graph->vertices[6], 1, 2);
    make_incidenceEdge_and_insert_in_vertex(graph->vertices[6], 5, 3);
    return;
}
void print_incidence_list(G *graph, int search_node_id) {// 해당 인덱스 접점의 인접리스트 정보 출력
    // if (graph->vertices[search_node_id].next == NULL) { // 인접한 노드가 없으면
    //     // 지금은 모든 노드가 인접한 노드가 있음
    // }
    if (graph->vertices[search_node_id]->next == NULL) {
        printf("-1\n");
        return;
    }
    IEN *p = graph->vertices[search_node_id]->next;
    while(1) {
        printf(" %d %d", p->endpoint, p->worth);
        if (p->next == NULL) break;
        else p = p->next;
    }
    printf("\n");
}
int check_exist_edge_and_fix(G *graph, int ep1, int ep2, int fw) {// 접점 ep1에서 ep2로의 간선이 존재하면 가중치를 fw로 수정하는 함수
    if (graph->vertices[ep1]->next==NULL) return 0;
    IEN *p = graph->vertices[ep1]->next;
    while(1) {
        if (p->endpoint == ep2) {
            p->worth = fw;
            return 1;// 수정했으면 1반환
        }
        if (p->next == NULL) break; // 마지막 IEN 까지 살펴봤는데 없으면 그만
        else p = p->next;
    }
    // 수정 안했으면 0 반환
    return 0;
}
void add_incidence_edge_from_ep1_to_ep2(G *graph, int ep1, int ep2, int fw) {// 접점 ep1에서 ep2로 향하는 가중치가 fw인 간선 IEN 삽입
    
    IEN *new_incidence_edge = (IEN *)malloc(sizeof(IEN));
    new_incidence_edge->endpoint = ep2;
    new_incidence_edge->worth = fw;
    if (graph->vertices[ep1]->next == NULL) {// 정점의 인접리스트가 비어있는 상태면
        new_incidence_edge->next = NULL;
        graph->vertices[ep1]->next = new_incidence_edge;
        return;
    }
    IEN *p = graph->vertices[ep1]->next;
    while(1) {
        if (p->next == NULL) { // 정점 ep1에 edgelist에 IEN이 하나밖에 존재하지 않는다면
            if (ep2 < p->endpoint) { // 정점 ep1 바로 다음에 삽입하는 경우 
                new_incidence_edge->next = p;
                graph->vertices[ep1]->next = new_incidence_edge;
            }
            else { // 정점 ep1의 다음 다음에 삽입하는 경우
                p->next = new_incidence_edge;
                new_incidence_edge->next = NULL;
            }
            break;
        }
        else if (ep2 < p->endpoint) { // 인접리스트 맨앞에 삽입하는 경우
            new_incidence_edge->next = p;
            graph->vertices[ep1]->next = new_incidence_edge;
            break;
        }
        else {
            while(p->next != NULL) {
                if (ep2 > p->next->endpoint) p = p->next;
                else break;
            }
            
            new_incidence_edge->next = p->next;
            p->next = new_incidence_edge;
            break;
        }        
    }

}
void add_or_fix_edge_between_two_points(G *graph, int ep1, int ep2, int fw) {
    // 접점 ep1에서 ep2로 향하는 간선이 있는지 확인
    int check1, check2;
    check1 = check_exist_edge_and_fix(graph, ep1, ep2, fw);
    check2 = check_exist_edge_and_fix(graph, ep2, ep1, fw);
    if (check1 == 1 && check2 == 1) return;

    // 여기까지 왔으면 간선을 추가해야한다는 의미
    if (ep1 == ep2) add_incidence_edge_from_ep1_to_ep2(graph, ep1, ep2, fw); // 자기자신으로의 간선 추가
    else {
        add_incidence_edge_from_ep1_to_ep2(graph, ep1, ep2, fw); // 접점 ep1에서 접점 ep2로 향하는 간선 추가
        add_incidence_edge_from_ep1_to_ep2(graph, ep2, ep1, fw); // 접점 ep2에서 접점 ep1로 향하는 간선 추가
    }
}
void remove_incidence_edge(G *graph, int ep1, int ep2) {// 정점 ep1에서부터 ep2로의 간선을 제거
    // 이미 ep1으로부터 ep2로의 간선이 존재함을 확인했다
    if (graph->vertices[ep1]->next == NULL) {// 정점ep1의 인접리스트가 비어있으면
        return;
    }
    IEN *p = graph->vertices[ep1]->next;
    IEN *q; // p이전에 존재하는 IEN
    while(p->endpoint != ep2) {
        q = p;
        p = p->next;
    }
    if (p == graph->vertices[ep1]->next) {// 삭제해야할 IEN이 맨 앞에 존재하면
        graph->vertices[ep1]->next = p->next;
        p->next = NULL;
        free(p);
    }
    else {
        q->next = p->next;
        p->next = NULL;
        free(p);
    }
}
void remove_edge_between_two_points(G *graph, int ep1, int ep2) {
    if (check_exist_edge_and_fix(graph, ep1, ep2, 0)) remove_incidence_edge(graph, ep1, ep2);
    if (check_exist_edge_and_fix(graph, ep2, ep1, 0)) remove_incidence_edge(graph, ep2, ep1);
    
}
void free_incidence_list(V *vt) {
    if (vt->next == NULL) return;
    IEN *p = vt->next;
    vt->next = NULL;
    IEN *q;
    while(1) {        
        if (p->next == NULL) {
            free(p);
            break;
        }
        else {
            q = p;
            p = p->next;
            q->next=NULL;
            free(q);
        }
    }
}
void free_graph(G *graph) {
    for (int i=1;i<=6;i++) {
        free_incidence_list(graph->vertices[i]);
    }
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
            // 조건 같은 건 함수 내부에서 해주기(너무 잡다함)
            if (1 <= search_node_id && search_node_id <= 6) print_incidence_list(graph, search_node_id);
            else printf("-1\n");
        }
        else if (cmd == 'm') {
            scanf("%d %d %d", &endpoint1, &endpoint2, &fix_worth);
            getchar();
            if (endpoint1 < 1 || 6 < endpoint1) printf("-1\n");
            else if (endpoint2 < 1 || 6 < endpoint2) printf("-1\n");
            else if (fix_worth != 0) add_or_fix_edge_between_two_points(graph, endpoint1, endpoint2, fix_worth);
            else if (fix_worth == 0) remove_edge_between_two_points(graph, endpoint1, endpoint2);
        }
    }

    free_graph(graph);
    free(graph);
    return 0;
}