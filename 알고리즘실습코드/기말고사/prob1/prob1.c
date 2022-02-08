#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int eid;
    struct node *next;
}Node;
typedef struct vertex{
    int vname;
    int d;
    Node *incid_list;
}Vertex;
typedef struct edge {
    int ename;
    int weight;
    int v1, v2;
}Edge;
typedef struct graph {
    Edge *edges;
    Vertex *vertices;
    int vsize;
    int esize;
}Graph;
Node* get_node(int eid, Node *next) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->eid = eid;
    node->next = next;
    return node;
}
void set_vertices(Graph *G) {
    G->vertices = (Vertex *)malloc(sizeof(Vertex) * (G->vsize + 1));
    for (int i=1;i<=G->vsize;i++) {
        G->vertices[i].d = 30000;
        G->vertices[i].incid_list = get_node(-1, NULL); // 헤더노드
        G->vertices[i].vname = i;
    }
}
int opposite(Graph *G, Node *node, int vs) {
    Edge e = G->edges[node->eid];
    return (e.v1 == vs) ? e.v2 : e.v1;
}
void add_incid_node(Graph *G, int vs, int vd, int eid) {
    Node *node = G->vertices[vs].incid_list;


    while (node->next && opposite(G, node->next, vs) < vd) node = node->next;
    Node *new_node = get_node(eid, node->next);
    node->next = new_node;
}
void set_edges(Graph *G) {
    G->edges = (Edge *)malloc(sizeof(Edge)* (G->esize));
    int v1, v2, w;
    for (int i=0;i<G->esize;i++) {

        // edges
        scanf("%d %d %d", &v1, &v2, &w);
        G->edges[i].ename = i;
        G->edges[i].v1 = v1;
        G->edges[i].v2 = v2;
        G->edges[i].weight = w;

        // 인접리스트
        add_incid_node(G, v1, v2, i); // G에 v1->v2  인접노드 삽입
        add_incid_node(G, v2, v1, i);
    }
}
void build_graph(Graph *G) {
    int vsize, esize;
    scanf("%d %d", &vsize, &esize);
    G->vsize = vsize;
    G->esize = esize;
    set_vertices(G);
    set_edges(G);
}
void free_inicd_list(Node *node) {
    Node *p = node;
    while(node) {
        p = node;
        node = node->next;
        free(p);
    }
}
void freeGraph(Graph *G) {
    // 인접리스트 프리
    for (int i=1;i<=G->vsize;i++) {
        free_inicd_list(G->vertices[i].incid_list);
    }
    free(G->vertices);
    free(G->edges);
}
int main() {
    Graph G;
    build_graph(&G);

    int sum, e;
    Node *node;
    for (int i=1;i<=G.vsize;i++){
        sum =0;
        node = G.vertices[i].incid_list->next;
        
        while(node) {
            e = node->eid;
            sum += G.edges[e].weight;
            node = node->next;
        }
        printf("%d %d\n", i, sum);
        
    }

    freeGraph(&G);
}