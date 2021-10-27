#include <stdio.h>
#include <stdlib.h>
typedef struct NODE {
    struct NODE *left;
    struct NODE *right;
    struct NODE *parent;
    struct NODE *last;
    int data;
}ND;
typedef struct QUEUE{
    
}Q;

void enQueue(Q *q, ND *v) {

}
int main() {
    Q q = (Q *)malloc(sizeof(Q));

}