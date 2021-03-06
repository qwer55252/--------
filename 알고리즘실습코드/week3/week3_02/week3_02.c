#include <stdio.h>
int H[101]; // μ΅λ???
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
void downHeap(int i) { // ? ?΄ ?μΉ? i? ????₯? ?€λ₯? ?¬κΈ°μ λ§λ ?μΉλ‘ ??₯ ?΄?
    int l_idx, r_idx; // heap_arr[i]? leftchild, rightchild
    int larger_idx; // l, r μ€? ?° κ²? ????₯ ?  λ³??
    if (2*i>n && 2*i+1>n) return; // l, r λͺ¨λ ?ΈλΆ??Έ??΄λ©?
    
    l_idx = 2*i; // i ? left
    larger_idx = l_idx; // leftchild
    if (2*i+1<=n) { // rightchildκ°? ?΄λΆ??Έ??΄λ©?
        r_idx = 2*i+1; // i ? right
        if (H[r_idx] > H[l_idx]) larger_idx = r_idx; // 
    }
    // max? lκ³? r(? ?€ ?΄λΆ??Έ??΄λ©?) μ€? μ΅λκ°? ????₯??΄ ??
    if (H[larger_idx] < H[i]) return; // ?΄λ―? μ΅λ??? ??λ©? κ·Έλ??λ‘?
    swap(larger_idx, i);
    downHeap(larger_idx);
}
// n??λΆ??° ?¬?Όκ°?λ©΄μ downHeap ?΄μ£Όλ κ²μ λ³? ? ?? -> ??₯? ? ??±
void buildHeap() { // ?΄λΆ??Έ??€? ? λΆ? downHeap?΄μ€? (λΉμ¬κ·??  λ²μ )
    int i;
    for (i=n/2;i>=1;i--) {
        downHeap(i);
    }
    return;
}
void rBuildHeap(int i) { // ??₯? ? build (?¬κ·??  λ²μ )
    // i = λΆ?λΆ? ?? λ£¨νΈ ?Έ?±?€
    if (i>n) return; 
    // ???? ??Όλ‘? rBuildHeap!!!!!!!
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