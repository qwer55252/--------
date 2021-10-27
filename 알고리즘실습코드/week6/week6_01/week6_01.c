#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void input_arr(int *arr, int n);
int findElement_index(int *arr, int k, int l, int r);
int rFE(int *arr, int k, int l, int r);

int rFE(int *arr, int k, int l, int r) {
// ��������� l�� r���̿� k���� �۰ų� ����, ���� ����� �ε��� ��ȯ
    int mid;
    if (l>r) return -1;
    if (arr[r]<k) return r;
    mid = (l+r)/2;
    if (k == arr[mid]) return mid; // arr[mid] == k �� ���
    else if (arr[mid-1] <= k && k < arr[mid]) return mid-1; // arr[mid-1] < k < arr[mid]�� ��� -> mid-1 ��ȯ
    else if(arr[mid] < k && k < arr[mid+1]) return mid; // arr[mid] < k < arr[mid+1] -> mid ��ȯ
    // ���� ��ã������ mid�� �������� ����, �������� Ž��
    else if(k > arr[mid]) return rFE(arr, k, mid+1, r); 
    else return rFE(arr, k, l, mid-1); // (k < arr[mid])
}
int findElement_index(int *arr, int k, int l, int r) { 
// �迭 arr���� l �� r ���̿��� Ű������ k�� ���� �ε����� ã���ִ� �Լ�
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