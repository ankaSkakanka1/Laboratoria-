#include <iostream>
#include <stdio.h>
using namespace std;

const int n = 10;
int A[n] = {89, 10, 74, 52, 10, 77, 41, 56, 85, 78};

void InsertionSort(int A[], int n){
    int key=0, i=0;
    for(int j=1; j<=n-1; j++){
        key=A[j];
        i = j - 1;
        while(i>=0 && A[i]>key){
            A[i+1]=A[i];
            i = i - 1;
        }
        A[i+1]=key;
    }
    return;
}

int main () {
    InsertionSort(A,n);
    cout << n << "\n";
    for(int i=0; i<=n-1; i++){
        cout << A[i] << " ";
    }
    cout << "\n";

    return 0;
}