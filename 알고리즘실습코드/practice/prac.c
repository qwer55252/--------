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
void initTree(AVL *T);
void expandExternal(TND *w);
TND* treeSearch(TND *v, int k);
int isExternal(TND *w);
void insertItem(AVL *T, int k);
void updateHeight(TND *w);
TND* return_root(TND *w);
void updateHeight_by_postorder(TND *node);
void searchAndFixAfterInsertion(TND *w);
int isBalanced(TND *node);
void restructure(TND *x, TND *y, TND *z);

int isInternal(TND *w) {// node w가 외부노드면 0 반환 아니면 1 반환
    if (w->lchild == NULL && w->rchild == NULL) return 0;
    else return 1;
}
void restructure(TND *x, TND *y, TND *z) {
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
    // printf("x : %p\t", x);
    // printf("y : %p\t", y);
    // printf("z : %p\n", z);
    // printf("a : %p\t", a);
    // printf("b : %p\t", b);
    // printf("c : %p\n", c);
    // 3. z를 루트로 하는 부트리를 b를 루트로하는 부트리로 대체
    if (z->parent == NULL) { // z가 Root 이면
        b->parent = NULL;
    }
    else if(z->parent->lchild == z) { // z가 root가 아니고 부모의 lchild이면
        z->parent->lchild = b;b->parent = z->parent;
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
    

    updateHeight(return_root(b)); 
    return;
}
int isBalanced(TND *node) {
    int difference = node->rchild->height - node->lchild->height;
    if (-2<difference && difference<2) return 1;
    else return 0;
}
void searchAndFixAfterInsertion(TND *w) { // 균형검사를 수행하고 불균형하면 수정하여 AVL형태 유지
    // printf("w : %p\n", w);
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
    printf("x : %d\t", x->height);
    printf("y : %d\t", y->height);
    printf("z : %d\n", z->height);
    
    // 4. x, y, z 개조
    restructure(x, y, z);
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
    printf("%p\t%d\n", node, node->height);
    return;   
}
TND* return_root(TND *w) {
    while(w->parent == NULL) w = w->parent;
    return w;
}
void updateHeight(TND *node) { // 내부노드 w의 높이를 root에서부터 재귀적으로 갱신
    printf("in updateHeight function, node's address is %p", node);
    printf("return_root(node)'s address is %p\n", return_root(node));
    updateHeight_by_postorder(return_root(node));
}
void insertItem(AVL *T, int k) { // AVL T에 k삽입
    printf("T's root : %p\t%d\n",T->root, T->root->height);
    TND *w = treeSearch(T->root, k); // w <- k값이 위치해야할 노드 반환
    printf("w's address is %p\t%d\n", w, w->height);
    if (isInternal(w)) return; // 이미 있으면 종료
    else { // 외부노드이면 그 자리에 삽입
        printf("w is External node\n");
        w->key = k;
        
        expandExternal(w);
        printf("expandExternal is success\n");
        printf("w'lchild's address is %p\n", w->lchild);
        printf("w'rchild's address is %p\n", w->rchild);
        updateHeight_by_postorder(T->root); // 삽입 후 높이 갱신
        printf("updateHeight is success\n");
        printf("w's address is %p \t w's height is %d", w, w->height);
        searchAndFixAfterInsertion(w);// 삽입 후 불균형한지 조사
    }
}
int isExternal(TND *w) { // node w가 외부노드면 1 반환 아니면 0 반환
    if (w->lchild == NULL && w->rchild == NULL) return 1;
    else return 0;
}
TND* treeSearch(TND *v, int k) { // v나 v의 부트리에서 k값을 갖는 노드 찾아서 반환 만약 없다면 있었다면 위치할 외부노드 반환 -> 후에 insert 작업을 편하게 하기 위해서
    printf("in treeSearch node v : %p\t%d\n", v, v->height);
    if (isExternal(v)) {
        printf("%p which is v's address is External node!\n", v);
        return v;
    }
    if (k == v->key) return v;
    else if (k < v->key) return treeSearch(v->lchild, k);
    else return treeSearch(v->rchild, k);
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
            printf("%p\t%d\n", T->root, k);
            insertItem(T, k);
        }
    }

    return 0;
}