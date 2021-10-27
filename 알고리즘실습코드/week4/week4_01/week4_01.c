#include <stdio.h>
void downHeap(int i, int last);
void upHeap(int i);
void buildHeap();
int n=0; // ����Ʈ �Ǵ� ���� ũ��
int H[101]; // Heap
void swap(int idx1, int idx2) {
    int tmp;
    tmp = H[idx1];
    H[idx1] = H[idx2];
    H[idx2] = tmp;
}
void inPlaceHeapSort() {
// n ���� Ű�� ������ �����迭(H)�� ���ڸ� �� ����
    int i;
    
    for (i=n;i>=2;i--) {
        swap(1, i);
        downHeap(1, i-1);
    }
    return;
}
void printArray() {
// H ���
    int i;
    for (i=1;i<=n;i++) {
        printf(" %d", H[i]);
    }
}
void downHeap(int i, int last) {
// �� �� ��ġ i�� ����� Ű�� ũ�⿡ �´� ��ġ�� ���� �̵�
    int larger_idx;
    int left = 2*i;
    int right = 2*i+1;
    // ���� ����
    if (left>last) return; // i �� l, r ��� ������ return
    larger_idx = left;
    if (2*i+1<=last) { // i�� r�� �����ϸ�
        if (H[right]>H[larger_idx]) { // i�� l�� r ��
            larger_idx = right;
        }
    }
    if (H[i] >= H[larger_idx]) return; // �̹� �ִ��� �����̸� return
    swap(i, larger_idx);
    downHeap(larger_idx, last);
}
void insertItem(int key) {
// n ��ġ�� key ����, upHeap(n) ȣ�� ���� �� n(�� Ű ����)�� ����
    n++;
    H[n] = key;
    upHeap(n);
}
void upHeap(int i) {
// �� �� ��ġ i�� ����� Ű�� ũ�⿡ �´� ��ġ�� ���� �̵�
    if (i==1) return;
    if (H[i/2] > H[i]) return;
    swap(i/2, i);
    upHeap(i/2);
}
void rBuildHeap(int i) { 
// ��� ������� ����� �� ����, i : �κ� ���� ��Ʈ �ε���

}
void buildHeap() {
// ����� ������� ����� �� ����
    int i;
    for (i=n/2;i>=1;i--) {
        downHeap(i, n);
    }
    return;
}

int main() {
// �ʱ� ����Ʈ�� ���� �� ������ 1�ܰ�, 2�ܰ� �۾��� �����Ͽ� ���� ����Ʈ�� �μ��ϰ� ����
    
    int i;

    scanf("%d", &n);
    for (i=1;i<=n;i++) scanf("%d", &H[i]);
    buildHeap(); // 1��
    inPlaceHeapSort(); // 2��
    printArray();
}