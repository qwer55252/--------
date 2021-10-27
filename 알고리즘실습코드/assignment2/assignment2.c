#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tNODE { // Ʈ���� ���� ���
    struct tNODE *left;
    struct tNODE *right;
    struct tNODE *parent;
    int data;
}ND;
typedef struct lNODE { // ���Ḯ��Ʈ�� ���̴� ���
    struct tNODE *nodedata; // nodedata�� ����Ʈ���� ��带 ���
    struct lNODE *next;
    struct lNODE *prev;
}lND;
typedef struct DoublyLinkedList { // Queue�뵵�� ���� ���߿��Ḯ��Ʈ
    struct lNODE *front;
    struct lNODE *rear;
}DLL;
typedef struct TREE { // ������ ���� ��Ʈ�� ���� �ִ� Ʈ��
    struct tNODE *root;
    struct tNODE *last;
}TR;

int isInternal(ND *v);
ND* deQueue(DLL *queueList);
void initTree(TR *T);

ND* advancedLast(ND *last) {// last �����ϴ� �Լ�(last ������ ��� ��ȯ)
    // ���� ��尡 ������ �ڽ��� ����, �θ� ���� �̵�
    while(last->parent != NULL && last == last->parent->right) {
        last = last->parent;
    }
    
    // ���� ��尡 ���� �ڽ��̸�, ���� ���� �̵�
    if (last->parent != NULL && last == last->parent->left) {
        last = last->parent->right;
    }
    // ���� ��尡 ���γ���� ����, ���� �ڽ����� �̵�
    while(isInternal(last)) {
        last = last->left;
    }
    return last;
}
// ND retreatLast(NE *root) {// last �����ϴ� �Լ�(last ������ ��� ��ȯ)
//     ND *last;
//     last = root->last;
// }
ND* expandExternal(ND *z) { // node z�� �ܺγ�带 �����Ͽ� ��ȯ
    ND *l = (ND *)malloc(sizeof(ND));
    ND *r = (ND *)malloc(sizeof(ND));
    l->left = NULL;
    l->right = NULL;
    l->parent = z;
    r->left = NULL;
    r->right = NULL;
    r->parent = z;
    z->left = l;
    z->right = r;
    return z;
}
int isEmptyQueue(DLL *queueList) {
    if (queueList->front->next == queueList->rear) return 1;
    else return 0;
}
void freeQueue(DLL *queueList) {
    while(!isEmptyQueue(queueList)) deQueue(queueList);
    queueList->front->next = NULL;
    queueList->rear->prev = NULL;
    free(queueList->front);
    free(queueList->rear);
}
void initQueue(DLL *queueList) {
    lND *front = (lND *)malloc(sizeof(lND));
    lND *rear = (lND *)malloc(sizeof(lND));
    //front->nodedata = NULL;
    //rear->nodedata = NULL;
    front->next = rear;
    front->prev = NULL;
    rear->next = NULL;
    rear->prev = front;
    queueList->front = front;
    queueList->rear = rear;
}
void enQueue(DLL *queueList, ND *node) { // queueList�� �� �տ� node ����
    lND *newnode = (lND *)malloc(sizeof(lND)); // deQueue�� �� free����
    newnode->nodedata = node;
    newnode->next = queueList->front->next;
    newnode->prev = queueList->front;
    queueList->front->next->prev = newnode;
    queueList->front->next = newnode;
}
ND* deQueue(DLL *queueList) { // queueList�� �� �ڿ� lnode deQueue�ϰ� �� ���(listnode)�� nodedata(treenode) ��ȯ
    lND *tmp = queueList->rear->prev;
    ND *returnnode = tmp->nodedata;
    queueList->rear->prev = queueList->rear->prev->prev;
    queueList->rear->prev->next = queueList->rear;
    // deQueue�� �� �޸� ����
    tmp->next = NULL;
    tmp->prev = NULL;
    free(tmp);
    return returnnode;
}
void printByLevelOrder(ND *root, int n) { // Ʈ���� ������ȸ�ϸ� ����ϴ� ���
    DLL *queueList = (DLL *)malloc(sizeof(DLL));
    initQueue(queueList); // Queue����Ʈ ����

    if (root == NULL) return;
    enQueue(queueList, root); // Queue����Ʈ�� Tree�� root��� enQueue
    while(!isEmptyQueue(queueList)) { // Queue����Ʈ�� ������� ������ deQueue�ϸ鼭 deQueue�� ���� �ڽĵ� enQueue
        ND *tnode = deQueue(queueList);
        printf(" %d", tnode->data);
        if (isInternal(tnode->left)) enQueue(queueList, tnode->left);
        if (isInternal(tnode->right)) enQueue(queueList, tnode->right);
    }

    freeQueue(queueList); // queueList�� �ִ� ��� ������ ���� ���ο� �����ϴ� ��� ��� free
    free(queueList);
}
void swapElements(ND *a, ND *b) {
    int tmp;
    tmp = a->data;
    a->data = b->data;
    b->data = tmp;
}
void upHeap(ND *v) { // ���Ҹ� �ٲٸ鼭 upHeap(��带 �ٲ��� �ʿ�� ����)
    if (v->parent == NULL) return; // v�� root�̸� �׸�
    if (v->data <= v->parent->data) return; // �̹� �ִ����̸� �׸�
    swapElements(v, v->parent);
    upHeap(v->parent);
}
void insert_heap(TR *T, int k) { // ���� k ����(upHeap���� ���Ը�)
    ND *z;
    z = advancedLast(T->last);
    T->last = z;
    z->data = k;
    z = expandExternal(z);
    return;
}
int isInternal(ND *v) { // ���γ��� 1 ��ȯ
    if (v->left == NULL && v->right == NULL) return 0;
    else return 1;
}
int isExternal(ND *v) { // �ܺγ��� 1 ��ȯ
    if (v->left == NULL && v->right == NULL) return 1;
    else return 0;
}
void downHeap(ND *v) { // v�� ���Ҹ� downHeap
    int larger;
    ND *larger_node;
    if (isExternal(v->left) && isExternal(v->right)) return; // ���̻� ������ ���� ����
    larger_node = v->left; // ���� ��带 �� ũ�ٰ� �ΰ�
    if (isInternal(v->right)) { //������ ��尡 ���γ��� ���ؼ� �ٲ��ش�
        if (larger_node->data < v->right->data) larger_node = v->right;
    }
    if (v->data >= larger_node->data) return;
    swapElements(v, larger_node); // ������ �� �ǳ� �Ҿ��ѵ�?
    downHeap(larger_node);
}
void rBuildHeap(ND *v) { // ����� �� ����(�����)
    if (isInternal(v)) {
        rBuildHeap(v->left);
        rBuildHeap(v->right);
        downHeap(v);
    }
    return;
}
TR* convertToCompleteBinaryTree(int *L, int n) { // list L�� ��������Ʈ�� T��ȯ
    TR *T = (TR *)malloc(sizeof(TR)); // ����Ʈ�� ����
    initTree(T);
    T->root->data = L[0];
    T->last = T->root;
    
    for (int i=1;i<n;i++) {
        insert_heap(T, L[i]);
        //T->last = advancedLast(T->last);
    }
    return T;
}
TR* buildHeap(int *L, int n) { // list L�� �ִ� ������ Ű������ Heap T�� �����Ͽ� T(T��ü�� root) ��ȯ
    TR *T;

    T = convertToCompleteBinaryTree(L, n);
    rBuildHeap(T->root);
    return T;
}
void initTree(TR *T) {
    ND *root = (ND *)malloc(sizeof(ND));
    root = expandExternal(root);
    root->parent = NULL;
    T->root = root;
}
void freeTree(ND *node) { // T->root�� ��带 �޾Ƽ� ��������� free(����� free)
    if (isExternal(node)) {
        node->parent = NULL;
        free(node);
        return;
    }
    freeTree(node->left);
    freeTree(node->right);
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    free(node);
}
int main() {
    int n, i;
    int *arr;
    TR *T;
    //�Է�
    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int)*n);    
    for (i=0;i<n;i++) scanf("%d", &arr[i]);
    
    //������ �� ����
    T = buildHeap(arr, n);
    
    //���
    printByLevelOrder(T->root, n);

    //�޸� ����
    freeTree(T->root);
    free(T->last);
    free(T);
    free(arr);
    return 0;
}