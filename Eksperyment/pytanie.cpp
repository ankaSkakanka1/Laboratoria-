#include <iostream>
#include "pytanie.h"
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

void Pytanie :: wczytaj(){
    fstream plik;
    plik.open("pytania.txt",ios::in);
    if(plik.good()==false){
        cout << "Nie udalo sie otworzyc pliku";
        exit(0);//konczy program
    }
    int nr_linii = (nr_pytania-1)*6+1;
    int aktualny_numer=1;
    string linia;

    while(getline(plik,linia)){
        if(aktualny_numer==nr_linii) tresc=linia;
        if(aktualny_numer==nr_linii+1) A=linia;
        if(aktualny_numer==nr_linii+2) B=linia;
        if(aktualny_numer==nr_linii+3) C=linia;
        if(aktualny_numer==nr_linii+4) D=linia;
        if(aktualny_numer==nr_linii+5) poprawnaOdp=linia;
        aktualny_numer++;
    }

}

void Pytanie :: zadaj(){
    cout << tresc << endl;
    cout << A << endl;
    cout << B << endl;
    cout << C << endl;
    cout << D << endl;
    cout << "Podaj odpowiedz:";
    cin >> odpowiedz;
}

void Pytanie :: sprawdz(){
    if(odpowiedz==poprawnaOdp) punkt=1;
    else punkt=0;
}
