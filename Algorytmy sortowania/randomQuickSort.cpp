#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void Swap(vector<int>& A, int i, int j)
{
    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

int Partition(vector<int>& A, int p, int r)
{
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (A[j] <= x)
        {
            i++;
            Swap(A, i, j);
        }
    }
    i++;
    Swap(A, i, r);
    
    
    cout << i << endl;
    for (int num : A) {
        cout << num << " ";
    }
    cout << "\n";
    
    return i;
}

int Random(int p, int r)
{
    return p + rand() % (r - p + 1);
}

int RandomizedPartition(vector<int>& A, int p, int r)
{
    int i = Random(p, r);
    Swap(A, i, r);
    return Partition(A, p, r);
}

void RandomizedQuickSort(vector<int>& A, int p, int r)
{
    if (p < r)
    {
        int q = RandomizedPartition(A, p, r);
        RandomizedQuickSort(A, p, q - 1);
        RandomizedQuickSort(A, q + 1, r);
    }
}

int main()
{
    int n;
    cin >> n;
    srand(time(NULL));
    if (n < 5 || n > 100000) {
        return 0;
    }
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int p = 0;
    RandomizedQuickSort(A, p, n - 1);
    
    return 0;
}
