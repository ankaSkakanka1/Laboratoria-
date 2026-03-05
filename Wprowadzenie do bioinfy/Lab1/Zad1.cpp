#include <iostream>
#include <stdio.h>
using namespace std;

int main (){
    string s;
    int A, C, G, T;
    int n = s.length();

    cin >> s;
    if(n > 1000){
        cout << "Blad";
    }

    A = 0;
    G = 0;
    C = 0;
    T = 0;

    for(char c : s){
        if(c == 'A'){
            A++;
        } else if (c == 'C'){
            C++;
        } else if (c == 'G'){
            G++;
        } else if (c == 'T'){
            T++;
        }
    }

    cout << A << " " << C << " " << G << " " << T << endl;

    return 0;

}


