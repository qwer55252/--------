// ����1. n���� �� �޴��� �𸣰ڽ��ϴ�.
// ����2. ���ڿ��� �Է��� �迭�� �Է¹޴°� �³���?
// ����3. findNumber�� ���ڸ� ������ �ص� �ǳ���?


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findNumber(char *ch, int i, int l, int r) { 
// �ڿ��� l�� r ������ �� ã��
    char Y_or_N;
    int m;
    Y_or_N = ch[i];
    if (l==r) return l;
    m = (l+r)/2;
    if (Y_or_N == 'Y') {
        //printf("if Y : ");
        //printf("findNumber(%d, %d)\n", m+1, r);
        return findNumber(ch, i+1, m+1, r);
    }
    else {
        //printf("if N : ");
        //printf("findNumber(%d, %d)\n", l, m);
        return findNumber(ch, i+1, l, m);
    }
}
int main() {
    int a, b, n;
    char *ch;
    scanf("%d %d %d", &a, &b, &n);
    getchar();
    ch = (char *)malloc(sizeof(ch)*n);
    scanf("%s", ch);
    

    printf("%d", findNumber(ch, 0, a, b));
}