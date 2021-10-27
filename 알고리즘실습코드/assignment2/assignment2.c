#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tNODE { // 트리에 쓰일 노드
    struct tNODE *left;
    struct tNODE *right;
    struct tNODE *parent;
    int data;
}ND;
typedef struct lNODE { // 연결리스트에 쓰이는 노드
    struct tNODE *nodedata; // nodedata로 이진트리의 노드를 사용
    struct lNODE *next;
    struct lNODE *prev;
}lND;
typedef struct DoublyLinkedList { // Queue용도로 쓰일 이중연결리스트
    struct lNODE *front;
    struct lNODE *rear;
}DLL;
typedef struct TREE { // 마지막 노드와 루트를 갖고 있는 트리
    struct tNODE *root;
    struct tNODE *last;
}TR;

int isInternal(ND *v);
ND* deQueue(DLL *queueList);
void initTree(TR *T);

ND* advancedLast(ND *last) {// last 전진하는 함수(last 전진한 노드 반환)
    // 현재 노드가 오른쪽 자식인 동안, 부모 노드로 이동
    while(last->parent != NULL && last == last->parent->right) {
        last = last->parent;
    }
    
    // 현재 노드가 왼쪽 자식이면, 형제 노드로 이동
    if (last->parent != NULL && last == last->parent->left) {
        last = last->parent->right;
    }
    // 현재 노드가 내부노드인 동안, 왼쪽 자식으로 이동
    while(isInternal(last)) {
        last = last->left;
    }
    return last;
}
// ND retreatLast(NE *root) {// last 후진하는 함수(last 후진한 노드 반환)
//     ND *last;
//     last = root->last;
// }
ND* expandExternal(ND *z) { // node z의 외부노드를 생성하여 반환
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
void enQueue(DLL *queueList, ND *node) { // queueList의 맨 앞에 node 삽입
    lND *newnode = (lND *)malloc(sizeof(lND)); // deQueue할 때 free해줌
    newnode->nodedata = node;
    newnode->next = queueList->front->next;
    newnode->prev = queueList->front;
    queueList->front->next->prev = newnode;
    queueList->front->next = newnode;
}
ND* deQueue(DLL *queueList) { // queueList의 맨 뒤에 lnode deQueue하고 그 노드(listnode)의 nodedata(treenode) 반환
    lND *tmp = queueList->rear->prev;
    ND *returnnode = tmp->nodedata;
    queueList->rear->prev = queueList->rear->prev->prev;
    queueList->rear->prev->next = queueList->rear;
    // deQueue한 것 메모리 해제
    tmp->next = NULL;
    tmp->prev = NULL;
    free(tmp);
    return returnnode;
}
void printByLevelOrder(ND *root, int n) { // 트리를 레벨순회하며 출력하는 방법
    DLL *queueList = (DLL *)malloc(sizeof(DLL));
    initQueue(queueList); // Queue리스트 생성

    if (root == NULL) return;
    enQueue(queueList, root); // Queue리스트에 Tree의 root노드 enQueue
    while(!isEmptyQueue(queueList)) { // Queue리스트가 비어있을 때까지 deQueue하면서 deQueue한 것의 자식들 enQueue
        ND *tnode = deQueue(queueList);
        printf(" %d", tnode->data);
        if (isInternal(tnode->left)) enQueue(queueList, tnode->left);
        if (isInternal(tnode->right)) enQueue(queueList, tnode->right);
    }

    freeQueue(queueList); // queueList에 있는 모든 연결을 끊고 내부에 존재하는 모든 노드 free
    free(queueList);
}
void swapElements(ND *a, ND *b) {
    int tmp;
    tmp = a->data;
    a->data = b->data;
    b->data = tmp;
}
void upHeap(ND *v) { // 원소만 바꾸면서 upHeap(노드를 바꿔줄 필요는 없음)
    if (v->parent == NULL) return; // v가 root이면 그만
    if (v->data <= v->parent->data) return; // 이미 최대힙이면 그만
    swapElements(v, v->parent);
    upHeap(v->parent);
}
void insert_heap(TR *T, int k) { // 힙에 k 삽입(upHeap없이 삽입만)
    ND *z;
    z = advancedLast(T->last);
    T->last = z;
    z->data = k;
    z = expandExternal(z);
    return;
}
int isInternal(ND *v) { // 내부노드면 1 반환
    if (v->left == NULL && v->right == NULL) return 0;
    else return 1;
}
int isExternal(ND *v) { // 외부노드면 1 반환
    if (v->left == NULL && v->right == NULL) return 1;
    else return 0;
}
void downHeap(ND *v) { // v의 원소를 downHeap
    int larger;
    ND *larger_node;
    if (isExternal(v->left) && isExternal(v->right)) return; // 더이상 내려갈 곳이 없음
    larger_node = v->left; // 왼쪽 노드를 더 크다고 두고
    if (isInternal(v->right)) { //오른쪽 노드가 내부노드면 비교해서 바꿔준다
        if (larger_node->data < v->right->data) larger_node = v->right;
    }
    if (v->data >= larger_node->data) return;
    swapElements(v, larger_node); // 스왑이 잘 되나 불안한데?
    downHeap(larger_node);
}
void rBuildHeap(ND *v) { // 상향식 힙 생성(재귀적)
    if (isInternal(v)) {
        rBuildHeap(v->left);
        rBuildHeap(v->right);
        downHeap(v);
    }
    return;
}
TR* convertToCompleteBinaryTree(int *L, int n) { // list L을 완전이진트리 T전환
    TR *T = (TR *)malloc(sizeof(TR)); // 이진트리 선언
    initTree(T);
    T->root->data = L[0];
    T->last = T->root;
    
    for (int i=1;i<n;i++) {
        insert_heap(T, L[i]);
        //T->last = advancedLast(T->last);
    }
    return T;
}
TR* buildHeap(int *L, int n) { // list L에 있는 노드들을 키값들을 Heap T에 저장하여 T(T자체가 root) 반환
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
void freeTree(ND *node) { // T->root의 노드를 받아서 재귀적으로 free(상향식 free)
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
    //입력
    scanf("%d", &n);
    arr = (int *)malloc(sizeof(int)*n);    
    for (i=0;i<n;i++) scanf("%d", &arr[i]);
    
    //힙생성 후 저장
    T = buildHeap(arr, n);
    
    //출력
    printByLevelOrder(T->root, n);

    //메모리 해제
    freeTree(T->root);
    free(T->last);
    free(T);
    free(arr);
    return 0;
}