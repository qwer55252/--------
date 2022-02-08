#include <stdio.h>
#include <stdlib.h>

typedef struct incidentEdge {
    int end_id;
    int lable; // 0 : Fresh, 1 : Tree, 2 : Back
    struct incidentEdge *next;
}IE; // ��������Ʈ�� ���
typedef struct vertex{ // ������ ���� : id, �������� ����Ʈ(��������)
    int id; 
    int lable; // 0 : Fresh, 1 : Visited
    struct incidentEdge *header;
}V; // ���� �迭�� ����
typedef struct edge { // ������ �׷����̹Ƿ� ep1, ep2 ��������
    int ename;
    int lable; // 0 : Fresh, 1 : Tree, 2 : Back
    int vtx1, vtx2;
}E; // ���� �迭�� ����
typedef struct graph {
    struct vertex *vertices[101]; // �׷����� �������� �迭
    struct edge *edges[1001]; // �׷����� �������� �迭
    int esize;
    int vsize;
}G; // �������� ���� ���
void get_header(V *v){//���� v�� ��������Ʈ ������ ����
    IE *header = (IE *)malloc(sizeof(IE));
    header->next = NULL;
    header->end_id = -1; 
    header->lable = 0; 
    v->header = header;
}
V *get_vertex(int vertex_id) { // �Լ� ���ڸ� ������ȣ���ϴ� ���� ����    
    V *new_vertex = (V *)malloc(sizeof(V));
    new_vertex->id = vertex_id; 
    new_vertex->lable = 0; 
    get_header(new_vertex); // ������ ��� ����
    return new_vertex;
}// id = vertex_id�� ����, ����� ���� ���� ����
void make_vertices(G *graph) {// graph�� n���� ������ ����� vertices���� ����
    //graph->vertices = (V *)malloc(sizeof(V)*(graph->vsize + 1)); // �ε���1���� ����� ����

    for (int i=1;i<=graph->vsize;i++) {
        // ���� ����(������� ����� ����), vertices �迭�� ����
        graph->vertices[i] = get_vertex(i);        
    } 
}// ������ ���Ѱ� ��� ����
IE *get_incidentEdge(int end_id, IE *next) { // next�տ� �������(end_id�� ���ϴ�) ���� ����
    IE *new_node = (IE *)malloc(sizeof(IE));
    new_node->end_id = end_id;
    new_node->next = next;
    new_node->lable = 0;
    return new_node;
}// ������� ������ִ� �Լ�
void insert_incidentEdge(G *graph, int start_vtx, int end_vtx) { // graph�� start_vtx->end_vtx ������� ����
    IE *node = graph->vertices[start_vtx]->header;
    IE *new_node;
    
    // ���� ��带 �����ؾ��� ������ node�� �̵�
    // node->next�� �����ϰ� ���� ��������� ������ ������ Ŀ�� �� ���� �̵�
    while(node->next && node->next->end_id < end_vtx) node = node->next;
    new_node = get_incidentEdge(end_vtx, node->next); // node->next �տ� new_node ����
    node->next = new_node; // node->next�� ����
}
void make_incidenceList(G *graph) { // �������� �Է¹����鼭 ��������Ʈ�� ����
    int vtx1, vtx2;
    for (int i=0;i<graph->esize;i++) {
        scanf("%d %d", &vtx1, &vtx2);
        insert_incidentEdge(graph, vtx1, vtx2);
        if (vtx1 != vtx2) { // loop�� �ƴϸ�
            insert_incidentEdge(graph, vtx2, vtx1); // �ݴ������� ���ϴ� ��������Ʈ�� ��� �߰�
        }
    }
    
}// ������ ���� ���� �� ��� ����(edges, incidentedges)
void init_graph(G *graph, int n, int m) {// graph �ʱ�ȭ n : ������ ����, m : ������ ����
    graph->vsize = n;
    graph->esize = m;
    make_vertices(graph);
    make_incidenceList(graph); // �Է¹����鼭 
}// vertices, edges ������ (incidentedges�� ���� ����)

V* opposite(G *graph, IE *node) { // node : ���� v�� �������
    V *opposite_vertex = graph->vertices[node->end_id]; 
    return opposite_vertex;
}// ������� node �ݴ���� ��ȯ ������ NULL ��ȯ
void rDFS(G *graph, V *v) { // �׷����� ������ ���ڷ��ϴ� ������� ��ȸ
    v->lable = 1; // ������ lable : Fresh->Visited
    printf("%d\n", v->id);
    IE *node = v->header->next;
    while(node) { // ������尡 �����ϸ�
        if (node->lable == 0) { // ���� ��尡 Fresh�ϸ�
            V *w = opposite(graph, node); // w�� node�� ����Ű�� ���� ����
            if (w->lable == 0) { // �ݴ��� ������ �ķ����ϸ�
                node->lable = 1; // ������带 Tree�� �󺧸��ϰ�
                rDFS(graph, w); // �ݴ��� ������ ���Ͽ� ��� ����
            }
            else { // �ݴ��� ������ �ķ������� ������
                node->lable = 2; // ������带 Back���� �󺧸���
            }
        }
        node = node->next; // ���� �������� �̵�
    }
    
}
void DFS(G *graph, int start_vertex) {
    // ��� ������� ���������� label�� ������ ���ÿ� �ʱ�ȭ����
    for (int i=1;i<=graph->vsize;i++) { // vertices�� ��� ���ҿ�
        if (graph->vertices[i]->lable == 0) {// Fresh��
            rDFS(graph, graph->vertices[start_vertex]);
        }
    }
}
int main() {
    int n, m, s; // n : ������ ����, m : ������ ����, s : ���� ������ ��ȣ
    scanf("%d %d %d", &n, &m, &s);
    G *graph = (G *)malloc(sizeof(G));
    init_graph(graph, n, m);

    DFS(graph, s);
    
    // graph free���ֱ�
}