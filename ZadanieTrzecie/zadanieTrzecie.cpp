#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cmath>

using namespace std;


struct Sekwencja {
    string identyfikator;
    string sekwencja;
    vector<int> wiarygodnosc;
    string sekwencjaModyfikowana;
    vector<int> pozycje;
};

struct Wierzcholek {
    int id; 
    string podciag;
    int pozycjaOryginalna;
    string nazwaSekwencji;
    int globalneId; 
};

struct Krawedz {
    int start; 
    int koniec; 
};

struct Klika {
    vector<int> indeksyWierzcholkow;
    int rozmiar() { return indeksyWierzcholkow.size(); }
};


map<string, Sekwencja> wczytywanie(const string& nazwaFasta, const string& nazwaQual) {
    map<string, Sekwencja> sekwencje;
    string linia, id;
    ifstream plikFasta(nazwaFasta);
    if (!plikFasta.is_open()) return sekwencje;
    while (getline(plikFasta, linia)) {
        if (linia.empty()) continue;
        if (linia[0] == '>') {
            stringstream ss(linia.substr(1));
            ss >> id;
            sekwencje[id] = {id, "", {}, "", {}};
        } else if (!id.empty()) {
            for (char c : linia) if (!isspace(c)) sekwencje[id].sekwencja += c;
        }
    }
    plikFasta.close();
    ifstream plikQual(nazwaQual);
    if (!plikQual.is_open()) return sekwencje;
    id.clear();
    while (getline(plikQual, linia)) {
        if (linia.empty()) continue;
        if (linia[0] == '>') {
            stringstream ss(linia.substr(1));
            string n_id; ss >> n_id;
            id = (sekwencje.count(n_id)) ? n_id : "";
        } else if (!id.empty()) {
            stringstream ss(linia);
            int w; while (ss >> w) sekwencje[id].wiarygodnosc.push_back(w);
        }
    }
    return sekwencje;
}

void modyfikuj_sekwencje(map<string, Sekwencja>& sekwencje, int prog) {
    for (auto& [id, sek] : sekwencje) {
        sek.sekwencjaModyfikowana.clear();
        sek.pozycje.clear();
        for (size_t i = 0; i < sek.sekwencja.length(); i++) {
            if (sek.wiarygodnosc[i] >= prog) {
                sek.sekwencjaModyfikowana += sek.sekwencja[i];
                sek.pozycje.push_back(i + 1);
            }
        }
    }
}

vector<Wierzcholek> utworz_wierzcholki(const map<string, Sekwencja>& instancja, int k) {
    vector<Wierzcholek> wierzcholki;
    int numerSekwencji = 0;
    int gId = 0;
    for (const auto& [id, s] : instancja) {
        if (s.sekwencjaModyfikowana.length() >= k) {
            for (size_t i = 0; i <= s.sekwencjaModyfikowana.length() - k; ++i) {
                wierzcholki.push_back({numerSekwencji, s.sekwencjaModyfikowana.substr(i, k), s.pozycje[i], id, gId++});
            }
        }
        numerSekwencji++;
    }
    return wierzcholki;
}


vector<Krawedz> utworz_krawedzie(const vector<Wierzcholek>& wierzcholki, int k) {
    vector<Krawedz> krawedzie;
    map<string, vector<int>> grupyPodciagow;
    for (int i = 0; i < wierzcholki.size(); ++i) {
        grupyPodciagow[wierzcholki[i].podciag].push_back(i);
    }
    int limit = 10 * k;
    for (auto const& [podciag, indeksy] : grupyPodciagow) {
        for (size_t i = 0; i < indeksy.size(); ++i) {
            for (size_t j = i + 1; j < indeksy.size(); ++j) {
                const Wierzcholek& v1 = wierzcholki[indeksy[i]];
                const Wierzcholek& v2 = wierzcholki[indeksy[j]];
                if (v1.id != v2.id && abs(v1.pozycjaOryginalna - v2.pozycjaOryginalna) <= limit) {
                    krawedzie.push_back({v1.globalneId, v2.globalneId});
                }
            }
        }
    }
    return krawedzie;
}


bool czy_poloczony_ze_wszystkimi(int vGId, const Klika& klika, const vector<Krawedz>& krawedzie, const vector<Wierzcholek>& wierzcholki) {
    for (int idx_w_klikie : klika.indeksyWierzcholkow) {
        int klikaGId = wierzcholki[idx_w_klikie].globalneId;
        bool polaczony = false;
        for (const auto& e : krawedzie) {
            if ((e.start == vGId && e.koniec == klikaGId) || (e.start == klikaGId && e.koniec == vGId)) {
                polaczony = true;
                break;
            }
        }
        if (!polaczony) return false;
    }
    return true;
}


Klika znajdz_klike(const vector<Wierzcholek>& wierzcholki, const vector<Krawedz>& krawedzie, int liczbaSekwencji) {
    map<string, vector<int>> grupy;
    for (int i = 0; i < wierzcholki.size(); ++i) grupy[wierzcholki[i].podciag].push_back(i);

    Klika najlepszaKlika;
    for (const auto& [podciag, indeksy] : grupy) {
        for (int start : indeksy) {
            Klika aktualnaKlika;
            aktualnaKlika.indeksyWierzcholkow.push_back(start);
            vector<bool> czySekwencjaWKlice(liczbaSekwencji, false);
            czySekwencjaWKlice[wierzcholki[start].id] = true;

            for (int inny : indeksy) {
                if (!czySekwencjaWKlice[wierzcholki[inny].id]) {
                    if (czy_poloczony_ze_wszystkimi(wierzcholki[inny].globalneId, aktualnaKlika, krawedzie, wierzcholki)) {
                        aktualnaKlika.indeksyWierzcholkow.push_back(inny);
                        czySekwencjaWKlice[wierzcholki[inny].id] = true;
                    }
                }
                if (aktualnaKlika.rozmiar() == liczbaSekwencji) break;
            }
            if (aktualnaKlika.rozmiar() > najlepszaKlika.rozmiar()) najlepszaKlika = aktualnaKlika;
            if (najlepszaKlika.rozmiar() == liczbaSekwencji) break;
        }
        if (najlepszaKlika.rozmiar() == liczbaSekwencji) break;
    }
    return najlepszaKlika;
}

int main() {
    string plikFasta, plikQual;
    int progWiarygodnosci, k;

    cout << "Podaj nazwe pliku Fasta: "; cin >> plikFasta;
    cout << "Podaj nazwe pliku Qual: "; cin >> plikQual;
    cout << "Podaj prog wiarygodnosci: ";
    while (!(cin >> progWiarygodnosci)) {
        cout << "Niepoprawna wartosc, podaj liczbe calkowita:";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    map<string, Sekwencja> instancja = wczytywanie(plikFasta, plikQual);
    if (instancja.empty()) { cout << "Nie wczytano zadnych sekwencji." << endl; return 1; }

    cout << "Wczytano sekwencje, liczba sekwencji: " << instancja.size() << endl;
    modyfikuj_sekwencje(instancja, progWiarygodnosci);

    cout << "Podaj dlugosc k-meru(od 4 do 9 ): ";
    while (!(cin >> k) || k < 4 || k > 9) {
        cout << "Niepoprawna wartosc, podaj liczbe calkowita od 4 do 9:";
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    vector<Wierzcholek> wierzcholki = utworz_wierzcholki(instancja, k);
    cout << "\nWygenerowano " << wierzcholki.size() << " wierzcholkow (wystapien podciagow) dla k = " << k << "." << endl;

    vector<Krawedz> krawedzie = utworz_krawedzie(wierzcholki, k);
    cout << "Wygenerowano " << krawedzie.size() << " krawedzi miedzy wierzcholkami." << endl;

    Klika wynik = znajdz_klike(wierzcholki, krawedzie, instancja.size());

    cout << "\nREZULTAT: Znaleziono motyw w grafie: " << endl;
    if (wynik.rozmiar() > 0) {
        for (int idx : wynik.indeksyWierzcholkow) {
            const Wierzcholek& v = wierzcholki[idx];
            cout << "Sekwencja |ID: " << v.nazwaSekwencji << endl;
            cout << "Pozycja sekwencji: " << v.pozycjaOryginalna << endl;
            cout << "Podciag: " << v.podciag << endl;
        }
    } else {
        cout << "Nie znaleziono motywu wspolnego dla zadanych sekwencji." << endl;
    }
    return 0;
}