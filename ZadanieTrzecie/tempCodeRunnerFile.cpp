#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <filesystem>
#include <map>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>
using namespace std;

struct Sekwencja{
    string identyfikator;
    string sekwencja;
    vector<int> wiarygodnosc;
    string sekwencjaModyfikowana;
    vector<int> pozycje;
};

map<string,Sekwencja> wczytywanie(const string& nazwaFasta, const string& nazwaQual){
    map<string,Sekwencja> sekwencje;
    string linia;
    string id; 
    //Wczytywanie Fasty
    ifstream plikFasta(nazwaFasta);
    if(!plikFasta.is_open()){
        cout << "Nie mozna otworzyc pliku" << nazwaFasta << endl;
        return sekwencje;
    }
    while(getline(plikFasta,linia)){
        if(linia[0]=='>'){
            stringstream ss(linia.substr(1));
            ss >> id;
            sekwencje[id] = {id,"",{}};
        } else if (!id.empty() && sekwencje.count(id)){
            string n_linia;
            stringstream ss_linia(linia);
            ss_linia >> n_linia;
            sekwencje[id].sekwencja += n_linia;
        }
        }
        plikFasta.close();
        //Wczytywanie Qual
        ifstream plikQual (nazwaQual);
        if(!plikQual.is_open()){
            cout << "Nie mozna otworzyc pliku" << nazwaQual << endl;
            return sekwencje;
        }
        id.clear();
        while(getline(plikQual,linia)){
            if(linia[0]=='>'){
                stringstream ss(linia.substr(1));
                string n_id;
                ss >> n_id;
                if(sekwencje.count(n_id)){
                    id = n_id;
                } else {
                    id.clear();
                }
            } else if(!id.empty()){
                stringstream ss(linia);
                int wiarygodnosc;
                while(ss >> wiarygodnosc){
                    sekwencje[id].wiarygodnosc.push_back(wiarygodnosc);
                }

            }
        }
        plikQual.close();

        /*for (auto it = sekwencje.begin(); it != sekwencje.end(); ) {
          if (it->second.sekwencja.length() != it->second.wiarygodnosc.size()) {
            cout << "Ostrzezenie: Usuwam sekwencję " << it->first 
                 << " z powodu niespójnej długości." << endl;
            it = sekwencje.erase(it);
          } else {
            ++it;
          }
        }*/
        return sekwencje;

}

void modyfikuj_sekwencje(map<string,Sekwencja>& sekwencje, int prog){
    for(auto& [id, sek]:sekwencje){
        Sekwencja& s = sek;
        s.sekwencjaModyfikowana.clear();
        s.pozycje.clear();
        for(size_t i=0; i<s.sekwencja.length();i++){
            if(s.wiarygodnosc[i]>=prog){
                s.sekwencjaModyfikowana += s.sekwencja[i];
                s.pozycje.push_back(i+1);
            }
        }
    }
}

int main(){
    string plikFasta;
    string plikQual;
    int progWiarygodnosci;
    cout << "Podaj nazwe pliku Fasta: ";
    cin >> plikFasta;
    cout << "Podaj nazwe pliku Qual: ";
    cin >> plikQual;
    cout << "Podaj prog wiarygodnosci: ";
    while(!(cin>>progWiarygodnosci)){
        cout << "Niepoprawna wartosc, podaj liczbe calkowita:";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    map<string,Sekwencja> instancja = wczytywanie(plikFasta,plikQual);
    if(instancja.empty()){
        cout << "Nie wczytano zadnych sekwencji." << endl;
        return 1;
    }

    cout << "Wczytano sekwencje, liczba sekwencji: " << instancja.size() << endl;

    modyfikuj_sekwencje(instancja,progWiarygodnosci);

    cout << "Po modyfikacji(usunieciu nukelotydow o niskiej wiarygodnosci):" << endl;
    for(const auto& [id,sek]:instancja){
        const Sekwencja& s = sek;
        cout << "Identyfikator: " << s.identyfikator << endl;
        cout << "Dlugosc oryginalnej sekwencji: " << s.sekwencja.length() << endl;
        cout << "Dlugosc zmodyfikowanej sekwencji: " << s.sekwencjaModyfikowana.length() << endl;
        if(s.sekwencjaModyfikowana.length()>0){
            cout << "Pierwsze 10 nuklotydow zmodyfikowanej sekwencji: " << endl;
            for(size_t i=0; i<min((size_t)10,s.sekwencjaModyfikowana.length());i++){
                cout << s.sekwencjaModyfikowana[i];
            }
            cout << endl;
        }
    }

}