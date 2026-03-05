#include <iostream>
#include <stdio.h>
using namespace std;

class Wektor{
    protected:
    int x;
    int y;

    public:

    Wektor(int a=0, int b=0){
        x=a;
        y=b;
    }
    Wektor& operator++ (){
        x++;
        y++;
        return *this;
    }
    void pokaz(){
        cout <<"x: "<< x << " y: "<< y << endl;
    }
    friend Wektor operator+(const Wektor& a, const Wektor& b);
    
};

Wektor operator +(const Wektor& a, const Wektor& b){
    return Wektor(a.x + b.x, a.y + b.y);
}

int main(){
    Wektor A(1,2), B(3,4);
    Wektor C = A+B;
    C.pokaz();
    ++A;
    A.pokaz();

    return 0;

}