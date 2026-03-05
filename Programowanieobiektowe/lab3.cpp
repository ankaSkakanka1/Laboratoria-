#include <iostream>
#include <stdio.h>
using namespace std;

class Zwierze{
    public:
    static int ile_zwierzat;
    Zwierze(){
        ile_zwierzat++;
    };
    virtual void daj_glos(){ //ona tu jest ale nie musi nic robic, ma tylko zajac miejsce
        cout << "Zwierze wydaje glos" << endl;
    }
    static void getLiczbaZwierzat(){
        cout << "Liczba zwierzat: " << ile_zwierzat << endl;
    }

};

class Pies : public Zwierze{
    public :
    void daj_glos() override{
        cout << "Hau hau" << endl;
    }
};

class Kot : public Zwierze{
    public:
    void daj_glos() override{
        cout << "Miau miau" << endl;
    }
};

int Zwierze::ile_zwierzat=0;

int main () {
    Zwierze*zwierzeta[2];
    zwierzeta[0] = new Pies();          // ale wstawiamy psa i kota
    zwierzeta[1] = new Kot();

    for (int i = 0; i < 2; ++i) {
        zwierzeta[i]->daj_glos(); // Polimorficzne wywołanie
        delete zwierzeta[i];
    }
    Zwierze::getLiczbaZwierzat();

    return 0;
}

