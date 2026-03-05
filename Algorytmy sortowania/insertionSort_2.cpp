#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void InsertionSort(vector<int>& A) {
    int n = A.size();
    for (int j = 1; j < n; j++) {
        int key = A[j];
        int i = j - 1;
        while (i >= 0 && A[i] > key) {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
}

int main() {
    int n;
    cout << "Podaj rozmiar tablicy:";
    cin >> n;
    cout << endl;
    if (n < 10 || n > 100000) {
        return 0;
    }

    cout << "Podaj elementy tablicy:";
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    InsertionSort(A);

    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n";

    return 0;
}