#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;

int main(){
    string s,t;
    cin >> s;
    cin >> t;
    int n = s.length();
    int k = t.length();
    if (n!=k && n>1000 && k>1000){
        return 0;
    }
    int hamming = 0;
    for(int i=0; i<n; i++){
        if (s[i]!=t[i]){
            hamming ++;
        }
    }
    cout << hamming;
}