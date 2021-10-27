#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void input_arr(int *arr, int n);
int findElement_index(int *arr, int k, int l, int r);
int rFE(int *arr, int k, int l, int r);

int rFE(int *arr, int k, int l, int r) {
// 재귀적으로 l과 r사이에 k보다 작거나 같은, 가장 가까운 인덱스 반환
    int mid;
    if (l>r) return -1;
    if (arr[r]<k) return r;
    mid = (l+r)/2;
    if (k == arr[mid]) return mid; // arr[mid] == k 인 경우
    else if (arr[mid-1] <= k && k < arr[mid]) return mid-1; // arr[mid-1] < k < arr[mid]인 경우 -> mid-1 반환
    else if(arr[mid] < k && k < arr[mid+1]) return mid; // arr[mid] < k < arr[mid+1] -> mid 반환
    // 아직 못찾았으면 mid를 기준으로 왼쪽, 오른쪽을 탐색
    else if(k > arr[mid]) return rFE(arr, k, mid+1, r); 
    else return rFE(arr, k, l, mid-1); // (k < arr[mid])
}
int findElement_index(int *arr, int k, int l, int r) { 
// 배열 arr에서 l 과 r 사이에서 키값으로 k를 갖는 인덱스를 찾아주는 함수
    return rFE(arr, k, l, r);
}
void input_arr(int *arr, int n){
    for (int i=0;i<n;i++) scanf("%d", &arr[i]);
}
void print_arr(int *arr, int n) {
    for (int i=0;i<n;i++) printf(" %d", arr[i]);
    printf("\n");
}
int main() {
    int n, k;
    int *arr;
    scanf("%d %d", &n, &k);
    arr = (int *)malloc(sizeof(int)*n);
    input_arr(arr, n);
    printf(" %d", findElement_index(arr, k, 0, n-1));
}