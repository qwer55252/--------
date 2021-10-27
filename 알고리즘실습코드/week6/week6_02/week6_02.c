#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void input_arr(int *arr, int n);

void input_arr(int *arr, int n){
    for (int i=0;i<n;i++) scanf("%d", &arr[i]);
}
void print_arr(int *arr, int n) {
    for (int i=0;i<n;i++) printf(" %d", arr[i]);
    printf("\n");
}
int findIndex(int *arr, int k, int n) {
// k 값과 오른쪽에서 가장 가까운 인덱스 반환
    int mid, l, r;
    l=0;
    r = n-1;
    mid = (l+r)/2;
    if (k < arr[l]) return 0;
    if (arr[r]<k) return n;
    while (1) {
        if (arr[mid-1] < k && k <= arr[mid]) return mid;
        else if (arr[mid] < k && k <= arr[mid+1]) return mid+1;
        else if (k < arr[mid]) {
            r = mid-1;
            mid = (l+r)/2;
        }
        else {
            l = mid+1;
            mid = (l+r)/2;
        }
    }

    //return n;
}
int main() {
    int n, k;
    int *arr;
    scanf("%d %d", &n, &k);
    arr = (int *)malloc(sizeof(int)*n);
    input_arr(arr, n);
    printf(" %d", findIndex(arr, k, n));
    free(arr);
}