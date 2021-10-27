#include <stdio.h>
int H[101]; // ìµœë???™
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
void downHeap(int i) { // ?™ ?‚´ ?œ„ì¹? i?— ????¥?œ ?‚¤ë¥? ?¬ê¸°ì— ë§ëŠ” ?œ„ì¹˜ë¡œ ?•˜?–¥ ?´?™
    int l_idx, r_idx; // heap_arr[i]?˜ leftchild, rightchild
    int larger_idx; // l, r ì¤? ?° ê²? ????¥ ?•  ë³??ˆ˜
    if (2*i>n && 2*i+1>n) return; // l, r ëª¨ë‘ ?™¸ë¶??…¸?“œ?´ë©?
    
    l_idx = 2*i; // i ?˜ left
    larger_idx = l_idx; // leftchild
    if (2*i+1<=n) { // rightchildê°? ?‚´ë¶??…¸?“œ?´ë©?
        r_idx = 2*i+1; // i ?˜ right
        if (H[r_idx] > H[l_idx]) larger_idx = r_idx; // 
    }
    // max?— lê³? r(?‘˜ ?‹¤ ?‚´ë¶??…¸?“œ?´ë©?) ì¤? ìµœëŒ“ê°? ????¥?˜?–´ ?ˆ?Œ
    if (H[larger_idx] < H[i]) return; // ?´ë¯? ìµœë???™ ?ƒ?ƒœë©? ê·¸ë??ë¡?
    swap(larger_idx, i);
    downHeap(larger_idx);
}
// n?—?„œë¶??„° ?˜¬?¼ê°?ë©´ì„œ downHeap ?•´ì£¼ëŠ” ê²ƒì„ ë³? ?ˆ˜ ?ˆ?Œ -> ?ƒ?–¥?‹ ?™ ?ƒ?„±
void buildHeap() { // ?‚´ë¶??…¸?“œ?“¤?„ ? „ë¶? downHeap?•´ì¤? (ë¹„ì¬ê·??  ë²„ì „)
    int i;
    for (i=n/2;i>=1;i--) {
        downHeap(i);
    }
    return;
}
void rBuildHeap(int i) { // ?ƒ?–¥?‹ ?™ build (?¬ê·??  ë²„ì „)
    // i = ë¶?ë¶? ?™?˜ ë£¨íŠ¸ ?¸?±?Š¤
    if (i>n) return; 
    // ?›„?œ„?ˆœ?œ„ ?ˆœ?œ¼ë¡? rBuildHeap!!!!!!!
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