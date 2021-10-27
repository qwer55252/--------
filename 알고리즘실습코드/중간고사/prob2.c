#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NODE{ 
    struct NODE *leftchild;
    struct NODE *rightchild;
    struct NODE *parent;
    int data;
}ND;
typedef struct TREE{
    struct NODE *root;
    int size;
}TR;

// void print_by_preorder() {

//     printf("%d ", )
// }
void expandExternal(ND *z) { // 외부노드 z를 확장시키줌
    ND *l = (ND *)malloc(sizeof(ND));
    ND *r = (ND *)malloc(sizeof(ND));
    l->leftchild = NULL;
    l->rightchild = NULL;
    l->parent = z;
    r->leftchild = NULL;
    r->rightchild = NULL;
    r->parent = z;
    z->leftchild = l;
    z->rightchild = r;
}
void init_tree(TR *T) { // 초키 트리 루트 만들어줌
    ND *root = (ND *)malloc(sizeof(ND));
    root->parent = NULL;
    root->leftchild = NULL;
    root->rightchild = NULL;
    T->root = root;
    T->size = 0;
}
int isExternal(ND *node) {// 외부노드면 1 반환
    if (node->leftchild == NULL && node->rightchild == NULL) return 1;
    else return 0; 
}
ND* search(ND *w, int key) { // key값을 갖는 노드 반환 혹은 key가 들어가야 할 노드 반환
    // 종료 조건
    if(isExternal(w)) return w; 
    if(w->data == key) return w;
    if(w->data < key) return search(w->rightchild, key);
    else return search(w->leftchild, key);
    
}
void insertItem(TR *T, int item) {//트리에 item삽입
    ND *w = search(T->root, item);
    w->data = item;
    expandExternal(w);
}
void print_by_preorder(ND *node) {
    if (isExternal(node)) return;
    printf("%d ", node->data);
    print_by_preorder(node->leftchild);
    print_by_preorder(node->rightchild);
}
int main() {
    int N;
    int *arr;
    scanf("%d", &N);
    //N = 6;
    arr = (int *)malloc(sizeof(int)*N);
    for (int i=0;i<N;i++) scanf("%d", &arr[i]);
    //arr[0]=3;arr[1]=7;arr[2]=8;arr[3]=6;arr[4]=2;arr[5]=5;

    TR *T = (TR *)malloc(sizeof(TR));
    init_tree(T);
    expandExternal(T->root);
    T->root->data = arr[0];
    for (int i=1;i<N;i++) {
        insertItem(T, arr[i]);

    }
    print_by_preorder(T->root);
    
    
}