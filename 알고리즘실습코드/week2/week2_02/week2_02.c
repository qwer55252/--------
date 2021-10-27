#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void print_arr(int *arr, int size) {
    int i;
    for (i=0;i<size;i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");
}
void insertion_sort(int *arr, int n) { // size = arr사이즈
    int pass, save, j;
    for (pass=1;pass<n;pass++) {
        save = arr[pass];
        j = pass-1;
        while(j>=0 && arr[j]>save) {
            arr[j+1] = arr[j];
            j=j-1;
        }
        arr[j+1] = save;
    }
}
int main() {
    int n, i;
    int *arr;

    scanf("%d", &n);

    arr = (int *)malloc(sizeof(int)*n);
    for (i=0;i<n;i++) scanf("%d", &arr[i]);

    insertion_sort(arr, n);
    print_arr(arr, n);

    free(arr);

    return 0;
}