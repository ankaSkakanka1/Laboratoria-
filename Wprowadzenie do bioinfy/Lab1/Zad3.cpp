#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;

int main () {
    string s;
    cin >> s;
    int n = s.length();
    if(n>1000){
        return 0;
    }
    reverse(s.begin(), s.end());
    for(int i=0; i<n; i++){
        if(s[i]=='A'){
            s[i] = 'T';
        }else if(s[i]=='T'){
            s[i] = 'A';
        }else if(s[i]=='G'){
            s[i] = 'C';
        }else if(s[i]=='C'){
            s[i]='G';
        }
    }

    cout << "\n\n" << s << endl;

    return 0;

}