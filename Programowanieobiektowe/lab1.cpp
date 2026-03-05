#include <iostream>
#include <stdio.h>
using namespace std;

/*class Zwierz {//klasa rodzic - tu sa rzeczy wspolne dla podrzednych klas
    public : 
    string gatunek;
    string imie;

    Zwierz(){//konstruktor - funkacja odpala sie przy tworzeniu instancji klasy 
        cout << "podaj imie\n";
        cin >> imie;
        cout << "utworzono zwierza :) " << imie << "\n";
    }
    ~Zwierz(){//destruktor - pozbywa sie konstruktora 
        cout << "ubito zwierza :( \n";

    };


};//sredniczek

//dziedziczenie klas
class Ssak : public Zwierz{//dziecko
    public :
    int nogi;

    Ssak(){
        cout << "utworzono ssaka\n";
    }
    ~Ssak(){
        cout << "ubito ssaka\n";
    };


};

//najpierw wywolywany jest konstruktor rodzica przy tworzeniu, a przy wylaczaniu na odwrot*/

class Trojkat {
    public :
    int wysokosc;
    int podstawa;

    Trojkat(){
        cout << "Podaj wysokosc:\n";
        cin >> wysokosc;
        cout << "Podaj podstawe:\n";
        cin >> podstawa;

        /*int oblicz = 0;
        oblicz = pole(wysokosc, podstawa);

        
        cout << "Pole trojkata wynosi: " << oblicz << "\n";*/

    }

    //~Trojkat(){
       // cout << "usunieto dane\n";
    //};

    int pole(){
        int pole = 0;
        pole = (wysokosc*podstawa)/2;
        return pole;
    }

};

int main (){
    
    for(int i=0;i<200;i++){
    Trojkat trojkat;
    cout << "Licza operacji : " << i+1 << "\n";
    cout << "Pole: " << trojkat.pole() << "\n";
    }
    
    

    return 0;
}