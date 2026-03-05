#include <iostream>
#include <stdio.h>
using namespace std;

template <typename T>
class Maksimum {
    T* tablica;
    int rozmiar;
    public :
    Maksimum(T*t,int n){
        tablica = t;
        rozmiar = n;
    };
    T znajdzMaks(){
        int max = tablica[0];
        for(int i = 1; i<rozmiar; i++){
            if(tablica[i]>max){
                max = tablica[i];
            }
        }
        return max;

    }

};

int main (){

    int tabInt[] = {2,3,4,5,6};
    float tabFloat[] = {2.4, 3.4 , 1.2, 2.2, 2.5};
    char tabChar[] = {'a', 'b', 'c', 'd', 'e'};

    Maksimum<int>max1(tabInt,5);
    Maksimum<float>max2(tabFloat,5);
    Maksimum<char>max3(tabChar, 5);

    cout << "Max: " << endl;
    cout << "Int: " << max1.znajdzMaks() << " Float: " << max2.znajdzMaks() << " Char: " << max3.znajdzMaks();

    return 0;


}