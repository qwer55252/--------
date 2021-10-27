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

void findElement(AVL *T, int k) { // k�� ������ k ��ȯ, ������ ?
    TND *w = treeSearch(T->root, k);
    if (isExternal(w)) printf("X");
    else printf(" %d", w->key);
}
void insertItem(AVL *T, int k) { // AVL T�� k����
    TND *w = treeSearch(T->root, k); // w <- k���� ��ġ�ؾ��� ��� ��ȯ
    if (isInternal(w)) return; // �̹� ������ ����
    else { // �ܺγ���̸� �� �ڸ��� ����
        w->key = k;
        expandExternal(w);
    }
}
TND* treeSearch(TND *v, int k) { // v�� v�� ��Ʈ������ k���� ���� ��� ã�Ƽ� ��ȯ ���� ���ٸ� �־��ٸ� ��ġ�� �ܺγ�� ��ȯ -> �Ŀ� insert �۾��� ���ϰ� �ϱ� ���ؼ�
    if (isExternal(v)) return v;
    if (k == v->key) {
        return v;
    }
    else if (k < v->key) return treeSearch(v->lchild, k);
    else return treeSearch(v->rchild, k);
}
TND* d_treeSearch(TND *v, int k) { // v�� v�� ��Ʈ������ k���� ���� ��� ã�Ƽ� ��ȯ ���� ���ٸ� �־��ٸ� ��ġ�� �ܺγ�� ��ȯ -> �Ŀ� insert �۾��� ���ϰ� �ϱ� ���ؼ�
    // printf("%p ", v);
    // printf("%d %d\n", v->key, k);
    if (isExternal(v)) return v;
    if (k == v->key) {
        return v;
    }
    else if (k < v->key) return d_treeSearch(v->lchild, k);
    else return d_treeSearch(v->rchild, k);
}
int isRoot(TND *w) { // w�� root����̸� 1 ��ȯ �ƴϸ� 0 ��ȯ
    if (w->parent == NULL) return 1;
    else return 0;
}
TND* sibling(TND *w) {// w�� ���� ��带 ��ȯ
    // ������ �ܺγ���� ������ ã�� ���̹Ƿ� �׻� ������ ���� -> �ܺγ���� ������ root�� �� ����
    if (w->parent->lchild == w) return w->parent->rchild; // w�� ���� �ڽ��̾����� w->par->rch ��ȯ
    else return w->parent->lchild; // w�� ������ �ڽ��̾����� w->par->lch ��ȯ
}
void putnode(TND *node) { // node�� ��� ���� ���� free
    node->lchild = NULL;
    node->rchild = NULL;
    node->parent = NULL;
    //free(node);
}
TND* reduceExternal(TND *z, AVL *T) { // �ܺγ�� z�� z->parent�� ��°�� ������ ���ڸ� z�� ���� ���� ��ü�� ��ȯ
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
void removeElement(AVL *T, int k) {// AVL T���� k���� ���� ��� ���� �� ��ȯ
    TND *w = d_treeSearch(T->root, k);

    if (isExternal(w)) { // w�� �ܺγ���̸�(��, Ű���� Ʈ���� �������� ������)
        printf("X\n");
        return;
    }
    int e = w->key;
    TND *z = w->lchild; // w�� �ڽ��� �ܺγ�尡 �ִ��� Ȯ���۾�
    if (!isExternal(z)) z = w->rchild;
    
    // w�� �ڽ��� �ܺγ�尡 �ִٸ� z�� �ܺγ�尡 ����Ǿ� ����
    if (isExternal(z)) {
        reduceExternal(z, T); // z�� w�� ��°�� ������ zs�� w�� ��ü
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
int isExternal(TND *w) { // node w�� �ܺγ��� 1 ��ȯ �ƴϸ� 0 ��ȯ
    if (w->lchild == NULL && w->rchild == NULL) return 1;
    else return 0;
}
int isInternal(TND *w) {// node w�� �ܺγ��� 0 ��ȯ �ƴϸ� 1 ��ȯ
    if (w->lchild == NULL && w->rchild == NULL) return 0;
    else return 1;
}
TND* inOrderSucc(TND *w) { // ���γ�� w�� ��Ʈ�� �߿���! ������ȸ �İ���(���γ��)�� ��ȯ
    w = w->rchild;
    if (isExternal(w)) printf("invalid Node Exception\n");
    while(isInternal(w->lchild)) w = w->lchild;
    return w;
}

void expandExternal(TND *w) { // node w �� �ܺγ�带 expand
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
void initTree(AVL *T) { // AVL T�� �ܺγ�� 1�� ����
    TND *root = (TND *)malloc(sizeof(TND));
    root->parent = NULL;
    root->lchild = NULL;
    root->rchild = NULL;
    T->root = root;
}
void printByPreOrder(TND *node) { // node�� root�� ��� ��������� ������ȸ ���
    if (isExternal(node)) return;
    printf(" %d", node->key);
    printByPreOrder(node->lchild);
    printByPreOrder(node->rchild);
}
void freeTree(TND *node) { // T->root�� ��带 �޾Ƽ� ��������� free(����� free)
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