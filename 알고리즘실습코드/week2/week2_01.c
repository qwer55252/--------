#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void print_arr(int *arr, int size);
void swap(int *arr, int idx1, int idx2) { //arr 배열의 idx1과 idx2자리에 있는 원소들을 swap
    int tmp;
    tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;
}
void inPlaceSelectionSort(int *arr, int n) {
    int pass, j, minLoc;

    for (pass=0;pass<n-1;pass++) {
        minLoc = pass;
        for (j=pass+1;j<n;j++) {
            if(arr[j] < arr[minLoc]) {
                minLoc = j;
            }
        }
        swap(arr, pass, minLoc);
        print_arr(arr, n);
    }

}
void print_arr(int *arr, int size) {
    int i;
    for (i=0;i<size;i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");
}
int main() {

    int n, i;
    int *arr;
    int max, max_idx, tmp;

    //scanf("%d", &n);
    n=8;
    
    arr = (int *)malloc(sizeof(int)*n);
    
    //for (i=0;i<n;i++) scanf("%d", &arr[i]); // 입력
    arr[0] = 32; arr[1] = 51; arr[2] = 11; arr[3] = 75; arr[4] = 54; arr[5] = 83; arr[6] = 77; arr[7] = 59; // 입력

    inPlaceSelectionSort(arr, n);

    print_arr(arr, n);

    return 0;
}