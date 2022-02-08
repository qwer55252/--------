#include <stdio.h>
#include <stdlib.h>
int hashfunc(int M, int key);
int hashfunc1(int key, int M, int q);
void insertItem(int *hashtable, int key, int M, int q) { // 해시테이블에 key값 삽입하는 함수
    int h = hashfunc(key, M);
    while(hashtable[h]!=0) { // 비어있지 않으면(충돌이 일어나면)
        printf("C");
        int h1 = hashfunc1(key ,M, q);
        h = (h + h1)%M;
    } // C출력하고 비어있을 때까지 h 주소 1 증가, 만약 M보다 크거나 같아지면 다시 0으로
    hashtable[h]=key;
    printf("%d\n", h);
 }
int hashfunc(int key, int M) {
    int h = key % M;
    return h;
}
int hashfunc1(int key, int M, int q) {
    int h = q - (key%q);
    return h;
}
void init_list(int *arr, int M) {
    for (int i=0;i<M;i++) arr[i]=0;// 맞나?
} 
void searchItem(int *arr, int key, int M) {
    for (int i=0;i<M;i++) {
        if (arr[i] == key) {
            printf("%d %d\n", i, key);
            return;
        }
    }
    printf("-1\n");
    return;
}
void printHashTable(int *hashtable, int M) {
    for (int i=0;i<M;i++) printf(" %d", hashtable[i]);
    printf("\n");
}
int main() {
    int M, n, q, key, cnt=0;
    int *hashtable;
    char cmd;
    scanf("%d %d %d", &M, &n, &q);
    getchar();
    hashtable = (int *)malloc(sizeof(int)*M);
    while(1) {
        scanf("%c", &cmd);
        getchar();
        if (cmd == 'i' && cnt<n) {
            scanf("%d", &key);
            getchar();
            insertItem(hashtable, key, M, q);
            cnt++;
        }
        if (cmd == 's') {
            scanf("%d", &key);
            getchar();
            searchItem(hashtable, key, M);
        }
        if (cmd == 'p') {
            printHashTable(hashtable, M);
        }
        if (cmd == 'e') {
            printHashTable(hashtable, M);
            break;
        }
      }
    free(hashtable);
    return 0;
}