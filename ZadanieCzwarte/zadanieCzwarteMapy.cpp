#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>

using namespace std;


map<int,int> Multiset;
vector<int> Pozycje;
int dlugoscDna;
int k;
bool znaleziono = false;


bool dostepne(int d) {
    return Multiset.count(d) && Multiset[d] > 0;
}


void uzyj(int d) { Multiset[d]--; }
void cofnij(int d) { Multiset[d]++; }


bool moznaUmiescic(int p, int ind){
    if(!dostepne(p)||!dostepne(dlugoscDna - p))
        return false;
    for(int i=0;i<ind;i++){
        if(!dostepne(abs(p - Pozycje[i])))
            return false;
    }
    return true;
}


void zastosujOdleglosc(int p, int ind){
    uzyj(p);
    uzyj(dlugoscDna - p);
    for(int i=0;i<ind;i++){
        uzyj(abs(p - Pozycje[i]));
    }
}


void cofnijOdleglosc(int p, int ind){
    cofnij(p);
    cofnij(dlugoscDna - p);
    for(int i=0;i<ind;i++){
        cofnij(abs(p-Pozycje[i]));
    }
}

bool wszystkieZuzyte() {
    for (auto &el : Multiset) {
        if (el.second != 0) return false;
    }
    return true;
}


void szukaj(int ind){

    if(znaleziono) return;
    if(ind == k){
        if(wszystkieZuzyte()){
            znaleziono = true;
        }
        return;
    }

    for(auto &el : Multiset){
        int p = el.first;
        if(p<=0 || p>=dlugoscDna) continue;

        if(moznaUmiescic(p, ind)){
            Pozycje[ind] = p;
            zastosujOdleglosc(p, ind);
            szukaj(ind + 1);
            if(znaleziono) return;
            cofnijOdleglosc(p, ind);
        }
    }
}


bool obliczK(int rozmiarMulti){

    for(int i=1;i<=100;i++){
        if((i+2)*(i+1)/2 == rozmiarMulti){
            k = i ;
            return true;
        }
    }
    return false;
}


int main() {

    ifstream plik("instancja2_k5.txt");
    if(!plik){
        cout << "Nie mozna otworzyc pliku\n";
        return 0;
    }

    int x;
    vector<int> dane;

    while(plik >> x){
        dane.push_back(x);
    }

    plik.close();


    if(dane.empty()){
        cout << "Plik jest pusty\n";
        return 0;
    }

    for(int v : dane){
        Multiset[v]++;
    }

    if(!obliczK(dane.size())){
        cout << "Bledna liczba elementow Multizbioru A\n";
        return 0;
    }

    dlugoscDna = *max_element(dane.begin(), dane.end());
    uzyj(dlugoscDna);

    int drugiMax = -1;

    for(int v : dane){
        if(v != dlugoscDna){
            drugiMax = max(drugiMax, v);
        }
    }


    int pierwszy = dlugoscDna - drugiMax;

    if(!dostepne(pierwszy)){
        cout << "Brak rozwiazania\n";
        return 0;
    }


    Pozycje.resize(k);
    Pozycje[0] = pierwszy;

    uzyj(pierwszy);
    uzyj(dlugoscDna - pierwszy);


    auto start = chrono::high_resolution_clock::now();
    szukaj(1);
    auto end = chrono::high_resolution_clock::now();


    if(!znaleziono){
        cout << "Brak rozwiazania\n";
        return 0;
    }


    sort(Pozycje.begin(), Pozycje.end());

    cout << "Mapa odcinkow: \n";
    cout << Pozycje[0] << " ";

    for(int i=1;i<k;i++){
        cout << Pozycje[i] - Pozycje[i-1] << " ";
    }

    cout << dlugoscDna - Pozycje[k-1] << "\n";

    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Czas obliczen: " << duration.count() << " ms\n";

    return 0;
} 