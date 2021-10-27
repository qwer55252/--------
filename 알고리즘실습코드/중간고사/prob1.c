#include <stdio.h>
#include <stdlib.h>


void merge(int *A, int l, int m, int r) {//두 배열 A1, A2를 머지하는 과정
    int i = l;
    int k = l;
    int j = m+1;
    int *B = (int *)malloc(sizeof(int)*r);
    while(i<=m && j<=r) {
        if (A[i] > A[j]) B[k++] = A[i++];
        else B[k++] = A[j++];
    }
    while(i<=m) B[k++] = A[i++];
    while(j<=r) B[k++] = A[j++];
    
    for (i=l;i<=r;i++) A[i] = B[i];
    free(B);
}
void mergeSort(int *arr, int l, int r) { // arr(l~r)를 반으로 나눠서 머지소트
    int m = (l+r)/2;
    if (l < r) {
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
int main() {
    int N;
    int *arr;
    
    scanf("%d", &N);
    
    arr = (int *)malloc(sizeof(int)*N);
    for (int i=0;i<N;i++) scanf("%d", &arr[i]);
    
    
    mergeSort(arr, 0, N-1);
    for (int i=0;i<N;i++) printf(" %d", arr[i]);

    
}