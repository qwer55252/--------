#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct PIVOT_INDEXES {
    int a;
    int b;
}PI;
void swap(int *A, int idx1, int idx2) {
    int tmp;
    tmp = A[idx1];
    A[idx1] = A[idx2];
    A[idx2] = tmp;
}
int find_pivot_num(int *A, int l, int r, int p) {
    int cnt =0;
    for (int i=l;i<=r;i++) {
        if (A[i] == p) cnt++;
    } 
    return cnt;
}
PI* inPlacePartition(int *A, int l, int r, int k){ 
    // k번째 인덱스를 pivot 삼아서 (a, b) 반환
    // a : pivot의 시작 인덱스 , b : pivot의 끝 인덱스
    int p; // pivot
    int pivot_num, i, j, cnt=0, m;
    int pivot_start_idx, pivot_end_idx;
    PI *pi = (PI *)malloc(sizeof(PI)); 
    p = A[k];
    pivot_num = find_pivot_num(A, l, r, p);
    j=r;
    while(j >= l && cnt<pivot_num) { // pivot과 같은 것들은 전부 뒤로 빼놓는 과정
        if (A[j] == p) {
            swap(A, r-cnt, j);
            cnt++;
        }
        j--;
    } 
    j = r - pivot_num;
    i = l;
    while(i<=j) {
        // A[i] == p 가 될 수 없음 p와 같은 것들은 뒤로 빼놓음
        while(i<=j && A[i]<p) i++;
        while(i<=j && A[j]>p) j--;
        if(i<j) swap(A, i, j);
    }
    pivot_start_idx = i;
    pivot_end_idx = i + pivot_num -1;
    for (cnt=0;cnt<pivot_num;cnt++) swap(A, i+cnt, r-cnt);
    
    pi->a = pivot_start_idx;    
    pi->b = pivot_end_idx;

    // printf("partition result is :");
    // for (m=l;m<=r;m++) printf(" %d", A[m]);
    // printf("\n");
    return pi;
}
int findPivot(int l, int r) {
    int pivot_idx;
    pivot_idx = rand()%(r+1-l)+l;
    return pivot_idx;
}
void inPlaceQuickSort(int *A, int l, int r) {
    int k; // k : pivot index
    PI *pi = (PI *)malloc(sizeof(PI));
    int pivot_start_idx, pivot_end_idx;
    int a, b;
    if (r <= l) return;
    k = findPivot(l, r); // l과 r 사이의 피벗의 인덱스를 구하는 함수
    // printf("pivot is %d\n", A[k]);
    pi = inPlacePartition(A, l, r, k);
    pivot_start_idx = pi->a;
    pivot_end_idx = pi->b;
    
    inPlaceQuickSort(A, l, pivot_start_idx-1);
    inPlaceQuickSort(A, pivot_end_idx+1, r);
}
int main() {
    int n, i;
    int *arr;
    srand(time(NULL));
    scanf("%d", &n);
    
    arr = (int *)malloc(sizeof(int)*n);
    for (i=0;i<n;i++) scanf("%d", &arr[i]);
    
    
    inPlaceQuickSort(arr, 0, n-1);
    for (i=0;i<n;i++) printf(" %d", arr[i]);
}