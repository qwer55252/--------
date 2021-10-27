// 질문1. n값을 왜 받는지 모르겠습니다.
// 질문2. 문자열의 입력을 배열로 입력받는게 맞나요?
// 질문3. findNumber의 인자를 저렇게 해도 되나요?


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findNumber(char *ch, int i, int l, int r) { 
// 자연수 l과 r 사이의 수 찾기
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