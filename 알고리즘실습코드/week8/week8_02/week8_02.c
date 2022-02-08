#include <stdio.h>
#include <stdlib.h>
int hashfunc(int M, int key);

void insertItem(int *hashtable, int key, int M) { // �ؽ����̺� key�� �����ϴ� �Լ�
    int h = hashfunc(key, M);
    while(hashtable[h]!=0) { // ������� ������(�浹�� �Ͼ��)
        printf("C");
        h = (h+1)%M;
    } // C����ϰ� ������� ������ h �ּ� 1 ����, ���� M���� ũ�ų� �������� �ٽ� 0����
    hashtable[h]=key;
    printf("%d\n", h);
 }
int hashfunc(int key, int M) {
    int h = key % M;
    return h;
}
void init_list(int *arr, int M) {
    for (int i=0;i<M;i++) arr[i]=0;// �³�?
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
int main() {
    int M, n, key, cnt=0;
    int *hashtable;
    char cmd;
    scanf("%d %d", &M, &n);
    getchar();
    hashtable = (int *)malloc(sizeof(int)*M);
    while(1) {
        scanf("%c", &cmd);
        getchar();
        if (cmd == 'i' && cnt<n) {
            scanf("%d", &key);
            getchar();
            insertItem(hashtable, key, M);
            cnt++;
        }
        if (cmd == 's') {
            scanf("%d", &key);
            getchar();
            searchItem(hashtable, key, M);
        }
        if (cmd == 'e') break;
      }
    free(hashtable);
    return 0;
}