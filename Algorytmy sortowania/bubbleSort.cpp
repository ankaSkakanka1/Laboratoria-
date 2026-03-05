#include <iostream>
#include <stdio.h>
using namespace std;

const int n = 10;
int A[n] = {89, 10, 74, 52, 10, 77, 41, 56, 85, 78};

void Swap (int A[], int i, int j){
    int tmp = 0;
    tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

void BubbleSort(int A[], int n){
    for(int i = 0; i<n-1; i++){
        for(int j = n-1; j>i; i--){
            if(A[j]<A[j-1])
            Swap(A,j,j-1);
        }
    }
    return;
}

int main(){
    BubbleSort(A,n);
    cout << n << "\n";
    for(int i=0; i<n; i++){
        cout << A[i] << " ";
    }
    cout << "\n";
    
    return 0;

}