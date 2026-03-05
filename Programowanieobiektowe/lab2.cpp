#include <iostream>
#include <stdio.h>
using namespace std;

class Figura {
    public:
    string kolor;

    Figura(){
        cout << "Podaj kolor: ";
        cin >> kolor;
        cout << endl;
    }

    void opis (){
        cout << "Kolor figury: " << kolor;
        cout << endl;
    }

};

class Kolo : public Figura {
    public:
    double promien;

    Kolo(){
        cout << "Podaj promien: ";
        cin >> promien;
    }

    double pole(){
        int pole = 0;
        pole = 3.14 * (promien*promien);
        return pole;
    }

    double obwod(){
        int obwod = 0;
        obwod = 2.0 * 3.14 * promien;
        return obwod;
    }
    void opis(){
        cout << "Pole kola: " << pole() << endl;
        cout << "Obwod kola: " << obwod() << endl;
        cout << "Kolor kola: " << kolor << endl;

    }

};

class Kwadrat : public Figura {
    public:
    double bok;

    Kwadrat(){
        cout << "Podaj bok: ";
        cin>> bok;
        cout << endl;
    }

    double pole(){
        int pole = 0;
        pole = bok*bok;
        return pole;
    }

    double obwod(){
        int obwod = 0;
        obwod = 4.0 * bok;
        return obwod;
    }
    void opis(){
        cout << "Pole kwadratu: " << pole() << endl;
        cout << "Obwod kwadratu: " << obwod() << endl;
        cout << "Kolor kwadratu: " << kolor << endl;

    }

};

int main () {
    int wybor;
    cout << "Wybierz figure: " << endl;
    cout << "1->kolo\n";
    cout << "2->kwadrat\n";
    cin >> wybor;

    if(wybor==1){
        Kolo kolo;
        kolo.opis();
    } else if (wybor==2){
        Kwadrat kwadrat;
        kwadrat.opis();
    } else {
        cout << "Niepoprawny wybor\n";
    }

    return 0;

}