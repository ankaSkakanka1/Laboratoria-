#include <iostream>
#include <stdio.h>
using namespace std;

const int n = 10;
int A[n] = {89, 10, 74, 52, 10, 77, 41, 56, 85, 78};

int ArgMin(int A[], int begin, int end){
    int argmin = begin;
    for(int i=begin+1; i<=end; i++){
        if(A[i]<A[argmin])
        argmin = i;
    }
    return argmin;
}

void Swap (int A[], int i, int j){
    int tmp = 0;
    tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

void SelectionSort(int A[], int n){
    int j = 0;
    for(int i = 0; i<=n-1; i++){
        j = ArgMin(A,i,n-1);
        Swap(A,i,j);
    }
    return;
}

int main (){
    SelectionSort(A,n);
    cout << n << "\n";
    for(int i=0; i<n; i++){
        cout << A[i] << " ";
    }
    cout << "\n";
    
    return 0;
}