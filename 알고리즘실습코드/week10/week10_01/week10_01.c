#include <stdio.h>
#include <stdlib.h>

typedef struct incidenceEdgeNode {
    int endpoint;
    int worth;
    struct incidenceEdgeNode *next;
}IEN;
typedef struct vertex{ // ������ ���� : id, �������� ����Ʈ(��������)
    int id;
    struct incidenceEdgeNode *next;
}V;
typedef struct graph {
    struct vertex *vertices[21]; // �׷����� �������� �迭
    struct edge *edges[21]; // �׷����� �������� �迭
}G;
void make_vertex_and_insert_in_graph (G *graph, int i){// i�� ������ ����� �׷����� �߰�
    V *new_vertex = (V *)malloc(sizeof(V));
    new_vertex->id = i;
    new_vertex->next = NULL;
    graph->vertices[i] = new_vertex;
}
void make_incidenceEdge_and_insert_in_vertex(V *vertex, int endpoint, int edge_worth) {
    // ������ ������ ����� ������ ����Ʈ ����
    IEN *new_incidence_edge = (IEN *)malloc(sizeof(IEN));
    new_incidence_edge->endpoint = endpoint;
    new_incidence_edge->worth = edge_worth;
    new_incidence_edge->next=NULL;
    // vertex IEN�� ���������
    if (vertex->next==NULL) vertex->next = new_incidence_edge;
    else {
        IEN *p = vertex->next;
        while(p->next != NULL) p = p->next; // ������ IEN ���� �̵�
        p->next = new_incidence_edge; // ������ IEN �ڿ� ����
    }

}
void make_graph(G *graph) { // �־��� �׷����� ����� �Լ�
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
void print_incidence_list(G *graph, int search_node_id) {// �ش� �ε��� ������ ��������Ʈ ���� ���
    // if (graph->vertices[search_node_id].next == NULL) { // ������ ��尡 ������
    //     // ������ ��� ��尡 ������ ��尡 ����
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
int check_exist_edge_and_fix(G *graph, int ep1, int ep2, int fw) {// ���� ep1���� ep2���� ������ �����ϸ� ����ġ�� fw�� �����ϴ� �Լ�
    if (graph->vertices[ep1]->next==NULL) return 0;
    IEN *p = graph->vertices[ep1]->next;
    while(1) {
        if (p->endpoint == ep2) {
            p->worth = fw;
            return 1;// ���������� 1��ȯ
        }
        if (p->next == NULL) break; // ������ IEN ���� ����ôµ� ������ �׸�
        else p = p->next;
    }
    // ���� �������� 0 ��ȯ
    return 0;
}
void add_incidence_edge_from_ep1_to_ep2(G *graph, int ep1, int ep2, int fw) {// ���� ep1���� ep2�� ���ϴ� ����ġ�� fw�� ���� IEN ����
    
    IEN *new_incidence_edge = (IEN *)malloc(sizeof(IEN));
    new_incidence_edge->endpoint = ep2;
    new_incidence_edge->worth = fw;
    if (graph->vertices[ep1]->next == NULL) {// ������ ��������Ʈ�� ����ִ� ���¸�
        new_incidence_edge->next = NULL;
        graph->vertices[ep1]->next = new_incidence_edge;
        return;
    }
    IEN *p = graph->vertices[ep1]->next;
    while(1) {
        if (p->next == NULL) { // ���� ep1�� edgelist�� IEN�� �ϳ��ۿ� �������� �ʴ´ٸ�
            if (ep2 < p->endpoint) { // ���� ep1 �ٷ� ������ �����ϴ� ��� 
                new_incidence_edge->next = p;
                graph->vertices[ep1]->next = new_incidence_edge;
            }
            else { // ���� ep1�� ���� ������ �����ϴ� ���
                p->next = new_incidence_edge;
                new_incidence_edge->next = NULL;
            }
            break;
        }
        else if (ep2 < p->endpoint) { // ��������Ʈ �Ǿտ� �����ϴ� ���
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
    // ���� ep1���� ep2�� ���ϴ� ������ �ִ��� Ȯ��
    int check1, check2;
    check1 = check_exist_edge_and_fix(graph, ep1, ep2, fw);
    check2 = check_exist_edge_and_fix(graph, ep2, ep1, fw);
    if (check1 == 1 && check2 == 1) return;

    // ������� ������ ������ �߰��ؾ��Ѵٴ� �ǹ�
    if (ep1 == ep2) add_incidence_edge_from_ep1_to_ep2(graph, ep1, ep2, fw); // �ڱ��ڽ������� ���� �߰�
    else {
        add_incidence_edge_from_ep1_to_ep2(graph, ep1, ep2, fw); // ���� ep1���� ���� ep2�� ���ϴ� ���� �߰�
        add_incidence_edge_from_ep1_to_ep2(graph, ep2, ep1, fw); // ���� ep2���� ���� ep1�� ���ϴ� ���� �߰�
    }
}
void remove_incidence_edge(G *graph, int ep1, int ep2) {// ���� ep1�������� ep2���� ������ ����
    // �̹� ep1���κ��� ep2���� ������ �������� Ȯ���ߴ�
    if (graph->vertices[ep1]->next == NULL) {// ����ep1�� ��������Ʈ�� ���������
        return;
    }
    IEN *p = graph->vertices[ep1]->next;
    IEN *q; // p������ �����ϴ� IEN
    while(p->endpoint != ep2) {
        q = p;
        p = p->next;
    }
    if (p == graph->vertices[ep1]->next) {// �����ؾ��� IEN�� �� �տ� �����ϸ�
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

    // ��������Ʈ ���� 
    G *graph = (G *)malloc(sizeof(G));
    make_graph(graph);

    while(1) {
        scanf("%c", &cmd);
        getchar();
        if (cmd == 'q') break;
        else if (cmd == 'a') {
            scanf("%d", &search_node_id);
            getchar();
            // ���� ���� �� �Լ� ���ο��� ���ֱ�(�ʹ� �����)
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