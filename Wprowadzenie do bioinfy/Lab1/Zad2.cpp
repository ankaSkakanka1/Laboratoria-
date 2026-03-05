#include <iostream>
#include <stdio.h>
using namespace std;

int main (){
    string t;
    cin >> t;
    int n = t.length();
    if (n>1000){
        cout << "Blad";
        return 0;
    }

    for(int i=0; i<n; i++){
        if(t[i]=='T'){
            t[i] = 'U';
        }
    }
    
    cout << "\n\n" << t << endl;

    return 0;

}


