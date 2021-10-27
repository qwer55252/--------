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


void findElement(AVL *T, int k) { // k�� ������ k ��ȯ, ������ ?
    TND *w = treeSearch(T->root, k);
    if (isExternal(w)) printf("X");
    else printf(" %d", w->key);
}
void restructure(AVL *T, TND *x, TND *y, TND *z) {
    // 1. x, y, z�� ������ȸ ������ a, b, c�� ����
    // 2, x, y, z�� ��Ʈ������ ������ȸ������ T0, T1, T2, T3�� ����
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
    // 3. z�� ��Ʈ�� �ϴ� ��Ʈ���� b�� ��Ʈ���ϴ� ��Ʈ���� ��ü
    if (z->parent == NULL) { // z�� Root �̸�
        b->parent = NULL;b->lchild=NULL;b->rchild=NULL;//�̷��� T1, T2�� ��������?->�Ⱦ�����
        T->root = b;
        a->rchild = NULL;
    }
    else if(z->parent->lchild == z) { // z�� root�� �ƴϰ� �θ��� lchild�̸�
        b->parent = z->parent;b->lchild=NULL;b->rchild=NULL;
        z->parent->lchild = b;z->parent = NULL;
        
    }
    else { // z�� root�� �ƴϰ�, z->parent->rchild == z
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
void searchAndFixAfterInsertion(AVL *T, TND *w) { // �����˻縦 �����ϰ� �ұ����ϸ� �����Ͽ� AVL���� ����
    // 1. w���� T�� ��Ʈ�� ���� �ö󰡴ٰ� ó�� ������ �ұ��� ��Ʈ�� z�� ����(z�� ������ Return)
    TND *z = w; // z�� ���ϰ� w�� �Ⱥ���
    while(z != NULL) { // w�� root�̱� ���� ����
        if (!isBalanced(z)) break; // z�� �ұ����ϸ� ������
        else z = z->parent; // �������̸� ��� �ö󰣴�
    }
    if (z == NULL) return; // �ұ����� z�� ������ return
    // z���� �ұ����� ��尡 ����Ǿ� �ִ� ����
    // 2. z�� ���� �ڽ��� y�� ����.
    TND *y = z->lchild;
    if (y->height < z->rchild->height) y = z->rchild; 
    // 3. y�� ���� �ڽ��� x�� ����.
    TND *x = y->lchild;
    if (x->height < y->rchild->height) x = y->rchild;
    
    // 4. x, y, z ����
    restructure(T, x, y, z);
    
    return;
}
void updateHeight_by_postorder(TND *node) { // ��Ʈ�� ������ ��������� ���� ����
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
void printAddressByPostOrder(TND *node) { // node�� root�� ��� ��������� ������ȸ ���
    if (isExternal(node)) {
        printf("%p %d\n", node, node->height);
        return;
    }
    printAddressByPostOrder(node->lchild);
    printAddressByPostOrder(node->rchild);
    printf("%p %d\n", node, node->height);
    return;
}
void insertItem(AVL *T, int k) { // AVL T�� k����
    TND *w = treeSearch(T->root, k); // w <- k���� ��ġ�ؾ��� ��� ��ȯ
    if (isInternal(w)) return; // �̹� ������ ����
    else { // �ܺγ���̸� �� �ڸ��� ����
        w->key = k;
        expandExternal(w);
        updateHeight_by_postorder(T->root);
        //printAddressByPostOrder(T->root);
        searchAndFixAfterInsertion(T, w);// ���� �� �ұ������� ����
        updateHeight_by_postorder(T->root);
        //printAddressByPostOrder(T->root);
    }
}
TND* treeSearch(TND *v, int k) { // v�� v�� ��Ʈ������ k���� ���� ��� ã�Ƽ� ��ȯ ���� ���ٸ� �־��ٸ� ��ġ�� �ܺγ�� ��ȯ -> �Ŀ� insert �۾��� ���ϰ� �ϱ� ���ؼ�
    if (isExternal(v)) return v;
    if (k == v->key) return v;
    else if (k < v->key) return treeSearch(v->lchild, k);
    else return treeSearch(v->rchild, k);
}
TND* d_treeSearch(TND *v, int k) { // v�� v�� ��Ʈ������ k���� ���� ��� ã�Ƽ� ��ȯ ���� ���ٸ� �־��ٸ� ��ġ�� �ܺγ�� ��ȯ -> �Ŀ� insert �۾��� ���ϰ� �ϱ� ���ؼ�
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
    l->height = 0; // ���� ����
    r->lchild = NULL;
    r->rchild = NULL;
    r->parent = w;
    r->height = 0; // ���� ����
    w->lchild = l;
    w->rchild = r;
}
void initTree(AVL *T) { // AVL T�� �ܺγ�� 1�� ����
    TND *root = (TND *)malloc(sizeof(TND));
    root->parent = NULL;
    root->lchild = NULL;
    root->rchild = NULL;
    T->root = root;
    root->height = 0;
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