#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
    int  vertices[101]; // �׷����� �������� �迭(0 : fresh, 1 : visited)
    int adjacencyMatrix[101][101]; // (0 : not exist, 1 : fresh, 2 : visited, 3 : cross)
    int vsize;
}G; // �迭�� ��� ��ҵ��� 0���� �ʱ�ȭ�Ǿ�����

void set_edge(G *graph, int vtx1, int vtx2) {
    graph->adjacencyMatrix[vtx1][vtx2] = 1;
    graph->adjacencyMatrix[vtx2][vtx1] = 1;
    // ���Ƶ�(vtx1 == vtx2) �������
}
void input_and_set_graph(G *graph, int n, int m) {// m���� ���� �Է� �޾� graph �ʱ�ȭ
    int vtx1, vtx2;
    for (int i=0;i<m;i++) {
        scanf("%d %d", &vtx1, &vtx2);
        set_edge(graph, vtx1, vtx2); // �׷����� ������ ���� ǥ��
    }
}
void BFS1(G *graph, int vtx, int n) { // vtx : ó�� �鸱 ����, n : ������ ����
    int w; // ������ �ݴ� ������ ������ ����
    int L[101][101]; // �������� �鸰 ���� ������ ������ �迭
    L[0][0] = vtx; // L�迭�� �鸰 ���� �߰�
    graph->vertices[vtx] = 1;
    printf("%d\n", vtx);
    int i=0;
    while(L[i][0] != 0) { //���� �������� ������ �������� ���� ������
        int l=0; // L[i+1] �迭�� ��ȸ�� ����
        int j=0; // L[i]�迭�� ��ȸ�� ����
        while(L[i][j] !=0) { // L[i] �迭�� ��� ����(����)�� ���Ͽ�
            int v = L[i][j]; // L[i]�� �־��� ���� ���ʷ� v�� ����
            
            for (int k=1;k<=n;k++) { // v�� ���� ��� ��
                if (graph->adjacencyMatrix[v][k] == 1) { // v�� fresh�� ������ ���Ͽ�
                    w = k;
                    if (graph->vertices[w] == 0) {
                        graph->adjacencyMatrix[v][k] = 2; // v->k�� ���� ������� visited�� �󺧸�
                        graph->adjacencyMatrix[k][v] = 2; // k->v�� ���� ������� visited�� �󺧸�
                        graph->vertices[w] = 1; // ���� w�� visited�� �󺧸�
                        printf("%d\n", w);
                        L[i+1][l] = w;
                        l++;
                    }
                    else {
                        graph->adjacencyMatrix[v][k] = 3; // v->k�� ���� ������� cross�� �󺧸�
                        graph->adjacencyMatrix[k][v] = 3; // k->v�� ���� ������� cross�� �󺧸�
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
        search_vtx = (s+i-1)%(n) + 1; // �׷����� ������ ���� ���� ����, ��� ������ ���� ����
        if (graph->vertices[search_vtx] == 0) { // �ش� ������ �ķ����ϸ� �ʺ� �켱 Ž�� ����
            BFS1(graph, search_vtx, n);
        }
    }
}
int main() {
    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);
    G *graph = (G *)malloc(sizeof(G));
    input_and_set_graph(graph, n, m); // m���� ���� �Է�
    
    BFS(graph, n, m, s);
}