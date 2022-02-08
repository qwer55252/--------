#include <stdio.h>
#include <stdlib.h>

typedef struct BUCKET{
    struct BUCKET *next;
    int value;
}BC;

int hashfunc(int key, int M) { // return key%M
    return key%M;
}
void insertItem(BC *bc_list, int key, int M) {
    int h = hashfunc(key, M);
    BC *new_bucket = (BC *)malloc(sizeof(BC));
    new_bucket->value = key;
    // 해당 버켓이 비어있으면
    if ((bc_list + h)->next == NULL) {
        (bc_list + h)->next = new_bucket;
        new_bucket->next = NULL;
        
    }
    // 해당 버켓에 충돌이 일어나면
    else if ((bc_list + h)->next != NULL) {
        new_bucket->next = (bc_list + h)->next;
        (bc_list + h)->next = new_bucket;
    }
}
void init_BC(BC *bc_list, int M) { // 버켓리스트의 next는 NULL, value는 0으로 초기화
    for (int i=0;i<M;i++){
        (bc_list + i)->next = NULL;
        (bc_list + i)->value = 0;
    }
}
void searchItem(BC *bc_list, int key, int M) {
    int h = hashfunc(key, M);
    int cnt=0;
    BC *curr = (bc_list+h); // 괜찮나? 나중에 확인
    while(curr->next != NULL) {        
        curr = curr->next;
        cnt++;
        if (curr->value == key) {
            printf("%d\n", cnt);
            return;
        }
    }
    printf("0\n");
    return;
}
void removeItem(BC *bc_list, int key, int M) { // bc_list에서 key 삭제, 삭제하면 1, 안하면 0;
    int h = hashfunc(key, M);
    int cnt=0;
    BC *curr = (bc_list+h);
    while(curr->next != NULL) { // curr->next가 NULL일때도 curr = curr->next가 작동할까?
        cnt++;
        if (curr->next->value == key)  { // remove 할 노드 찾았으면
            BC *remove_tmp = curr->next;
            curr->next = curr->next->next;
            remove_tmp->next = NULL;
            free(remove_tmp);
            printf("%d\n", cnt);
            return;
        }
        curr = curr->next;
    }
    printf("0\n");
}
void printHashTable(BC *bc_list, int M) {
    // BC *curr = (bc_list+2);
    // printf("%p\t%p\t%p\t%p\n", curr, curr->next,curr->next->next, curr->next->next->next);
    // printf("%d\t%d\t%d\t%d\n", curr->value, curr->next->value,curr->next->next->value, curr->next->next->next->value);
    for (int i=0;i<M;i++) {
        BC *curr = (bc_list+i);
        while(curr->next != NULL && curr!=NULL) {
            printf(" %d", curr->next->value);
            curr=curr->next;
        }
    }
    printf("\n");
}
void freehashtable(BC *bc_list, int M) {
    for (int i=0;i<M;i++) {
        if ((bc_list + i)->next !=NULL) {
            BC *curr = (bc_list + i)->next;
            (bc_list + i)->next = NULL;
            BC *prev;
            while(curr->next != NULL) {
                prev = curr;
                curr = curr->next;
                prev->next = NULL;
                free(prev);
            }
            free(curr);
        }
    }
    free(bc_list);
}
int main() {
    int M, key;
    char cmd;
    scanf("%d", &M);
    getchar();
    BC *bc_list = (BC *)malloc(sizeof(BC)*M);
    init_BC(bc_list, M);

    while(1) {
        scanf("%c", &cmd);
        getchar();
        if (cmd == 'i') {
            scanf("%d", &key);
            getchar();
            insertItem(bc_list, key, M);
        }
        if (cmd == 's') {
            scanf("%d", &key);
            getchar();
            searchItem(bc_list, key, M);
        }
        if (cmd == 'd') {
            scanf("%d", &key);
            getchar();
            removeItem(bc_list, key, M);
        }
        if (cmd == 'p') {
            printHashTable(bc_list, M);
        }
        if (cmd == 'e') break;
        
    }

    freehashtable(bc_list, M);

}