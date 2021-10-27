#include <stdio.h>
int heap_arr[100]; // 최대힙
int n=0;
void downHeap(int i);
void swap(int idx1, int idx2) {
    int tmp;
    tmp = heap_arr[idx1];
    heap_arr[idx1] = heap_arr[idx2];
    heap_arr[idx2] = tmp;
}
int removeMax() { // downHeap 호출 수행 후 n을 갱신
    int max;
    if(n<=0 || n>100) return 0;
    max = heap_arr[1];
    heap_arr[1] = heap_arr[n];
    n--;
    downHeap(1);
    
    return max;
}
void upHeap(int i) { // 힙 내 위치 i에 저장된 키를 크기에 맞는 위치로 상향 이동
    int tmp;
    // 종료 조건
    if (i==1) return; // 루트이면 오릴 곳이 없으므로 종료 
    // 루트가 아니므로 parent 존재
    if (heap_arr[i/2] >= heap_arr[i]) return; // 이미 최대힙 상태이면 종료
    
    // 큰게 아래 있으면 위로 올려줌
    swap(i, i/2);
   
    upHeap(i/2); // upHeap 된 상태에서 똑같이 적용
}
void downHeap(int i) { // 힙 내 위치 i에 저장된 키를 크기에 맞는 위치로 하향 이동
    int l_idx, r_idx; // heap_arr[i]의 leftchild, rightchild
    int larger_idx; // l, r 중 큰 것 저장 할 변수
    if (2*i>n && 2*i+1>n) return; // l, r 모두 외부노드이면
    
    l_idx = 2*i; // i 의 left
    larger_idx = l_idx; // leftchild
    if (2*i+1<=n) { // rightchild가 내부노드이면
        r_idx = 2*i+1; // i 의 right
        if (heap_arr[r_idx] > heap_arr[l_idx]) larger_idx = r_idx; // 
    }
    // max에 l과 r(둘 다 내부노드이면) 중 최댓값 저장되어 있음
    if (heap_arr[larger_idx] < heap_arr[i]) return; // 이미 최대힙 상태면 그대로
    swap(larger_idx, i);
    downHeap(larger_idx);
}
void insertItem(int key) {
    n++;
    heap_arr[n] = key;
    upHeap(n);
    printf("0\n");
}
void printHeap() {
    int i;
    for (i=1;i<=n;i++) {
        printf(" %d", heap_arr[i]);
    }   
    printf("\n");
}
int main() {
    int i;
    int key;    
    char cmd;

    scanf("%c", &cmd);
    getchar();
    while(cmd != 'q') {
        if (cmd == 'i') {
            scanf("%d", &key);
            getchar();
            insertItem(key);

        }
        if(cmd == 'd') {
            printf("%d\n", removeMax());
            
        }
        if(cmd == 'p') {
            printHeap();
        }

        scanf("%c", &cmd);
        getchar();
    }

    
    return 0;
}