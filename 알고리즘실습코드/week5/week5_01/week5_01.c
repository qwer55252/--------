#include <stdio.h>
#include <stdlib.h>

typedef struct NODE{
    int data;
    struct NODE *next;
}ND;
typedef struct singlyLinkedList{
    struct NODE *head;
    struct NODE *tail;
    int len;
}sLL;
typedef struct PartitionStorage{
    struct singlyLinkedList *L1;
    struct singlyLinkedList *L2;
}PS;
void listFree(sLL *L);
PS* partition_func(sLL *L, int k);
void init_sLL(sLL *list);
sLL* mergeSort(sLL *L);
int get(sLL *L);
int removeFirst(sLL *L);
void addLast(sLL *L, int data);
sLL* merge(sLL *L1, sLL *L2);
sLL* input_sLL(sLL *L, int n);
void print_sLL(sLL *L, int n);
void Clear(sLL *L);

void listFree(sLL *L) {
    ND *tmp;
    while(L->head != NULL) {
        tmp = L->head;
        L->head = L->head->next;
        free(tmp);
        tmp = NULL;
    }
}
// 구조체 포인터를 반환할땐 구조체_변수* 선언!
PS* partition_func(sLL *L, int k) { 
// input : partition할 단일연결리스트 L, output : PS변수(partition_func 된 L1(len:k), L2(len:|L|-k) 저장되어있음)
    PS *ps = (PS *)malloc(sizeof(PS));
    ND *curr;
    curr = L->head;
    // L1 
    sLL *L1 = (sLL *)malloc(sizeof(sLL));
    init_sLL(L1);
    L1->head->next = NULL;
    L1->head = L->head;
    for (int i=0;i<k;i++) curr = curr->next;

    // L2
    sLL *L2 = (sLL *)malloc(sizeof(sLL));
    init_sLL(L2);
    //free(L2->tail);
    L2->head->next = curr->next;
    curr->next = L1->tail;
    
    L1->len = k;
    L2->len = L->len-k;
    
    ps->L1 = L1;
    ps->L2 = L2;
    return ps;
}
void init_sLL(sLL *L) { // input : sLL 객체, output : init된 sLL객체
    // head, tail 생성
    ND *head = (ND *)malloc(sizeof(ND));
    L->head = head;
    ND *tail = (ND *)malloc(sizeof(ND));
    L->tail = tail;
    tail->next = NULL;
    // head, tail 단일 연결
    L->head->next = tail;
    L->len = 0;
}
sLL* mergeSort(sLL *L){ // input : sLL 객체 L, output : 오름차순으로 정렬된 sLL객체 L
    PS *complete_ps = (PS *)malloc(sizeof(PS));
    sLL *L1 = (sLL *)malloc(sizeof(sLL));
    sLL *L2 = (sLL *)malloc(sizeof(sLL));

    if (L->len>1) {// if(L.list_len>1)
        complete_ps = partition_func(L, L->len/2);// L1, L2 <- partition(L)
        L1 = complete_ps->L1;
        L2 = complete_ps->L2;
        L1 = mergeSort(L1);
        L2 = mergeSort(L2);
        L = merge(L1, L2);
    }

    free(complete_ps->L1);
    free(complete_ps->L2);
    free(complete_ps);
    //Clear(L1);
    //Clear(L2);
    return L;
}
int get(sLL *L) {
    if (L->len > 0) return L->head->next->data;
    else {
        printf("there is no element, L->len <= 0\n");
        return 0;
    }
}
int removeFirst(sLL *L) {
    int output;
    if (L->len<1) {
        printf("there is no data\n");
        return 0;
    }
    output = L->head->next->data;
    L->head->next = L->head->next->next;
    L->len--;
    return output;
}
void addLast(sLL *L, int data) {
    ND *curr = (ND *)malloc(sizeof(ND));
    ND *newNode = (ND *)malloc(sizeof(ND));
    newNode->data = data;
    curr = L->head;
    for (int i=0;i<L->len;i++) curr = curr->next;
    curr->next = newNode;
    newNode->next = L->tail;
    L->len++;
}
sLL* merge(sLL *L1, sLL *L2) {
    sLL *mergedList = (sLL *)malloc(sizeof(sLL));
    init_sLL(mergedList);// 1. L <- empty list (mergedList 선언, 초기화)
    
    while(L1->len>0 && L2->len>0) {// 2. 둘 다 비어있지 않으면(둘중 하나가 비어있을 때까지)
        if (get(L1)<=get(L2)) addLast(mergedList, removeFirst(L1));
        else addLast(mergedList, removeFirst(L2));
    }
    while(L1->len>0) addLast(mergedList, removeFirst(L1)); // 3. L1이 비어있지 않으면
    while(L2->len>0) addLast(mergedList, removeFirst(L2)); // 4. L2가 비어있지 않으면
    Clear(L1);
    Clear(L2);
    return mergedList;
}
sLL* input_sLL(sLL *L, int n) {
    int data;
    for (int i=n;i>=1;i--) {
        scanf("%d", &data);
        addLast(L, data);
    }
    return L;
}
void print_sLL(sLL *L, int n) {
    ND *curr = (ND *)malloc(sizeof(ND));
    curr = L->head;
    for (int i=0;i<n;i++) {
        curr = curr->next;
        printf(" %d", curr->data);
    }
    printf("\n");
}
void Clear(sLL *L) {
    ND *prev = NULL;
    ND *seek = L->head;
    while(seek){
        prev=seek;
        seek=seek->next;
        free(prev);
    }
    L = NULL;
}
int main() {
    int n;
    scanf("%d", &n);
    sLL *sLL1 = (sLL *)malloc(sizeof(sLL));
    init_sLL(sLL1);
    sLL1 = input_sLL(sLL1, n);
    sLL1 = mergeSort(sLL1);
    print_sLL(sLL1, n);
    Clear(sLL1);
}