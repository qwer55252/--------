#include <stdio.h>
int H[101]; // 최�???��
int n = 0;
void swap(int idx1, int idx2) {
    int tmp;
    tmp = H[idx1];
    H[idx1] = H[idx2];
    H[idx2] = tmp;
}
void printHeap() {
    int i;
    for (i=1;i<=n;i++) {
        printf(" %d", H[i]);
    }   
    printf("\n");
}
void downHeap(int i) { // ?�� ?�� ?���? i?�� ????��?�� ?���? ?��기에 맞는 ?��치로 ?��?�� ?��?��
    int l_idx, r_idx; // heap_arr[i]?�� leftchild, rightchild
    int larger_idx; // l, r �? ?�� �? ????�� ?�� �??��
    if (2*i>n && 2*i+1>n) return; // l, r 모두 ?���??��?��?���?
    
    l_idx = 2*i; // i ?�� left
    larger_idx = l_idx; // leftchild
    if (2*i+1<=n) { // rightchild�? ?���??��?��?���?
        r_idx = 2*i+1; // i ?�� right
        if (H[r_idx] > H[l_idx]) larger_idx = r_idx; // 
    }
    // max?�� l�? r(?�� ?�� ?���??��?��?���?) �? 최댓�? ????��?��?�� ?��?��
    if (H[larger_idx] < H[i]) return; // ?���? 최�???�� ?��?���? 그�??�?
    swap(larger_idx, i);
    downHeap(larger_idx);
}
// n?��?���??�� ?��?���?면서 downHeap ?��주는 것을 �? ?�� ?��?�� -> ?��?��?�� ?�� ?��?��
void buildHeap() { // ?���??��?��?��?�� ?���? downHeap?���? (비재�??�� 버전)
    int i;
    for (i=n/2;i>=1;i--) {
        downHeap(i);
    }
    return;
}
void rBuildHeap(int i) { // ?��?��?�� ?�� build (?���??�� 버전)
    // i = �?�? ?��?�� 루트 ?��?��?��
    if (i>n) return; 
    // ?��?��?��?�� ?��?���? rBuildHeap!!!!!!!
    rBuildHeap(2*i);
    rBuildHeap(2*i+1);
    downHeap(i);
    return;
}
int main() {
    int i;
    scanf("%d", &n);
    for (i=0;i<n;i++) scanf("%d", &H[i+1]);
    rBuildHeap(1);
    printHeap();
    return 0;
}