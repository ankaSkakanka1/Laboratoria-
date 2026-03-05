#include <iostream>
#include <string>
using namespace std;

class Pytanie{
    public :
    string tresc;
    string A,B,C,D;
    int nr_pytania;
    string poprawnaOdp;
    string odpowiedz;
    int punkt; //1 lub 0

    void wczytaj(); //wczytuje dane z pliku
    void zadaj();
    void sprawdz();
};