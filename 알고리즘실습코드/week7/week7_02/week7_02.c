#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode{
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    struct TreeNode *parent;
    int key;
    int height;
}TND;
typedef struct BinarySearchTree {
    struct TreeNode *root;
}AVL;


TND* treeSearch(TND *v, int k);
void expandExternal(TND *w);
int isExternal(TND *w);
int isInternal(TND *w);
TND* inOrderSucc(TND *w);
void printByPreOrder(TND *node);


void findElement(AVL *T, int k) { // k가 있으면 k 반환, 없으면 ?
    TND *w = treeSearch(T->root, k);
    if (isExternal(w)) printf("X");
    else printf(" %d", w->key);
}
void restructure(AVL *T, TND *x, TND *y, TND *z) {
    // 1. x, y, z를 중위순회 순으로 a, b, c로 저장
    // 2, x, y, z의 부트리들을 중위순회순으로 T0, T1, T2, T3로 저장
    TND *a; TND *b; TND *c;
    TND *T0; TND *T1; TND *T2; TND *T3;
    if (y == z->rchild) {
        a = z;
        if (x == y->rchild) {
            b = y;c = x;
            T0 = z->lchild;T1 = y->lchild;T2 = x->lchild;T3 = x->rchild;
        }
        else {// x == y->lchild
            c = y;b = x;
            T0=z->lchild;T1=x->lchild;T2=x->rchild;T3=y->rchild;
        }
    }
    else { // y == z->lchild
        c = z;
        if (x == y->rchild) {
            a = y;b = x;
            T0=y->lchild;T1=x->lchild;T2=x->rchild;T3=z->rchild;
        }
        else { // x == y->lchild
            b = y;a = x;
            T0=x->lchild;T1=x->rchild;T2=y->rchild;T3=z->rchild;
        }
    }
    // 3. z를 루트로 하는 부트리를 b를 루트로하는 부트리로 대체
    if (z->parent == NULL) { // z가 Root 이면
        b->parent = NULL;b->lchild=NULL;b->rchild=NULL;//이러면 T1, T2도 없어지나?->안없어짐
        T->root = b;
        a->rchild = NULL;
    }
    else if(z->parent->lchild == z) { // z가 root가 아니고 부모의 lchild이면
        b->parent = z->parent;b->lchild=NULL;b->rchild=NULL;
        z->parent->lchild = b;z->parent = NULL;
        
    }
    else { // z가 root가 아니고, z->parent->rchild == z
        z->parent->rchild = b;b->parent = z->parent;
    }
    b->rchild = c;c->parent = b;
    b->lchild = a;a->parent = b;

    a->lchild = T0;T0->parent = a;
    a->rchild = T1;T1->parent = a;
    c->lchild = T2;T2->parent = c;
    c->rchild = T3;T3->parent = c;
    
    

    return;
}
int isBalanced(TND *node) {
    int difference = node->rchild->height - node->lchild->height;
    if (-2<difference && difference<2) return 1;
    else return 0;
}
void searchAndFixAfterInsertion(AVL *T, TND *w) { // 균형검사를 수행하고 불균형하면 수정하여 AVL형태 유지
    // 1. w에서 T의 루트로 향해 올라가다가 처음 만나는 불균형 노트를 z라 하자(z가 없으면 Return)
    TND *z = w; // z만 변하고 w는 안변함
    while(z != NULL) { // w가 root이기 까지 조사
        if (!isBalanced(z)) break; // z가 불균형하면 나간다
        else z = z->parent; // 균형적이면 계속 올라간다
    }
    if (z == NULL) return; // 불균형한 z가 없으면 return
    // z에는 불균형한 노드가 저장되어 있는 상태
    // 2. z의 높은 자식을 y라 하자.
    TND *y = z->lchild;
    if (y->height < z->rchild->height) y = z->rchild; 
    // 3. y의 높은 자식을 x라 하자.
    TND *x = y->lchild;
    if (x->height < y->rchild->height) x = y->rchild;
    
    // 4. x, y, z 개조
    restructure(T, x, y, z);
    
    return;
}
void updateHeight_by_postorder(TND *node) { // 루트를 받으면 재귀적으로 높이 설정
    if (isExternal(node)) {
        node->height=0;
        return;
    }
    updateHeight_by_postorder(node->lchild);
    updateHeight_by_postorder(node->rchild);
    int greater;
    greater = node->lchild->height;
    if (greater < node->rchild->height) greater = node->rchild->height;
    node->height = greater+1;
    return;   
}
TND* return_root(TND *w) {
    while(w->parent == NULL) w = w->parent;
    return w;
}
void printAddressByPostOrder(TND *node) { // node를 root로 삼아 재귀적으로 전위순회 출력
    if (isExternal(node)) {
        printf("%p %d\n", node, node->height);
        return;
    }
    printAddressByPostOrder(node->lchild);
    printAddressByPostOrder(node->rchild);
    printf("%p %d\n", node, node->height);
    return;
}
void insertItem(AVL *T, int k) { // AVL T에 k삽입
    TND *w = treeSearch(T->root, k); // w <- k값이 위치해야할 노드 반환
    if (isInternal(w)) return; // 이미 있으면 종료
    else { // 외부노드이면 그 자리에 삽입
        w->key = k;
        expandExternal(w);
        updateHeight_by_postorder(T->root);
        //printAddressByPostOrder(T->root);
        searchAndFixAfterInsertion(T, w);// 삽입 후 불균형한지 조사
        updateHeight_by_postorder(T->root);
        //printAddressByPostOrder(T->root);
    }
}
TND* treeSearch(TND *v, int k) { // v나 v의 부트리에서 k값을 갖는 노드 찾아서 반환 만약 없다면 있었다면 위치할 외부노드 반환 -> 후에 insert 작업을 편하게 하기 위해서
    if (isExternal(v)) return v;
    if (k == v->key) return v;
    else if (k < v->key) return treeSearch(v->lchild, k);
    else return treeSearch(v->rchild, k);
}
TND* d_treeSearch(TND *v, int k) { // v나 v의 부트리에서 k값을 갖는 노드 찾아서 반환 만약 없다면 있었다면 위치할 외부노드 반환 -> 후에 insert 작업을 편하게 하기 위해서
    if (isExternal(v)) return v;
    if (k == v->key) {
        return v;
    }
    else if (k < v->key) return d_treeSearch(v->lchild, k);
    else return d_treeSearch(v->rchild, k);
}
int isRoot(TND *w) { // w가 root노드이면 1 반환 아니면 0 반환
    if (w->parent == NULL) return 1;
    else return 0;
}
TND* sibling(TND *w) {// w의 형제 노드를 반환
    // 어차피 외부노드의 형제를 찾는 것이므로 항상 형제가 존재 -> 외부노드의 형제가 root일 수 없음
    if (w->parent->lchild == w) return w->parent->rchild; // w가 왼쪽 자식이었으면 w->par->rch 반환
    else return w->parent->lchild; // w가 오른쪽 자식이었으면 w->par->lch 반환
}
void putnode(TND *node) { // node의 모든 연결 끊고 free
    node->lchild = NULL;
    node->rchild = NULL;
    node->parent = NULL;
    //free(node);
}
TND* reduceExternal(TND *z, AVL *T) { // 외부노드 z와 z->parent를 통째로 날리고 그자리 z의 형제 노드로 대체후 반환
    TND *w = z->parent;
    TND *zs = sibling(z);
    if (isRoot(w)) {
        T->root = zs;
        zs->parent = NULL;
    }
    else {
        TND *g = w->parent;
        zs->parent = g;
        if (w == g->lchild) g->lchild = zs;
        else g->rchild = zs;
    }
    putnode(z);
    putnode(w);
    return zs;
}
void removeElement(AVL *T, int k) {// AVL T에서 k값을 갖는 노드 삭제 후 반환
    TND *w = d_treeSearch(T->root, k);

    if (isExternal(w)) { // w가 외부노드이면(즉, 키값이 트리에 존재하지 않으면)
        printf("X\n");
        return;
    }
    int e = w->key;
    TND *z = w->lchild; // w의 자식중 외부노드가 있는지 확인작업
    if (!isExternal(z)) z = w->rchild;
    
    // w의 자식중 외부노드가 있다면 z에 외부노드가 저장되어 있음
    if (isExternal(z)) {
        reduceExternal(z, T); // z와 w를 통째로 날리고 zs를 w에 대체
        printf("%d\n", e);
        return;
    }
    else {
        TND *y = inOrderSucc(w);
        z = y->lchild;
        w->key = y->key;
        reduceExternal(z, T);
        printf("%d\n", e);
    }
}
int isExternal(TND *w) { // node w가 외부노드면 1 반환 아니면 0 반환
    if (w->lchild == NULL && w->rchild == NULL) return 1;
    else return 0;
}
int isInternal(TND *w) {// node w가 외부노드면 0 반환 아니면 1 반환
    if (w->lchild == NULL && w->rchild == NULL) return 0;
    else return 1;
}
TND* inOrderSucc(TND *w) { // 내부노드 w의 부트리 중에서! 중위순회 후계자(내부노드)를 반환
    w = w->rchild;
    if (isExternal(w)) printf("invalid Node Exception\n");
    while(isInternal(w->lchild)) w = w->lchild;
    return w;
}
void expandExternal(TND *w) { // node w 의 외부노드를 expand
    TND *l = (TND *)malloc(sizeof(TND));
    TND *r = (TND *)malloc(sizeof(TND));
    l->lchild = NULL;
    l->rchild = NULL;
    l->parent = w;
    l->height = 0; // 높이 갱신
    r->lchild = NULL;
    r->rchild = NULL;
    r->parent = w;
    r->height = 0; // 높이 갱신
    w->lchild = l;
    w->rchild = r;
}
void initTree(AVL *T) { // AVL T의 외부노드 1개 생성
    TND *root = (TND *)malloc(sizeof(TND));
    root->parent = NULL;
    root->lchild = NULL;
    root->rchild = NULL;
    T->root = root;
    root->height = 0;
}
void printByPreOrder(TND *node) { // node를 root로 삼아 재귀적으로 전위순회 출력
    if (isExternal(node)) return;
    printf(" %d", node->key);
    printByPreOrder(node->lchild);
    printByPreOrder(node->rchild);
}
void freeTree(TND *node) { // T->root의 노드를 받아서 재귀적으로 free(상향식 free)
    if (isExternal(node)) {
        node->parent = NULL;
        free(node);
        return;
    }
    freeTree(node->lchild);
    freeTree(node->rchild);
    node->lchild = NULL;
    node->rchild = NULL;
    node->parent = NULL;
    free(node);
}
int main() {
    char cmd;
    AVL *T = (AVL *)malloc(sizeof(AVL));
    initTree(T);

    while(1) {
        int k;
        scanf("%c", &cmd);
        getchar();

        if (cmd == 'q') break;
        if (cmd == 'i') {
            scanf("%d", &k);
            getchar();
            insertItem(T, k);
        }
        if (cmd == 'd') {
            scanf("%d", &k);
            getchar();
            removeElement(T, k);
        }
        if (cmd == 's') {
            scanf("%d", &k);
            getchar();
            if (isExternal(treeSearch(T->root, k))) printf("X\n");
            else printf("%d\n", treeSearch(T->root, k)->key);
        }
        if (cmd == 'p') {
            printByPreOrder(T->root);
            printf("\n");
        }
    }


    freeTree(T->root);
    free(T);

    return 0;
}