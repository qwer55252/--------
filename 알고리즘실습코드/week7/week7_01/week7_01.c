#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TreeNode {
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    struct TreeNode *parent;
    int key;
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
void insertItem(AVL *T, int k) { // AVL T에 k삽입
    TND *w = treeSearch(T->root, k); // w <- k값이 위치해야할 노드 반환
    if (isInternal(w)) return; // 이미 있으면 종료
    else { // 외부노드이면 그 자리에 삽입
        w->key = k;
        expandExternal(w);
    }
}
TND* treeSearch(TND *v, int k) { // v나 v의 부트리에서 k값을 갖는 노드 찾아서 반환 만약 없다면 있었다면 위치할 외부노드 반환 -> 후에 insert 작업을 편하게 하기 위해서
    if (isExternal(v)) return v;
    if (k == v->key) {
        return v;
    }
    else if (k < v->key) return treeSearch(v->lchild, k);
    else return treeSearch(v->rchild, k);
}
TND* d_treeSearch(TND *v, int k) { // v나 v의 부트리에서 k값을 갖는 노드 찾아서 반환 만약 없다면 있었다면 위치할 외부노드 반환 -> 후에 insert 작업을 편하게 하기 위해서
    // printf("%p ", v);
    // printf("%d %d\n", v->key, k);
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
    r->lchild = NULL;
    r->rchild = NULL;
    r->parent = w;
    w->lchild = l;
    w->rchild = r;
}
void initTree(AVL *T) { // AVL T의 외부노드 1개 생성
    TND *root = (TND *)malloc(sizeof(TND));
    root->parent = NULL;
    root->lchild = NULL;
    root->rchild = NULL;
    T->root = root;
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