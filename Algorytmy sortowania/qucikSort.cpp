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

int Partition(int A[], int p, int r){
    int x = A[r];
    int i = p - 1;
    for(int j = p; j<r; j++){
        if(A[j]<=x){
            i++;
            Swap(A,i,j);
        }
    }
    i++;
    Swap(A,i,r);
    return i;
}

void QuickSort(int A[], int p, int r){
    if(p<r){
        int q=Partition(A,p,r);
        QuickSort(A,p,q-1);
        QuickSort(A,q+1,r);
    }
}

int main(){
    int p = 0;
    QuickSort(A,p,n-1);
    cout << n << "\n";
    for(int i=0; i<n; i++){
        cout << A[i] << " ";
    }
    cout << "\n";
    
    return 0;

}