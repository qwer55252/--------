#include <stdio.h>
void downHeap(int i, int last);
void upHeap(int i);
void buildHeap();
int n=0; // 리스트 또는 힙의 크기
int H[101]; // Heap
void swap(int idx1, int idx2) {
    int tmp;
    tmp = H[idx1];
    H[idx1] = H[idx2];
    H[idx2] = tmp;
}
void inPlaceHeapSort() {
// n 개의 키로 구성된 무순배열(H)을 제자리 힙 정렬
    int i;
    
    for (i=n;i>=2;i--) {
        swap(1, i);
        downHeap(1, i-1);
    }
    return;
}
void printArray() {
// H 출력
    int i;
    for (i=1;i<=n;i++) {
        printf(" %d", H[i]);
    }
}
void downHeap(int i, int last) {
// 힙 내 위치 i에 저장된 키를 크기에 맞는 위치로 하향 이동
    int larger_idx;
    int left = 2*i;
    int right = 2*i+1;
    // 종료 조건
    if (left>last) return; // i 의 l, r 모두 없으면 return
    larger_idx = left;
    if (2*i+1<=last) { // i의 r이 존재하면
        if (H[right]>H[larger_idx]) { // i의 l과 r 비교
            larger_idx = right;
        }
    }
    if (H[i] >= H[larger_idx]) return; // 이미 최대힙 상태이면 return
    swap(i, larger_idx);
    downHeap(larger_idx, last);
}
void insertItem(int key) {
// n 위치에 key 삽입, upHeap(n) 호출 수행 후 n(총 키 개수)을 갱신
    n++;
    H[n] = key;
    upHeap(n);
}
void upHeap(int i) {
// 힙 내 위치 i에 저장된 키를 크기에 맞는 위치로 상향 이동
    if (i==1) return;
    if (H[i/2] > H[i]) return;
    swap(i/2, i);
    upHeap(i/2);
}
void rBuildHeap(int i) { 
// 재귀 방식으로 상향식 힙 생성, i : 부분 힙의 루트 인덱스

}
void buildHeap() {
// 비재귀 방식으로 상향식 힙 생성
    int i;
    for (i=n/2;i>=1;i--) {
        downHeap(i, n);
    }
    return;
}

int main() {
// 초기 리스트에 대해 힙 정렬의 1단계, 2단계 작업을 수행하여 정렬 리스트를 인쇄하고 종료
    
    int i;

    scanf("%d", &n);
    for (i=1;i<=n;i++) scanf("%d", &H[i]);
    buildHeap(); // 1기
    inPlaceHeapSort(); // 2기
    printArray();
}