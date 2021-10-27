#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>

void swap(int *arr, int idx1, int idx2) { //arr 배열의 idx1과 idx2자리에 있는 원소들을 swap
    int tmp;
    tmp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = tmp;
}
void inPlaceSelectionSort(int *arr, int n) { // 제자리 선택 정렬
    int pass, j, minLoc ,tmp;

    for (pass=0;pass<n-1;pass++) {
        minLoc = pass;
        for (j=pass+1;j<n;j++) {
            if(arr[j] < arr[minLoc]) {
                minLoc = j;
            }
        }
        swap(arr, pass, minLoc);
    }
}
void inPlaceInsertionSort(int *arr, int n) { // 제자리 삽입 정렬
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
    int n, i, j;
    clock_t start_iSS, end_iSS, start_iIS, end_iIS;
    int *arr_by_iSS; // 선택 정렬할 배열
    int *arr_by_iIS; // 삽입 정렬할 ㅏ배열
    int *arr; // 정방향 배열
    int *arr_reverse; // 역방향 배열
    double elapsed_iSS, elapsed_iIS;
    // scanf("%d", &n);
    n=100000;
    arr_by_iSS = (int *)malloc(sizeof(int)*n); // 제자리 선택정렬할 배열
    arr_by_iIS = (int *)malloc(sizeof(int)*n); // 제자리 삽입정렬할 배열
    arr = (int *)malloc(sizeof(int)*n);
    arr_reverse = (int *)malloc(sizeof(int)*n);
    // for (j=0;j<10000000;j++) {
    //     arr_by_iIS[j] = arr_by_iSS[j] = j+1;
    // }
    
    srand(time(NULL));

    for (j=0;j<n;j++) {
        arr_by_iSS[j] = arr_by_iIS[j] = rand();
        arr[j] = j+1;
        arr_reverse[j] = n-j;
    } // arr_by_iTS배열과 arr_by_iIS배열 모두 난수가 n개의 똑같은 난수가 들어간 배열

    // // 똑같은 n에 대한 실험
    // start_iSS = clock(); // A
    // inPlaceInsertionSort(arr_by_iSS, n);
    // end_iSS = clock();
    // elapsed_iSS = (double)(end_iSS - start_iSS)/CLOCKS_PER_SEC;
    // printf("A : %.3fms\n", 1000*elapsed_iSS);

    // start_iSS = clock(); // B
    // inPlaceInsertionSort(arr, n);
    // end_iSS = clock();
    // elapsed_iSS = (double)(end_iSS - start_iSS)/CLOCKS_PER_SEC;
    // printf("B : %.3fms\n", 1000*elapsed_iSS);

    // start_iSS = clock(); // C
    // inPlaceInsertionSort(arr_reverse, n);
    // end_iSS = clock(); 
    // elapsed_iSS = (double)(end_iSS - start_iSS)/CLOCKS_PER_SEC;
    // printf("C : %.3fms\n", 1000*elapsed_iSS);


    for (i=1;i<=10;i++) {
        n= 10000*i;
        for (j=0;j<n;j++) {
            arr_by_iSS[j] = arr_by_iIS[j] = rand();
            arr[j] = j+1;
            arr_reverse[j] = n-j;
        } // arr_by_iTS배열과 arr_by_iIS배열 모두 난수가 n개의 똑같은 난수가 들어간 배열
        

        start_iSS = clock(); // 프로세스는 clock 단위로 일을 한다고 생각하자.
        inPlaceSelectionSort(arr_by_iSS, n);
        end_iSS = clock();
        elapsed_iSS = (double)(end_iSS - start_iSS)/CLOCKS_PER_SEC; // CLOCKS_PER_SEC == 1000000이다. 즉, 1초에 1000000CLOCKS

        for (j=0;j<n;j++) {
            arr[j] = j+1;
            arr_reverse[j] = n-j;
        }
        start_iIS = clock();
        inPlaceInsertionSort(arr_by_iIS, n);
        end_iIS = clock();
        elapsed_iIS = (double)(end_iIS - start_iIS)/CLOCKS_PER_SEC;
        printf("\nn : %d00000\n", i);
        printf("선택 정렬 : %.3fms\n", 1000*elapsed_iSS);
        printf("삽입 정렬 : %.3fms\n", 1000*elapsed_iIS);
    
    }

    free(arr_by_iIS);
    free(arr_by_iSS);
    free(arr);
    free(arr_reverse);
    return 0;
}




