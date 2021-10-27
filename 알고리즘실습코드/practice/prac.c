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

int isInternal(TND *w) {// node w�� �ܺγ��� 0 ��ȯ �ƴϸ� 1 ��ȯ
    if (w->lchild == NULL && w->rchild == NULL) return 0;
    else return 1;
}
void restructure(TND *x, TND *y, TND *z) {
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
    // printf("x : %p\t", x);
    // printf("y : %p\t", y);
    // printf("z : %p\n", z);
    // printf("a : %p\t", a);
    // printf("b : %p\t", b);
    // printf("c : %p\n", c);
    // 3. z�� ��Ʈ�� �ϴ� ��Ʈ���� b�� ��Ʈ���ϴ� ��Ʈ���� ��ü
    if (z->parent == NULL) { // z�� Root �̸�
        b->parent = NULL;
    }
    else if(z->parent->lchild == z) { // z�� root�� �ƴϰ� �θ��� lchild�̸�
        z->parent->lchild = b;b->parent = z->parent;
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
    

    updateHeight(return_root(b)); 
    return;
}
int isBalanced(TND *node) {
    int difference = node->rchild->height - node->lchild->height;
    if (-2<difference && difference<2) return 1;
    else return 0;
}
void searchAndFixAfterInsertion(TND *w) { // �����˻縦 �����ϰ� �ұ����ϸ� �����Ͽ� AVL���� ����
    // printf("w : %p\n", w);
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
    printf("x : %d\t", x->height);
    printf("y : %d\t", y->height);
    printf("z : %d\n", z->height);
    
    // 4. x, y, z ����
    restructure(x, y, z);
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
    printf("%p\t%d\n", node, node->height);
    return;   
}
TND* return_root(TND *w) {
    while(w->parent == NULL) w = w->parent;
    return w;
}
void updateHeight(TND *node) { // ���γ�� w�� ���̸� root�������� ��������� ����
    printf("in updateHeight function, node's address is %p", node);
    printf("return_root(node)'s address is %p\n", return_root(node));
    updateHeight_by_postorder(return_root(node));
}
void insertItem(AVL *T, int k) { // AVL T�� k����
    printf("T's root : %p\t%d\n",T->root, T->root->height);
    TND *w = treeSearch(T->root, k); // w <- k���� ��ġ�ؾ��� ��� ��ȯ
    printf("w's address is %p\t%d\n", w, w->height);
    if (isInternal(w)) return; // �̹� ������ ����
    else { // �ܺγ���̸� �� �ڸ��� ����
        printf("w is External node\n");
        w->key = k;
        
        expandExternal(w);
        printf("expandExternal is success\n");
        printf("w'lchild's address is %p\n", w->lchild);
        printf("w'rchild's address is %p\n", w->rchild);
        updateHeight_by_postorder(T->root); // ���� �� ���� ����
        printf("updateHeight is success\n");
        printf("w's address is %p \t w's height is %d", w, w->height);
        searchAndFixAfterInsertion(w);// ���� �� �ұ������� ����
    }
}
int isExternal(TND *w) { // node w�� �ܺγ��� 1 ��ȯ �ƴϸ� 0 ��ȯ
    if (w->lchild == NULL && w->rchild == NULL) return 1;
    else return 0;
}
TND* treeSearch(TND *v, int k) { // v�� v�� ��Ʈ������ k���� ���� ��� ã�Ƽ� ��ȯ ���� ���ٸ� �־��ٸ� ��ġ�� �ܺγ�� ��ȯ -> �Ŀ� insert �۾��� ���ϰ� �ϱ� ���ؼ�
    printf("in treeSearch node v : %p\t%d\n", v, v->height);
    if (isExternal(v)) {
        printf("%p which is v's address is External node!\n", v);
        return v;
    }
    if (k == v->key) return v;
    else if (k < v->key) return treeSearch(v->lchild, k);
    else return treeSearch(v->rchild, k);
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